#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "rand.h"

// Code prior to lab 6 was provided by Brian C.
// All changes post lab 5 work are our own.

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

static struct proc *initproc;

static const char *run_states[] = {
    [UNUSED]    "unused",
    [EMBRYO]    "embryo",
    [SLEEPING]  "sleep ",
    [RUNNABLE]  "runble",
    [RUNNING]   "run   ",
    [ZOMBIE]    "zombie"
};

int _forkcount = 0;
int nextpid = 1;

static ushort debugMesg = FALSE;

extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);
static char *proc_state(int);

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

// Must be called with interrupts disabled
int
cpuid() {
  return (mycpu() - cpus);
}

// Must be called with interrupts disabled to avoid the caller being
// rescheduled between reading lapicid and running through the loop.
struct cpu*
mycpu(void)
{
  int apicid, i;

  if(readeflags()&FL_IF)
    panic("mycpu called with interrupts enabled\n");

  apicid = lapicid();
  // APIC IDs are not guaranteed to be contiguous. Maybe we should have
  // a reverse map, or reserve a register to store &cpus[i].
  for (i = 0; i < ncpu; ++i) {
    if (cpus[i].apicid == apicid)
      return &cpus[i];
  }
  panic("unknown apicid\n");
}

// Disable interrupts so that we are not rescheduled
// while reading proc from the cpu structure
struct proc*
myproc(void) {
  struct cpu *c;
  struct proc *p;
  pushcli();
  c = mycpu();
  p = c->proc;
  popcli();
  return p;
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;
#ifdef LOTTERY_SCHED
  p->nice_value = DEFAULT_NICE_VALUE;
#endif // LOTTERY_SCHED

#ifdef PROC_TIME
  cmostime(&(p->begin_date));
  p->ticks_total = 0;
  p->sched_times = 0;
#endif // PROC_TIME

  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

#ifdef KTHREADS
  p->oncpu = -1;
  p->isthread = FALSE;
  p->isparent = FALSE;
  p->thread_count = 0;
#endif // KTHREADS

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  p = allocproc();

  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.
  acquire(&ptable.lock);

  p->state = RUNNABLE;

  release(&ptable.lock);
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  struct proc *curproc = myproc();

  sz = curproc->sz;
  if(n > 0){
    if((sz = allocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  curproc->sz = sz;
  switchuvm(curproc);
  return 0;
}

int forkcount(void)
{
    return _forkcount;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;
  struct proc *curproc = myproc();

  _forkcount++;

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = curproc->sz;
  np->parent = curproc;
  *np->tf = *curproc->tf;
#ifdef LOTTERY_SCHED
  np->nice_value = curproc->nice_value;
#endif

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));

  pid = np->pid;

  acquire(&ptable.lock);

  np->state = RUNNABLE;

  release(&ptable.lock);

  return pid;
}

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *curproc = myproc();
  struct proc *p;
  int fd;

  if(curproc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd]){
      fileclose(curproc->ofile[fd]);
      curproc->ofile[fd] = 0;
    }
  }

  begin_op();
  iput(curproc->cwd);
  end_op();
  curproc->cwd = 0;

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(curproc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == curproc) {
      #ifdef KTHREADS
      if(p->isthread == 1) {
        kfree(p->kstack);
        p->kstack = 0;
        p->state = UNUSED;
      } else {
        p->parent = initproc;
        if(p->state == ZOMBIE)
          wakeup1(initproc);
      }
      #endif // KTHREADS
      #ifndef KTHREADS
        p->parent = initproc;
          if(p->state == ZOMBIE)
            wakeup1(initproc);
      #endif // !KTHREADS
    }
  }

  // Jump into the scheduler, never to return.
  curproc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;
  struct proc *curproc = myproc();

  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for exited children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != curproc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->state = UNUSED;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}

#ifdef PROC_TIME
// call sys_uptime
int
uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
#endif // PROC_TIME

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();

#ifdef LOTTERY_SCHED
  int nice_sum = 0;
  int random_num = 0;
#endif // LOTTERY_SCHED

#ifdef KTHREADS
  int current_cpu = cpuid();
#endif // KTHREADS

  c->proc = 0;

  for(;;){
    // Enable interrupts on this processor.
    sti();

    acquire(&ptable.lock);

#ifdef LOTTERY_SCHED
    for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
        if (p->state != RUNNABLE) {
            continue;
        }
        nice_sum += p->nice_value;
    }

    // check for 0
    if (nice_sum == 0) {
      release(&ptable.lock);
      continue;
    }

    random_num = rand() % nice_sum;
    nice_sum = 0;
#endif // LOTTERY_SCHED

    for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
        if (p->state != RUNNABLE) {
            continue;
        }
#ifdef LOTTERY_SCHED
        nice_sum += p->nice_value;
        if (nice_sum < random_num) {
            continue;
        }
#endif // LOTTERY_SCHED

#ifdef KTHREADS
        p->oncpu = current_cpu;
#endif // KTHREADS

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;

#ifdef PROC_TIME
      p->sched_times++;
#ifdef D_TICK
      p->ticks_begin = ticks;
#else
      p->ticks_begin = uptime();
#endif // D_TICK
#endif // PROC_TIME

      swtch(&(c->scheduler), p->context);
      switchkvm();

#ifdef KTHREADS
      p->oncpu = -1;
#endif // KTHREADS

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
#ifdef PROC_TIME
#ifdef D_TICK
      p->ticks_total += ticks - p->ticks_begin;
#else
      p->ticks_total += uptime() - p->ticks_begin;
#endif // D_TICK
#endif // PROC_TIME

    }
    release(&ptable.lock);

  }
}

int
renice(int renice_value, int pid)
{
  #ifdef LOTTERY_SCHED
  
    struct proc *p;
    int ret = -1;

    if (renice_value < MIN_NICE_VALUE || renice_value > MAX_NICE_VALUE) {
        ret = 1;
    } else {
        acquire(&ptable.lock);

        for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
            if (p->pid == pid) {
                p->nice_value = renice_value;
                ret = 0;
                break;
            }
        }
        ret = 2;
    }
        release(&ptable.lock);

    return ret;
  #endif // LOTTERY_SCHED
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state. Saves and restores
// intena because intena is a property of this
// kernel thread, not this CPU. It should
// be proc->intena and proc->ncli, but that would
// break in the few places where a lock is held but
// there's no process.
void
sched(void)
{
  int intena;
  struct proc *p = myproc();

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(mycpu()->ncli != 1)
    panic("sched locks");
  if(p->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = mycpu()->intena;
  swtch(&p->context, mycpu()->scheduler);
  mycpu()->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  acquire(&ptable.lock);  //DOC: yieldlock
  myproc()->state = RUNNABLE;
  sched();
  release(&ptable.lock);
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
  }

  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();

  if(p == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }
  // Go to sleep.
  p->chan = chan;
  p->state = SLEEPING;

  sched();

  // Tidy up.
  p->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p, *np;

  if (debugMesg == 1) {
      cprintf("%s %s %d: %d\n", __FILE__, __func__, __LINE__, pid);
  }

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      if (debugMesg == 1) {
          cprintf("%s %s %d: %d", __FILE__, __func__, __LINE__, pid);
          #ifdef KTHREADS
            cprintf(" %d %d %d", p->isthread, p->isparent, p->thread_count);
          #endif // KTHREADS
          cprintf(" %s\n", proc_state(p->state));
      }

      #ifdef KTHREADS
      if(p->isparent) {
        for(np = ptable.proc; np < &ptable.proc[NPROC]; np++) {
          if (np->isthread && np->parent->pid == pid) {
            np->killed = 1;
            if (np->state == SLEEPING) {
               np->state = RUNNABLE;
            }
          }
        }
        release(&ptable.lock);
        return 0;
      }
      #endif // KTHREADS

      p->killed = 1;

      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}

#ifdef KTHREADS

int
clone(void *(*func)(void*), void *arg, void *stack)
{
  int i;
  int pid = -1;
  struct proc *np;
  struct proc *curproc = myproc();

  if ((np = allocproc()) == 0) {
    return -1;
  }

  np->pgdir = curproc->pgdir;
  np->sz = curproc->sz;

  if (curproc->isthread == TRUE) {
    np->parent = curproc->parent;
  }
  else {
    np->parent = curproc;
  }
  // trap frame
  *(np->tf) = *(curproc->tf);

  np->tstack = stack;
  np->tf->eax = 0;
  np->tf->eip = (int) func;
  np->isthread = TRUE;
  curproc->isparent = TRUE;
  curproc->thread_count++;

  np->tf->esp = ((int) stack) + PGSIZE;

  np->tf->esp -= sizeof(int);
  *((int *) (np->tf->esp)) = (int) arg;

  np->tf->esp -= sizeof(int);
  *((int *) (np->tf->esp)) = 0xFFFFFFFF;

  for (i = 0; i < NOFILE; i++) {
    if (curproc->ofile[i]) {
      np->ofile[i] = filedup(curproc->ofile[i]);
    }
  }
  np->cwd = idup(curproc->cwd);

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));
  pid = np->pid;

  acquire(&ptable.lock);
  np->state = RUNNABLE;
  release(&ptable.lock);

  return pid;
}

int
join(void)
{
    int pid = -1;
    struct proc *p;
    struct proc *curproc = myproc();
    ushort has_children = FALSE;

    acquire(&ptable.lock);
    for (;;) {
        for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
            if (p->state == UNUSED || !p->parent || p->parent != curproc) {
                continue;
            }
            has_children = 1;
            if (p->state == ZOMBIE) {
                pid = p->pid;
                kfree(p->kstack);
                p->kstack = NULL;
                p->state = UNUSED;
                p->pid = 0;
                p->parent = NULL;
                p->name[0] = NULL;
                p->killed = FALSE;
                release(&ptable.lock);
                return pid;
            }
        }
        if (has_children == 0) {
            release(&ptable.lock);
            return -1;
        }
        sleep(curproc, &ptable.lock);
    }
    return pid;
}

void cps(void) {
  struct proc *p;

  acquire(&ptable.lock);
  cprintf("pid\tppid\tname\tstate\tsize\tstart time\t\tticks\tsched\tnice\tcpu\tkilled\tthread?\tparent?\tThread #\t\n");


  for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if (p->state == UNUSED || p->isthread == TRUE)
      continue;
    cprintf("%d\t%d\t%s\t%s\t%d\t%d-%s%d-%s%d %s%d:%s%d:%s%d\t%d\t%d\t%d",
      p->pid,
      p->parent ? p->parent->pid : 1, 
      p->name, 
      proc_state(p->state), 
      p->sz,
      p->begin_date.year,
      p->begin_date.month < 10 ? "0":"",
      p->begin_date.month,
      p->begin_date.day < 10 ? "0":"",
      p->begin_date.day,
      p->begin_date.hour < 10 ? "0":"",
      p->begin_date.hour,
      p->begin_date.minute < 10 ? "0":"",
      p->begin_date.minute,
      p->begin_date.second < 10 ? "0":"",
      p->begin_date.second,
      p->ticks_total,
      p->sched_times,
      p->nice_value);

    if (p->oncpu >= 0) {
      cprintf("\t%d", p->oncpu);
    } else { 
      cprintf("\t "); 
    }

    cprintf("\t%d\t%d\t%d\t%d",
      p->killed,
      p->isthread,
      p->isparent,
      p->thread_count);

    cprintf("\n");
  }
  release(&ptable.lock);
}

void detailed_cps(void) {
  struct proc *p;

  acquire(&ptable.lock);
  cprintf("pid\tppid\tname\tstate\tsize\tstart time\t\tticks\tsched\tnice\tcpu\tkilled\tthread?\tparent?\tThread #\t\n");


  for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if (p->state == UNUSED)
      continue;
    cprintf("%d\t%d\t%s\t%s\t%d\t%d-%s%d-%s%d %s%d:%s%d:%s%d\t%d\t%d\t%d",
      p->pid,
      p->parent ? p->parent->pid : 1, 
      p->name, 
      proc_state(p->state), 
      p->isthread ? p->parent->sz : p->sz,
      p->begin_date.year,
      p->begin_date.month < 10 ? "0":"",
      p->begin_date.month,
      p->begin_date.day < 10 ? "0":"",
      p->begin_date.day,
      p->begin_date.hour < 10 ? "0":"",
      p->begin_date.hour,
      p->begin_date.minute < 10 ? "0":"",
      p->begin_date.minute,
      p->begin_date.second < 10 ? "0":"",
      p->begin_date.second,
      p->ticks_total,
      p->sched_times,
      p->nice_value);

    if (p->oncpu >= 0) {
      cprintf("\t%d", p->oncpu);
    } else { 
      cprintf("\t "); 
    }

    cprintf("\t%d\t%d\t%d\t%d",
      p->killed,
      p->isthread,
      p->isparent,
      p->thread_count);

    cprintf("\n");
  }
  release(&ptable.lock);
}

#endif // KTHREADS

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  int i;
  struct proc *p;
  const char *state;
  uint pc[10];

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(run_states) && run_states[p->state])
      state = run_states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}

static char *
proc_state(int state)
{
    static char *str = "???";

    if (state >= 0 && state < NELEM(run_states) && run_states[state]) {
        str = (char *) run_states[state];
    }

    return str;
}

int
kernel_debug(int val)
{
    cprintf("** changing kernel debug: %s\n", (val == 0) ? "disabled" : "enabled");
    return debugMesg = ((val == 0) ? 0 : 1);
}


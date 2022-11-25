#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

extern void cps(void);
extern void detailed_cps(void);
extern int _forkcount;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_brk(void)
{
    int addr = 0;
    int n = 0;

    if (argint(0, &n) < 0) {
        return -1;
    }

    addr = myproc()->sz;
    if (growproc(n - addr) < 0) {
        return -1;
    }

    return 0;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;

  addr = myproc()->sz;

  if (n == 0) return addr;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_forkcount(void)
{
    return _forkcount;
}

int sys_getppid(void) {
  int ppid = 1;

  if (myproc()->parent) {
      ppid = myproc()->parent->pid;
  }

  return ppid;
}

int sys_cps(void) {
  cps();
  return 0;
}

int sys_detailed_cps(void) {
  detailed_cps();
  return 0;
}

int
sys_renice(void)
{
  int pid;
  int renice_value;

  if (argint(0, &renice_value) < 0) {
    return -1;
  }

  if (argint(1, &pid) < 0) {
      return -1;
  }

  return renice(renice_value, pid);
}

#ifdef KTHREADS

int sys_clone(void) {
  void *(* func)(void *);
  void *arg;
  void *stack;

  if(argptr(0, (void *) &func, sizeof(func) < 0)) {
    return -1;
  }
  if(argptr(1, (void *) &arg, sizeof(arg) < 0)) {
    return -1;
  }
  if(argptr(2, (void *) &stack, sizeof(stack) < 0)) {
    return -1;
  }

  return clone(func, arg, stack);
}

int sys_join(void) {
  return join();
}

#endif // KTHREADS

int
sys_debug(void)
{
    int n = -1;
    if (argint(0, &n) < 0) {
        return -1;
    }
    return kernel_debug(n);
}


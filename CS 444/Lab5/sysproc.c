#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;

  if (n == 0) { return addr; }

  if(growproc(n) < 0)
    return -1;  
  return addr;
}

int
sys_brk(void)
{
  int addr, n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;

  if (n == 0) { return addr; }

  if(growproc(n - addr) < 0)
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
int sys_uptime(void) { return uptime(); }

int sys_forkcount(void) { return _forkcount; }

int sys_cps(void) { return cps(); }

int sys_renice(void) {
  int pid, nice;

  if (argint(0, &pid) < 0) { return -1; }
  if (argint(1, &nice) < 0) { return -1; }

  return renice(pid, nice);
}

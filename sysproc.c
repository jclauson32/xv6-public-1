#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


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
  struct proc *curproc = myproc();
  int return_val = wait();

  if(return_val != -1){
    (curproc->goodcall_count)++;	
    }
  (curproc->call_count)++;
  return return_val;
}

int
sys_kill(void)
{
  int pid;
  struct proc *curproc = myproc();

  if(argint(0, &pid) < 0)
    return -1;
  int return_val = kill(pid);

  if(return_val != -1){
    (curproc->goodcall_count)++;	
    }
  (curproc->call_count)++;
  return return_val;
 
}

int
sys_getpid(void)
{
  int return_val = myproc()->pid;
  struct proc *curproc = myproc();

  if(return_val != -1){
    (curproc->goodcall_count)++;	
    }
  (curproc->call_count)++;
  return return_val;
  
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  struct proc *curproc = myproc();
  int n;
  uint ticks0;

  if(argint(0, &n) < 0) {
		
    
    (curproc->call_count)++;

    return -1;
	}
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
     
    
    (curproc->call_count)++;

      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  (curproc->goodcall_count)++;	
  (curproc->call_count)++;

  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  struct proc *curproc = myproc();

  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  int return_val = xticks;
  
  if(return_val != -1){
    (curproc->goodcall_count)++;	
    }
  (curproc->call_count)++;
  return return_val;

}

int
sys_getnumsyscalls(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return getnumsyscalls(pid);

}

int
sys_getnumsyscallsgood(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return getnumsyscallsgood(pid);

}




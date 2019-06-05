#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
# define NUM_CHILDREN 5

  int key = 2001;
  int res = 0;
  int cpid = -1;
  int pid = -1;
  int i = -1;
  int j = -1;
  int k = -1;

  res = sem_open(key, 1);
  if (res < 0) {
    printf(2, "sem_open failed: %d\n", res);
    exit();
  }
  sem_status();
  printf(1, "-----------------------\n");

  for (i = 0; i < NUM_CHILDREN; i++) {
    cpid = fork();
    if (cpid == 0) {
      pid = getpid();
      for (j = 0; j < 5; j++) {
        res = sem_dec(key);
        for (k = 0; k <= i; k++) {
          printf(1, " ");
        }
        printf(1, "loop %d %d got the semaphore\n", i, pid);
        for (k = 0; k < 100; k++) {
          sleep(1);
        }
        res = sem_inc(key);
      }
      exit();
    }
  }

  for (i = 0; i < NUM_CHILDREN; i++) {
    cpid = wait();
    //if (cpid > 0) {
    //  printf(1, ">> pid %d is done\n", cpid);
    //}
  }
  sem_status();
  printf(1, "-----------------------\n");

  exit();
}

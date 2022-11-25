#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int key = 42;
  int res = 0;
  
  res = sem_open(key, 3);
  if (res < 0) {
    printf(2, "sem_open failed: %d\n", res);
    exit();
  }
  
  sem_status();
  printf(1, "-----------------------\n");

  res = sem_close(key);
  if (res < 0) {
    printf(2, "sem_open failed: %d\n", res);
    exit();
  }

  sem_status();
  printf(1, "-----------------------\n");

  res = sem_free(key);
  if (res < 0) {
    printf(2, "sem_open failed: %d\n", res);
    exit();
  }

  sem_status();
  printf(1, "-----------------------\n");

  exit();
}

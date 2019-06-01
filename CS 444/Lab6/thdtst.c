#include "types.h"
#include "stat.h"
#include "user.h"

void *func1(void *arg);
void *func2(void *arg);

static int global = 10;

void *
func1(void *arg)
{
  uint *i = (uint *) ((int *) arg);

  assert(global == 10);
  assert(*i == 0xffffffff);

  *i = 0xaeaeaeae;
  global = 100;

  exit();
}

void *
func2(void *arg)
{
  uint inc = *(uint *) ((int *) arg);
  int i;
  int j;
  int max = 1000000;
  int sum = 0;

  for (j = 0; j < max; j++) {
    for(i = 1; i < max; i += inc) {
      sum ++;
      if (sum % (MAXSHORT) == 0) {
        printf(1, "  mult: %d  %d\n", getpid(), sum);
      }
      if (sum > (MAXINT / 2)) {
        sum = 0;
      }
    }
  }
  printf(1, "%s thread done: tid = %d\n", __func__, getpid());

  exit();
}

int
main(int argc, char *argv[])
{
  void *stack1 = malloc(PGSIZE * 2);
  void *stack2 = malloc(PGSIZE * 2);
  void *st = stack1;
  uint i = 0xffffffff;
  int res = -1;

  memset(stack1, 0, PGSIZE * 2);
  memset(stack2, 0, PGSIZE * 2);

#ifdef KTHREADS
  printf(1, "global before: %d\n", global);
  st = stack1;
  res = clone(func1, &i, st);
  if (res < 0) {
    printf(2, "clone1 failed\n");
    exit();
  }
  st = stack2;
  res = clone(func2, &i, st);
  if (res < 0) {
    printf(2, "clone2 failed\n");
    exit();
  }

  res = join();
  if (res < 0) {
    printf(2, "join1 failed\n");
    exit();
  }
#endif // KTHREADS
  free(stack1);
#ifdef KTHREADS
  printf(1, "global after: %d\n", global);

  assert(global == 100);

  printf(1, "i after: %x\n", i);
  assert(i == 0xaeaeaeae);

  res = join();
  if (res < 0) {
    printf(2, "join2 failed\n");
    exit();
  }
#endif // KTHREADS
  free(stack2);

  exit();
}

#include "types.h"
#include "stat.h"
#include "user.h"

void *func1(void *arg);
void *func2(void *arg);

void *
func1(void *arg)
{
#ifdef KTHREADS
  uint inc = *(uint *) ((int *) arg);
  int i;
  int j;
  int max = MAXINT;
  int sum = 0;

  for (j = 0; j < max; j++) {
    for(i = 1; i < max; i += inc) {
      sum ++;
      if (sum % (MAXSHORT * MAXSHORT) == 0) {
        printf(1, "  mult: %d  %d\n", getpid(), sum);
      }
      if (sum > (MAXINT / 2)) {
        sum = 0;
      }
    }
  }
  printf(1, "%s thread done: tid = %d\n", __func__, getpid());

  exit();
#endif // KTHREADS
}

void *
func2(void *arg)
{
#ifdef KTHREADS
  uint inc = *(uint *) ((int *) arg);
  int i;
  int j;
  int max = MAXINT;
  int sum = 0;

  for (j = 0; j < max; j++) {
    for(i = 1; i < max; i += inc) {
      sum ++;
      if (sum % (MAXSHORT * MAXSHORT) == 0) {
        printf(1, "  mult: %d  %d\n", getpid(), sum);
      }
      if (sum > (MAXINT / 2)) {
        sum = 0;
      }
    }
  }
  printf(1, "%s thread done: tid = %d\n", __func__, getpid());

  exit();
#endif // KTHREADS
}

#define THRD_COUNT 5

int
main(int argc, char *argv[])
{
  //void *stack = malloc(PGSIZE * 2);
  void *st = NULL;
  uint i = 0xffffffff;
  int res = -1;
  void *stacks[2 * THRD_COUNT] = {'\0'};
  int max = THRD_COUNT;

  if (argc > 1) {
    // change the upper bound on the iteration loops.
    max = atoi(argv[1]);
    if (max > THRD_COUNT || max < 1) {
      max = THRD_COUNT;
    }
  }

#ifdef KTHREADS
  for (i = 0; i < max; i++) {
    stacks[i] = malloc(PGSIZE * 2);
    memset(stacks[i], 0, PGSIZE * 2);
    if (((uint) stacks[i]) % PGSIZE) {
      st = stacks[i] + (PGSIZE - ((uint) stacks[i]) % PGSIZE);
    }

    res = clone(func1, &i, st);
    if (res < 0) {
      printf(2, "clone failed\n");
      exit();
    }
  }

  for (i = 0; i < max; i++) {
    stacks[i] = malloc(PGSIZE * 2);
    memset(stacks[i], 0, PGSIZE * 2);
    if (((uint) stacks[i]) % PGSIZE) {
      st = stacks[i] + (PGSIZE - ((uint) stacks[i]) % PGSIZE);
    }

    res = clone(func2, &i, st);
    if (res < 0) {
      printf(2, "clone failed\n");
      exit();
    }
  }

#ifdef NOMORE
  printf(2, "%s %d\n", __FILE__, __LINE__);
  for (i = 0; i < 2 * max; i++) {
    printf(2, "%s %d\n", __FILE__, __LINE__);
    res = join();
    if (res < 0) {
      printf(2, "join failed\n");
      exit();
    }
  }
#endif // NOMORE
  for (;;) {
    sleep(1);
  }
#endif // KTHREADS
  for (i = 0; i < 2 * max; i++) {
      free(stacks[i]);
  }

  exit();
}


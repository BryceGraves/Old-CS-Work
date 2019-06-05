#include "types.h"
#include "defs.h"
#include "sem.h"
#include "mmu.h"
#include "spinlock.h"

#ifndef NULL
  #define NULL 0
#endif // NULL
#ifndef TRUE
  #define TRUE 1
#endif // TRUE
#ifndef FALSE
  #define FALSE 0
#endif // FALSE
#ifndef SUCCESS
  #define SUCCESS 0
#endif // SUCCESS
#ifndef FAILURE
  #define FAILURE 1
#endif // FAILURE

#define NSEM (PGSIZE / sizeof(sem_t))

typedef struct sem_s {
  uint key;
  ushort cur_val, max_val, ref_count;
  struct spinlock lock;
} sem_t;

static struct {
  struct spinlock lock;
  sem_t sem_array[NSEM];
} semtable;

int semaphore_initialize_system(void) {
  int index = 0;

  initlock(&semtable.lock, "semtable");
  acquire(&semtable.lock);

  for (; index < NSEM; index++) {
    semtable.sem_array[index].key = NULL;
    semtable.sem_array[index].cur_val = NULL;
    semtable.sem_array[index].max_val = NULL;
    initlock(&semtable.sem_array[index].lock, "semaphore");
  }

  release(&semtable.lock);
  return 0;
}

// If a semaphore with this key does not
// exist, create the semaphore, give it initial and max values of max_value, set its
// ref_count to 1, and return success. If the semaphore with that key already exists,
// increment the ref_count member and return success. This function is very similar to
// the POSIX function sem_init().
int sem_open(int key, int initial_value) {
  int index = 0;

  if (key < 1) { return FAILURE; }

  for (; index < NSEM; index++) {
    acquire(&semtable.sem_array[index].lock);

    if (semtable.sem_array[index].key == key) {
      semtable.sem_array[index].ref_count++;

      release(&semtable.sem_array[index].lock);
      return SUCCESS;
    } else if (semtable.sem_array[index].key == NULL) {
      semtable.sem_array[index].key = key;
      semtable.sem_array[index].cur_val = initial_value;
      semtable.sem_array[index].max_val = initial_value;
      semtable.sem_array[index].ref_count = 1;

      release(&semtable.sem_array[index].lock);
      return SUCCESS;
    }

    release(&semtable.sem_array[index].lock);
  }

  return FAILURE;
}

// If a semaphore with the given key exists, decrement its
// ref_count member, but do not allow the ref_count to go below zero. If a
// semaphore with that key does not exist, return an error. This function, roughly,
// corresponds to the POSIX call sem_close().
int sem_close(int key) {
  int index = 0;

  if (key < 1) { return FAILURE; }

  for (; index < NSEM; index++) {
    acquire(&semtable.sem_array[index].lock);

    if (semtable.sem_array[index].key == key && semtable.sem_array[index].ref_count > 0) {
      semtable.sem_array[index].ref_count--;
      release(&semtable.sem_array[index].lock);
      return SUCCESS;
    }

    release(&semtable.sem_array[index].lock);
  }

  return FAILURE;
}

// If a semaphore with the given key exists, decrement its
// ref_count member, but do not allow the ref_count to go below zero. If the
// ref_count is equal to zero, “deallocate” the semaphore. If a semaphore with that
// key does not exist, return an error. This function, roughly, corresponds to the POSIX call
// sem_unlink().
int sem_free(int key) {
  int index = 0;

  if (key < 1) { return FAILURE; }

  for (; index < NSEM; index++) {
    acquire(&semtable.sem_array[index].lock);
    if (semtable.sem_array[index].key == key && semtable.sem_array[index].ref_count > 0) {
      semtable.sem_array[index].ref_count--;

      release(&semtable.sem_array[index].lock);
      return SUCCESS;
    } else if (semtable.sem_array[index].key == key && semtable.sem_array[index].ref_count == 0) {
      semtable.sem_array[index].key = NULL;
      semtable.sem_array[index].cur_val = NULL;
      semtable.sem_array[index].max_val = NULL;
      semtable.sem_array[index].ref_count = 0;

      release(&semtable.sem_array[index].lock);
      return SUCCESS;
    }

    release(&semtable.sem_array[index].lock);
  }

  return FAILURE;
}

// If a semaphore with the given key exists, increment its
// cur_val member, not allowing the cur_val to exceed max_val. Wakeup any
// threads/processes that may be blocked waiting for the resource to become available. If
// a semaphore with that key does not exist, return an error. This call is similar in function
// to the POSIX call sem_post().
int sem_inc(int key) {
  int index = 0;

  if (key < 1) { return FAILURE; }

  for (; index < NSEM; index++) {
    acquire(&semtable.sem_array[index].lock);

    if (semtable.sem_array[index].key == key) {
      if (semtable.sem_array[index].cur_val < semtable.sem_array[index].max_val) {
        semtable.sem_array[index].cur_val++;
        wakeup(&semtable.sem_array[index]);
      }

      release(&semtable.sem_array[index].lock);
      return SUCCESS;
    }

    release(&semtable.sem_array[index].lock);
  }

  return FAILURE;
}

// If a semaphore with the given key exists and its current value
// is greater than 0, decrement it and return success. If a semaphore with the given key
// exists and the value is equal to zero, block indefinitely, waiting for the value to be
// incremented from a call to sem_inc() by another thread/process. If a semaphore
// with that key does not exist, return an error. This call is similar in function to the POSIX
// call sem_wait().
int sem_dec(int key) {
  int index = 0;

  if (key < 1) { return FAILURE; }

  for (; index < NSEM; index++) {
    acquire(&semtable.sem_array[index].lock);

    if (semtable.sem_array[index].key == key && semtable.sem_array[index].cur_val > 0) {
      semtable.sem_array[index].cur_val--;
      release(&semtable.sem_array[index].lock);
      return SUCCESS;
    } else if (semtable.sem_array[index].key == key && semtable.sem_array[index].cur_val == 0) {
      while (semtable.sem_array[index].cur_val == 0) {
        sleep(&semtable.sem_array[index], &semtable.sem_array[index].lock);
      }

      semtable.sem_array[index].cur_val--;

      release(&semtable.sem_array[index].lock);
      return SUCCESS;
    }

    release(&semtable.sem_array[index].lock);
  }

  return FAILURE; 
}

// Print information about every semaphore in use by the kernel.
// See the image below for the data that must be shown for each in-use semaphore. The
// idx column simply shows where the data for the semaphore is kept in the array of
// semaphores available in the kernel. Resources in the kernel are limited and a single
// PGSIZE lump of memory is allocated for the array semaphores in the kernel. Only a
// certain number of semaphores can be stored in the lump of memory. The total number
// of kernel available semaphores can be easily calculated once the size of the structure
// used to represent a semaphore is known. We reviewed this in class. Glad you took
// notes? The key column in sem_status shows the key value used for the semaphore.
// The cur column shows the current number of resources available from the semaphore.
// The cur value will be between 0 and max. The max contains the number of resources
// available from the semaphore. This is the value passed as max_value to the function
// sem_open(). Each semaphore must be protected by its own lock. The current status
// of the lock is shown in the last column, locked, in sem_status(). When the
// sem_status() call was run, was the semaphore, at that instant, locked. Usually, this
// will be zero. The last line in the sem_status() output should show how many
// unallocated semaphores are available.
int sem_status(void) {
  int index, total_free_sem;
  index = total_free_sem = 0;

  cprintf("idx\tkey\tcur\tmax\tref\tlocked\n");
  
  acquire(&semtable.lock);
  for (; index < NSEM; index++) {
    if (semtable.sem_array[index].key == NULL) {
      total_free_sem++;
      continue;
    }
    cprintf("%d\t%d\t%d\t%d\t%d\t%d\n",
            index,
            semtable.sem_array[index].key,
            semtable.sem_array[index].cur_val,
            semtable.sem_array[index].max_val,
            semtable.sem_array[index].ref_count,
            semtable.sem_array[index].lock.locked
    );
  }
  release(&semtable.lock);
  cprintf("** %d available. **\n", total_free_sem);

  return SUCCESS;
}
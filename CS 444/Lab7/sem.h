#ifndef __SEM_H
#define __SEM_H

int semaphore_initialize_system(void);
int sem_open(int, int); // key, initial value
int sem_close(int);     // key
int sem_free(int);      // key
int sem_inc(int); // key --> acquire
int sem_dec(int); // key --> release
int sem_status(void);

// these are not required
// don't spend time on these, unless you really want some fun.
int sem_test(int);
int sem_test_dec(int);
int sem_val(int);

#endif // __SEM_H

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef __BEAVALLOC_H
# define __BEAVALLOC_H

#ifndef MAX
# define MAX(_a,_b) ((_a) > (_b) ? (_a) : (_b))
#endif // MAX

#ifndef TRUE
# define TRUE 1
#endif // TRUE
#ifndef FALSE
# define FALSE 0
#endif // FALSE

typedef enum {
  FIRST_FIT
  , BEST_FIT
  , WORST_FIT
  , NEXT_FIT
} beavalloc_fit_algo_t;

typedef struct memory_block_s {
  unsigned long capacity;
  unsigned long total;
  _Bool free;
  struct memory_block_s *next;
  struct memory_block_s *prev;
} memory_block_t;

#define MEMORY_BLOCK_SIZE sizeof(memory_block_t)

void *beavalloc(unsigned long size);
memory_block_t *create_block(memory_block_t *, unsigned long);
memory_block_t *locate_free_block(memory_block_t **, unsigned long);
void split_memory_chunk(memory_block_t *, unsigned long);
void beavfree(void *ptr);
void coalesce(memory_block_t *);
void beavalloc_info(void);
void beavalloc_walk(void);
void beavalloc_reset(void);
void beavalloc_leaks(void);
void beavalloc_set_algorithm(beavalloc_fit_algo_t);
void beavalloc_set_verbose(uint8_t);

#endif

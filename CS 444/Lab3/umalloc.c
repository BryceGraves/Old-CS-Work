#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

#ifdef MY_MALLOC

# define MIN_DATA_SIZE 30

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

memory_block_t *create_block(memory_block_t *, unsigned long);
memory_block_t *locate_free_block(memory_block_t **, unsigned long);
void split_memory_chunk(memory_block_t *, unsigned long);
void coalesce(memory_block_t *);
void beavalloc_info(void);
void beavalloc_walk(void);
void beavalloc_leaks(void);
void beavalloc_set_algorithm(beavalloc_fit_algo_t);
void beavalloc_set_verbose(uint);

#endif // MY_MALLOC

// Memory allocator by Kernighan and Ritchie,
// The C programming Language, 2nd ed.  Section 8.7.

#ifndef MY_MALLOC

typedef long Align;

union header {
  struct {
    union header *ptr;
    uint size;
  } s;
  Align x;
};

typedef union header Header;

static Header base;
static Header *freep;

void
free(void *ap)
{
  Header *bp, *p;

  bp = (Header*)ap - 1;
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  if(bp + bp->s.size == p->s.ptr){
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  if(p + p->s.size == bp){
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else
    p->s.ptr = bp;
  freep = p;
}

static Header*
morecore(uint nu)
{
  char *p;
  Header *hp;

  if(nu < 4096)
    nu = 4096;
  p = sbrk(nu * sizeof(Header));
  if(p == (char*)-1)
    return 0;
  hp = (Header*)p;
  hp->s.size = nu;
  free((void*)(hp + 1));
  return freep;
}

void*
malloc(uint nbytes)
{
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
  if((prevp = freep) == 0){
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
    if(p->s.size >= nunits){
      if(p->s.size == nunits)
        prevp->s.ptr = p->s.ptr;
      else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void*)(p + 1);
    }
    if(p == freep)
      if((p = morecore(nunits)) == 0)
        return 0;
  }
}

#endif // !MY_MALLOC

#ifdef MY_MALLOC

// Making some global variables - shield your eyes
static uint algorithm = 0, verbose = FALSE;
static void *list_head = NULL;

// More global variables - these are stats tho
static void *lower_bound, *upper_bound;
static int malloc_call_count = 0, free_call_count = 0, user_data_total = 0;


// The basic memory allocator.
// If you pass NULL or 0, then NULL is returned.
// If, for some reason, the system cannot allocate the requested
//   memory, set errno and return NULL.
// Do not allocate a chunk of memory smaller than MIN_DATA_SIZE bytes (plus
//   whatever you need for your structure).
// You must use sbrk() or brk() in requesting more memory for your
//   beavalloc() routine to manage.
void *malloc(uint capacity) {
  memory_block_t *block;

  if (verbose) {
    printf(2, "Checking a few things\n");
  }

  // Guard Clauses
  if (capacity <= 0) { return NULL; }
  if (capacity < MIN_DATA_SIZE) { capacity = MIN_DATA_SIZE; }

  if (!list_head) {
    if (verbose) {
      printf(2, "No free list found making one\n");
    }

    lower_bound = sbrk(0);
    block = create_block(NULL, capacity);

    if (!block) {
      return NULL;
    }

    list_head = block;
  } else {
    memory_block_t *head = list_head;
    block = locate_free_block(&head, capacity);

    if (verbose) {
      printf(2, "Free list found, locating a free block.\n");
    }

    if (!block) {
      if (verbose) {
        printf(2, "No block found making a new block.\n");
      }
      block = create_block(head, capacity);

      if (!block) {
        return NULL;
      }
    } else {
      if (verbose) {
        printf(2, "Block found, it is now allocated.\n");
      }

      if (block->capacity > (capacity + MEMORY_BLOCK_SIZE + MIN_DATA_SIZE)) {
        split_memory_chunk(block, capacity);
      }

      block->free = FALSE;
    }
  }

  malloc_call_count++;
  user_data_total += capacity;
  upper_bound = block + 1;
  return upper_bound;
}

memory_block_t *create_block(memory_block_t *tail, unsigned long size) {
  memory_block_t *block = (void *) sbrk(0);
  void *created_block =  sbrk(size + MEMORY_BLOCK_SIZE);

  // Errorno is set by this failure. Great Success.
  if (created_block == (void*) -1) {
    return NULL;
  }

  if (tail) {
    tail->next = block;
    block->prev = tail;
  } else {
    block->prev = NULL;
  }

  block->capacity = size;
  block->free = FALSE;
  block->next = NULL;
  block->total = size + MEMORY_BLOCK_SIZE;

  if (verbose) {
    printf(2, "Block made!\n");
  }

  return block;
}

memory_block_t *locate_free_block(memory_block_t **head, unsigned long size) {
  memory_block_t *current = (memory_block_t *) list_head, *temp = NULL;
  unsigned long int current_closest_capacity = -1;

  if (verbose) {
    printf(2, "Locating a free block!\n");
  }

  if (algorithm == FIRST_FIT) {
    while (current && !(current->free && current->capacity >= size)) {
      *head = current;
      current = current->next;
    }
  } else if (algorithm == BEST_FIT) {
    while (current) {
      if (current_closest_capacity > current->capacity && current->capacity >= size && current->free == TRUE) {
        temp = current;
        current_closest_capacity = current->capacity;
      }
      current = current->next;
    }
    current = list_head;
    while (temp != current && current) {
      *head = current;
      current = current->next;
    }
  }

  return current;
}

void split_memory_chunk(memory_block_t *allocated_block, unsigned long capacity) {
  void *new_block_location = allocated_block;
  memory_block_t *free_block = new_block_location + (MEMORY_BLOCK_SIZE + capacity);

  // Sanity check, sorry uncle bob
  if (!allocated_block) {
    printf(2, "There was no chunk passed to split memory. Somthing is very wrong.");
    return;
  }

  free_block->total = allocated_block->total - (MEMORY_BLOCK_SIZE + capacity);
  free_block->capacity = allocated_block->capacity - (MEMORY_BLOCK_SIZE + capacity);
  free_block->prev = allocated_block;
  free_block->next = allocated_block->next;

  if (allocated_block->next) {
    allocated_block->next->prev = free_block;
  }

  free_block->free = TRUE;

  if (verbose) {
    printf(2, "Free Block info:\n\
    Capacity: %ld\n\
    Size: %ld\n",
    free_block->capacity, free_block->total);
  }

  allocated_block->total = capacity + MEMORY_BLOCK_SIZE;
  allocated_block->capacity = capacity;
  allocated_block->next = free_block;

  if (verbose) {
    printf(2, "Split chunk\n");
  }
}

// A pointer returned from a prevous call to beavalloc() must
//   be passed.
// If a pointer is passed to a block than is already free, 
//   simply return. If you are in verbose mode, print a snarky message
//   before returning.
// Blocks must be coalesced, where possible, as they are free'ed.
void free(void *ptr) {
  memory_block_t *block = (memory_block_t *) ptr - 1;

  if (verbose) {
    printf(2, "Checking to see if the given pointer is null!\n");
  }

  if (ptr == NULL) {
    if (verbose) {
      printf(2, "You passed NULL you dumb dumb.\n");
    }
    return;
  }

  if (verbose) {
    printf(2, "Checking to see if the block exists!\n");
  }


  if (!block) {
    return;
  }

  if (block->free == TRUE) {
    printf(2, "Printing a snarky message.\n");
    return;
  }

  block->free = TRUE;


  free_call_count++;
  user_data_total -= block->capacity;

  coalesce(block);
}

// coalesce previous and current: previous->next = current->next; if there is a current->next then current->next->previous = current->prev
// coalesce current and next: current->next = current->next->next; if there is a current->next->next then current->next->next->previous = current

void coalesce(memory_block_t * block) {
  if (verbose) {
    printf(2, "Starting to coalesce!\n");
  }

  if (verbose) {
    printf(2, "Checking to see if there is a previous node!\n");
  }

  if (block->prev) {
    if (verbose) {
      printf(2, "There is a previous node! Is it free?\n");
    }
    if (block->prev->free) {
      if (verbose) {
        printf(2, "Adding current block capacity to previous, then coalesce.\n");
      }
      
      block->prev->total += block->total;
      block->prev->capacity += block->total;
      block->prev->next = block->next;

      if (block->next) {
        block->next->prev = block->prev;
      }

      block = block->prev;
    }
  }

  if (verbose) {
    printf(2, "Checking to see if there is a next node!\n");
  }

  if (block->next) {
    if (verbose) {
      printf(2, "There is a next node! Is it free?\n");
    }

    if (block->next->free) {
      if (verbose) {
        printf(2, "Adding current block capacity to next block, then coalesce.\n");
      }

      block->total += block->next->total;
      block->capacity += block->next->total;

      if (block->next->next) {
        block->next->next->prev = block;
      }

      block->next = block->next->next;
    }
  }
}

// Print some stats about the status of your heap.
// Required data:
//   lower bound on the heap memory
//   current upper bound on the heap
//   number of calls to beavalloc
//   number of calls to beavfree
//   number bytes, currently, allocated to user data in the heap
// Use the output from my code as a guide.
void beavalloc_info(void) {
  printf(1, "Lower bound address: %p\nUpper bound address: %p\n\
  Calls to beavalloc: %d\n\
  Calls to beavfree: %d\n\
  Data Allocated: %d\n",\
  lower_bound, upper_bound,\
  malloc_call_count,\
  free_call_count,\
  user_data_total);
}

// Walk down through your memory structure/structures and show
// information about current allocated blocks in your heap.
// You must show:
//   the address of each block
//   blocks currenly in use
//   blocks allocated, but not currently in use (aka free)
//   the bytes capacity of each block
//   the number of bytes currently in use for each block
// Use the output from my code as a guide.
void beavalloc_walk(void) {
  memory_block_t *block = list_head;

  while (block) {
    printf(1, "Address: %p\n\
      Is free?: %d\n\
      Capacity: %ld\n\
      Size: %ld\n",\
      block,\
      block->free,\
      block->capacity,\
      block->total);
    block = block->next;
  }
}

void heapreset(void) {
  brk(lower_bound);
  list_head = NULL;
  upper_bound = lower_bound;
  malloc_call_count = free_call_count = user_data_total = 0;
}

// Completely reset your heap back to zero bytes allocated.
// You are going to like being able to do this.
// Implementation can be done in as few as 1 line, though
//   you will probably use more to reset the stats you keep
//   about heap.
// After you've called this function, everything you had in
//   the heap is just __GONE__!!!
// You should be able to call beavalloc() after calling beavalloc_reset()
//   to restart building the heap again.
void heapdump(ushort leaks_only)
{
    memory_block_t *curr = (memory_block_t *) list_head;
    ulong i = 0;
    ulong leak_count = 0;
    ulong user_bytes = 0;
    ulong capacity_bytes = 0;
    ulong block_bytes = 0;
    ulong used_blocks = 0;
    ulong free_blocks = 0;

    if (leaks_only) {
        printf(1, "heap lost blocks\n");
    }
    else {
        printf(1, "heap map\n");
    }
    printf(1,
            "  %s\t%s\t%s\t%s\t%s" 
            "\t%s\t%s\t%s\t%s\t%s\t%s"
            "\n"
            , "blk no "
            , "block add "
            , "next add  "
            , "prev add  "

            , "blk off  "
            , "capacity "
            , "bytes usd"
            , "blk size "
            , "status   "
        );
    for (i = 0; curr != NULL; curr = curr->next, i++) {
        if (leaks_only == FALSE || (leaks_only == TRUE && curr->free == FALSE)) {
            printf(1,
                   "  %u\t\t%p\t\t%p\t\t%p\t\t%p\t\t%u\t\t%u\t\t"
                   "%u\t\t%u\t\t%u\t\t%s\t%c\n"
                   , i
                   , curr
                   , curr->next
                   , curr->prev
                   , ((void *) curr - lower_bound)
                   , (unsigned long) curr->capacity, (unsigned long) curr->total
                   , curr->capacity + sizeof(memory_block_t)
                   , curr->free ? "free  " : "in use"
                   , curr->free ? '*' : ' '
              );
            user_bytes += curr->total;
            capacity_bytes += curr->capacity;
            block_bytes += curr->capacity + sizeof(memory_block_t);
            if (curr->free == FALSE && leaks_only == TRUE) {
                leak_count++;
            }
            if (curr->free == TRUE) {
                free_blocks++;
            }
            else {
                used_blocks++;
            }
        }
    }

    if (leaks_only) {
      if (leak_count == 0) {
        printf(1, "  *** No leaks found!!! That does NOT mean no leaks are possible. ***\n");
      }
      else {
        printf(1,
               "  %s\t\t\t\t\t\t\t\t\t\t\t\t"
               "%u\t\t%u\t\t%u\n"
               , "Total bytes lost"
               , capacity_bytes
               , user_bytes
               , block_bytes
          );
      }
    }
    else {
      printf(1,
               "  %s\t\t\t\t\t\t\t\t\t\t\t\t"
               "%u\t\t%u\t\t%u\n"
             , "Total bytes used"
             , capacity_bytes
             , user_bytes
             , block_bytes
        );
      printf(1, "  Used blocks: %u  Free blocks: %u  "
             "Min heap: %p    Max heap: %p\n"
             , used_blocks, free_blocks
             , lower_bound, upper_bound
        );
    }
}

// Walk through your list of data blocks and display information
//   about blocks that are still allocated.
// You'd only use this when you __think__ you have called beavfree()
//   on all allocated memory to see if you've missed something.
// Use the output from my code as a guide.
void beavalloc_leaks(void) {
  int blocks_still_in_use = 0, bytes_lost = 0;
  memory_block_t *current = list_head;

  while (current) {
    if (!current->free) {
      blocks_still_in_use++;
      bytes_lost += current->total;
    }
    current = current->next;
  }

  printf(1, "Number of blocks left unfree: %d\nNumber of bytes lost: %d\n",\
    blocks_still_in_use, bytes_lost);
}

// Set the fit algorithm.
// This should modify a variable that is static to your C module.
void beavalloc_set_algorithm(beavalloc_fit_algo_t alg) {
  algorithm = alg;
}

// Set the verbosity of your beavalloc() code (and related functions).
// This should modify a variable that is static to your C module.
void beavalloc_set_verbose(uint verbosity) {
  verbose = verbosity; 
}

#endif // MY_MALLOC

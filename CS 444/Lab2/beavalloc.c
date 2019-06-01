#include "beavalloc.h"

// Making some global variables - shield your eyes
static uint8_t algorithm = 0, verbose = FALSE;
static void *list_head = NULL;

// More global variables - these are stats tho
static void *lower_bound, *upper_bound;
static int malloc_call_count = 0, free_call_count = 0, user_data_total = 0;


// The basic memory allocator.
// If you pass NULL or 0, then NULL is returned.
// If, for some reason, the system cannot allocate the requested
//   memory, set errno and return NULL.
// Do not allocate a chunk of memory smaller than 20 bytes (plus
//   whatever you need for your structure).
// You must use sbrk() or brk() in requesting more memory for your
//   beavalloc() routine to manage.
void *beavalloc(unsigned long capacity) {
  memory_block_t *block;

  if (verbose) {
    fprintf(stderr, "Checking a few things\n");
  }

  // Guard Clauses
  if (capacity <= 0) { return NULL; }
  if (capacity < 20) { capacity = 20; }

  if (!list_head) {
    if (verbose) {
      fprintf(stderr, "No free list found making one\n");
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
      fprintf(stderr, "Free list found, locating a free block.\n");
    }

    if (!block) {
      if (verbose) {
        fprintf(stderr, "No block found making a new block.\n");
      }
      block = create_block(head, capacity);

      if (!block) {
        return NULL;
      }
    } else {
      if (verbose) {
        fprintf(stderr, "Block found, it is now allocated.\n");
      }

      if (block->capacity > (capacity + MEMORY_BLOCK_SIZE + 40)) {
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
  memory_block_t *block = sbrk(0);
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
    fprintf(stderr, "Block made!\n");
  }

  return block;
}

memory_block_t *locate_free_block(memory_block_t **head, unsigned long size) {
  memory_block_t *current = (memory_block_t *) list_head, *temp = NULL;
  unsigned long int current_closest_capacity = -1;

  if (verbose) {
    fprintf(stderr, "Locating a free block!\n");
  }

  if (algorithm == FIRST_FIT) {
    if (verbose) {
      fprintf(stderr, "Using First Fit!\n");
    }

    while (current && !(current->free && current->capacity >= size)) {
      *head = current;
      current = current->next;
    }
  } else if (algorithm == BEST_FIT) {
    if (verbose) {
      fprintf(stderr, "Using Best Fit!\n");
    }

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
    fprintf(stderr, "There was no chunk passed to split memory. Somthing is very wrong.");
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
    fprintf(stderr, "Free Block info:\n\
    Capacity: %ld\n\
    Size: %ld\n",
    free_block->capacity, free_block->total);
  }

  allocated_block->total = capacity + MEMORY_BLOCK_SIZE;
  allocated_block->capacity = capacity;
  allocated_block->next = free_block;

  if (verbose) {
    fprintf(stderr, "Split chunk\n");
  }
}

// A pointer returned from a prevous call to beavalloc() must
//   be passed.
// If a pointer is passed to a block than is already free, 
//   simply return. If you are in verbose mode, print a snarky message
//   before returning.
// Blocks must be coalesced, where possible, as they are free'ed.
void beavfree(void *ptr) {
  memory_block_t *block = (memory_block_t *) ptr - 1;

  if (verbose) {
    fprintf(stderr, "Checking to see if the given pointer is null!\n");
  }

  if (ptr == NULL) {
    if (verbose) {
      fprintf(stderr, "You passed NULL you dumb dumb.\n");
    }
    return;
  }

  if (verbose) {
    fprintf(stderr, "Checking to see if the block exists!\n");
  }


  if (!block) {
    return;
  }

  if (block->free == TRUE) {
    printf("Printing a snarky message.\n");
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
    fprintf(stderr, "Starting to coalesce!\n");
  }

  if (verbose) {
    fprintf(stderr, "Checking to see if there is a previous node!\n");
  }

  if (block->prev) {
    if (verbose) {
      fprintf(stderr, "There is a previous node! Is it free?\n");
    }
    if (block->prev->free) {
      if (verbose) {
        fprintf(stderr, "Adding current block capacity to previous, then coalesce.\n");
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
    fprintf(stderr, "Checking to see if there is a next node!\n");
  }

  if (block->next) {
    if (verbose) {
      fprintf(stderr, "There is a next node! Is it free?\n");
    }

    if (block->next->free) {
      if (verbose) {
        fprintf(stderr, "Adding current block capacity to next block, then coalesce.\n");
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
  printf("Lower bound address: %p\nUpper bound address: %p\n\
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
    printf("Address: %p\n\
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

// Completely reset your heap back to zero bytes allocated.
// You are going to like being able to do this.
// Implementation can be done in as few as 1 line, though
//   you will probably use more to reset the stats you keep
//   about heap.
// After you've called this function, everything you had in
//   the heap is just __GONE__!!!
// You should be able to call beavalloc() after calling beavalloc_reset()
//   to restart building the heap again.
void beavalloc_reset(void) {
  brk(lower_bound);
  list_head = NULL;
  upper_bound = lower_bound;
  malloc_call_count = free_call_count = user_data_total = 0;
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

  printf("Number of blocks left unfree: %d\nNumber of bytes lost: %d\n",\
    blocks_still_in_use, bytes_lost);
}

// Set the fit algorithm.
// This should modify a variable that is static to your C module.
void beavalloc_set_algorithm(beavalloc_fit_algo_t alg) {
  algorithm = alg;
}

// Set the verbosity of your beavalloc() code (and related functions).
// This should modify a variable that is static to your C module.
void beavalloc_set_verbose(uint8_t verbosity) {
  verbose = verbosity; 
}

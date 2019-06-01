#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

typedef struct block_s {
    struct block_s *next;
    struct block_s *prev;
    uint capacity;
    uint user_data_size;
    int is_free;
} block_t;

#define HDR_SIZE sizeof(block_t)
#define MIN_DATA_SIZE 30

typedef union header Header;
int first_fit = 1;
typedef long Align;
static int *top_heap = NULL;
static block_t *head = NULL;

void
free(void *ptr)
{
    block_t *block_to_free = (block_t*) (ptr - sizeof(block_t));

    if (ptr == NULL || block_to_free->is_free == 1) {

    } else {
      block_to_free->is_free = 1;
      block_to_free->user_data_size = 0;

        if (block_to_free->next != NULL && block_to_free->next->is_free == 1) {
            block_to_free->user_data_size = 0;
            block_to_free->capacity += block_to_free->next->capacity;

            if (block_to_free->next->next != NULL) {
                block_to_free->next->next->prev = block_to_free;
            }
            block_to_free->next = block_to_free->next->next;
        }
        if (block_to_free->prev != NULL && block_to_free->prev->is_free == 1) {
            block_to_free->prev->is_free = 0;
            free(block_to_free->prev + 1);
        }
    }
}

void*
malloc(uint size)
{
    block_t *curr_block = NULL;
    block_t *list_location = NULL;
    void *ret = NULL;
    int temp_user_size = 0;
    int temp_capacity = 0;

    if (top_heap == NULL) {
        top_heap = (int*) sbrk(0);
    }

    if (size == 0 || size == (uint) NULL) {
        ret = NULL;
    } else {
        if (size < 30) {
            temp_capacity = 30;
        } else {
            temp_capacity = size;
        }

        temp_user_size = size;
        
        list_location = head;
        if (first_fit == 1) {
            curr_block = NULL;
            while (list_location) {
                if (list_location->is_free == 1 && list_location->capacity >= temp_capacity) {
                    break;
                }
                curr_block = list_location;
                list_location = list_location->next;
            }

            if (list_location && list_location->capacity > ((size + HDR_SIZE) + (HDR_SIZE + MIN_DATA_SIZE))) {
                block_t *split_block = NULL;
                split_block = (((void *) list_location) + HDR_SIZE + temp_capacity);
                split_block->is_free = 1;
                split_block->user_data_size = 0;
                split_block->capacity = (list_location->capacity - temp_user_size - HDR_SIZE);

                split_block->prev = list_location;
                split_block->next = list_location->next;
                if (list_location->next != NULL) {
                    list_location->next->prev = split_block;
                }
                list_location->next = split_block;
            }

            if (list_location == NULL) {
                list_location = (block_t*) sbrk(sizeof(block_t) + size);
                list_location->prev = curr_block;
                list_location->next = NULL;
            }

            if (curr_block == NULL) {
                head = list_location;
            } else {
                curr_block->next = list_location;
            }
        }

        list_location->is_free = 0;
        list_location->user_data_size = temp_user_size;
        list_location->capacity = temp_capacity;

        ret = (list_location + 1);
    }

    return ret;
}

void heapreset(void) 
{
    if (top_heap != NULL) {
        brk((int) top_heap);
    }

    head = NULL;
    top_heap = NULL;
}

void heapdump(ushort leaks_only)
{
    block_t *curr = NULL;
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
            , "data add  "

            , "blk off  "
            , "dat off  "
            , "capacity "
            , "bytes usd"
            , "blk size "
            , "status   "
        );
    for (curr = head, i = 0; curr != NULL; curr = curr->next, i++) {
        if (leaks_only == FALSE || (leaks_only == TRUE && curr->is_free == FALSE)) {
            printf(1,
                   "  %u\t\t%p\t\t%p\t\t%p\t\t%p\t\t%u\t\t%u\t\t"
                   "%u\t\t%u\t\t%u\t\t%s\t%c\n"
                   , i
                   , curr
                   , curr->next
                   , curr->prev
                   , (((void *) curr) + sizeof(block_t))
                   , ((void *) (((void *)curr) - (void *) top_heap))
                   , ((void *) ((void *)curr + sizeof(block_t)) - (void *) top_heap)
                   , (unsigned long) curr->capacity, (unsigned long) curr->user_data_size
                   , curr->capacity + sizeof(block_t)
                   , curr->is_free ? "free  " : "in use"
                   , curr->is_free ? '*' : ' '
              );
            user_bytes += curr->user_data_size;
            capacity_bytes += curr->capacity;
            block_bytes += curr->capacity + sizeof(block_t);
            if (curr->is_free == FALSE && leaks_only == TRUE) {
                leak_count++;
            }
            if (curr->is_free == TRUE) {
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
             , (((void *)curr) - (void *) top_heap), sbrk(0)
        );
    }
}


void heapdump(ushort leaks_only)
{
    struct block_list *curr = NULL;
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
    for (curr = block_list, i = 0; curr != NULL; curr = curr->next, i++) {
        if (leaks_only == FALSE || (leaks_only == TRUE && curr->free == FALSE)) {
            printf(1,
                   "  %u\t\t%p\t\t%p\t\t%p\t\t%p\t\t%u\t\t%u\t\t"
                   "%u\t\t%u\t\t%u\t\t%s\t%c\n"
                   , i
                   , curr
                   , curr->next
                   , curr->prev
                   , curr->data
                   , ((void *) curr - lower_mem_bound)
                   , ((void *) curr->data - lower_mem_bound)
                   , (unsigned long) curr->capacity, (unsigned long) curr->size
                   , curr->capacity + sizeof(struct block_list)
                   , curr->free ? "free  " : "in use"
                   , curr->free ? '*' : ' '
              );
            user_bytes += curr->size;
            capacity_bytes += curr->capacity;
            block_bytes += curr->capacity + sizeof(struct block_list);
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
             , lower_mem_bound, upper_mem_bound
        );
    }
}

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

//#define NDEBUG
#include <assert.h>

#include "beavalloc.h"

extern char end, etext, edata;

int main(int argc, char **argv)
{
    uint8_t isVerbose = FALSE;
    char *base = NULL;

    {
        int opt = -1;

        while ((opt = getopt(argc, argv, "hvbfnws")) != -1) {
            switch (opt) {
            case 'h':
                break;
            case 'b':
                beavalloc_set_algorithm(BEST_FIT);
                break;
            case 'f':
                beavalloc_set_algorithm(FIRST_FIT);
                break;
            case 'n':
                beavalloc_set_algorithm(NEXT_FIT);
                break;
            case 'w':
                beavalloc_set_algorithm(WORST_FIT);
                break;
            case 'v':
                isVerbose = isVerbose;
                beavalloc_set_verbose(TRUE);
                fprintf(stderr, "Verbose enabled\n");
                break;
            default: /* '?' */
                fprintf(stderr, "%s\n", argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }
    base = sbrk(0);
    {
#define NUM_PTRS 10000
        void *ptrs[NUM_PTRS];
        int i = 0;
        char *ptr1 = NULL;

        fprintf(stderr, "Begin 12\n");
        for (i = 0; i < NUM_PTRS; i++) {
            ptrs[i] = beavalloc(i * 10);
        }

        for (i = 0; i < NUM_PTRS; i += 2) {
            beavfree(ptrs[i]);
        }

        for (i = 1; i < NUM_PTRS; i++) {
            beavfree(ptrs[i]);
        }

        beavalloc_walk();
        beavalloc_info();

        for (i = 0; i < NUM_PTRS; i++) {
            ptrs[i] = beavalloc(i * 2);
        }
        beavalloc_info();
        for (i = 1; i < NUM_PTRS; i++) {
            beavfree(ptrs[i]);
        }
        beavalloc_walk();

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);

        fprintf(stderr, "End 12\n");
    }
    {
        char *ptr1 = NULL;
        void *ptrs[NUM_PTRS];
        int i;

        fprintf(stderr, "Begin 13\n");
        ptr1 = beavalloc(100000);

        beavalloc_walk();

        beavfree(ptr1);
        beavalloc_walk();

        for (i = 0; i < NUM_PTRS; i++) {
            ptrs[i] = beavalloc(i + 10);
        }

        for (i = 0; i < NUM_PTRS; i++) {
            beavfree(ptrs[i]);
        }

        beavalloc_walk();
        beavalloc_info();
        beavalloc_leaks();

        beavalloc_reset();
        ptr1 = sbrk(0);
        assert(ptr1 == base);
        fprintf(stderr, "End 13\n");
    }

#ifdef OLD_TESTS
    {
        char *ptr1 = NULL;
        char *ptr2 = NULL;
        char *ptr3 = NULL;

        if (isVerbose) {
            fprintf(stderr, "Begin test1\n");
        }
        beavalloc_walk();

        //printf("end : %p\n", &end);
        //printf("etext: %p\n", &etext);
        //printf("edata: %p\n", &edata);

        //ptr1 = beavalloc(0);
        //printf("ptr : %p\n", ptr);

        ptr1 = beavalloc(10);
        beavalloc_reset();        //printf("ptr : %p\n", ptr);
        //memset(ptr, 0, 10);

        ptr2 = beavalloc(100);
        //printf("ptr : %p\n", ptr);
        //memset(ptr, 0, 100);

        ptr3 = beavalloc(50);
        printf("ptr3 : %p\n", ptr3);
        //memset(ptr, 0, 50);

        beavalloc_walk();

        //beavfree(ptr2);
        //beavalloc_walk();

        beavfree(NULL);
        beavfree(ptr1);
        beavfree(ptr1);
        //beavalloc_walk();

        beavfree(ptr3);
        //beavalloc_walk();

        ptr1 = beavalloc(15);
        printf("ptr : %p\n", ptr1);
        //memset(ptr, 0, 75);

        ptr2 = beavalloc(3000);
        printf("ptr : %p\n", ptr2);
        //memset(ptr, 0, 3000);

        beavalloc_info();
        beavalloc_walk();
        
        //beavfree(ptr1);
        //beavfree(ptr2);

        beavalloc_leaks();

        beavalloc_reset();
        ptr1 = sbrk(0);

        printf("These should be the same after a call to beavalloc_reset()\n");
        printf("    base: %p\n", base);
        printf("    ptr : %p\n", ptr1);
    }
#endif // OLD_TESTS
    return 0;
}

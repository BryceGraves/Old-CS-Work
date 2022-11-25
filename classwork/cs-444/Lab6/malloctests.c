#include "types.h"
#include "user.h"

#define NUM_PTRS 100

int
main(int argc, char *argv[])
{
  char *base = NULL;
  int test_number = 0;

  if (argc > 1) {
    test_number = atoi(argv[1]);
  }

  printf(1, "malloctests starting\n");
  if (test_number == 0) {
    printf(1, "  running all tests\n");
  }
  else {
    printf(1, "  running only test %d\n", test_number);
  }

  base = sbrk(0);
  printf(1, "base: %x\n", base);
  if (test_number == 0 || test_number == 1) {
    char *ptr1 = NULL;

    printf(1, "*** Begin %d\n", 1);
    printf(1, "      Basic reset\n");

    heapreset();
    ptr1 = sbrk(0);
    printf(1, "  ptr : %p\n", base);
    assert(ptr1 == base);

    heapreset();
    ptr1 = sbrk(0);
    printf(1, "  ptr : %p\n", base);
    assert(ptr1 == base);

    printf(1, "*** End %d\n", 1);
  }
  if (test_number == 0 || test_number == 2) {
    char *ptr1 = NULL;

    printf(1, "*** Begin %d\n", 2);
    printf(1, "      zero bytes\n");

    ptr1 = malloc(0);
    assert(ptr1 == NULL);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);
    printf(1, "*** End %d\n", 2);
  }
  if (test_number == 0 || test_number == 3) {
    char *ptr1 = NULL;

    printf(1, "*** Begin %d\n", 3);
    printf(1, "      10 bytes\n");

    ptr1 = malloc(10);
    assert(ptr1 != NULL);
    
    heapreset();

    ptr1 = sbrk(0);
    assert(ptr1 == base);
    printf(1, "*** End %d\n", 3);
  }
  //exit();
  if (test_number == 0 || test_number == 4) {
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    char *ptr4 = NULL;
    char *ptr5 = NULL;

    printf(1, "*** Begin %d\n", 4);
    printf(1, "      5 allocs\n");

    ptr1 = malloc(10);
    heapdump(FALSE);

    ptr2 = malloc(30);
    heapdump(FALSE);

    ptr3 = malloc(50);
    heapdump(FALSE);

    ptr4 = malloc(70);
    heapdump(FALSE);

    ptr5 = malloc(90);
    heapdump(FALSE);

    printf(1, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
            , ptr1, ptr2, ptr3, ptr4, ptr5);

    heapdump(FALSE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);
    printf(1, "*** End %d\n", 4);
  }

  if (test_number == 0 || test_number == 5) {
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    char *ptr4 = NULL;
    char *ptr5 = NULL;

    printf(1, "*** Begin %d\n", 5);
    printf(1, "      5 allocs 3 frees\n");
    ptr1 = malloc(10);
    ptr2 = malloc(30);
    ptr3 = malloc(50);
    ptr4 = malloc(70);
    ptr5 = malloc(90);

    printf(1, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
            , ptr1, ptr2, ptr3, ptr4, ptr5);

    heapdump(FALSE);

    free(ptr1);
    free(ptr3);
    free(ptr5);

    heapdump(FALSE);
    heapdump(TRUE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);
    printf(1, "*** End %d\n", 5);
  }
  if (test_number == 0 || test_number == 6) {
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    char *ptr4 = NULL;
    char *ptr5 = NULL;

    printf(1, "*** Begin %d\n", 6);
    printf(1, "      5 allocs 2 frees\n");

    ptr1 = malloc(10);
    ptr2 = malloc(30);
    ptr3 = malloc(50);
    ptr4 = malloc(70);
    ptr5 = malloc(90);

    printf(1, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
            , ptr1, ptr2, ptr3, ptr4, ptr5);

    heapdump(FALSE);

    free(ptr2);
    free(ptr4);

    heapdump(FALSE);
    heapdump(TRUE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);
    printf(1, "*** End %d\n", 6);
  }
  if (test_number == 0 || test_number == 7) {
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    char *ptr4 = NULL;
    char *ptr5 = NULL;

    printf(1,"*** Begin %d\n", 7);
    printf(1,"      begin coalesce\n");

    ptr1 = malloc(10);
    ptr2 = malloc(30);
    ptr3 = malloc(50);
    ptr4 = malloc(70);
    ptr5 = malloc(90);

    heapdump(FALSE);

    free(ptr2);
    free(ptr4);

    heapdump(FALSE);

    free(ptr1);

    heapdump(FALSE);

    free(ptr5);

    heapdump(FALSE);

    free(ptr3);

    heapdump(FALSE);
    heapdump(TRUE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);
    printf(1,"*** End %d\n", 7);
  }
  if (test_number == 0 || test_number == 8) {
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    char *ptr4 = NULL;
    char *ptr5 = NULL;

    printf(1, "*** Begin %d\n", 8);
    printf(1, "      memset\n");

    ptr1 = malloc(1000);
    ptr2 = malloc(3000);
    ptr3 = malloc(5000);
    ptr4 = malloc(7000);
    ptr5 = malloc(10000);

    printf(1, "  ptr1 : %p\n  ptr2 : %p\n  ptr3 : %p\n  ptr4 : %p\n  ptr5 : %p\n"
            , ptr1, ptr2, ptr3, ptr4, ptr5);

    heapdump(FALSE);

    memset(ptr1, 0, 1000);
    memset(ptr2, 0, 3000);
    memset(ptr3, 0, 5000);
    memset(ptr4, 0, 7000);
    memset(ptr5, 0, 10000);

    heapdump(FALSE);

    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    free(ptr5);

    heapdump(FALSE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);
    printf(1, "*** End %d\n", 8);
  }
  if (test_number == 0 || test_number == 9) {
    char *ptr1 = NULL;

    printf(1, "*** Begin %d\n", 9);
    printf(1, "      split and coalesce\n");

    ptr1 = malloc(10000);
    heapdump(FALSE);
    free(ptr1);
    heapdump(FALSE);

    // should cause a split
    ptr1 = malloc(100);

    heapdump(FALSE);

    // coalesce right
    free(ptr1);
    heapdump(FALSE);

    heapdump(TRUE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);

    printf(1, "*** End %d\n", 9);
  }
  if (test_number == 0 || test_number == 10) {
    const ushort num_ptrs = NUM_PTRS;
    void *ptrs[num_ptrs];
    int i = 0;
    char *ptr1 = NULL;

    printf(1, "*** Begin %d\n", 10);
    printf(1, "      stress 1\n");

    for (i = 0; i < num_ptrs; i++) {
      ptrs[i] = malloc(i + 10);
    }

    for (i = 2; i < num_ptrs; i += 4) {
      free(ptrs[i]);
    }

    for (i = 3; i < num_ptrs; i += 4) {
      free(ptrs[i]);
    }

    for (i = 1; i < num_ptrs; i += 4) {
      free(ptrs[i]);
    }
    for (i = 0; i < num_ptrs; i += 4) {
      free(ptrs[i]);
    }

    heapdump(FALSE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);

    printf(1, "*** End %d\n", 10);
  }
  if (test_number == 0 || test_number == 11) {
    const ushort num_ptrs = NUM_PTRS;
    void *ptrs[num_ptrs];
    int i = 0;
    char *ptr1 = NULL;

    printf(1, "*** Begin %d\n", 11);
    printf(1, "      stress 2\n");

    for (i = 0; i < num_ptrs; i++) {
      ptrs[i] = malloc(i + 10);
    }

    for (i = 3; i < num_ptrs; i += 4) {
      free(ptrs[i]);
    }

    for (i = 2; i < num_ptrs; i += 4) {
      free(ptrs[i]);
    }

    for (i = 1; i < num_ptrs; i += 4) {
      free(ptrs[i]);
    }
    for (i = 0; i < num_ptrs; i += 4) {
      free(ptrs[i]);
    }

    heapdump(FALSE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);

    printf(1, "*** End %d\n", 11);
  }
  if (test_number == 0 || test_number == 12) {
    const ushort num_ptrs = NUM_PTRS;
    void *ptrs[num_ptrs];
    int i = 0;
    char *ptr1 = NULL;

    printf(1, "*** Begin %d\n", 12);
    printf(1, "      stress 3\n");

    for (i = 0; i < num_ptrs; i++) {
      ptrs[i] = malloc(i + 10);
    }
    printf(1, "*** malloc num_ptrs\n");
    
    for (i = 0; i < num_ptrs; i ++) {
      free(ptrs[i]);
    }
    printf(1, "*** free num_ptrs\n");
    heapdump(FALSE);

    for (i = 0; i < num_ptrs; i ++) {
      printf(1, "*** inside second malloc\n");
      ptrs[i] = malloc(i + 10);
    }
    printf(1, "*** second malloc num_ptrs\n");
    
    for (i = 0; i < num_ptrs; i ++) {
      free(ptrs[i]);
    }
    printf(1, "*** second free num_ptrs\n");

    heapdump(FALSE);

    heapreset();
    ptr1 = sbrk(0);
    assert(ptr1 == base);

    printf(1, "*** End %d\n", 12);
  }

  printf(1, "\n\nWoooooooHooooooo!!! Tests done and you survived.\n\n\n");

  exit();
}

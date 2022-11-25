#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "primesMT.h"

unsigned long numThreads = 1, upperLimit = 10240;
BitBlock_t *dataBlock;

void *nullifyBitsOfMultiple(void *arg) {
  unsigned long startingPosition = *((unsigned long *) arg), currentIndex, i;
  free(arg);

  for (i = startingPosition; i < upperLimit; i += numThreads) {
    if (!TestBit(dataBlock[i / 32].bits, i % 32)) {
      for (currentIndex = (i + i); currentIndex < upperLimit; currentIndex += i) {
        pthread_mutex_lock(&dataBlock[currentIndex / 32].mutex);
        SetBit(dataBlock[currentIndex / 32].bits, currentIndex % 32);
        pthread_mutex_unlock(&dataBlock[currentIndex / 32].mutex);
      }
    }
  }

  pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  unsigned long i = 0, numberOfBitBlocks, startingPosition = 3, tid;
  int opt, vflag = 0;
  pthread_t *wthreads = NULL;

  while ((opt = getopt(argc, argv, "hvt:u:")) != -1) {
    switch(opt) {
      case 'h':
        printf("THAR BE NO HELP.\n");
        return(EXIT_SUCCESS);

      case 'v':
        vflag = 1;
        fprintf(stderr, "Verbose Mode Enabled\n");
        break;

      case 't':
        numThreads = (unsigned long) atol(optarg);
        fprintf(stderr, "Number of threads set to: %ld\n", numThreads);
        break;

      case 'u':
        upperLimit = (unsigned long) atol(optarg);
        fprintf(stderr, "Upper bound set to: %ld\n", upperLimit);
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        exit(1);
    }
  }

  numberOfBitBlocks = (upperLimit / 32) + 1;
  wthreads = calloc(numThreads, sizeof(pthread_t));
  dataBlock = malloc(sizeof(BitBlock_t) * numberOfBitBlocks);

  for (i = 0; i < numberOfBitBlocks; i++) {
    dataBlock[i].bits = 0;
    pthread_mutex_init(&dataBlock[i].mutex, NULL);
    if (vflag) {
      fprintf(stderr, "Building dataBlock.data number: %ld!\n", i + 1);
    }
  }

  for (tid = 0; tid < numThreads; tid++) {
    unsigned long *arg = malloc(sizeof(*arg));
    *arg = startingPosition;
    pthread_create(&wthreads[tid], NULL, nullifyBitsOfMultiple, arg);
    startingPosition += 2;
  }

  for (tid = 0; tid < numThreads; tid++) {
    pthread_join(wthreads[tid], NULL);
  }

  printf("%d\n", 2);
  for (i = 3; i < upperLimit; i += 2) {
    if (!TestBit(dataBlock[i / 32].bits, i % 32)) {
      printf("%ld\n", i);
    }
  }

  for (i = 0; i < numberOfBitBlocks; i++) {
    pthread_mutex_destroy(&dataBlock[i].mutex);
  }

  free(dataBlock);
  free(wthreads);

  return EXIT_SUCCESS;
}

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file_struct.h"
#include "file_index.h"

int compareId(const void *, const void *);

int compareId(const void *p1, const void *p2) {
  file_index_t *t1 = (file_index_t *) p1;
  file_index_t *t2 = (file_index_t *) p2;
  return strcmp(t1->id, t2->id);
}

int main(int argc, char *argv[]) {
  // Sad Variables
  int inputFile = STDIN_FILENO, outputFile=STDOUT_FILENO, opt = 0, oflag = 0, iflag = 0, vflag = 0, numberOfIndexes = 0;
  file_index_t *indexArray, *outputContainer = malloc(sizeof(file_index_t));
  file_struct_t *inputContainer = malloc(sizeof(file_struct_t));
  struct stat fileStat;
  unsigned currentSize = 0;
  off_t currentIndex = 0;
  // End of Sad Variables

  // Pull each opt out with getopt and do what we need to with it
  while ((opt = getopt(argc, argv, "hvi:o:")) != -1) {
    switch(opt) {
      case 'h':
        printf("THAR BE NO HELP.\n");
        return(EXIT_SUCCESS);

      case 'v':
        vflag = 1;
        fprintf(stderr, "Verbose Mode Enabled\n");
        break;

      case 'i':
        iflag = 1;
        inputFile = open(optarg, O_RDONLY);

        if (inputFile == -1) {
          perror("Thar be no file!\n");
          free(inputContainer);
          free(outputContainer);
          exit(2);
        }
        break;

      case 'o':
        oflag = 1;
        outputFile = open(optarg, O_WRONLY);

        if (outputFile == -1) {
          perror("Thar be no file!\n");
          free(inputContainer);
          free(outputContainer);
          exit(3);
        }
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        exit(1);
    }
  }

  fstat(inputFile, &fileStat);
  numberOfIndexes = fileStat.st_size / sizeof(file_struct_t);

  indexArray = malloc(sizeof(file_index_t) * numberOfIndexes);

  while (read(inputFile, inputContainer, sizeof(file_struct_t)) > 0) {
    strcpy(outputContainer->id, inputContainer->id);
    outputContainer->offset = currentIndex;
    memcpy(&indexArray[currentSize], outputContainer, sizeof(file_index_t));

    if (vflag == 1) {
      fprintf(stderr, "Processing ID: %s\n", inputContainer->id);
    }

    memset(inputContainer, 0, sizeof(file_struct_t));
    memset(outputContainer, 0, sizeof(file_index_t));

    currentIndex += sizeof(file_struct_t);
    currentSize++;
  }

  qsort(indexArray, currentSize, sizeof(file_index_t), compareId);
  write(outputFile, indexArray, sizeof(file_index_t) * (currentSize));

  if (iflag == 1) {
    close(inputFile);
  }

  if (oflag == 1) {
    close(outputFile);
  }

  free(indexArray);
  free(inputContainer);
  free(outputContainer);

  // Time to go home boiz
  return(EXIT_SUCCESS);
}

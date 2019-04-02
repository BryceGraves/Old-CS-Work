#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    char **raggyArray = NULL, *bufferPointer = NULL, fileBuffer[MAX_LINE_LENGTH];
    unsigned currentSize = 0;
    FILE *inputFile = stdin;

    while ((bufferPointer = fgets(fileBuffer, MAX_LINE_LENGTH, inputFile)) != NULL) {
      raggyArray = realloc(raggyArray, (currentSize + 1) * sizeof(char*));
      raggyArray[currentSize++] = strdup(fileBuffer);
    }

    for (i = 0; i < currentSize; i++) {
      printf("%04d:  %s", i+1, raggyArray[i]);
    }

    for (i = 0; i < currentSize; i++) {
      free(raggyArray[i]);
    }
    free(raggyArray);
    return(EXIT_SUCCESS);
}

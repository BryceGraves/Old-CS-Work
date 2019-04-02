#include <stdio.h>
#include <stdlib.h>

#define true 1

int main(int argc, char *argv[]) {
  char currentLine[1025];
  int numberOfLines = atoi(argv[1]);
  FILE *inputFile = fopen(argv[2], "r");

  if (inputFile == NULL) {
    perror("Thar be no file");
    return(-1);
  }

  while (true) {
    char *currentLinePointer = fgets(currentLine, 1025, inputFile);
    if (currentLinePointer == NULL || numberOfLines <= 0) { break; }

    printf("%s", currentLinePointer);
    numberOfLines--;
  }

  fclose(inputFile);
	return(0);
}

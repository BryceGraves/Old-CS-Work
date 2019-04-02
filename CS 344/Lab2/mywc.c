#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Sad Variables
  FILE *inputFile;
  char currentLine[1025], fileName[100];
  char *currentLinePointer, *word;
  int opt = 0, cflag = 0, wflag = 0, lflag = 0, fflag = 0,
    character = 0, characterCount = 0, wordCount = 0, lineCount = 0;
  // End of Sad Variables

  // Pull each opt out with getopt and do what we need to with it
  while ((opt = getopt(argc, argv, "clwf:hv")) != -1) {
    switch(opt) {
      case 'h':
        printf("The accepted command line arguments are c, w, l, and f.\n");
        return(0);

      case 'c':
        cflag = 1;
        break;

      case 'w':
        wflag = 1;
        break;

      case 'l':
        lflag = 1;
        break;

      case 'f':
        fflag = 1;
        inputFile = fopen(optarg, "r");

        if (inputFile == NULL) {
          perror("Thar be no file!\n");
          return(-1);
        } else {
          strcpy(fileName, optarg);
        }
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        return(1);
    }
  }

  // If not input file argument is passed use stdin
  if ( fflag != 1 ) {
    inputFile = stdin;
  }

  // Check to see if any of the c, w, or l flags are in use
  // If not flip them all
  if ((cflag + wflag + lflag) == 0) {
    cflag = 1;
    wflag = 1;
    lflag = 1;
  }

  // Count characters if flag is active
  if (cflag == 1) {
    while ((character = fgetc(inputFile)) != EOF) {
      characterCount++;
    }
    rewind(inputFile);
  }

  // Count words if flag is active
  if (wflag == 1) {
    while ((currentLinePointer = fgets(currentLine, 1025, inputFile)) != NULL) {
      while ((word = strtok_r(currentLinePointer, " \n\r", &currentLinePointer)) != NULL) {
        wordCount++;
      }
    }
    rewind(inputFile);
  }

  // Count lines if flag is active
  if (lflag == 1) {
    while ((currentLinePointer = fgets(currentLine, 1025, inputFile)) != NULL) {
      if (lflag == 1) { lineCount++; }
    }
    rewind(inputFile);
  }

  // Based on active flags print out correct values or close file
  // In the future I should probably close file stream as soon as it is opened
  if (lflag == 1) { printf("%d ", lineCount); }
  if (wflag == 1) { printf("%d ", wordCount); }
  if (cflag == 1) { printf("%d ", characterCount); }
  if (fflag == 1) { printf("%s\n", fileName); fclose(inputFile); }
  else { printf("\n"); }

  // Time to go home boys
	return(0);
}

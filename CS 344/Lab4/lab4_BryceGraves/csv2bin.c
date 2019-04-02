#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "file_struct.h"

#define STREET_LEN STREEN_LEN

int main(int argc, char *argv[]) {
  // Sad Variables
  FILE *inputFile = stdin;
  char currentLine[1025];
  char *currentLinePointer, *word;
  int outputFile = STDOUT_FILENO, opt = 0, oflag = 0, iflag = 0, vflag = 0;
  file_struct_t* outputContainer = malloc(sizeof(file_struct_t));
  // End of Sad Variables

  // Pull each opt out with getopt and do what we need to with it
  while ((opt = getopt(argc, argv, "i:o:hv")) != -1) {
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
        inputFile = fopen(optarg, "r");

        if (inputFile == NULL) {
          perror("Thar be no file!\n");
          exit(2);
        }
        break;

        case 'o':
          oflag = 1;
          outputFile = open(optarg, O_WRONLY);

          if (outputFile == -1) {
            perror("Thar be no file!\n");
            exit(3);
          }
          break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        exit(1);
    }
  }

  currentLinePointer = fgets(currentLine, 1025, inputFile);

  while ((currentLinePointer = fgets(currentLine, 1025, inputFile)) != NULL) {
    memset(outputContainer, 0, sizeof(file_struct_t));
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, ID_LEN);
    if (vflag == 1) {
      fprintf(stderr, "ID: %s\n", word);
    }
    strcpy(outputContainer->id, word);
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, NAME_LEN);
    strcpy(outputContainer->fname, word);
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, NAME_LEN);
    strcpy(outputContainer->mname, word);
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, NAME_LEN);
    strcpy(outputContainer->lname, word);
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, STREET_LEN);
    strcpy(outputContainer->street, word);
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, CITY_LEN);
    strcpy(outputContainer->city, word);
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, ZIP_LEN);
    strcpy(outputContainer->zip, word);
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, COUNTRY_LEN);
    strcpy(outputContainer->country_code, word);
    word = strtok_r(currentLinePointer, ",", &currentLinePointer);
    truncate(word, EMAIL_LEN);
    strcpy(outputContainer->email, word);
    word = strtok_r(currentLinePointer, ",\n", &currentLinePointer);
    truncate(word, PHONE_LEN);
    strcpy(outputContainer->phone, word);

    write(outputFile, outputContainer, sizeof(file_struct_t));
  }

  if (iflag == 1) {
    fclose(inputFile);
  }

  if (oflag == 1) {
    close(outputFile);
  }

  free(outputContainer);
  // Time to go home boiz
	return(EXIT_SUCCESS);
}

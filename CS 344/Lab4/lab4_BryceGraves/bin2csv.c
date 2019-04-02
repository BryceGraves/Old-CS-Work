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
  FILE *outputFile = stdout;
  char ourline[1024];
  int inputFile = STDIN_FILENO, opt = 0, oflag = 0, iflag = 0, vflag = 0;
  file_struct_t* inputContainer = malloc(sizeof(file_struct_t));
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
        inputFile = open(optarg, O_RDONLY);

        if (inputFile == -1) {
          perror("Thar be no file!\n");
          free(inputContainer);
          exit(2);
        }
        break;

        case 'o':
          oflag = 1;
          outputFile = fopen(optarg, "w");

          if (outputFile == NULL) {
            perror("Thar be no file!\n");
            free(inputContainer);
            exit(3);
          }
          break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        exit(1);
    }
  }

  fwrite("id,first_name,middle_name,last_name,street,city,zip,country,email,phone\n", sizeof(char), 72, outputFile);

  while (read(inputFile, inputContainer, sizeof(file_struct_t)) > 0) {
    memset(ourline, 0, 1024);
    strcat(ourline, inputContainer->id);
    if (vflag == 1) {
      fprintf(stderr, "ID: %s\n", ourline);
    }
    strcat(ourline, ",");
    strcat(ourline, inputContainer->fname);
    strcat(ourline, ",");
    strcat(ourline, inputContainer->mname);
    strcat(ourline, ",");
    strcat(ourline, inputContainer->lname);
    strcat(ourline, ",");
    strcat(ourline, inputContainer->street);
    strcat(ourline, ",");
    strcat(ourline, inputContainer->city);
    strcat(ourline, ",");
    strcat(ourline, inputContainer->zip);
    strcat(ourline, ",");
    strcat(ourline, inputContainer->country_code);
    strcat(ourline, ",");
    strcat(ourline, inputContainer->email);
    strcat(ourline, ",");
    strcat(ourline, inputContainer->phone);
    strcat(ourline, "\n");
    fwrite(ourline, sizeof(char), strlen(ourline), outputFile);
  }

  if (iflag == 1) {
    close(inputFile);
  }

  if (oflag == 1) {
    fclose(outputFile);
  }

  free(inputContainer);

  // Time to go home boiz
	return(EXIT_SUCCESS);
}

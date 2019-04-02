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
void printAccount(int, file_struct_t *);

int compareId(const void *p1, const void *p2) {
  file_index_t *t1 = (file_index_t *) p1;
  file_index_t *t2 = (file_index_t *) p2;
  return strcmp(t1->id, t2->id);
}

void printAccount(int outputFile, file_struct_t *account) {
  dprintf(outputFile, "id: %s\n\
  first_name: %s\n\
  middle_name: %s\n\
  last_name: %s\n\
  street: %s\n\
  city: %s\n\
  zip: %s\n\
  country: %s\n\
  email: %s\n\
  phone: %s\n",\
  account->id, account->fname, account->mname, account->lname,\
  account->street, account->city, account->zip, account->country_code,\
  account->email, account->phone);
}

int main(int argc, char *argv[]) {
  // Sad Variables
  int i = 0, indexFile, inputFile, outputFile = STDOUT_FILENO, opt = 0, oflag = 0, iflag = 0, vflag = 0, Iflag = 0;
  file_struct_t *inputContainer = malloc(sizeof(file_struct_t));
  file_index_t *indexes, *currentIndex;
  struct stat fileStat;
  // End of Sad Variables

  // Pull each opt out with getopt and do what we need to with it
  while((opt = getopt(argc, argv, "hvi:o:I:")) != -1) {
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

        if(inputFile == -1) {
          perror("Thar be no file!\n");
          free(inputContainer);
          exit(EXIT_FAILURE);
        }
        break;

      case 'o':
        oflag = 1;
        outputFile = open(optarg, O_WRONLY);

        if(outputFile == -1) {
          perror("Thar be no file!\n");
          free(inputContainer);
          exit(EXIT_FAILURE);
        }
        break;

      case 'I':
        Iflag = 1;
        indexFile = open(optarg, O_RDONLY);

        if(indexFile == -1) {
          perror("Thar be no file!\n");
          free(inputContainer);
          exit(EXIT_FAILURE);
        } else {
          fstat(indexFile, &fileStat);
          indexes = malloc(fileStat.st_size);
          read(indexFile, indexes, fileStat.st_size);
        }
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        exit(1);
    }
  }

  if(iflag != 1) {
    fprintf(stderr, "%s", "The argument <-i> is required to run this program!\n");
    exit(1);
  }

  if(optind >= argc) {
    fprintf(stderr, "Expected ID after option flags!\n");
    exit(EXIT_FAILURE);
  }

  if(Iflag  == 1) {
    if(vflag == 1) {
      fprintf(stderr, "Index file given, searching data based on offsets!\n");
    }
    for(i = optind; i < argc; i++) {
      currentIndex = bsearch(argv[i], indexes, (fileStat.st_size / sizeof(file_index_t)) + 1, sizeof(file_index_t), compareId);
      if (vflag == 1) {
        fprintf(stderr, "Read offset for the ID: %s\n", currentIndex->id);
        fprintf(stderr, "The offset is: %ld\n", currentIndex->offset);
      }
      lseek(inputFile, currentIndex->offset, SEEK_SET);
      read(inputFile, inputContainer, sizeof(file_struct_t));
      printAccount(outputFile, inputContainer);
      memset(inputContainer, 0, sizeof(file_struct_t));
    }
    free(indexes);
  } else {
    if (vflag == 1) {
      fprintf(stderr, "No index file given, searching data linearly!\n");
    }
    while(read(inputFile, inputContainer, sizeof(file_struct_t)) > 0) {
      if(vflag == 1) {
        fprintf(stderr, "Read data for the ID: %s\n", inputContainer->id);
      }
      for(i = optind; i < argc; i++) {
        if(vflag == 1) {
          fprintf(stderr, "Checking data against query: %s\n", argv[i]);
        }
        if(strcmp(argv[i], inputContainer->id) == 0) {
          printAccount(outputFile, inputContainer);
          memset(inputContainer, 0, sizeof(file_struct_t));
        }
      }
    }
  }

  close(inputFile);

  if(oflag == 1) {
    close(outputFile);
  }

  free(inputContainer);

  // Time to go home boiz
  return(EXIT_SUCCESS);
}

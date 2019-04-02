#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "beavar.h"

_Bool headerIsValid(int);
void printSlimHeader(beavar_hdr_t *, int, char*);
void printThiccHeader(beavar_hdr_t *, int, char*);
void addBeavarHeaderToOutputFile(int);
void populateHeaderFromInputFile(beavar_hdr_t *, char *, struct stat);
void writeDataToArchive(char *, int, int);
void writeArchiveDataToFile(int, int, int);
void charBufferToTerminatedString(char *, char *, int);
void itoa(char *, int, int);

_Bool headerIsValid(int inputfile) {
  char fileHeader[BEAVAR_ID_LEN];
  read(inputfile, fileHeader, BEAVAR_ID_LEN);
  return strcmp(fileHeader, BEAVAR_ID) == 0;
}

void printSlimHeader(beavar_hdr_t * header, int inputFile, char * fileName) {
  char *fileNameLengthString = malloc(sizeof(char) * (BEAVAR_FNAME_LEN_SIZE + 1)),\
  *currentFileName = malloc(sizeof(char) * (BEAVAR_MAX_FILE_NAME_LEN + 1));
  int fileNameLength = 0;
  dprintf(STDOUT_FILENO, "Short table of contents for beavar archive file: %s\n", fileName);
  while (read(inputFile, header, sizeof(beavar_hdr_t)) > 0) {
    charBufferToTerminatedString(header->beavar_fname_len, fileNameLengthString, BEAVAR_FNAME_LEN_SIZE);
    fileNameLength = atoi(fileNameLengthString);
    charBufferToTerminatedString(header->beavar_fname, currentFileName, fileNameLength);
    dprintf(STDOUT_FILENO, "\t%s\n", currentFileName);
    lseek(inputFile, atoi(header->beavar_size), SEEK_CUR);

    memset(header, ' ', sizeof(beavar_hdr_t));
  }
  free(fileNameLengthString);
  free(currentFileName);
}

void printThiccHeader(beavar_hdr_t * header, int inputFile, char * fileName) {
  // Start of REALLY sad variables.
  // Shield your eyes
  char *accessTimeString = malloc(sizeof(char) * (BEAVAR_DATE_SIZE + 1)),\
  *modifyTimeString = malloc(sizeof(char) * (BEAVAR_DATE_SIZE + 1)),\
  *fileNameLengthString = malloc(sizeof(char) * (BEAVAR_FNAME_LEN_SIZE + 1)),\
  *currentFileName = malloc(sizeof(char) * (BEAVAR_MAX_FILE_NAME_LEN + 1)),\
  *uidString = malloc(sizeof(char) * (BEAVAR_UGID_SIZE + 1)),\
  *gidString = malloc(sizeof(char) * (BEAVAR_UGID_SIZE + 1)),\
  *sizeString = malloc(sizeof(char) * (BEAVAR_FILE_SIZE + 1)),\
  *modeString = malloc(sizeof(char) * (BEAVAR_MODE_SIZE + 1)),\
  permissions[10], accessDate[40], modificationDate[40];
  int chmodValue = 0, fileNameLength = 0, size = 0, mode = 0;
  time_t atime, mtime;
  struct group  *groupStuffs;
  struct passwd *userStuffs;
  dprintf(STDOUT_FILENO, "Long table of contents for beavar archive file: %s\n", fileName);
  while (read(inputFile, header, sizeof(beavar_hdr_t)) > 0) {
    charBufferToTerminatedString(header->beavar_fname_len, fileNameLengthString, BEAVAR_FNAME_LEN_SIZE);
    charBufferToTerminatedString(header->beavar_adate, accessTimeString, BEAVAR_DATE_SIZE);
    charBufferToTerminatedString(header->beavar_mdate, modifyTimeString, BEAVAR_DATE_SIZE);
    charBufferToTerminatedString(header->beavar_uid, uidString, BEAVAR_UGID_SIZE);
    charBufferToTerminatedString(header->beavar_gid, gidString, BEAVAR_UGID_SIZE);
    charBufferToTerminatedString(header->beavar_size, sizeString, BEAVAR_FILE_SIZE);

    mode = atoi(modeString);
    chmodValue = mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    fileNameLength = atoi(fileNameLengthString);
    size = atoi(sizeString);
    atime = atoi(accessTimeString);
    mtime = atoi(modifyTimeString);

    charBufferToTerminatedString(header->beavar_fname, currentFileName, fileNameLength);

    userStuffs = getpwuid((__uid_t) atoi(uidString));
    groupStuffs = getgrgid((__gid_t) atoi(gidString));

    atime = atoi(accessTimeString);
    mtime = atoi(modifyTimeString);

    strftime(accessDate, 40, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&atime));
    strftime(modificationDate, 40, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&mtime));

    chmodValue = atoi(header->beavar_mode) & (S_IRWXU | S_IRWXG | S_IRWXO);
    permissions[0] = (chmodValue & S_IRUSR) ? 'r' : '-';
    permissions[1] = (chmodValue & S_IWUSR) ? 'w' : '-';
    permissions[2] = (chmodValue & S_IXUSR) ? 'x' : '-';
    permissions[3] = (chmodValue & S_IRGRP) ? 'r' : '-';
    permissions[4] = (chmodValue & S_IWGRP) ? 'w' : '-';
    permissions[5] = (chmodValue & S_IXGRP) ? 'x' : '-';
    permissions[6] = (chmodValue & S_IROTH) ? 'r' : '-';
    permissions[7] = (chmodValue & S_IWOTH) ? 'w' : '-';
    permissions[8] = (chmodValue & S_IXOTH) ? 'x' : '-';
    permissions[9] = '\0';

    dprintf(STDOUT_FILENO, "    File name: %s\n", currentFileName);
    dprintf(STDOUT_FILENO, "\tFile size:  %s\n", sizeString);
    dprintf(STDOUT_FILENO, "\tPermissions: %s       (%d)\n", permissions, chmodValue);
    dprintf(STDOUT_FILENO, "\tFile owner:  %s         (uid: %d)\n", userStuffs->pw_name, atoi(uidString));
    dprintf(STDOUT_FILENO, "\tFile group:  %s         (gid: %d)\n", groupStuffs->gr_name, atoi(uidString));
    dprintf(STDOUT_FILENO, "\tAccess date: %s %s\n", accessDate, accessTimeString);
    dprintf(STDOUT_FILENO, "\tModify date: %s %s\n", modificationDate, modifyTimeString);
    lseek(inputFile, size, SEEK_CUR);
    memset(header, ' ', sizeof(beavar_hdr_t));
  }

  free(accessTimeString);
  free(modifyTimeString);
  free(fileNameLengthString);
  free(currentFileName);
  free(uidString);
  free(gidString);
  free(sizeString);
  free(modeString);
}

void addBeavarHeaderToOutputFile(int outputFile) {
  write(outputFile, BEAVAR_ID, BEAVAR_ID_LEN);
}

void populateHeaderFromInputFile(beavar_hdr_t *header, char *file, struct stat fileStat) {
  memset(header, ' ', sizeof(beavar_hdr_t));
  strncpy(header->beavar_fname, file, strlen(file));
  itoa(header->beavar_fname_len, strlen(file), 1);
  itoa(header->beavar_adate, fileStat.st_atime, 9);
  itoa(header->beavar_mdate, fileStat.st_mtime, 9);
  itoa(header->beavar_uid, fileStat.st_uid, 5);
  itoa(header->beavar_gid, fileStat.st_gid, 5);
  itoa(header->beavar_mode, fileStat.st_mode, 6);
  itoa(header->beavar_size, fileStat.st_size, 11);
  strcpy(header->beavar_hdr_end, BEAVAR_HDR_END);
}

void writeDataToArchive(char * inputFile, int fileSize, int outputFile) {
  char *dataFromFile = malloc(sizeof(char) * fileSize);
  int fileDescriptor = open(inputFile, O_RDONLY);
  read(fileDescriptor, dataFromFile, fileSize);
  write(outputFile, dataFromFile, fileSize);
  free(dataFromFile);
  close(fileDescriptor);
}

void writeArchiveDataToFile(int inputFile, int fileSize, int outputFile) {
  char *dataFromFile = malloc(sizeof(char) * fileSize);
  read(inputFile, dataFromFile, fileSize);
  write(outputFile, dataFromFile, fileSize);
  free(dataFromFile);
}

void charBufferToTerminatedString(char * charArray, char * newString, int size) {
  memset(newString, 0, size);
  strncpy(newString, charArray, size);
}

void itoa(char *valueAsCharArray, int value, int sizeOfArray) {
  while (value > 0) {
    valueAsCharArray[sizeOfArray] = (value % 10) + '0';
    value /= 10;
    sizeOfArray--;
  }
}

int main(int argc, char *argv[]) {
  // Sad Variables
  char version[] = "1.0.0",\
  *fileNameLengthString = malloc(sizeof(char) * (BEAVAR_FNAME_LEN_SIZE + 1)),\
  *currentFileName = malloc(sizeof(char) * (BEAVAR_MAX_FILE_NAME_LEN + 1));
  int i = 0, fileNameLength = 0, flagCount = 0, inputFile, outputFile=STDOUT_FILENO,\
  opt = 0, aflag = 0, eflag = 0, vflag = 0;
  beavar_hdr_t *currentFileHeader = malloc(sizeof(beavar_hdr_t));
  struct stat fileStat;
  // End of Sad Variables

  // Pull each opt out with getopt and do what we need to with it
  while ((opt = getopt(argc, argv, "a:e:ht:T:vV")) != -1) {
    switch (opt) {
      case 'a':
        aflag = 1;
        flagCount++;
        outputFile = open(optarg, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

      if (inputFile == -1) {
        perror("Thar be no file!\n");
        close(outputFile);
        exit(BEAVAR_FILE_COULD_NOT_OPEN);
      } else {
        strcpy(currentFileHeader->beavar_fname, optarg);
      }
      break;

      case 'e':
        eflag = 1;
        flagCount++;
        inputFile = open(optarg, O_RDONLY);

        if (outputFile == -1) {
          perror("Thar be no file!\n");
          close(inputFile);
          close(outputFile);
          exit(BEAVAR_FILE_COULD_NOT_OPEN);
        }
        break;

      case 'h':
        printf("THAR BE NO HELP.\n");
        exit(EXIT_SUCCESS);

      case 't':
        inputFile = open(optarg, O_RDONLY);
        if (headerIsValid(inputFile)) {
          printSlimHeader(currentFileHeader, inputFile, optarg);
        } else {
          fprintf(stderr, "%s", "The archive file passed is corrupt!!!\n");
          exit(BEAVAR_FILE_CORRUPT);
        }
        free(fileNameLengthString);
        free(currentFileName);
        free(currentFileHeader);
        close(inputFile);
        close(outputFile);
        exit(EXIT_SUCCESS);

      case 'T':
        inputFile = open(optarg, O_RDONLY);
        if (headerIsValid(inputFile)) {
          printThiccHeader(currentFileHeader, inputFile, optarg);
        } else {
          fprintf(stderr, "%s", "The archive file passed is corrupt!!!\n");
        }
        free(fileNameLengthString);
        free(currentFileName);
        free(currentFileHeader);
        close(inputFile);
        close(outputFile);
        return(EXIT_SUCCESS);

      case 'v':
        vflag = 1;
        fprintf(stderr, "Verbose Mode Enabled\n");
        break;

      case 'V':
        printf("Beavar Version: %s\n", version);
        exit(EXIT_SUCCESS);

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        exit(EXIT_FAILURE);
        free(currentFileHeader);
    }
  }

  if (vflag == 1) {
    fprintf(stderr, "Checking for the correct amount of flags!\n");
  }

  if (flagCount <= 0 || flagCount >= 2) {
    fprintf(stderr, "More than one argument option used!\nUse only a or only e!\n");
    exit(EXIT_FAILURE);
  }

  if (vflag == 1) {
    fprintf(stderr, "Checking that there are the correct number things for the current mode!\n");
  }

  if (optind >= argc) {
    if (aflag == 1) {
      fprintf(stderr, "Expected files to be passed when a option is used!\n");
      exit(EXIT_FAILURE);
    }
  } else if (optind != argc) {
    if (eflag == 1) {
      fprintf(stderr, "Extra files are not required when using extract function!\n");
      exit(EXIT_FAILURE);
    }
  }

  if (aflag == 1) {
    if (vflag == 1) {
      fprintf(stderr, "Adding beavar header to output file if file is a fresh archive\n");
    }

    fstat(outputFile, &fileStat);

    if (fileStat.st_size == 0) {
      addBeavarHeaderToOutputFile(outputFile);
    }

    for (i = optind; i < argc; i++) {
      if (vflag == 1) {
        fprintf(stderr, "Reading system info of file!\n");
      }

      stat(argv[i], &fileStat);

      if (vflag == 1) {
        fprintf(stderr, "Populating header from info collected!\n");
      }

      populateHeaderFromInputFile(currentFileHeader, argv[i], fileStat);

      if (vflag == 1) {
        fprintf(stderr, "Writing the header to archive!\n");
      }

      write(outputFile, currentFileHeader, sizeof(beavar_hdr_t));

      if (vflag == 1) {
        fprintf(stderr, "Writing file data to archive!\n");
      }

      writeDataToArchive(argv[i], atoi(currentFileHeader->beavar_size), outputFile);
    }
  }

  if (eflag == 1) {
    if (vflag == 1) {
      fprintf(stderr, "Checking if beavar file is corrupt!\n");
    }
    if (headerIsValid(inputFile)) {
      if (vflag == 1) {
        fprintf(stderr, "Whew, it is not!\n");
      }

      while (read(inputFile, currentFileHeader, sizeof(beavar_hdr_t)) > 0) {
        if (vflag == 1) {
          fprintf(stderr, "Read header of archived file!\n");
        }

        charBufferToTerminatedString(currentFileHeader->beavar_fname_len, fileNameLengthString, BEAVAR_FNAME_LEN_SIZE);

        if (vflag == 1) {
          fprintf(stderr, "Retrieving filename from the header for use!\n");
        }

        fileNameLength = atoi(fileNameLengthString);
        charBufferToTerminatedString(currentFileHeader->beavar_fname, currentFileName, fileNameLength);

        if (vflag == 1) {
          fprintf(stderr, "Creating file from header infos!\n");
        }

        outputFile = open(currentFileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

        if (vflag == 1) {
          fprintf(stderr, "Writing the archived data to new file!\n");
        }

        writeArchiveDataToFile(inputFile, atoi(currentFileHeader->beavar_size), outputFile);

        if (vflag == 1) {
          fprintf(stderr, "Clearing data buffer and heading back for more!\n");
        }

        memset(currentFileHeader, ' ', sizeof(beavar_hdr_t));
      }
    } else {
      fprintf(stderr, "%s", "The archive file passed is corrupt!!!\n");
    }
    close(inputFile);
  }
  free(currentFileHeader);
  free(currentFileName);
  free(fileNameLengthString);
  close(outputFile);
}

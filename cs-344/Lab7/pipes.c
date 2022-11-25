#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "pipes.h"

void addCommandToPipe(pipeListType *list, char *command[]) {
  int i = 0;
  pipeNodeType *newCommand = (pipeNodeType *)malloc(sizeof(pipeNodeType));
  newCommand->next = NULL;
  memset(newCommand->command, 0, sizeof(char *) * MAX_STR_LEN);

  while (command[i] != NULL) {
    newCommand->command[i] = strdup(command[i]);
    i++;
  }

  if (list->head == NULL) {
    list->head = newCommand;
    list->tail = newCommand;
  } else {
    list->tail->next = newCommand;
    list->tail = newCommand;
  }
}

void freePipeline(pipeListType *list) {
  pipeNodeType *currentNode = list->head;
  pipeNodeType *temp;

  while (currentNode != NULL) {
    temp = currentNode->next;
    freeCharPointerArray(currentNode->command);
    free(currentNode);
    currentNode = temp;
  }
  free(list);
}

void freeCharPointerArray(char *ourList[]) {
  int i = 0;
  while (ourList[i] != NULL) {
    free(ourList[i]);
    i++;
  }
}

void printPipeLine(pipeListType *list) {
  pipeNodeType *temp = list->head;
  int i = 0;

  while (temp != NULL) {
    i = 0;
    while (temp->command[i] != NULL) {
      printf("%s\n", temp->command[i]);
      i++;
    }
    temp = temp->next;
  }
}

void pipeline(pipeListType *list) {
  pipeNodeType *currentCommand = list->head;
  int pipeEnds[2];
  pid_t pid;
  int previousPipe = STDIN_FILENO;

  while (currentCommand != NULL) {
    pipe(pipeEnds);
    if ((pid = fork()) == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == STDIN_FILENO) {
      dup2(previousPipe, STDIN_FILENO);
      if (currentCommand->next != NULL) {
        dup2(pipeEnds[STDOUT_FILENO], STDOUT_FILENO);
      }
      close(pipeEnds[STDIN_FILENO]);
      execvp(currentCommand->command[STDIN_FILENO], currentCommand->command);
      exit(EXIT_FAILURE);
    } else {
      wait(NULL);
      close(pipeEnds[STDOUT_FILENO]);
      previousPipe = pipeEnds[STDIN_FILENO];
      currentCommand = currentCommand->next;
    }
  }
}

int main(int argc, char *argv[]) {
  char linesToPrint[] = "10";
  int opt;
  pipeListType *ourList = (pipeListType *)malloc(sizeof(pipeListType));
  ourList-> head = ourList->tail = NULL;

  while ((opt = getopt(argc, argv, "n:")) != -1) {
    switch(opt) {
      case 'n':
        strcpy(linesToPrint, optarg);
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        return(EXIT_FAILURE);
    }
  }

  addCommandToPipe(ourList, (char*[]){"ls", NULL});
  addCommandToPipe(ourList, (char*[]){"xargs", "du", "-s", NULL});
  addCommandToPipe(ourList, (char*[]){"sort", "-nr", NULL});
  addCommandToPipe(ourList, (char*[]){"head", "-n", linesToPrint, NULL});
  // printPipeLine(ourList);

  pipeline(ourList);

  freePipeline(ourList);

  return (EXIT_SUCCESS);
}

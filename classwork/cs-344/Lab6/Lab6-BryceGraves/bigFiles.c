#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void pipeline(char ***);

void pipeline(char ***currentCommand) {
  int pipeEnds[2];
  pid_t pid;
  int previousPipe = STDIN_FILENO;

  while (*currentCommand != NULL) {
    pipe(pipeEnds);
    if ((pid = fork()) == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == STDIN_FILENO) {
      dup2(previousPipe, STDIN_FILENO);
      if (*(currentCommand + 1) != NULL) {
        dup2(pipeEnds[STDOUT_FILENO], STDOUT_FILENO);
      }
      close(pipeEnds[STDIN_FILENO]);
      execvp((*currentCommand)[STDIN_FILENO], *currentCommand);
      exit(EXIT_FAILURE);
    } else {
      wait(NULL);
      close(pipeEnds[STDOUT_FILENO]);
      previousPipe = pipeEnds[STDIN_FILENO];
      currentCommand++;
    }
  }
}

int main(int argc, char *argv[]) {
  char linesToPrint[] = "10";
  int opt;

  char *ls_args[] = {"ls", NULL};
  char *xargs_args[] = {"xargs", "du", "-s", NULL};
  char *sort_args[] = {"sort", "-nr", NULL};
  char *head_args[] = {"head", "-n", linesToPrint, NULL};
  char **commandsToRun[] = {ls_args, xargs_args, sort_args, head_args, NULL};

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

  pipeline(commandsToRun);
  return (EXIT_SUCCESS);
}

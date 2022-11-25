#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
Write a C program that calls fork() and then the child process calls one of the exec()
functions to run the program “ls -l -F -h”.

Done

Try this with each of the following exec() functions:execl(), execlp(), execv(), and execvp().

Done
*/

int main(void) {
  if (fork() == 0) {
    execl("/bin/ls", "ls -l -F -h", (char *) NULL);
  }

  if (fork() == 0) {
    execlp("/bin/ls", "ls -l -F -h", (char *) NULL);
  }

  if (fork() == 0) {
    char * command[] = { "ls -l -F -h", (char *) NULL };
    execv("/bin/ls", command);
  }

  if (fork() == 0) {
    char * command[] = { "ls -l -F -h", (char *) NULL };
    execvp("/bin/ls", command);
  }

  exit(EXIT_SUCCESS);
}

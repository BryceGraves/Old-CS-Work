#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
  FILE *dir = popen("ls -lF", "r");
  char buffer[1024];

  bzero(&buffer, 1024);
  while (fgets(buffer, 1024, dir) != NULL) {
    write(STDOUT_FILENO, buffer, 1024);
    bzero(&buffer, 1024);
  }

  exit(EXIT_SUCCESS);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FALSE 0;
#define TRUE 1;

/*
Write a C program using fork().

Done

The child process should print “hello”; the parent process should print “goodbye”.

Done

You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

Done, you are able to have the parent sleep, but it requires some fiddling to achieve.
*/

int main(void) {
  _Bool use_sleep = TRUE;

  if (fork() == 0) {
    printf("hello\n");
  } else {
    use_sleep ? usleep(300) : wait(0);
    printf("goodbye\n");
  }

  exit(EXIT_SUCCESS);
}

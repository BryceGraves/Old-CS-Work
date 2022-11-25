#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


/*
Write a C program that calls fork().

Done

Before calling fork(), have the parent process assign the value 100 to int called x.

Done

What value is the value of x in the child process?

The value is 100 in both processes.

What happens to x variable when both the child and parent change the value of x?

They change on their own. Since both are running in different memory spaces they can not effect
each other.

Have both processes print the value of x.

Done
*/

int main(void) {
  int x = 100;

  if (fork() == 0) {
    x += 10;
    printf("Child: %d\n", x);
  } else {
    x += -10;
    printf("Parent: %d\n", x);
  }
  

  exit(EXIT_SUCCESS);
}
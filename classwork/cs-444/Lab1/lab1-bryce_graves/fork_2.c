#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

/*
Write a C program that opens a file (with the open() system call) and then calls fork() to create a new process.

Done

Can both the child and parent access the file descriptor returned from open()?
What happens when they are writing to the file concurrently, i.e., at the same time?

The writes are indeterminate.
*/

int main(void) {
  int fd = open("testFile.txt", O_WRONLY);
  char parent[] = "Parent\n";
  char child[] = "Child\n";

  if (fork() == 0) {
    write(fd, child, (sizeof(child) - 1));
  } else {
    write(fd, parent, (sizeof(parent) - 1));
  }

  close(fd);

  exit(EXIT_SUCCESS);
}

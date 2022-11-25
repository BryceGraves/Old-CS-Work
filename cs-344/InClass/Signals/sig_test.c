#include <ctype.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// Alarm sends an alarm signal after the specified amount of seconds
// When you try to make a kill handler you get a warning that you cant redefine the handler for sigkill
// The error reads: An error trying to set signal on SIGINT: Invalid argument

extern void handler_sigterm(int);
extern void handler_sigint(int);
extern void handler_sigalrm(int);
extern void handler_sigusr(int);
// extern void handler_sigkill(int);

void handler_sigterm(int sig) {
  printf("Caught a terminating signal. Leaving.\n");
  exit(1);
}

void handler_sigint(int sig) {
  char input[4];
  char expected[] = "yes";
  int i = 0;
  psignal(sig, "\n");
  printf("Do you want to exit?\n");
  scanf("%s", input);

  while(input[i]) {
    input[i] = tolower(input[i]);
    i++;
  }

  if (strcmp(input, expected) == 0) {
    exit(1);
  }

  return;
}

void handler_sigalrm(int sig) {
  time_t curtime;
  time(&curtime);
  printf("Current Time: %s\n", ctime(&curtime));

  return;
}

void handler_sigusr(int sig) {
  if(sig == SIGUSR1) {
    printf("Caught SIGUSR1\n");
  }

  if(sig == SIGUSR2) {
    printf("Caught SIGUSR2\n");
  }
}

void handler_sigkill(int sig) {
  if(sig == SIGUSR1) {
    printf("Caught SIGUSR1\n");
  }

  if(sig == SIGUSR2) {
    printf("Caught SIGUSR2\n");
  }
}

int main(int argc, char *argv[], char *envp[]) {
  alarm(3);

  printf("This is my pid: %d\n", getpid());

  signal(SIGINT, handler_sigint);
  signal(SIGTERM, handler_sigterm);
  signal(SIGALRM, handler_sigalrm);
  signal(SIGUSR1, handler_sigusr);
  signal(SIGUSR2, handler_sigusr);
  signal(SIGKILL, handler_sigkill);


  for ( ; ; ) {
    sleep(1);
  }

  return(EXIT_SUCCESS);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <linux/limits.h>
#include <stdlib.h>

#include "fifo_cs.h"

static char fifoListenerName[PATH_MAX] = {'\0'};
static char fifoDataName[PATH_MAX] = {'\0'};
static char fifoCmdName[PATH_MAX] = {'\0'};
static unsigned isVerbose = 0;

void sigint_handler(int);
void remove_client_pipes(void);
void handle_connection(void);
void handle_user_requests(void);

void sigint_handler(int sig) {
  fprintf(stderr, "signal handler called: %d\nfor signal: %d\n", (int) getpid(), sig);
  exit(CLIENT_EXIT_SUCCESS);
}

void remove_client_pipes(void) {
  unlink(fifoDataName);
  unlink(fifoCmdName);
}

void handle_connection(void) {
  int rez = -1;
  int listenerFd = -1;
  char buffer[200] = {'\0'};

  SERVER_FIFO_NAME(fifoListenerName);

  CLIENT_FIFO_DATA(fifoDataName, getpid());
  CLIENT_FIFO_CMD(fifoCmdName, getpid());

  rez = mkfifo(fifoDataName, FIFO_PERMISSIONS);
  if (rez != 0) {
    perror("cannot create data fifo");
    exit(CLIENT_EXIT_DATA_FIFO);
  }
  rez = mkfifo(fifoCmdName, FIFO_PERMISSIONS);
  if (rez != 0) {
    perror("cannot create command fifo");
    exit(CLIENT_EXIT_CMD_FIFO);
  }

  listenerFd = open(fifoListenerName, O_WRONLY);
  if (listenerFd < 0) {
    perror("could not open listener fifo\n");
    exit(CLIENT_EXIT_SRVR_OPEN);
  }

  // send the client pid to the server.
  sprintf(buffer, "%u\n", (unsigned) getpid());
  write(listenerFd, buffer, strlen(buffer));

  // This is the fifo the connects to the server. we are done
  // with it in the client. close it, but don't unlink it.
  close(listenerFd);
}

// handle all the i/o with the user.
void handle_user_requests(void) {
  char buffer[BUFFER_SIZE];
  int cFd = -1;
  int rez = -1;
  ssize_t bytes_read = -1;

  memset(buffer, 0, sizeof(buffer));
  cFd = open(fifoCmdName, O_WRONLY);
  fputs(CLIENTPROMPT, stdout);
  while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    buffer[strlen(buffer) - 1] = 0;
    if (strlen(buffer) == 0) {
      // An empty command line.
      continue;
    }
    if (isVerbose > 1) {
      fprintf(stderr, "verbose: cmd \"%s\"\n", buffer);
    }
    if (strcmp(buffer, CMD_EXIT) == 0) {
      // send exit to server side
      strcpy(buffer, CMD_EXIT);
      write(cFd, buffer, strlen(buffer));
      // break out of the look.
      break;
    } else if (strncmp(buffer, CMD_CD " ", strlen(CMD_CD) + 1) == 0) {
      // change directory on server side
      write(cFd, buffer, strlen(buffer));
    }
    else if (strncmp(buffer, CMD_LCD " ", strlen(CMD_LCD) + 1) == 0) {
      // change directory on client side
      char *dir = &buffer[strlen(CMD_CD) + 1];

      rez = chdir(dir);
      if (rez < 0) {
        perror("client side cd failed");
      }
    } else if (strcmp(buffer, CMD_DIR) == 0) {
      // server side directory
      write(cFd, buffer, strlen(buffer));
      {
        // One of the great things about using named pipes is that
        // persist through multiple open and close calls. This is
        // very different from unnamed pipes and sockets.
        int dFd = open(fifoDataName, O_RDONLY);

        if (dFd < 0) {
          perror("cannot open read fifo\n");
          exit(CLIENT_EXIT_DIR_FAIL);
        }
        memset(buffer, 0, BUFFER_SIZE);
        // Receive and print the direcory data from the cs process.
        while ((bytes_read = read(dFd, buffer, BUFFER_SIZE - 1)) > 0) {
          printf("%s", buffer);
          memset(buffer, 0, BUFFER_SIZE);
        }
        // Close of the data fifo. It will still be there if we need
        // it again.
        close(dFd);
      }
    }
    else if (strcmp(buffer, CMD_LDIR) == 0) {
      // client side directory
      // popen() is just soooo handy.
      FILE *dir = popen(CMD_LS_POPEN, "r");

      if (dir != NULL) {
        while (fgets(buffer, BUFFER_SIZE, dir) != NULL) {
          printf("%s", buffer);
        }
        pclose(dir);
      } else {
        perror("popen for dir failed");
      }
    } else if (strcmp(buffer, CMD_PWD) == 0) {
      // server side pwd
      // receive the present-working-directory from the cs.
      write(cFd, buffer, strlen(buffer));
      {
        int dFd = open(fifoDataName, O_RDONLY);

        memset(buffer, 0, BUFFER_SIZE);
        printf("server side pwd: ");
        while ((bytes_read = read(dFd, buffer, BUFFER_SIZE - 1)) > 0) {
            printf("%s", buffer);
            memset(buffer, 0, BUFFER_SIZE);
        }
        printf("\n");
        close(dFd);
      }
    } else if (strcmp(buffer, CMD_LPWD) == 0) {
      // client side pwd
      // this just seems to easy.
      getcwd(buffer, BUFFER_SIZE);
      printf("pwd: %s\n", buffer);
    } else if (strcmp(buffer, CMD_HOME) == 0) {
      // server side home
      // Tell the cs side to click its heels together 3 times and say
      // ... ... ...
      write(cFd, buffer, strlen(buffer));
      {
        int dFd = open(fifoDataName, O_RDONLY);

        memset(buffer, 0, BUFFER_SIZE);
        printf("server side home: ");
        // get back the cs side pwd.
        while ((bytes_read = read(dFd, buffer, BUFFER_SIZE - 1)) > 0) {
          printf("%s", buffer);
          memset(buffer, 0, BUFFER_SIZE);
        }
        printf("\n");
        close(dFd);
      }
    } else if (strcmp(buffer, CMD_LHOME) == 0) {
      // client side home
      char *home = getenv("HOME");
      chdir(home);
      printf("pwd: %s\n", home);
    } else if (strcmp(buffer, CMD_HELP) == 0) {
      // client side help
      // I bet you can do better than this.
      printf("Commands:\n\
      exit: exit out of the client side server\n\
      cd: change directory on server side\n\
      lcd: change directory on client side\n\
      pwd: show directory path on server side\n\
      lpwd: show directory path on client side\n\
      home: go to the $HOME dir on server side\n\
      lhome: go to the $HOME dir on the client side\n\
      help: show this list\n\
      put: copy a file from the client side to the server side\n\
      get: copy a file from the server side to the client side\n");
    } else if (strncmp(buffer, CMD_PUT " ", strlen(CMD_PUT) + 1) == 0) {
      // send file to server
      char *fileName = &buffer[strlen(CMD_PUT) + 1];

      write(cFd, buffer, strlen(buffer));
      {
        int dFd = open(fifoDataName, O_WRONLY);
        int file = open(fileName, O_RDONLY);
        while ((bytes_read = read(file, buffer, BUFFER_SIZE - 1)) > 0) {
          write(dFd, buffer, bytes_read);
          memset(buffer, 0, BUFFER_SIZE);
        }
        close(file);
        close(dFd);
      }
    }
    else if (strncmp(buffer, CMD_GET " ", strlen(CMD_GET) + 1) == 0) {
      // receive file from server
      char *fileName = &buffer[strlen(CMD_PUT) + 1];

      write(cFd, buffer, strlen(buffer));
      {
        int dFd = open(fifoDataName, O_RDONLY);
        int file = open(fileName, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
        while ((bytes_read = read(dFd, buffer, BUFFER_SIZE - 1)) > 0) {
          write(file, buffer, bytes_read);
          memset(buffer, 0, BUFFER_SIZE);
        }
        close(file);
        close(dFd);
      }
    }
    else {
      // ignore
      printf("unknown command \"%s\"\n", buffer);
    }

    memset(buffer, 0, sizeof(buffer));
    fputs(CLIENTPROMPT, stdout);
    fflush(stdout);
  }
  // user done, time to exit.
  close(cFd);
}

int main(int argc, char *argv[]) {
  int opt;

  // I don't feel like fighting with the umask.
  umask(0);
  while ((opt = getopt(argc, argv, "v")) != -1) {
    switch (opt) {
      case 'v':
        isVerbose++;
        break;
      default:
        fprintf(stderr
          , "*** opt:%c ptarg: <%s> optind: "
            "%d opterr: %d optopt: %d ***\n"
          , opt, optarg, optind, opterr, optopt);
        break;
    }
  }

  atexit(remove_client_pipes);
  signal(SIGINT, sigint_handler);

  handle_connection();
  handle_user_requests();

  return(CLIENT_EXIT_SUCCESS);
}

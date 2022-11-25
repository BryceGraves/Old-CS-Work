#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include "socket_hdr.h"

/* Globals Secetion -- Bryce Slowly Melts */
int uflag = 0, vflag = 0;
unsigned int usecs = 1000;
/* End of Globals Secetion -- Feat. Puddle Bryce */

void *process_connection(void *);
void *execute_dir(void *);
void *execute_get(void *);
void *execute_put(void *);
void error(char *);

int main(int argc, char *argv[]) {
  int *connectionfd, sockfd, opt, portno = SERV_PORT;
  struct sockaddr_in serv_addr, cli_addr;
  unsigned int clilen;
  pthread_t thread;

  while ((opt = getopt(argc, argv, SERVER_OPTIONS)) != -1) {
    switch (opt) {
      case 'p':
        portno = atoi(optarg);
        break;

      case 'u':
        uflag = 1;
        break;

      case 'v':
        vflag = 1;
        break;

      case 'h':
        fprintf(stderr, "%s", "Thar be no help!\n");
        exit(EXIT_SUCCESS);

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        exit(EXIT_FAILURE);
    }
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0)
    error("ERROR opening socket");

  bzero((char *) &serv_addr, sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  listen(sockfd, LISTENQ);

  clilen = sizeof(cli_addr);

  while (TRUE) {
    connectionfd = (int *) malloc(sizeof(int));
    *connectionfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    pthread_create(&thread, NULL, &process_connection, connectionfd);
  }

  return 0;
}

void *process_connection (void *arg) {
  int bytes_read, sockfd = *((int *) arg);
  cmd_t clientCommand, *threadCommand;
  pthread_t thread;

  free(arg);

  pthread_detach(pthread_self());

  bzero(&clientCommand, sizeof(cmd_t));

  if ((bytes_read = read(sockfd, &clientCommand, sizeof(cmd_t))) < 0)
    error("ERROR reading from socket");

  clientCommand.sock = sockfd;

  if (strcmp(clientCommand.cmd, CMD_DIR) == 0) {
    threadCommand = (cmd_t *) malloc(sizeof(cmd_t));
    *threadCommand = clientCommand;
    pthread_create(&thread, NULL, &execute_dir, threadCommand);
  } else if (strcmp(clientCommand.cmd, CMD_GET) == 0) {
    threadCommand = (cmd_t *) malloc(sizeof(cmd_t));
    *threadCommand = clientCommand;
    pthread_create(&thread, NULL, &execute_get, threadCommand);
  } else if (strcmp(clientCommand.cmd, CMD_PUT) == 0) {
    threadCommand = (cmd_t *) malloc(sizeof(cmd_t));
    *threadCommand = clientCommand;
    pthread_create(&thread, NULL, &execute_put, threadCommand);
  }

  pthread_exit(EXIT_SUCCESS);
}

void *execute_dir(void *arg) {
  cmd_t clientCommand = *((cmd_t *) arg);
  FILE *dir = popen(CMD_DIR_POPEN, "r");
  char buffer[MAXLINE];
  int bytes_read;

  free(arg);

  pthread_detach(pthread_self());

  bzero(&buffer, MAXLINE);

  while ((fgets(buffer, MAXLINE, dir)) != NULL) {
    if (uflag) {
      usleep(usecs);
    }

    if (vflag) {
      printf(".");
    }

    bytes_read = write(clientCommand.sock, buffer, MAXLINE);
    bzero(&buffer, MAXLINE);
  }

  pclose(dir);
  close(clientCommand.sock);

  if (bytes_read < 0) error("ERROR writing to socket");

  if (vflag) {
    printf("\n");
  }

  pthread_exit(EXIT_SUCCESS);
}

void *execute_get(void *arg) {
  cmd_t clientCommand = *((cmd_t *) arg);
  int file = open(clientCommand.name, O_RDONLY);
  char buffer[MAXLINE];
  int bytes_read;
  free(arg);

  pthread_detach(pthread_self());

  while ((bytes_read = read(file, buffer, MAXLINE)) > 0) {
    if (uflag) {
      usleep(usecs);
    }

    if (vflag) {
      printf(".");
    }

    write(clientCommand.sock, buffer, bytes_read);
    bzero(&buffer, MAXLINE);
  }

  close(file);
  close(clientCommand.sock);

  if (vflag) {
    printf("\n");
  }
  pthread_exit(EXIT_SUCCESS);
}

void *execute_put(void *arg) {
  cmd_t clientCommand = *((cmd_t *) arg);
  int file = open(clientCommand.name, O_TRUNC | O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  char buffer[MAXLINE];
  int bytes_read;
  free(arg);

  pthread_detach(pthread_self());

  while ((bytes_read = read(clientCommand.sock, buffer, MAXLINE)) > 0) {
    if (uflag) {
      usleep(usecs);
    }

    if (vflag) {
      printf(".");
    }

    write(file, buffer, bytes_read);
    bzero(&buffer, MAXLINE);
  }

  close(file);
  close(clientCommand.sock);

  if (vflag) {
    printf("\n");
  }

  pthread_exit(EXIT_SUCCESS);
}

void error(char *msg) {
  perror(msg);
  exit(1);
}

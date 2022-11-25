#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netinet/in.h>

#include "socket_hdr.h"

void *connectClient(void *);
void error(char *);

/* Globals Secetion -- Bryce Slowly Melts */
char ip_addr[MAXLINE] = "10.217.113.250";
int portno = SERV_PORT, uflag = 0, vflag = 0;
unsigned int usecs = 1000;
/* End of Globals Secetion -- Feat. Puddle Bryce */

int main(int argc, char *argv[]) {
  cmd_t commandToSend, *commandForThread;
  pthread_t *thread = NULL;
  int i, numberOfThreads, opt;

  while ((opt = getopt(argc, argv, CLIENT_OPTIONS)) != -1) {
    switch (opt) {
      case 'i':
        bzero(&ip_addr, MAXLINE);
        strcpy(ip_addr, optarg);
        break;

      case 'p':
        portno = atoi(optarg);
        break;

      case 'c':
        strcpy(commandToSend.cmd, optarg);
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

  numberOfThreads = (argc - optind);

  if (strcmp(commandToSend.cmd, CMD_DIR) == 0) {
    thread = malloc(sizeof(pthread_t));
    commandForThread = (cmd_t *) malloc(sizeof(cmd_t));
    *commandForThread = commandToSend;
    pthread_create(&thread[0], NULL, &connectClient, commandForThread);
    pthread_join(thread[0], NULL);
  } else if (strcmp(commandToSend.cmd, CMD_GET) == 0) {
    if (optind == argc) {
      printf("You need to pass an argument with get\n");
      exit(EXIT_FAILURE);
    }

    thread = malloc(sizeof(pthread_t) * numberOfThreads);

    for (i = 0; i < numberOfThreads; i++) {
      strcpy(commandToSend.name, argv[optind]);
      optind++;
      commandForThread = (cmd_t *) malloc(sizeof(cmd_t));
      *commandForThread = commandToSend;
      pthread_create(&thread[i], NULL, &connectClient, commandForThread);
    }

    for (i = 0; i < numberOfThreads; i++) {
      pthread_join(thread[i], NULL);
    }
  } else if (strcmp(commandToSend.cmd, CMD_PUT) == 0) {
    if (optind == argc) {
      printf("You need to pass an argument with put\n");
      exit(EXIT_FAILURE);
    }

    thread = malloc(sizeof(pthread_t) * numberOfThreads);

    for (i = 0; i < numberOfThreads; i++) {
      strcpy(commandToSend.name, argv[optind]);
      optind++;
      commandForThread = (cmd_t *) malloc(sizeof(cmd_t));
      *commandForThread = commandToSend;
      pthread_create(&thread[i], NULL, &connectClient, commandForThread);
    }

    for (i = 0; i < numberOfThreads; i++) {
      pthread_join(thread[i], NULL);
    }
  }

  free(thread);
  exit(EXIT_SUCCESS);
}

void *connectClient(void *arg) {
  cmd_t commandToSend = *((cmd_t *) arg);
  struct sockaddr_in serv_addr;
  char buffer[MAXLINE];
  int bytes_read;
  free(arg);

  commandToSend.sock = socket(AF_INET, SOCK_STREAM, 0);

  if (commandToSend.sock < 0) {
    error("ERROR opening socket");
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr.s_addr);

  if (connect(commandToSend.sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR connecting");
  }

  if ((bytes_read = write(commandToSend.sock, &commandToSend, sizeof(cmd_t))) < 0)
    error("ERROR writing to socket");


  if (strcmp(commandToSend.cmd, CMD_DIR) == 0) {
    while ((bytes_read = read(commandToSend.sock, buffer, MAXLINE)) > 0) {
      if (uflag) {
        usleep(usecs);
      }
      if (vflag) {
        printf(".");
      }

      printf("%s", buffer);
      bzero(&buffer, MAXLINE);
    }
  } else if (strcmp(commandToSend.cmd, CMD_GET) == 0) {
    int file = open(commandToSend.name, O_TRUNC | O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    while ((bytes_read = read(commandToSend.sock, buffer, MAXLINE)) > 0) {
      if (uflag) {
        usleep(usecs);
      }
      if (vflag) {
        printf(".");
      }

      write(file, buffer, bytes_read);
      bzero(&buffer, MAXLINE);
    }
  } else if (strcmp(commandToSend.cmd, CMD_PUT) == 0) {
    int file = open(commandToSend.name, O_RDONLY);

    while ((bytes_read = read(file, buffer, MAXLINE)) > 0) {
      if (uflag) {
        usleep(usecs);
      }
      if (vflag) {
        printf(".");
      }

      write(commandToSend.sock, buffer, bytes_read);
      bzero(&buffer, MAXLINE);
    }
  }

  if (vflag) {
    printf("\n");
  }

  pthread_exit(EXIT_SUCCESS);
}

void error(char *msg) {
  perror(msg);
  exit(0);
}

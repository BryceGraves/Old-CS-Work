// R Jesse Chaney
//

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

static char fifoListenerName[PATH_MAX];
static unsigned short isVerbose = 0;
static unsigned short isConnectionListener = TRUE;

void sigint_handler(int);
void sigchld_handler(int);
void remove_server_pipe(void);
void connection_listener( void );
void handle_client(pid_t client_pid);

void sigint_handler(int sig)
{
    fprintf(stderr, "signal hanler called: %d\n", (int) getpid());
    exit(SERVER_EXIT_SUCCESS);
}

void sigchld_handler(int sig)
{
    //int status;
    //pid_t cpid;

    // using waitpid() make sure you cleanup all exited child processes
}

void remove_server_pipe(void)
{
    if (isConnectionListener == TRUE) {
        // Only unlink if this is the 1 true server.
        fprintf(stderr, "  exit hanlder called on server: %d\n", getpid());
        // something goes here
    }
}

void connection_listener(void)
{
    int rFd;
    int wFd;
    ssize_t bytes_read;
    char buffer[200];
    int rez = 0;

    // Create the name of the FIFO.
    SERVER_FIFO_NAME(fifoListenerName);
    // Just in case SOMEONE forgot to cleanup!!!
    unlink(fifoListenerName);

    rez = mkfifo(fifoListenerName, FIFO_PERMISSIONS);
    if (rez != 0) {
        perror("cannot create listener fifo, exiting...");
        exit(SERVER_EXIT_FIFO_FAILED);
    }
    // Open the FIFO.
    // Each open will block until the first client makes a connection.
    rFd = open(fifoListenerName, O_RDONLY);
    wFd = open(fifoListenerName, O_WRONLY);
    for ( ; ; ) {
        memset(buffer, 0, sizeof(buffer));
        fputs("\n+++ ", stdout);
        fflush(stdout);
        // Read the FIFO for input.
        bytes_read = read(rFd, buffer, sizeof(buffer));
        if (0 == bytes_read) {
            if (isVerbose > 0) {
                fprintf(stderr, "verbose: connection fifo closed by client\n");
            }
            continue;
        }

        // Make sure the buffer is a NULL terminiated string.
        buffer[bytes_read] = 0;
        if (isVerbose > 0) {
            fprintf(stderr, "verbose: connection request received %s\n", buffer);
        }
        {
            pid_t client = (pid_t) atoi(buffer);
            pid_t child = -1;
            
            child = fork();
            switch(child) {
            case -1:
                perror("fork failed: exiting...");
                exit(SERVER_EXIT_FORK_FAIL);
                break;
            case 0:
                // this child process will be a client-server
                isConnectionListener = FALSE;
                handle_client(client);
                break;
            default:
                // the parent process remains the true server, listening for
                // more client connections.
                if (isVerbose > 0) {
                    fprintf(stderr, "verbose: server parent, new cs %d\n"
                            , (int) child);
                }
                break;
            }
        }
    }
    close(rFd);
    close(wFd);
}

void handle_client(pid_t clientPid)
{
    char clientFifoCmd[PATH_MAX];
    char clientFifoData[PATH_MAX];
    int cFd = -1;
    int rez = -1;
    char buffer[BUFFER_SIZE] = {'\0'};

    // generate the names used by the client for the command
    // and data fifos.
    CLIENT_FIFO_CMD(clientFifoCmd, (int) clientPid);
    CLIENT_FIFO_DATA(clientFifoData, (int) clientPid);

    if (isVerbose > 0) {
        fprintf(stderr, "verbose: client fifos:\n\t%s\n\t%s\n"
                , clientFifoCmd, clientFifoData);
    }
    // open the command fifo
    cFd = open(clientFifoCmd, O_RDONLY);

    memset(buffer, 0, BUFFER_SIZE);
    for ( ; ; ) {
        // fetch the next command from the client.
        int bytes_read = read(cFd, buffer, BUFFER_SIZE - 1);

        if (isVerbose > 1) {
            fprintf(stderr, "verbose: client-server %u  command: \"%s\"  %d\n"
                    , (unsigned) getpid(), buffer, (int) bytes_read);
        }

        if (bytes_read == 0) {
            // EOF on fifo, client must have closed it, break out.
            break;
        }
        else if (bytes_read < 0) {
            perror("read from client fifo failed\n");
        }
        if (strcmp(buffer, CMD_EXIT) == 0) {
            // if everything is setup correctly, this is an easy
            // way to cleanup and exit.
            raise(SIGINT);
            break;
        }
        else if (strncmp(buffer, CMD_CD " ", strlen(CMD_CD) + 1) == 0) {
            // change directory on server side
            char *dir = &buffer[strlen(CMD_CD) + 1];

            if (isVerbose > 2) {
                fprintf(stderr, "%d cd >%s<\n", __LINE__, dir);
            }
            rez = chdir(dir);
            if (rez < 0) {
                perror("server side cd failed");
            }
        }
        else if (strcmp(buffer, CMD_DIR) == 0) {
            // return the directory contents from the cs side to
            // the client.
            FILE *dir = popen(CMD_LS_POPEN, "r");
            int dFd = open(clientFifoData, O_WRONLY);

            if (dir != NULL) {
                while (fgets(buffer, BUFFER_SIZE, dir) != NULL) {
                    bytes_read = write(dFd, buffer, strlen(buffer));
                }
                pclose(dir);
            }
            else {
                perror("popen for dir failed");
            }
            close(dFd);
        }
        else if (strcmp(buffer, CMD_PWD) == 0) {
            int dFd = open(clientFifoData, O_WRONLY);

            // send the cs side pwd to the client.
            getcwd(buffer, BUFFER_SIZE);
            bytes_read = write(dFd, buffer, strlen(buffer));
            close(dFd);
        }
        else if (strcmp(buffer, CMD_HOME) == 0) {
            // https://www.youtube.com/watch?v=PzCANuQZEkY
            char *home = getenv("HOME");
            int dFd = open(clientFifoData, O_WRONLY);

            chdir(home);
            bytes_read = write(dFd, home, strlen(home));
            close(dFd);
        }
        else if (strncmp(buffer, CMD_PUT " ", strlen(CMD_PUT) + 1) == 0) {
            // receive file from client
            char *fileName = &buffer[strlen(CMD_PUT) + 1];

            // put code in here
            
            if (isVerbose) {
                fprintf(stderr, "  %u receiving file done %d\n"
                        , (unsigned) getpid(), __LINE__);
            }
        }
        else if (strncmp(buffer, CMD_GET " ", strlen(CMD_GET) + 1) == 0) {
            // send file to client
            char *fileName = &buffer[strlen(CMD_PUT) + 1];

            // put code in here

            if (isVerbose) {
                fprintf(stderr, "  %u sending file done %d\n"
                        , (unsigned) getpid(), __LINE__);
            }
        }
        else {
            // since the client should only send valid commands tp the cs
            // this should never happen.
            // we could send a bad command message back to client
        }
        memset(buffer, 0, BUFFER_SIZE);
    }
}

int main(int argc, char *argv[]) 
{
    int opt;

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

    atexit(remove_server_pipe);
    signal(SIGINT, sigint_handler);
    signal(SIGCHLD, sigchld_handler);

    connection_listener();

    return(SERVER_EXIT_SUCCESS);
}

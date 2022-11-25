#ifndef FIFO_SERVER_H
# define FIFO_SERVER_H

# define BUFFER_SIZE 1024

# define SERVER_FIFO_FILENAME    "FifoServerListener"
# define FIFO_PERMISSIONS  (S_IRUSR | S_IWUSR)

# define SERVER_FIFO_NAME(_BUF_) sprintf((_BUF_),"%s/%s__",getenv("HOME"),SERVER_FIFO_FILENAME);

# define CLIENTPROMPT    ">>> "

# define CLIENT_FIFO_DATA_FILENAME "FifoClientData"
# define CLIENT_FIFO_CMD_FILENAME "FifoClientCmd"

# define CLIENT_FIFO_DATA(_BUF_,_PID_) sprintf((_BUF_),"%s/%s__%d",getenv("HOME"),CLIENT_FIFO_DATA_FILENAME,_PID_);
# define CLIENT_FIFO_CMD(_BUF_,_PID_) sprintf((_BUF_),"%s/%s__%d",getenv("HOME"),CLIENT_FIFO_CMD_FILENAME,_PID_);

# ifndef FALSE
#  define FALSE 0
# endif // FALSE
# ifndef TRUE
#  define TRUE 1
# endif // TRUE

# define CMD_LS_POPEN "ls -lFh"

// cs stands for client-server. It is the server process that was fork-ed to
// process the commands from a single client.

# define CMD_EXIT  "exit"  // instruct the cs to exit, clean up client fifos, and exit
# define CMD_CD    "cd"    // change directory on the cs side.
# define CMD_LCD   "lcd"   // change directories on the client side
# define CMD_DIR   "dir"   // directory listing on the cs side
# define CMD_LDIR  "ldir"  // directory listing on client side
# define CMD_PWD   "pwd"   // show directory path from cs side
# define CMD_LPWD  "lpwd"  // show directory path on client side
# define CMD_HOME  "home"  // go to the $HOME dir on cs side
# define CMD_LHOME "lhome" // go to $HOME on client side
# define CMD_HELP  "help"  // show the list of commands
# define CMD_PUT   "put"   // copy a file from the client side to cs side
# define CMD_GET   "get"   // copy a file from the cs side to client side
//# define MSG_ACK   "ACK"   // this is not a command, but a synchronization message

# define SERVER_EXIT_SUCCESS     EXIT_SUCCESS
# define SERVER_EXIT_FIFO_FAILED 1
# define SERVER_EXIT_FORK_FAIL   2
# define SERVER_EXIT_PUT_FAIL    3
# define SERVER_EXIT_GET_FAIL    4

# define CLIENT_EXIT_SUCCESS     EXIT_SUCCESS
# define CLIENT_EXIT_DATA_FIFO   1
# define CLIENT_EXIT_CMD_FIFO    2
# define CLIENT_EXIT_SRVR_OPEN   3
# define CLIENT_EXIT_DIR_FAIL    4

#endif // FIFO_SERVER_H

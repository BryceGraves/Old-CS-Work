#ifndef CMD_PARSE_H
# define CMD_PARSE_H

# define MAX_STR_LEN 1024

# define FALSE 0
# define TRUE 1

# define CD_CMD  "cd"
# define PWD_CMD "pwd"
# define ECHO_CMD "echo"
# define EXIT_CMD "exit"
# define HISTORY_CMD "history"

# define PIPE_DELIM  "|"
# define SPACE_DELIM " "
# define REDIR_IN    "<"
# define REDIR_OUT   ">"

# define PROMPT_STR "bennysh"

// This enumeration is used when determining ifthe re direction
// characters (the < and >) were used on a command.
typedef enum {
    REDIRECT_NONE
    , REDIRECT_FILE
    , REDIRECT_PIPE
} redir_t;

// A list of param_t elements.
typedef struct param_s {
    char *param;
    struct param_s *next;
} param_t;

// A linked list that has a linked list as a member.
typedef struct cmd_s {
    char *raw_cmd;
    char *cmd;
    int param_count;
    param_t *param_list;
    redir_t input_src;
    redir_t output_dest;
    char *input_file_name;
    char *output_file_name;
    int list_location; // zero based
    struct cmd_s *next;
} cmd_t;

typedef struct cmd_list_s {
    cmd_t *head;
    cmd_t *tail;
    int count;
    _Bool errored;
} cmd_list_t;

typedef struct stringNode {
   char data[MAX_STR_LEN];
   struct stringNode *next;
} stringNodeType;

typedef struct stringList {
    stringNodeType *head;
    int count;
} stringListType;

typedef struct pipeNode {
   char *command[MAX_STR_LEN];
   struct pipeNode *next;
} pipeNodeType;

typedef struct pipeList {
    pipeNodeType *head;
    pipeNodeType *tail;
    int count;
} pipeListType;

void parse_commands(cmd_list_t *cmd_list);
void free_list(struct cmd_list_s *);
void print_list(struct cmd_list_s *);
void free_cmd(struct cmd_s *);
void print_cmd(struct cmd_s *);
void exec_commands(cmd_list_t *, stringListType *);
int process_user_input_simple(void);
void simple_argv(int argc, char *argv[]);
void free_param_list (param_t *);
void addToHistory(char [], stringListType *);
void print_history(stringNodeType *);
void free_history(stringListType *);
void addCommandToPipe(pipeListType *, char * []);
void freePipeline(pipeListType *);
void freeCharPointerArray(char * []);
void printPipeLine(pipeListType *);
void pipeline(pipeListType *, cmd_t *);
void executeCommand(cmd_t *);

#endif // CMD_PARSE_H

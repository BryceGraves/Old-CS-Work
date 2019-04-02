#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "cmd_parse.h"

// I have this a global so that I don't have to pass it to every
// function where I might want to use it. Yes, I know global variables
// are frowned upon, but there are a couple useful uses for them.
// This is one.
unsigned short isVerbose = 0;

//int main( int argc, char *argv[] )
int process_user_input_simple(void) {
  char str[MAX_STR_LEN];
  char *ret_val;
  char *raw_cmd;
  cmd_list_t *cmd_list = NULL;
  stringListType *history = (stringListType *)malloc(sizeof(stringListType));
  int cmd_count = 0;
  char prompt[30];
  history->head = NULL;
  history->count = 0;

  // Set up a cool user prompt.
  sprintf(prompt, PROMPT_STR " %s :-) ", getenv("LOGNAME"));
  for ( ; ; ) {
    fputs(prompt, stdout);
    memset(str, 0, MAX_STR_LEN);
    ret_val = fgets(str, MAX_STR_LEN, stdin);

    if (NULL == ret_val) {
      break;
    }

    str[strlen(str) - 1] = 0;
    if (strlen(str) == 0) {
      continue;
    }

    if (strcmp(str, EXIT_CMD) == 0) {
      break;
    }

    addToHistory(str, history);

    // Basic commands are pipe delimited.
    // This is really for Stage 2.
    raw_cmd = strtok(str, PIPE_DELIM);

    cmd_list = (cmd_list_t *) calloc(1, sizeof(cmd_list_t));

    // This block should probably be put into its own function.
    cmd_count = 0;
    while (raw_cmd != NULL ) {
      cmd_t *cmd = (cmd_t *) calloc(1, sizeof(cmd_t));

      cmd->raw_cmd = strdup(raw_cmd);
      cmd->list_location = cmd_count++;

      if (cmd_list->head == NULL) {
        // An empty list.
        cmd_list->tail = cmd_list->head = cmd;
      } else {
        // Make this the last in the list of cmds
        cmd_list->tail->next = cmd;
        cmd_list->tail = cmd;
      }
      cmd_list->count++;

      // Get the next raw command.
      raw_cmd = strtok(NULL, PIPE_DELIM);
    }
    // Now that I have a linked list of the pipe delimited commands,
    // go through each individual command.
    parse_commands(cmd_list);

    // This is a really good place to call a function to exec the
    // the commands just parsed from the user's command line.
    exec_commands(cmd_list, history);

    // We (that includes you) need to free up all the stuff we just
    // allocated from the heap. That linked list is linked lists looks
    // like it will be nasty to free up, but just follow the memory.
    free_list(cmd_list);
    cmd_list = NULL;
  }

  free_history(history);
  return(EXIT_SUCCESS);
}

void simple_argv(int argc, char *argv[] ) {
  int opt;

  while ((opt = getopt(argc, argv, "hv")) != -1) {
    switch (opt) {
    case 'h':
      // help
      // Show something helpful
      fprintf(stdout, "You must be out of your Vulcan mind if you think\n"
        "I'm going to put helpful things in here.\n\n");
      exit(EXIT_SUCCESS);
      break;
    case 'v':
      // verbose option to anything
      // I have this such that I can have -v on the command line multiple
      // time to increase the verbosity of the output.
      isVerbose++;
      if (isVerbose) {
        fprintf(stderr, "verbose: verbose option selected: %d\n", isVerbose);
      }
      break;
    case '?':
      fprintf(stderr, "*** Unknown option used, ignoring. ***\n");
      break;
    default:
      fprintf(stderr, "*** Oops, something strange happened <%c> ... ignoring ...***\n", opt);
      break;
    }
  }
}

void exec_commands( cmd_list_t *cmds, stringListType *history ) {
  cmd_t *cmd = cmds->head;
  param_t *currentParam = cmd->param_list;

  if (1 == cmds->count) {
    if (!cmd->cmd) {
      // if it is an empty command, bail.
      return;
    }
    if (0 == strcmp(cmd->cmd, CD_CMD)) {
      if (0 == cmd->param_count) {
        chdir(getenv("HOME"));
      } else {
        if (0 == chdir(cmd->param_list->param)) {
          char str[MAXPATHLEN];

          getcwd(str, MAXPATHLEN);
          printf("%s\n", getcwd(str, MAXPATHLEN));
        } else {
          printf("Unable to change directory!\n");
        }
      }
    } else if (0 == strcmp(cmd->cmd, PWD_CMD)) {
      char str[MAXPATHLEN];

      getcwd(str, MAXPATHLEN);
      printf(" " PWD_CMD ": %s\n", str);
    } else if (0 == strcmp(cmd->cmd, ECHO_CMD)) {
      while (currentParam != NULL) {
        printf("%s ", currentParam->param);
        currentParam = currentParam->next;
      }

      printf("\n");

    } else if (0 == strcmp(cmd->cmd, HISTORY_CMD)) {
      print_history(history->head);
    } else {
      if (!cmds->errored) {
        executeCommand(cmd);
      }
    }
  } else {
    if (!cmds->errored) {
      executeCommand(cmd);
    }
  }
}

void free_list(cmd_list_t *currentList) {
  free_cmd(currentList->head);
  free(currentList);
}

void free_cmd (cmd_t *currentNode) {
  cmd_t *nextNode = currentNode;

  while (currentNode != NULL) {
    nextNode = currentNode->next;
    free(currentNode->cmd);
    free(currentNode->input_file_name);
    free(currentNode->output_file_name);
    free(currentNode->raw_cmd);
    free_param_list(currentNode->param_list);
    free(currentNode);
    currentNode = nextNode;
  }
}

void free_param_list (param_t *currentParam) {
  param_t *nextParam = currentParam;

  while (currentParam != NULL) {
    nextParam = currentParam->next;
    free(currentParam->param);
    free(currentParam);
    currentParam = nextParam;
  }
}

void print_list(cmd_list_t *cmd_list) {
  cmd_t *cmd = cmd_list->head;

  while (NULL != cmd) {
    print_cmd(cmd);
    cmd = cmd->next;
  }
}

// Oooooo, this is nice. Show the fully parsed command line in a nice
// asy to read and digest format.
void print_cmd(cmd_t *cmd) {
  param_t *param = NULL;
  int pcount = 1;

  fprintf(stderr,"raw text: +%s+\n", cmd->raw_cmd);
  fprintf(stderr,"\tbase command: +%s+\n", cmd->cmd);
  fprintf(stderr,"\tparam count: %d\n", cmd->param_count);
  param = cmd->param_list;

  while (NULL != param) {
    fprintf(stderr,"\t\tparam %d: %s\n", pcount, param->param);
    param = param->next;
    pcount++;
  }

  fprintf(stderr,"\tinput source: %s\n"
    , (cmd->input_src == REDIRECT_FILE ? "redirect file" :
    (cmd->input_src == REDIRECT_PIPE ? "redirect pipe" : "redirect none")));
  fprintf(stderr,"\toutput dest:  %s\n"
    , (cmd->output_dest == REDIRECT_FILE ? "redirect file" :
    (cmd->output_dest == REDIRECT_PIPE ? "redirect pipe" : "redirect none")));
  fprintf(stderr,"\tinput file name:  %s\n"
    , (NULL == cmd->input_file_name ? "<na>" : cmd->input_file_name));
  fprintf(stderr,"\toutput file name: %s\n"
    , (NULL == cmd->output_file_name ? "<na>" : cmd->output_file_name));
  fprintf(stderr,"\tlocation in list of commands: %d\n", cmd->list_location);
  fprintf(stderr,"\n");
}

// Remember how I told you that use of alloca() is
// dangerous? You can trust me. I'm a professional.
// And, if you mention this in class, I'll deny it
// ever happened. What happens in stralloca stays in
// stralloca.
#define stralloca(_R,_S) {(_R) = alloca(strlen(_S) + 1); strcpy(_R,_S);}

void parse_commands(cmd_list_t *cmd_list) {
  cmd_t *cmd = cmd_list->head;
  char *arg;
  char *raw;

  while (cmd) {
    stralloca(raw, cmd->raw_cmd);

    arg = strtok(raw, SPACE_DELIM);
    if (NULL == arg) {
      cmd = cmd->next;
      continue;
    }

    if (arg[0] == '\'') {
      arg++;
    }

    if (arg[strlen(arg) - 1] == '\'') {
      arg[strlen(arg) - 1] = '\0';
    }

    cmd->cmd = strdup(arg);

    cmd->input_src = REDIRECT_NONE;
    cmd->output_dest = REDIRECT_NONE;

    while ((arg = strtok(NULL, SPACE_DELIM)) != NULL) {
      if (strcmp(arg, REDIR_IN) == 0) {
        if (cmd->input_src != REDIRECT_NONE) {
          fprintf(stderr, "You can only have in redirect in per command!\n");
          cmd_list->errored = TRUE;
          break;
        }

        if (cmd != cmd_list->head) {
          fprintf(stderr, "File input redirects MUST be at the start you dumb dumb.\n");
          cmd_list->errored = TRUE;
          break;
        }

        cmd->input_file_name = strdup(strtok(NULL, SPACE_DELIM));
        cmd->input_src = REDIRECT_FILE;

      } else if (strcmp(arg, REDIR_OUT) == 0) {
        if (cmd->output_dest != REDIRECT_NONE) {
          fprintf(stderr, "You can only have in redirect in per command!\n");
          cmd_list->errored = TRUE;
          break;
        }

        if (cmd != cmd_list->tail) {
          fprintf(stderr, "File output redirects MUST be at the end you dumb dumb.\n");
          cmd_list->errored = TRUE;
          break;
        }

        cmd->output_file_name = strdup(strtok(NULL, SPACE_DELIM));
        cmd->output_dest = REDIRECT_FILE;

      } else {
        // add next param
        param_t *param = (param_t *) calloc(1, sizeof(param_t));
        param_t *cparam = cmd->param_list;

        cmd->param_count++;
        // Put something in here to strip out the single quotes if
        // they are the first/last characters in arg.
        if (arg[0] == '\'') {
          arg++;
        }

        if (arg[strlen(arg) - 1] == '\'') {
          arg[strlen(arg) - 1] = '\0';
        }

        param->param = strdup(arg);

        if (NULL == cparam) {
          cmd->param_list = param;
        } else {
          // I should put a tail pointer on this.
          while (cparam->next != NULL) {
            cparam = cparam->next;
          }

          cparam->next = param;
        }
      }
    }
    // This could overwite some bogus file redirection.
    if (cmd->list_location > 0) {
      cmd->input_src = REDIRECT_PIPE;
    }

    if (cmd->list_location < (cmd_list->count - 1)) {
      cmd->output_dest = REDIRECT_PIPE;
    }

    cmd = cmd->next;
  }

  if (isVerbose > 0) {
    print_list(cmd_list);
  }
}

void addToHistory(char currentCommand[], stringListType *list) {
  stringNodeType *newNode = malloc(sizeof(stringNodeType));
  stringNodeType *currentNode = NULL;

  newNode->next = NULL;
  strcpy(newNode->data, currentCommand);

  if (list->count == 10) {
    currentNode = list->head;
    while (currentNode->next->next != NULL) {
      currentNode = currentNode->next;
    }

    free(currentNode->next);
    currentNode->next = NULL;
    list->count--;
  }

  if (list->head == NULL) {
    list->head = newNode;
  } else {
    currentNode = list->head;
    newNode->next = currentNode;
    list->head = newNode;
  }
  list->count++;
}

void print_history(stringNodeType *currentNode) {
  int index = 1;
  while (currentNode != NULL) {
    printf("%d %s\n", index, currentNode->data);
    currentNode = currentNode->next;
    index++;
  }
}

void free_history(stringListType *list) {
  stringNodeType *currentNode = list->head, *temp = NULL;
  while (currentNode != NULL) {
    temp = currentNode;
    currentNode = currentNode->next;
    free(temp);
  }
  free(list);
}

void addCommandToPipe(pipeListType *list, char *command[]) {
  int i = 0;
  pipeNodeType *newCommand = (pipeNodeType *)malloc(sizeof(pipeNodeType));
  newCommand->next = NULL;
  memset(newCommand->command, 0, sizeof(char *) * MAX_STR_LEN);

  while (command[i] != NULL) {
    newCommand->command[i] = strdup(command[i]);
    i++;
  }

  if (list->head == NULL) {
    list->head = newCommand;
    list->tail = newCommand;
  } else {
    list->tail->next = newCommand;
    list->tail = newCommand;
  }
}

void freePipeline(pipeListType *list) {
  pipeNodeType *currentNode = list->head;
  pipeNodeType *temp;

  while (currentNode != NULL) {
    temp = currentNode->next;
    freeCharPointerArray(currentNode->command);
    free(currentNode);
    currentNode = temp;
  }
  free(list);
}

void freeCharPointerArray(char *ourList[]) {
  int i = 0;
  while (ourList[i] != NULL) {
    free(ourList[i]);
    i++;
  }
}

void printPipeLine(pipeListType *list) {
  pipeNodeType *temp = list->head;
  int i = 0;

  while (temp != NULL) {
    i = 0;
    while (temp->command[i] != NULL) {
      printf("%s\n", temp->command[i]);
      i++;
    }
    temp = temp->next;
  }
}

void pipeline(pipeListType *list, cmd_t *cmd) {
  pipeNodeType *currentNode = list->head;
  cmd_t *currentCommand = cmd;
  int pipeEnds[2];
  pid_t pid;
  int previousPipe = STDIN_FILENO;

  while (currentNode != NULL) {
    pipe(pipeEnds);
    if ((pid = fork()) == -1) {
      perror("fork");
      _exit(EXIT_FAILURE);
    } else if (pid == 0) {

      if (currentCommand->input_src == REDIRECT_FILE) {
        pipeEnds[0] = open(currentCommand->input_file_name, O_RDONLY);
        dup2(pipeEnds[0], STDIN_FILENO);
        close(pipeEnds[0]);
      } else {
        dup2(previousPipe, STDIN_FILENO);
      }

      if (currentCommand->output_dest == REDIRECT_FILE) {
        pipeEnds[STDOUT_FILENO] = open(currentCommand->output_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(pipeEnds[STDOUT_FILENO], STDOUT_FILENO);
      } else if (currentNode->next != NULL) {
        dup2(pipeEnds[STDOUT_FILENO], STDOUT_FILENO);
      }

      close(pipeEnds[STDIN_FILENO]);
      execvp(currentNode->command[STDIN_FILENO], currentNode->command);
      _exit(EXIT_FAILURE);
    } else {
      close(pipeEnds[STDOUT_FILENO]);
      previousPipe = pipeEnds[STDIN_FILENO];
      currentNode = currentNode->next;
      currentCommand = currentCommand->next;
      wait(NULL);
  	}
  }
}

void executeCommand(cmd_t *commandHead) {
  pipeListType *commandsToRun = (pipeListType *)malloc(sizeof(pipeListType));
  cmd_t *currentCommand = commandHead;
  char *externalCommand[MAX_STR_LEN];
  param_t *currentParam;
  int i = 1;

  commandsToRun-> head = commandsToRun->tail = NULL;

  while (currentCommand != NULL) {
    memset(externalCommand, 0, sizeof(char *) * MAX_STR_LEN);
    externalCommand[0] = strdup(currentCommand->cmd);
    currentParam = currentCommand->param_list;

    i = 1;
    while (currentParam != NULL) {
      externalCommand[i++] = strdup(currentParam->param);
      currentParam = currentParam->next;
    }
    addCommandToPipe(commandsToRun, externalCommand);

    currentCommand = currentCommand->next;

    freeCharPointerArray(externalCommand);
  }

  pipeline(commandsToRun, commandHead);
  freePipeline(commandsToRun);
}

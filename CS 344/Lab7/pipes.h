# define MAX_STR_LEN 1024

typedef struct pipeNode {
   char *command[MAX_STR_LEN];
   struct pipeNode *next;
} pipeNodeType;

typedef struct pipeList {
    pipeNodeType *head;
    pipeNodeType *tail;
    int count;
} pipeListType;

void addCommandToPipe(pipeListType *, char * []);
void freePipeline(pipeListType *);
void freeCharPointerArray(char * []);
void printPipeLine(pipeListType *);
void pipeline(pipeListType *);

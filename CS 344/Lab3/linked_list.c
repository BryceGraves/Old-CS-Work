#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char *strdup(char * value);
list_t* createList(void);
void _addLink(list_t *ourList, char *fileBuffer);
void readFileToList(int argc, char *argv[], list_t  *ourList);
void printList(list_t  *ourList);
void freeList(list_t *ourList);

list_t* createList(void) {
  list_t *newList = malloc(sizeof(list_t));
  newList->head = NULL;
  return newList;
}

void _addLink(list_t *ourList, char *fileBuffer) {
  node_t *newLink = (node_t *)malloc(sizeof(node_t));

  newLink->line = fileBuffer;
  newLink->next = NULL;

  if (ourList->head == NULL) {
    ourList->head = newLink;
    ourList->tail = newLink;
  } else {
    ourList->tail->next = newLink;
    ourList->tail = newLink;
  }
}

void readFileToList(int argc, char *argv[], list_t  *ourList) {
  char *bufferPointer = NULL, fileBuffer[LINE_MAX];
  FILE *inputFile;
  int i;

  for (i = 1; i < argc; i++) {
    inputFile = fopen(argv[i], "r");

    while ((bufferPointer = fgets(fileBuffer, LINE_MAX, inputFile)) != NULL) {
      _addLink(ourList, strdup(fileBuffer));
    }

    fclose(inputFile);
  }
}

void printList(list_t  *ourList) {
  node_t *currentLink = ourList->head;
  int i = 1;

  while (currentLink != NULL) {
      printf("%04d:  %s", i, currentLink->line);
      currentLink = currentLink->next;
      i++;
  }
}

void freeList(list_t *ourList) {
  node_t *currentLink = ourList->head;
  node_t *temporaryNode;

  while (currentLink != NULL) {
      temporaryNode = currentLink;
      currentLink = currentLink->next;
      free(temporaryNode->line);
      free(temporaryNode);
  }
  free(ourList);
}

int main(int argc, char *argv[]) {
  list_t *linkedList = createList();

  readFileToList(argc, argv, linkedList);
  printList(linkedList);
  freeList(linkedList);

  return(EXIT_SUCCESS);
}

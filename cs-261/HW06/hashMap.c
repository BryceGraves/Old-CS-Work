#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"

int hashingFunction(struct hashMap *ht, int hashIndex, KeyType k);

int isItPrime(int n);

int nextPrime(int n);

struct hashLink {
   KeyType key; /*the key is what you use to look up a hashLink*/
   ValueType value; /*the value stored with the hashLink, a pointer to int in the case of concordance*/
   struct hashLink * next; /*notice how these are like linked list nodes*/
};
typedef struct hashLink hashLink;

struct hashMap {
    hashLink ** table; /*array of pointers to hashLinks*/
    int tableSize; /*number of buckets in the table*/
    int count; /*number of hashLinks in the table*/
};
typedef struct hashMap hashMap;

/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; // the difference between 1&2
	return r;
}

/* initialize the supplied hashMap struct*/
void _initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	_initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashLink, free the memory occupied by key and value
 */
 void _freeMap (struct hashMap * ht)
 {
 	int i;
 	struct hashLink *temp;
 	struct hashLink *temp2;
 	for(i=0; i<ht->tableSize; i++){
 		temp=ht->table[i];
 		while(temp!=0){
 			temp2=temp->next;
 			free(temp->key);
 			free(temp->value);
 			free(temp);
 			temp=temp2;
 		}
 	}
 	free(ht->table);
 	ht->count=0;
 	ht->table=0;
 	ht->tableSize=0;
 }

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/*
Resizes the hash table to be the size newTableSize
Remember what you had to do for the dynamic array!
This isn't elegant. Values have to be moved.
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
  struct hashMap *biggerMap;
  struct hashLink *currLink;
	biggerMap = createMap(newTableSize);
  printf("Fuck you, resizing! \n");

  for (int i = 0; i < ht->tableSize; ++i) {
    currLink = ht->table[i];
    while (currLink != 0) {
      ht->count--;
      insertMap(biggerMap, currLink->key, currLink->value);
      ht->count++;
      currLink = currLink->next;
    }
  }
  printf("Freeing the fucking table. \n");
  _freeMap(ht);
  printf("Finished freeing the fucking table. \n");
  ht->table = biggerMap->table;
  ht->tableSize = biggerMap->tableSize;
  ht->count = biggerMap->count;
  printf("assigning bigger map to ht! \n");
}

/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink--this requires freeing up the old memory pointed by hashLink->value
 and then pointing hashLink->value to value v.

 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{
  printf("Does this even start? \n");
	int hashIndex = hashingFunction(ht, hashIndex, k);
  struct hashLink* new = malloc(sizeof(struct hashLink));

  printf("Does it break here? \n");
  //initialize new link
  assert(new);
  new->next = 0;
  new->key = k;
  new->value = v;

  //check to see if map contains key. If so, remove it.
  printf("Does it break here? 1 \n");
  if(containsKey(ht, k)){
    printf("Does it break before break? \n");
    removeKey(ht, k);
    printf("Does it break after break? \n");
  }
  printf("Does it break here? 2 \n");

  if (hashIndex < 0) {
      hashIndex += ht->tableSize;
  }

  if (!ht->table[hashIndex]) {
    printf("Does it break here? 3 \n");
    ht->table[hashIndex] = new;
    printf("Does it break here? 4 \n");
  }

  else
  {
    printf("Does it break here? 5 \n");
    struct hashLink* cur = ht->table[hashIndex];
    printf("Does it break here? 6 \n");
    while (cur->next) {
      cur = cur->next;
    }
    printf("Does it break here? 7 \n");

    cur->next = new;
    printf("Does it break here? 8 \n");
  }
  ht->count++;

  if (tableLoad(ht) >= LOAD_FACTOR_THRESHOLD) {
    printf("Final break? \n");
    _setTableSize(ht, ht->tableSize * 2);
  }
}

/*
 this returns the value (which is void*) stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashLink that represents taco.

 if the supplied key is not in the hashtable return NULL.
 */
ValueType atMap (struct hashMap * ht, KeyType k)
{
	int hashIndex = hashingFunction(ht, hashIndex, k);
  struct hashLink *currLink;

  currLink = ht->table[hashIndex];

  while (currLink != 0) {
    if (strcmp(k, currLink->key) == 0) {
      return currLink->value;
    }
    currLink = currLink->next;
  }

  return 0;
}

/*
 a simple yes/no if the key is in the hashtable.
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{
  int hashIndex = hashingFunction(ht, hashIndex, k);
  struct hashLink *currLink;

  currLink = ht->table[hashIndex];

  while (currLink != 0) {
    if (strcmp(k, currLink->key) == 0) {
      return 1;
    }
    currLink = currLink->next;
  }

  return 0;
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{
  int hashIndex = hashingFunction(ht, hashIndex, k);

  //pointer of a pointer to the Linked List address
  hashLink **currLink = &ht->table[hashIndex];

  //while there is an address at currLink pointer
  while (*currLink) {
    //assign currLink as filler link
    hashLink *temp = *currLink;

    //If they don't compare assign next to temp, then free it
    //If they do assign next numbers address to current link's address.
    if (strcmp(temp->key, k) == 0) {
      *currLink = temp->next;
      free(temp);
      break;
    } else {
      currLink = &(*currLink)->next;
      return;
    }
  }
}

/*
 returns the number of hashLinks in the table
 */
int size (struct hashMap *ht)
{
	return ht->count;
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{
  return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{
  int numberEmpty = 0;

  for (int i = 0; i < ht->tableSize; i++) {
    if (ht->table[i] == 0) {
      numberEmpty++;
    }
  }

  return numberEmpty;
}

/*
 returns the ratio of: (number of hashlinks) / (number of buckets)

 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashlinks then buckets (but remember hashlinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{
  float loadRatio = 0.0;

  loadRatio = (float)ht->count / (float)ht->tableSize;

  return loadRatio;
}

/* print the hashMap */
void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {
			printf("\nBucket Index %d -> ", i);
		}
		while(temp != 0){
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;
		}
	}
}

int hashingFunction(struct hashMap *ht, int hashIndex, KeyType k) {
  if(HASHING_FUNCTION == 1) {
    hashIndex = stringHash1(k) % ht->tableSize;
  } else {
    hashIndex = stringHash2(k) % ht->tableSize;
  }

  return hashIndex;
}

int isItPrime(int n) {
  for (int i = 2; i <= n/2; i++){
    if (n%i == 0){
      return 0;
    }
  }
  return 1;
}

int nextPrime(int n) {
  n++;
  if (n == 2){
    return 3;
  }
  else if (n == 3){
    return 5;
  }
  else if (isItPrime(n) == 1){
    return n;
  }
  return nextPrime(n);
}

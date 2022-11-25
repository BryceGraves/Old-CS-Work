/*
 File: bst.c
 Implementation of the binary search tree data structure.
 TO COMPILE:
 Linux/Win: gcc -shared -Wl,-soname,bsT -o bsT.so -fPIC bst.c
 Mac: gcc -shared -Wl,-install_name,bsT.so -o bsT.so -fPIC bst.c
 ***
 if your python is 32 bit, you may need to add the -m32 flag!
 run: "import platform; platform.architecture()"
 in the python interpreter to check
 If you had to make other changes for linked list, you may have to make them here!
*/

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "bst.h"

struct Node {
	TYPE         val;
	struct Node *left;
	struct Node *right;
};

struct BSTree {
	struct Node *root;
	int          count;
};

/*----------------------------------------------------------------------------*/
/*
 function to initialize the binary search tree.
 param tree
 pre: tree is not null
 post:	tree size is 0
		root is null
 */

void initBSTree(struct BSTree *tree)
{
	tree->count  = 0;
	tree->root = 0;
}

/*
 function to create a binary search tree.
 param: none
 pre: none
 post: tree->count = 0
		tree->root = 0;
 */

struct BSTree*  newBSTree()
{
	struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
	assert(tree != 0);

	initBSTree(tree);
	return tree;
}

/*----------------------------------------------------------------------------*/
/*
function to free the nodes of a binary search tree
param: node  the root node of the tree to be freed
 pre: none
 post: node and all descendants are deallocated
*/

void _freeBST(struct Node *node)
{
	if (node != 0) {
		_freeBST(node->left);
		_freeBST(node->right);
		free(node);
	}
}

/*
 function to clear the nodes of a binary search tree
 param: tree    a binary search tree
 pre: tree ! = null
 post: the nodes of the tree are deallocated
		tree->root = 0;
		tree->count = 0
 */
void clearBSTree(struct BSTree *tree)
{
	_freeBST(tree->root);
	tree->root = 0;
	tree->count  = 0;
}

/*
 function to deallocate a dynamically allocated binary search tree
 param: tree   the binary search tree
 pre: tree != null;
 post: all nodes and the tree structure itself are deallocated.
 */
void deleteBSTree(struct BSTree *tree)
{
	clearBSTree(tree);
	free(tree);
}

/*----------------------------------------------------------------------------*/
/*
 function to determine if  a binary search tree is empty.
 param: tree    the binary search tree
 pre:  tree is not null
 */
int isEmptyBSTree(struct BSTree *tree) {
	return (tree->count == 0);
}

/*
 function to determine the size of a binary search tree
param: tree    the binary search tree
pre:  tree is not null
*/
int sizeBSTree(struct BSTree *tree) {
	return tree->count;
}

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater than, less than, or
 equal to the right value.
 if left < right return -1
 if left > right return 1
 if left == right return 0
*/

/*
I have greatly simplified this function from past iterations of this course.
It used to be that you'd have to deal with cases other than ints, but it is safe
to assume TYPE will always be cast to int for this assignment.
*/
int compare(TYPE left, TYPE right)
{

	if (left < right)
		return -1;
	else if (right < left)
		return 1;
	else
		return 0;

}

/*
 function to determine if the binary search tree contains a particular element
 HINT: You have to use the compare() function to compare values.
 param:	tree	the binary search tree
		val		the value to search for in the tree
 pre:	tree is not null
		val is not null
 post:	none
 */

/*----------------------------------------------------------------------------*/
int containsBSTree(struct BSTree *tree, TYPE val)
{
	struct Node *cur = tree->root;

	assert(tree != NULL);

	while(cur != NULL) {
		if (compare(cur->val, val) == -1) {
			cur = cur->left;
		} else if (compare(cur->val, val) == 1) {
			cur = cur->right;
		} else {
			return 1;
		}
	}
	return 0;
	}

/*----------------------------------------------------------------------------*/
/*
 recursive helper function to add a node to the binary search tree.
 HINT: You have to use the compare() function to compare values.
 param:  cur	the current root node
		 val	the value to be added to the binary search tree
 pre:	val is not null
 */
struct Node *_addNode(struct Node *cur, TYPE val)
{
	//assert(cur->val != val);

	if (cur == NULL) {
		struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
		newNode->val = val;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}

	if (compare(cur->val, val) == -1) {
		cur->left = _addNode(cur->left, val);
	} else if (compare(cur->val, val) == 1) {
		cur->right = _addNode(cur->right, val);
	}

}

/*
 function to add a value to the binary search tree
 param: tree   the binary search tree
		val		the value to be added to the tree
 pre:	tree is not null
		val is not null
 pose:  tree size increased by 1
		tree now contains the value, val
 */
void addBSTree(struct BSTree *tree, TYPE val)
{
	if (containsBSTree(tree, val) == 0) {
		tree->root = _addNode(tree->root, val);
		tree->count++;
	}

}

/*
 helper function to find the left most child of a node
 return the value of the left most child of cur
 param: cur		the current node
 pre:	cur is not null
 post: none
 */

/*----------------------------------------------------------------------------*/
TYPE _leftMost(struct Node *cur)
{

	assert(cur != NULL);
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur->val;

}


/*
 recursive helper function to remove the left most child of a node
 HINT: this function returns cur if its left child is NOT NULL. Otherwise,
 it returns the right child of cur and free cur.
Note:  If you do this iteratively, the above hint does not apply.
 param: cur	the current node
 pre:	cur is not null
 post:	the left most node of cur is not in the tree
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeLeftMost(struct Node *cur)
{

	if (cur->left != NULL) {
		cur = cur->left;
		_removeLeftMost(cur);
	} else {
		if (cur->right != NULL) {
			struct Node *temp = cur->right;
			free(cur);
			return temp;
		} else {
			struct Node *removed = cur;
			free(cur);
			return removed;
		}
	}

}
/*
 recursive helper function to remove a node from the tree
 HINT: You have to use the compare() function to compare values.
 param:	cur	the current node
		val	the value to be removed from the tree
 pre:	val is in the tree
		cur is not null
		val is not null
 */
/*----------------------------------------------------------------------------*/
struct Node *_removeNode(struct Node *cur, TYPE val)
{
	assert(cur != NULL);

  if (compare(cur->val, val) == 0) {

//Check if node does not have two children
		if (cur->right == NULL) {
      struct Node *temp = cur->left;
      free(cur);
      return temp;
    } else if (cur->left == NULL) {
      struct Node *temp = cur->right;
      free(cur);
      return temp;
    } else {
			struct Node *temp = cur->left;
			cur->val = _leftMost(cur->right);
			cur->right = _removeLeftMost(cur->right);
			return temp;
		}
    } else if (compare(cur->val, val) == -1) {
      cur->left = _removeNode(cur->left, val);
    } else {
      cur->right = _removeNode(cur->right, val);
    }
  }

/*
 function to remove a value from the binary search tree
 param: tree   the binary search tree
		val		the value to be removed from the tree
 pre:	tree is not null
		val is not null
		val is in the tree
 pose:	tree size is reduced by 1
 */
void removeBSTree(struct BSTree *tree, TYPE val)
{
	if (containsBSTree(tree, val) == 1) {
		tree->root = _removeNode(tree->root, val);
		tree->count--;
	}
}

/*----------------------------------------------------------------------------*/
void print_val(TYPE curval, int level)
{
	printf(" L%i:%i ", level, curval);
}

void printNode(struct Node *cur, int level) {
	 if (cur == 0) return;
	 printf("(");
	 printNode(cur->left, level+1);
	 /*Call print_val which prints the value of the TYPE*/
	 print_val(cur->val, level);
	 printNode(cur->right, level+1);
	 printf(")");
}

// PLEASE NOTE: This isn't perfect. I added it to help you debug more visually.
// It prints left to right instead of top to bottom, but hopefully shows you
// something resembling shape. There is no promise or warranty.
void printNodeDepth(struct Node *cur, int level) {
     int spaces, i;

	 if (cur == 0) return;
     if (level > 10){
	    printf("Depth print doesn't exceed 10 for formatting reasons. This may already look like crap.");
	    return;
	 }

	 printNodeDepth(cur->right, level+1);

     spaces = level*15;
     for(i=0; i<spaces; i++){
	    printf(" ");
	 }
	 printf("(");
	 print_val(cur->val, level);
	 printf(")\n");

	 printNodeDepth(cur->left, level+1);
}

void printTree(struct BSTree *tree) {
	 if (tree == 0) return;
	 printNode(tree->root, 0);
	 printf("\n");
}

void printTreeDepth(struct BSTree *tree){
	 if (tree == 0) return;
	 printNodeDepth(tree->root, 0);
	 printf("\n");
}

/*----------------------------------------------------------------------------*/

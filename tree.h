#ifndef _TREE
#define _TREE

#include <stdio.h>

struct _Tree {
	int key;
	struct _Tree *left;
	struct _Tree *right;
	int count;
	int height;
};

typedef struct _Tree Tree;

Tree * createNode(int key);
int height(Tree *t);
Tree * leftRotate(Tree *x);
Tree * rightRotate(Tree *y);

Tree * createTree();
int empty(Tree *t);
Tree * clearTree(Tree *t);
Tree * add(Tree *t, int key);
int find(Tree *t, int key);
Tree * delete(Tree *t, int key);

int recHeight(Tree *t);
int validAVL(Tree *t);
void convert2DOT(Tree *t, FILE *fptr);

int rankQ(Tree *t, int k);
int * rangeQ(Tree *t, int k1, int k2, int *size);
int inOrderSucc(Tree *t, int key);
int inOrderPred(Tree *t, int key);

#endif
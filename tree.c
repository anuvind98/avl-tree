/*
AVL Tree in C
Author: Anuvind Bhat
Date: 28th May 2018
A C implementation of a multi-set using an AVL Tree as the underlying data structure
*/

#include "tree.h"
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

Tree * createNode(int key) {
	Tree *newNode = (Tree *)malloc(sizeof(Tree));
	newNode->key = key;
	newNode->left = newNode->right = NULL;
	newNode->count = 1;
	newNode->height = 1;
	return newNode;
}

int height(Tree *t) {
	if(t == NULL) {
		return 0;
	}
	return t->height;
}

Tree * leftRotate(Tree *x) {
	Tree *y = x->right;
	Tree *b = y->left;

	y->left = x;
	x->right = b;

	x->height = 1 + MAX(height(x->left), height(x->right));
	y->height = 1 + MAX(height(y->left), height(y->right));

	return y;
}

Tree * rightRotate(Tree *y) {
	Tree *x = y->left;
	Tree *b = x->right;

	x->right = y;
	y->left = b;

	y->height = 1 + MAX(height(y->left), height(y->right));
	x->height = 1 + MAX(height(x->left), height(x->right));

	return x;
}

Tree * createTree() {
	return NULL;
}

int empty(Tree *t) {
	return t == NULL;
}

void clearTreeUtil(Tree *t) {
	if(t == NULL) {
		return;
	}
	clearTreeUtil(t->left);
	clearTreeUtil(t->right);
	free(t);
}

Tree * clearTree(Tree *t) {
	clearTreeUtil(t);
	return NULL;
}

Tree * add(Tree *t, int key) {
	if(t == NULL) {
		return createNode(key);
	}

	if(key == t->key) {
		t->count += 1;
		return t;
	}

	if(key < t->key) {
		t->left = add(t->left, key);
	}
	else {
		t->right = add(t->right, key);
	}

	t->height = 1 + MAX(height(t->left), height(t->right));

	int balance = height(t->right) - height(t->left);
	if(balance < -1) {
		if(key > t->left->key) {
			t->left = leftRotate(t->left);
		}
		return rightRotate(t);
	}
	if(balance > 1) {
		if(key < t->right->key) {
			t->right = rightRotate(t->right);
		}
		return leftRotate(t);
	}

	return t;
}

int find(Tree *t, int key) {
	if(t == NULL) {
		return 0;
	}

	if(key < t->key) {
		return find(t->left, key);
	}
	if(key > t->key) {
		return find(t->right, key);
	}
	return t->count;
}

Tree * delete(Tree *t, int key) {
	if(t == NULL) {
		return t;
	}

	if(key < t->key) {
		t->left = delete(t->left, key);
	}
	else if(key > t->key) {
		t->right = delete(t->right, key);
	}
	else {
		if(t->count > 1) {
			t->count -= 1;
			return t;
		}

		if(t->left == NULL) {
			Tree *temp = t->right;
			free(t);
			return temp;
		}
		else if(t->right == NULL) {
			Tree *temp = t->left;
			free(t);
			return temp;
		}
		else {
			Tree *succ = t->right;
			while(succ->left != NULL) {
				succ = succ->left;
			}

			t->key = succ->key;
			t->count = succ->count;

			succ->count = 1;
			t->right = delete(t->right, succ->key);
		}
	}

	t->height = 1 + MAX(height(t->left), height(t->right));

	int balance = height(t->right) - height(t->left);
	if(balance < -1) {
		int childBalance = height(t->left->right) - height(t->left->left);
		if(childBalance > 0) {
			t->left = leftRotate(t->left);
		}
		return rightRotate(t);
	}
	if(balance > 1) {
		int childBalance = height(t->right->right) - height(t->right->left);
		if(childBalance < 0) {
			t->right = rightRotate(t->right);
		}
		return leftRotate(t);
	}

	return t;
}

int recHeight(Tree *t) {
	if(t == NULL) {
		return 0;
	}
	return 1 + MAX(recHeight(t->left), recHeight(t->right));
}

int validAVL(Tree *t) {
	if(t == NULL) {
		return 1;
	}

	if(t->left != NULL && t->left->key > t->key) {
		return 0;
	}
	if(t->right != NULL && t->right->key < t->key) {
		return 0;
	}

	int balance = recHeight(t->right) - recHeight(t->left);
	if(balance < -1 || balance > 1) {
		return 0;
	}

	return validAVL(t->left) && validAVL(t->right);
}

void convert2DOTUtil(Tree *t, FILE *fptr) {
	if(t->left != NULL) {
		fprintf(fptr, "\t\"%d(%d)\" -> \"%d(%d)\" [color=\"red\" label=\"L\"];\n", t->key, t->count, t->left->key, t->left->count);
		convert2DOTUtil(t->left, fptr);
	}
	if(t->right != NULL) {
		fprintf(fptr, "\t\"%d(%d)\" -> \"%d(%d)\" [color=\"blue\" label=\"R\"];\n", t->key, t->count, t->right->key, t->right->count);
		convert2DOTUtil(t->right, fptr);
	}
}

void convert2DOT(Tree *t, FILE *fptr) {
	fprintf(fptr, "digraph BinaryTree {\n");
	if(t == NULL) {;}
	else if(t->left == NULL && t->right == NULL) {
		fprintf(fptr, "\t\"%d(%d)\";\n", t->key, t->count);
	}
	else {
		convert2DOTUtil(t, fptr);
	}
	fprintf(fptr, "}\n");
}

void rankQUtil(Tree *t, int *k, int *ans) {
	if(t == NULL || *k <= 0) {
		return;
	}

	rankQUtil(t->left, k, ans);
	if(*k > 0) {
		*k -= t->count;
		if(*k <= 0) {
			*ans = t->key;
			return;
		}
	}
	rankQUtil(t->right, k, ans);
}

int rankQ(Tree *t, int k) {
	int ans = -1;
	rankQUtil(t, &k, &ans);
	return ans;
}

void rangeQUtil(Tree *t, int k1, int k2, int **ptr2arr, int *size) {
	if(t == NULL) {
		return;
	}

	if(k1 < t->key) {
		rangeQUtil(t->left, k1, k2, ptr2arr, size);
	}
	if(k1 <= t->key && t->key <= k2) {
		int temp = *size;
		*size += t->count;
		*ptr2arr = (int *)realloc(*ptr2arr, *size * sizeof(int));
		int i;
		for(i = temp; i < *size; ++i) {
			*(*ptr2arr + i) = t->key;
		}
	}
	if(t->key < k2) {
		rangeQUtil(t->right, k1, k2, ptr2arr, size);
	}
}

int * rangeQ(Tree *t, int k1, int k2, int *size) {
	int **ptr2arr = (int **)malloc(sizeof(int *));
	*ptr2arr = NULL;
	*size = 0;
	rangeQUtil(t, k1, k2, ptr2arr, size);
	int *arr = *ptr2arr;
	free(ptr2arr);
	return arr;
}

int inOrderSucc(Tree *t, int key) {
	Tree *curr = t, *ancestor = NULL;
	while(1) {
		if(curr == NULL) {
			return -2;
		}

		if(key < curr->key) {
			ancestor = curr;
			curr = curr->left;
		}
		else if(key > curr->key) {
			curr = curr->right;
		}
		else {
			break;
		}
	}

	if(curr->right == NULL) {
		if(ancestor == NULL) {
			return -1;
		}
		return ancestor->key;
	}

	Tree *succ = curr->right;
	while(succ->left != NULL) {
		succ = succ->left;
	}
	return succ->key;
}

int inOrderPred(Tree *t, int key) {
	Tree *curr = t, *ancestor = NULL;
	while(1) {
		if(curr == NULL) {
			return -2;
		}

		if(key < curr->key) {
			curr = curr->left;
		}
		else if(key > curr->key) {
			ancestor = curr;
			curr = curr->right;
		}
		else {
			break;
		}
	}

	if(curr->left == NULL) {
		if(ancestor == NULL) {
			return -1;
		}
		return ancestor->key;
	}

	Tree *pred = curr->left;
	while(pred->right != NULL) {
		pred = pred->right;
	}
	return pred->key;
}

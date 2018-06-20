#include "tree.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

Tree * randomPopulate(Tree *t, int num, int lo, int hi) {
	int i;
	hi += 1;
	for(i = 0; i < num; ++i) {
		t = add(t, rand() % (hi - lo) + lo);
	}
	return t;
}

Tree * linearPopulate(Tree *t, int lo, int hi) {
	int i;
	for(i = lo; i <= hi; ++i) {
		t = add(t, i);
	}
	return t;
}

double getTimeInMS(struct timespec begin, struct timespec end) {
	return (double)(end.tv_sec - begin.tv_sec) * 1000.0 + (double)(end.tv_nsec - begin.tv_nsec) / 1000000.0;
}

int main() {
	srand((unsigned int)time(NULL));

	int choice, i, size;
	int num, lo, hi, key, count, k, k1, k2, succ, pred;
	Tree *t = createTree();
	FILE *fptr;
	int *arr;
	struct timespec begin, end;

	do {
		printf("0. Exit\n");
		printf("1. Clear Tree\n");
		printf("2. Check if AVL tree\n");
		printf("3. Random Populate [num, lo, hi]\n");
		printf("4. Linear Populate [lo, hi]\n");
		printf("5. Write tree to file\n");
		printf("6. Add key [key, count]\n");
		printf("7. Find key [key]\n");
		printf("8. Delete key [key, count]\n");
		printf("9. Rank Query [k]\n");
		printf("10. Range Query [k1, k2]\n");
		printf("11. In-order successor [key]\n");
		printf("12. In-order predecessor [key]\n");
		printf("\n");

		assert(scanf("%d", &choice) == 1);
		switch(choice) {
		case 1:
			clock_gettime(CLOCK_MONOTONIC, &begin);
			t = clearTree(t);
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("Cleared the tree in %lf ms\n", getTimeInMS(begin, end));
			break;
		case 2:
			if(validAVL(t)) {
				printf("Valid\n");
			}
			else {
				printf("Invalid\n");
			}
			break;
		case 3:
			assert(scanf("%d %d %d", &num, &lo, &hi) == 3);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			t = randomPopulate(t, num, lo, hi);
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("Inserted %d keys in %lf ms\n", num, getTimeInMS(begin, end));
			break;
		case 4:
			assert(scanf("%d %d", &lo, &hi) == 2);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			t = linearPopulate(t, lo, hi);
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("Inserted %d keys in %lf ms\n", hi - lo + 1, getTimeInMS(begin, end));
			break;
		case 5:
			fptr = fopen("bst.dot", "w");
			convert2DOT(t, fptr);
			fclose(fptr);
			break;
		case 6:
			assert(scanf("%d %d", &key, &count) == 2);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			for(i = 0; i < count; ++i) {
				t = add(t, key);
			}
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("Inserted %d keys in %lf ms\n", count, getTimeInMS(begin, end));
			break;
		case 7:
			assert(scanf("%d", &key) == 1);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			count = find(t, key);
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("%d has count %d (%lf ms)\n", key, count, getTimeInMS(begin, end));
			break;
		case 8:
			assert(scanf("%d %d", &key, &count) == 2);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			for(i = 0; i < count; ++i) {
				t = delete(t, key);
			}
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("Deleted %d keys in %lf ms\n", count, getTimeInMS(begin, end));
			break;
		case 9:
			assert(scanf("%d", &k) == 1);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			key = rankQ(t, k);
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("The key with rank %d is %d (%lf ms)\n", k, key, getTimeInMS(begin, end));
			break;
		case 10:
			assert(scanf("%d %d", &k1, &k2) == 2);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			arr = rangeQ(t, k1, k2, &size);
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("The keys in the range [%d, %d] are (%lf ms):\n", k1, k2, getTimeInMS(begin, end));
			for(i = 0; i < size; ++i) {
				printf("%d ", arr[i]);
			}
			printf("\n");
			free(arr);
			break;
		case 11:
			assert(scanf("%d", &key) == 1);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			succ = inOrderSucc(t, key);
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("The in-order successor of %d is %d (%lf ms)\n", key, succ, getTimeInMS(begin, end));
			break;
		case 12:
			assert(scanf("%d", &key) == 1);
			clock_gettime(CLOCK_MONOTONIC, &begin);
			pred = inOrderPred(t, key);
			clock_gettime(CLOCK_MONOTONIC, &end);
			printf("The in-order predecessor of %d is %d (%lf ms)\n", key, pred, getTimeInMS(begin, end));
			break;
		default:
			break;
		}
		printf("\n");
	} while(choice != 0);

	return 0;
}

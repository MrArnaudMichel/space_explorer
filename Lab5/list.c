#include <stdlib.h>
#include <stdio.h>

int randomGen(const int max) {
	return rand() % max + 1;
}

void fillTab(int* tab, int n) {
	for (int i = 0; i < n; i++) {
		tab[i] = rand() % 101;
	}
}

void interleave(int** lists, int* lengths, int num_lists, int* return_array) {
	int total_elements = 0;
	for (int i = 0; i < num_lists; i++) {
		total_elements += lengths[i];
	}

	int k = 0;
	int* indices = (int*)malloc(num_lists * sizeof(int));
	for (int i = 0; i < total_elements; i++) {
		for (int j = 0; j < num_lists; j++) {
			if (indices[j] < lengths[j]) {
				return_array[k++] = lists[j][indices[j]++];
			}
		}
	}
	free(indices);
}

void printTab(int* tab, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", tab[i]);
	}
	printf("\n");
}

void generateAndInterleave(int num_lists) {
	int** lists = (int**)malloc(num_lists * sizeof(int*));
	int* lengths = (int*)malloc(num_lists * sizeof(int));

	int total_elements = 0;
	for (int i = 0; i < num_lists; i++) {
		lengths[i] = randomGen(10) + 10;
		total_elements += lengths[i];
		lists[i] = (int*)malloc(lengths[i] * sizeof(int));
		fillTab(lists[i], lengths[i]);
	}

	int* interleaved_array = (int*)malloc(total_elements * sizeof(int));

	interleave(lists, lengths, num_lists, interleaved_array);

	for (int i = 0; i < num_lists; i++) {
		printf("Tab%d: ", i + 1);
		printTab(lists[i], lengths[i]);
		free(lists[i]);
	}
	printf("Result : ");
	printTab(interleaved_array, total_elements);

	free(lists);
	free(lengths);
	free(interleaved_array);
}


int* reverse_array(int *array, int length){
	// return a reversed version of the array
	int i;
	int *reversed = malloc(length*sizeof(int)); // allocate enough bytes for an array of integers

	for (i=0;i<length;i++){
		reversed[length-1-i] = array[i];
	}
	return reversed;
}


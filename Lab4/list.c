//
// Created by arnaud on 22/02/24.
//

#include "list.h"

#include <stdlib.h>
#include <stdio.h>

int randomGen(const int max) {
	return rand() % max+1;
}

void fillTab(int* tab, int n) {
	for (int i = 0; i < n; i++) {
		tab[i] = rand() % 101;
	}
}

void interleave(int * first, int * first_length, int *second, int *second_length, int *return_array) {
	int i = 0, j = 0, k = 0;

	while (i < *first_length && j < *second_length) {
		return_array[k++] = first[i++];
		return_array[k++] = second[j++];
	}

	while (i < *first_length) {
		return_array[k++] = first[i++];
	}

	while (j < *second_length) {
		return_array[k++] = second[j++];
	}
}

void printTab(int* tab, int n) {
	for (int i =0; i < n; i++) {
		printf("%d ", tab[i]);
	}
	printf("\n");
}

void concatTab() {
	int array1length = randomGen(10) + 10;
	int array2length = randomGen(10) + 10;

	int *array1 = malloc(array1length * sizeof(int));
	int *array2 = malloc(array2length * sizeof(int));

	fillTab(array1, array1length);
	fillTab(array2, array2length);

	int *interleaved_array = malloc((array1length + array2length) * sizeof(int));
	int interleaved_length = array1length + array2length;

	interleave(array1, &array1length, array2, &array2length, interleaved_array);

	printf("Tab1: ");
	printTab(array1, array1length);
	printf("Tab2: ");
	printTab(array2, array2length);
	printf("Result : ");
	printTab(interleaved_array, interleaved_length);

	free(array1);
	free(array2);
	free(interleaved_array);
}

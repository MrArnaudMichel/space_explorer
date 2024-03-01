//
// Created by arnaud on 22/02/24.
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lab5/list.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: <NumberOfArrays>");
		return EXIT_FAILURE;
	}
	generateAndInterleave(atoi(argv[1]));
}
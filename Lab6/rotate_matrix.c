//
// Created by arnaud on 08/03/24.
//

#include "rotateMatrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int length_check(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

char *duplicate(char *str_in) {
    int string_length = length_check(str_in);

    char *string_copy = (char *)malloc((string_length + 1) * sizeof(char));
    for (int i = 0; i < string_length + 1; i++) {
        string_copy[i] = str_in[i];
    }

    return string_copy;
}

void rotate_clockwise(char **matrix, int rows, int cols, int *out_rows, int *out_cols) {
    char **temp_matrix = (char **)malloc(cols * sizeof(char *));
    for (int i = 0; i < cols; i++) {
        temp_matrix[i] = (char *)malloc(rows * sizeof(char));
        for (int j = 0; j < rows; j++) {
            temp_matrix[i][j] = matrix[j][i];
        }
    }
/*
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            char temp = temp_matrix[i][j];
            temp_matrix[i][j] = temp_matrix[i][rows - j - 1];
            temp_matrix[i][rows - j - 1] = temp;
        }
    }
*/
    *out_rows = cols;
    *out_cols = rows;

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            matrix[i][j] = temp_matrix[i][j];
        }
        free(temp_matrix[i]);
    }
    free(temp_matrix);
}

int lab6() {
    int nbDups;
    char my_string[10];
    int num_rows, num_cols, n;
    printf("Enter a string: ");
    scanf("%s", my_string);
    printf("nbDuplicates ");
    scanf("%d", &nbDups);

    n = strlen(my_string);

    char **duplicates = (char **)malloc(strlen(my_string) * sizeof(char *));
    for (int i = 0; i < n; i++) {
        duplicates[i] = duplicate(my_string);
    }

    rotate_clockwise(duplicates, nbDups, strlen(my_string), &num_rows, &num_cols);

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("%c ", duplicates[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(duplicates[i]);
    }
    free(duplicates);

    return 0;
}
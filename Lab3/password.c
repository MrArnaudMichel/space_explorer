//
// Created by arnaud on 02/02/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int passwordCheck(char* password) {
	printf("Enter password: ");
	int i = 0;
	char c;
	int valid = 1;
	int upper = 0;
	int lower = 0;
	int digit = 0;
	int special = 0;
	while (1) {
		c = getchar();
		if (c == '\n') {
			if (valid && upper && lower && digit && i >= 8) {
				printf("Password: ");
				for (int j = 0; j < i; j++) {
					printf("%c", password[j]);
				}
				printf("\n");
				if (special) {
					printf("Strong valid password\n");
				} else {
					printf("Weak valid password\n");
				}
				return EXIT_SUCCESS;
			}
			printf("Invalid password\n");
			return EXIT_FAILURE;
		}
		if (i < 16) {
			password[i] = c;
			i++;
			if (c >= 'A' && c <= 'Z') upper = 1;
			if (c >= 'a' && c <= 'z') lower = 1;
			if (c >= '0' && c <= '9') digit = 1;
			(c != ' ' && c != '\t' && c != '\r' && c != '\v' && c != '\f' && c != '\0') ? special = 1 : 0;
		} else {
			valid = 0;
		}
	}
}

char* reverseString(char* sourceString) {
	int size = strlen(sourceString);
	char* reversedString = malloc(size);
	for (int i = 0; i < size; i++) {
		reversedString[i] = sourceString[size - i - 1];
	}
	return reversedString;
}

int sumListOfNumber() {
	printf("Input: ");
	int index = 0;
	char* number = malloc(4 * sizeof(char));
	int sum = 0;
	while (1) {
		char const c = getchar();
		if (c != '\n' && c != ';') {
			printf("%c\n", c);
			if (c == ',') {
				sum += atoi(number);
				printf("%d", sum);
				memset(number, 0, 4);
				index = 0;
				continue;
			}
			number[index] = c;
		}
		else {
			free(number);
			printf("Sum: %d\n", sum);
			return sum;
		}
	}
}

int main(){
	// char password[16];
	// while (passwordCheck(password) != 0);
	sumListOfNumber();
	return EXIT_SUCCESS;
}

int * resample(const int *input, int length, int step_size) {
	printTab(input, length);
	int new_length = length / step_size + (length % step_size != 0);
	int* resampled = (int*)malloc(new_length * sizeof(int));
	for (int i = 0; i < new_length; i++) {
		resampled[i] = input[i * step_size];
	}
	printTab(resampled, new_length);
	return resampled;
}

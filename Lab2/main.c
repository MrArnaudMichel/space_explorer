#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encode(char letter, int key) {
	if (letter >= 'A' && letter <= 'Z') letter = letter + 'a' - 'A';
	if (letter >= 'a' && letter <= 'z') {
		letter = letter - 'a';
		letter = (letter + key) % 26;
		letter = letter + 'a';
	}
	return letter;
}

int main() {
	int key = 5;
	int const direction = getchar();
	switch (direction) {
		case '+':
			break;
		case '-':
			key = -key;
			break;
		default:
			printf("Invalid direction\n");
			return EXIT_FAILURE;
	}
	char letter = getchar();
	letter = encode(letter, key);
	printf("%c\n", letter);
	return EXIT_SUCCESS;
}

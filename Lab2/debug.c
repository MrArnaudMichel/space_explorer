//
// Created by arnaud on 26/01/24.
//

#include <stdio.h>

/*
* Encrypt a word through letter repetition.
* You are given a base word and a hidden word.
* In the base word each letter will be repeated a number of times
* equal to the offset of the corresponding hidden letter in the alphabet + 1.
* For example, to represent an 'a' you repeat the underlying letter 'a'-'a'+1,
* so once.
*
* Example run:
* base string: howareyou
* input: abcde
* output: hhooowwwwaaaaarrrrrr
*/

int main(){

	char base_string[] = "howareyou\0";
	char input = 0;
	int offset = 0;
	char idx = 0;
	int i;

	while (1){
		input = getchar();
		offset = input - 'a';
		for (i=0;i<offset;i++){
			printf("%c", base_string[idx]);
		}
		idx++;
		if (base_string[idx] == '\0'){
			break;
		}
	}
	printf("\n");
	return 0;
}
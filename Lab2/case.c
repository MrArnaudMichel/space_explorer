//
// Created by arnaud on 26/01/24.
//

#include "case.h"

int upperToLower(char c){
	if (c >= 'A' && c <= 'Z') c = c + 'a' - 'A';
	return c;
}

int lowerToUpper(char c){
	if (c >= 'a' && c <= 'z') c = c + 'A' - 'a';
	return c;
}
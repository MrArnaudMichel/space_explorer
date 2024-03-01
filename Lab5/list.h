//
// Created by arnaud on 22/02/24.
//

#ifndef LIST_H
#define LIST_H

int randomGen(int max);
void fillTab(int* tab, int n);

void generateAndInterleave(int num_lists);
void printTab(int* tab, int n);

int * resample(const int *input, int length, int step_size);

#endif //LIST_H

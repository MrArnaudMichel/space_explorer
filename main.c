//
// Created by arnaud on 22/02/24.
//
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Lab7/structs.h"
#include "Lab7/student.h"

int main(int argc, char* argv[]) {
	student* stud = malloc(sizeof(student));
	populate_subjects(stud);
	display_subject_statistics(stud);
	free_student(stud);

}
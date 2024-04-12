//
// Created by arnaud on 15/03/24.
//

#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct subject {
	char *subject_name;
	float grade;
    struct subject *next;
}subject;

// Structure definition for student
typedef struct student {
	char *name;
	int num_subjects;
	subject *subjects; // Pointer to a linked list of subjects
}student;

#endif //STRUCTS_H

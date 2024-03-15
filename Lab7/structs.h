//
// Created by arnaud on 15/03/24.
//

#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct subject {
	char *subject_name;
	float grade;
}subject;

// Structure definition for student
typedef struct student {
	char *name;
	int num_subjects;
	subject *subjects; // Pointer to an array of subjects
}student;

#endif //STRUCTS_H

//
// Created by arnaud on 15/03/24.
//

#include <stdio.h>
#include "student.h"

#include <stdlib.h>

#include "structs.h"


void student_init(student* student) {
	student->name = malloc(100 * sizeof(char));
	student->num_subjects = 0;
	student->subjects = NULL;
}

void free_student(student* student) {
	free(student->name);
	for (int i = 0; i < student->num_subjects; ++i) {
		free_subject(&student->subjects[i]);
	}
	student->num_subjects = 0;
	free(student->subjects);
}

void free_subject(subject* subject) {
	subject->grade = 0;
	free(subject->subject_name);
}

void subject_init(subject* subject) {
	subject->subject_name = malloc(100 * sizeof(char));
	subject->grade = 0;
}

void subject_fill(subject* subject) {
	printf("Subject name: ");
	scanf("%s", subject->subject_name);
	printf("Grade: ");
	scanf("%f", &subject->grade);
}

void populate_subjects(student *student1) {
	student_init(student1);
	int nb_subjects;
	printf("Name: ");
	scanf("%s", student1->name);
	printf("Nb of subjects: ");
	scanf("%d", &nb_subjects);
	student1->num_subjects = nb_subjects;
	student1->subjects = malloc(nb_subjects * sizeof(subject));
	for (int i = 0; i < nb_subjects; i++) {
		subject_init(&student1->subjects[i]);
		subject_fill(&student1->subjects[i]);
	}
}

void display_subject_statistics(const student *student) {
	float mean = 0;
	float max = 0;
	int index_max = 0;
	for (int i = 0; i < student->num_subjects; ++i) {
		mean += student->subjects[i].grade;
		if (student->subjects[i].grade > max) {
			max = student->subjects[i].grade;
			index_max = i;
		}
	}
	mean /= student->num_subjects;
	printf("Mean: %f\n", mean);
	printf("Max: %s\n", student->subjects[index_max].subject_name);
}
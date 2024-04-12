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
    subject* node = student->subjects;
    while (node != NULL) {
        subject* next = node->next;
        free_subject(node);
        node = next;
    }
    free(student);
}

void free_subject(subject* subject) {
    free(subject->subject_name);
    free(subject);
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

void add_subject(student *student){
    // linked list (Subject)
    student->num_subjects++;
    subject* node = student->subjects;
    if (node == NULL) {
        student->subjects = malloc(sizeof(subject));
        subject_init(student->subjects);
        subject_fill(student->subjects);
        return;
    }
    while (node->next != NULL) {
        node = node->next;
    }
    node->next = malloc(sizeof(subject));
    subject_init(node->next);
    subject_fill(node->next);
}

void populate_subjects(student *student1) {
	student_init(student1);
	int nb_subjects;
	printf("Name: ");
	scanf("%s", student1->name);
	printf("Nb of subjects: ");
	scanf("%d", &nb_subjects);
	student1->num_subjects = 0;
	student1->subjects = malloc(sizeof(subject));
	for (int i = 0; i < nb_subjects; i++) {
        add_subject(student1);
	}
}

void display_subject_statistics(const student *student) {
	float mean = 0;
	float max = 0;
	int index_max = 0;
    subject *node = student->subjects;
    mean += node->grade;
    while (node->next != NULL) {
        mean += node->grade;
        if (node->grade > max) {
            max = node->grade;
            index_max = student->num_subjects;
        }
        node = node->next;
    }
    mean += node->grade;
    if (node->grade > max) {
        index_max = student->num_subjects;
    }
	mean /= (float)student->num_subjects;
	printf("Mean: %f\n", mean);
    subject* node_max = student->subjects;
    for (int i = 0; i < index_max; i++) {
        node_max = node_max->next;
    }
    printf("Max: %s %f\n", node_max->subject_name, node_max->grade);
}
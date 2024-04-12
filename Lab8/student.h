//
// Created by arnaud on 15/03/24.
//

#ifndef STUDENT_H
#define STUDENT_H

#include "structs.h"

void populate_subjects(student *student1);
void display_subject_statistics(const student *student);

void student_init(student* student) ;

void subject_fill(subject* subject);
void subject_init(subject* subject);

void free_student(student* student);
void free_subject(subject* subject);

#endif //STUDENT_H

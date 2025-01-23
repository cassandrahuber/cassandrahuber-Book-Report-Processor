#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

#include "student.h"

int add_stu(struct student **, int, char[], char[]);
int read_stu_file(struct student **, char[], int);
int read_book_file(struct student *, char[], int);
int find_stu(struct student *, int, int, char[], char[]);
int delete_stu(struct student **);
int write_file(struct student *, char[]);
void cleanup(struct student **);

#endif

#ifndef STUDENT_H
#define STUDENT_H

struct student
{
    int                Student_ID;
    char               Last_Name[15];
    char               First_Name[15];
    int                Book_ID;
    char               Book_Title[25];
    char               Report_Submitted[4];
    struct student*    next;
};

#endif

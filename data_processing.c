#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
#include "data_processing.h"

/* allocate memory on heap for new student and iterate through list to add student's
 * ID in order, assuming no duplicates */

int add_stu(struct student **start, int Student_ID, char Last_Name[], char First_Name[])
{
    struct student *current, *prev, *new_stu;

    new_stu = (struct student *) malloc(sizeof(struct student));

    if (*start == NULL || Student_ID < (*start)->Student_ID)
    {
        new_stu->next = *start;
        *start = new_stu;
    }
    else
    {
        current = *start;
        prev = NULL;

        while (current != NULL && Student_ID > current->Student_ID)
        {
            prev = current;
            current = prev->next;
        }

        prev->next = new_stu;
        new_stu->next = current;
    }

    new_stu->Student_ID = Student_ID;
    strcpy(new_stu->Last_Name, Last_Name);
    strcpy(new_stu->First_Name, First_Name);
    new_stu->Book_ID = 0;
    new_stu->Book_Title[0] = '\0';
    new_stu->Report_Submitted[0] = '\0';

    return 0;
}

/* Reads students' ID and Last/First names from specified csv file by using
 * strtok() function that splits string on the line by a delimiter "," and calls
 * add_stu to create linked list in heap memory. using atoi cast string to int value. */

int read_stu_file(struct student **start, char filename[], int stu_num)
{
    FILE *infile;
    int Student_ID, return_val, i;
    char Last_Name[15], First_Name[15];
    char line[100], *token, *result;

    infile = fopen(filename, "r");

    if (!infile)
    {
        return_val = -1;
    }
    else
    {
        fgets(line, sizeof(line), infile);

        for (i = 0; i < stu_num; i++)
        {
            fgets(line, sizeof(line), infile);
            token = strtok(line, ",");
            Student_ID = atoi(token);

            token = strtok(NULL, ",");
            strcpy(Last_Name, token);

            token = strtok(NULL, ",");
            strcpy(First_Name, token);

            /* strchr finds occurance of '\r' character in First_Name
             * string, then replace with null character. */

            if ((result = strchr(First_Name, '\r')) != NULL)
            {
                *result = '\0';
            }

            add_stu(start, Student_ID, Last_Name, First_Name);
        }

        return_val = 0;
    }

    return return_val;
}

/* Reads book report info lines in specified csv file with strtok() like above,
 * but then uses each corresponding Student's ID # to connect it with the
 * rest of the student's info with find_stu. */

int read_book_file(struct student *start, char filename[], int stu_num)
{
    FILE *infile;
    int Book_ID, Student_ID, return_val, i;
    char Book_Title[25], Report_Submitted[4];
    char line[100], *token, *result;

    infile = fopen(filename, "r");

    if (!infile)
    {
        printf("Error! File failed to open.\n");
        return_val = -1;
    }
    else
    {
        fgets(line, sizeof(line), infile);

        for (i = 0; i < stu_num; i++)
        {
            fgets(line, sizeof(line), infile);
            token = strtok(line, ",");
            Book_ID = atoi(token);

            token = strtok(NULL, ",");
            strcpy(Book_Title, token);

            token = strtok(NULL, ",");
            Student_ID = atoi(token);

            token = strtok(NULL, ",");
            strcpy(Report_Submitted, token);

            if ((result = strchr(Report_Submitted, '\r')) != NULL)
            {
                *result = '\0';
            }

            find_stu(start, Student_ID, Book_ID, Book_Title, Report_Submitted);
        }

        return_val = 0;
    }

    return return_val;
}

/* Finds the student in the heap by ID # and updates their book report assignment info. */

int find_stu(struct student *start, int Stu_ID, int Book_ID, char Book_Title[], char Rept_Sbmtd[])
{
    int return_val = -1;
    struct student *current;

    if (start != NULL)
    {
        current = start;

        while (current != NULL && return_val == -1)
        {
            if (Stu_ID == current->Student_ID)
            {
                current->Book_ID = Book_ID;
                strcpy(current->Book_Title, Book_Title);
                strcpy(current->Report_Submitted, Rept_Sbmtd);

                return_val = 0;
            }
            else
            {
                current = current->next;
            }
        }

        if (current == NULL && return_val == -1)
        {
            printf("Error! Failed to update book report data.\n");
        }
    }

    return return_val;
}

/* Removes all students that have submitted their reports "YES", leaving only those
 * who have not in the list "NO". (deallocates memory in heap) */

int delete_stu(struct student **start)
{
    struct student *current, *prev, *temp;

    current = *start;
    prev = NULL;
    temp = NULL;

    if (*start != NULL)
    {
        while (current != NULL)
        {
            if (strcmp(current->Report_Submitted, "YES") == 0)
            {
                if (prev == NULL)
                {
                    *start = current->next;
                }
                else
                {
                    prev->next = current->next;
                }

                temp = current;
                current = current->next;
                free(temp);
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
    }
    return 0;
}

/* Writes the linked list in heap space to a specified csv filename. Will create a table
 * with a header and each student's data that is in the list. First time called there are
 * 30 students, second there are less. */

int write_file(struct student *start, char filename[])
{
    FILE *outfile;
    int return_val;
    struct student *current;

    outfile = fopen(filename, "w");

    if (!outfile)
    {
        printf("Error!  File failed to open.\n");
        return_val = -1;
    }
    else
    {
        current = start;
        fprintf(outfile, "Student_ID,Last_Name,First_Name,Book_ID,Book_Title,Report_Submitted\n");

        while (current != NULL)
        {
            fprintf(outfile, "%d,%s,%s,%d,%s,%s\n",
                    current->Student_ID,
                    current->Last_Name,
                    current->First_Name,
                    current->Book_ID,
                    current->Book_Title,
                    current->Report_Submitted);

            current = current->next;
        }

        fclose(outfile);
        return_val = 0;
    }

    return return_val;
}

/* "Cleaning" all allocated memory by deallocating it all until start == NULL. */

void cleanup(struct student **start)
{
    struct student *current;

    current = *start;

    while (current != NULL)
    {
        *start = current->next;
        free(current);
        current = *start;
    }
}

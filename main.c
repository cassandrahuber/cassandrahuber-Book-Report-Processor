#include <stdio.h>
#include "student.h"
#include "data_processing.h"

#define STU_NUM 30

/* main function that calls all data_processing functions. returns -1 if fail/
 * cleans the heap memory, 0 if sucess. */

int main(int argc, char *argv[])
{
    struct student *start = NULL;
    int result, return_val;

    result = read_stu_file(&start, "students.csv", STU_NUM);

    if (result != 0)
    {
        return_val = -1;
    }
    else
    {
        result = read_book_file(start, "book_report_assignments.csv", STU_NUM);

        if (result != 0)
        {
            cleanup(&start);
            return_val = -1;
        }
        else
        {
            write_file(start, "full_information.csv");

            if (result != 0)
            {
                cleanup(&start);
                return_val = -1;
            }
            else
            {
                delete_stu(&start);
                write_file(start, "pending_reports.csv");

                if (result != 0)
                {
                    return_val = -1;
                }

                cleanup(&start);
            }
        }
    }

    return return_val;
}

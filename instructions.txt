The file students.csv contains the student ID’s and names of 30 students.  The file book_report_assignments.csv contains the ID and title of 30 books and the ID of the student assigned to write a book report for a particular book and whether or not they’ve already submitted their report.  
You can assume that each student is assigned only 1 book and each book listed is assigned to only 1 student (no duplicates of anyone or anything).  Using any programming language of your choice, please write a program that creates the following 2 files.  In addition, please note that we would like to see applications of clean coding practices, such as modular functions and comments.

1.	A .csv file called full_information.csv containing the Book_ID, Book_Title, Student_ID, Last_Name, First_Name, and Report_Submitted columns and all the data from the 2 given .csv files consolidated (you will thus end up with exactly 30 rows in this new file since they are no duplicates).  For example, one of the rows in the file will be:
1113	Pennypacker	Phuong	97	Haunted In Eternity	YES

2. A .csv file called pending_reports.csv containing the same columns as the above problem but contains only the rows of data of the students who did not submit their book report yet (you will thus end up with less than 30 rows of data in this new file).

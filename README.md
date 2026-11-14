# Student Record Manager

A menu-driven console application in C to manage student records. Data is saved to a file, so records are still there the next time you run the program.

## Features
- Add a student (roll number, name, marks) with input validation
- Prevents duplicate roll numbers
- View all students in a table
- Search a student by roll number
- Delete a student
- Show the topper and class average
- Sort students by marks (highest first)
- Automatic save and load using a text file (`students.txt`)

## Concepts Used
Variables and data types, loops, `switch` statements, arrays, strings, functions, structures (array of structures), file handling, preprocessor directives (`#define`).

## How to Compile and Run
```bash
gcc main.c -o app
./app          # on Windows: app.exe
```

## Sample Menu
```
===== STUDENT RECORD MANAGER =====
1. Add student
2. View all students
3. Search student by roll number
4. Delete student
5. Show topper and average marks
6. Sort students by marks
7. Exit
```

## Author
Daksh Batra,29070,CSE-1,Sem-1

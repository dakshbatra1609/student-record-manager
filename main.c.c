#include <stdio.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "students.txt"

// one student's details
struct Student {
    int roll;
    char name[30];
    float marks;
};

struct Student students[MAX];
int count = 0;  // how many students we have right now

// removes leftover characters so the next scanf doesn't break
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// keeps asking until the user types a proper number
int readInt(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        clearBuffer();
        printf("Invalid input. Enter a number: ");
    }
    clearBuffer();
    return value;
}

// same idea, but marks must be between 0 and 100
float readMarks() {
    float value;
    printf("Marks (0-100): ");
    while (scanf("%f", &value) != 1 || value < 0 || value > 100) {
        clearBuffer();
        printf("Invalid marks. Enter a number between 0 and 100: ");
    }
    clearBuffer();
    return value;
}

// finds a student by roll number, returns -1 if not found
int findIndex(int roll) {
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            return i;
        }
    }
    return -1;
}

// writes all students to the file
void saveToFile() {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error: could not save data.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d,%.2f,%s\n", students[i].roll, students[i].marks, students[i].name);
    }
    fclose(fp);
}

// reads old records from the file when the program starts
void loadFromFile() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        return;  // no file yet, so first run
    }
    while (count < MAX &&
           fscanf(fp, "%d,%f,%29[^\n]\n", &students[count].roll,
                  &students[count].marks, students[count].name) == 3) {
        count++;
    }
    fclose(fp);
}

void addStudent() {
    // stop if the array is full
    if (count >= MAX) {
        printf("List is full!\n");
        return;
    }

    // roll number must be unique
    int roll = readInt("Roll number: ");
    if (findIndex(roll) != -1) {
        printf("This roll number already exists.\n");
        return;
    }
    students[count].roll = roll;

    // %[^\n] lets the name have spaces
    printf("Name: ");
    scanf(" %29[^\n]", students[count].name);
    clearBuffer();

    students[count].marks = readMarks();

    // save the new student
    count++;
    saveToFile();
    printf("Student added!\n");
}

void viewAll() {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    // print the header, then one row per student
    printf("\n%-8s %-30s %s\n", "Roll", "Name", "Marks");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-8d %-30s %.2f\n", students[i].roll, students[i].name, students[i].marks);
    }
}

void searchStudent() {
    int roll = readInt("Enter roll number to search: ");
    int pos = findIndex(roll);

    // show the student if found
    if (pos == -1) {
        printf("Student not found.\n");
    } else {
        printf("Roll: %d | Name: %s | Marks: %.2f\n",
               students[pos].roll, students[pos].name, students[pos].marks);
    }
}

void deleteStudent() {
    int roll = readInt("Enter roll number to delete: ");
    int pos = findIndex(roll);

    if (pos == -1) {
        printf("Student not found.\n");
        return;
    }

    // move everyone after this student one step left
    for (int i = pos; i < count - 1; i++) {
        students[i] = students[i + 1];
    }
    count--;

    saveToFile();
    printf("Student deleted.\n");
}

void showStats() {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    float total = 0;
    int topIndex = 0;

    // add up all marks and keep track of the highest one
    for (int i = 0; i < count; i++) {
        total += students[i].marks;
        if (students[i].marks > students[topIndex].marks) {
            topIndex = i;
        }
    }

    // average = total / number of students
    printf("Total students : %d\n", count);
    printf("Average marks  : %.2f\n", total / count);
    printf("Topper         : %s (Roll %d) with %.2f marks\n",
           students[topIndex].name, students[topIndex].roll, students[topIndex].marks);
}

void sortByMarks() {
    if (count == 0) {
        printf("No records to sort.\n");
        return;
    }

    // bubble sort: swap neighbours if they're in the wrong order
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    saveToFile();
    printf("Sorted by marks (highest first).\n");
    viewAll();
}

int main() {
    int choice;

    // load saved data first
    loadFromFile();

    // keep showing the menu until the user picks Exit
    do {
        printf("\n===== STUDENT RECORD MANAGER =====\n");
        printf("1. Add student\n");
        printf("2. View all students\n");
        printf("3. Search student by roll number\n");
        printf("4. Delete student\n");
        printf("5. Show topper and average marks\n");
        printf("6. Sort students by marks\n");
        printf("7. Exit\n");
        choice = readInt("Enter your choice: ");

        // call the function for the chosen option
        switch (choice) {
            case 1: addStudent();    break;
            case 2: viewAll();       break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: showStats();     break;
            case 6: sortByMarks();   break;
            case 7: printf("Goodbye!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);

    return 0;
}
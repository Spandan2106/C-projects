#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_STUDENTS 1000
#define NAME_LEN 100
typedef struct {
    char name[NAME_LEN];
    int attendance;
} Student;
Student students[MAX_STUDENTS];
int student_count = 0;
void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Student list is full!\n");
        return;
    }
    printf("Enter student name: ");
    fgets(students[student_count].name, NAME_LEN, stdin);
    students[student_count].name[strcspn(students[student_count].name, "\n")] = 0; // remove newline
    students[student_count].attendance = 0;
    student_count++;
    printf("Student added successfully!\n");
}
int markAttendance(int index, const char *name) {
    if (index >= student_count) return -1;
    if (strcmp(students[index].name, name) == 0) {
        students[index].attendance++;
        return index;
    }
    return markAttendance(index + 1, name);
}

void displayAttendance() {
    if (student_count == 0) {
        printf("No students to display.\n");
        return;
    }
    printf("\n--- Student Attendance ---\n");
    for (int i = 0; i < student_count; i++) {
        printf("%d. Name: %s, Attendance: %d\n", i + 1, students[i].name, students[i].attendance);
    }
}
void deleteStudent() {
    char name[NAME_LEN];
    printf("Enter name of student to delete: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0; // remove newline
    int index = markAttendance(0, name); // Reusing markAttendance to find index
    if (index == -1) {
        printf("Student not found.\n");
        return;
    }
    for (int i = index; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;
    printf("Student deleted successfully.\n");
}

int main() {
    int choice;
    char query[100];
    int index;
    while (1) {
        printf("\n--- Student Attendance Menu ---\n");
        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. Display Attendance\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                printf("Enter student name to mark attendance: ");
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = 0; // remove newline
                index = markAttendance(0, query);
                if (index == -1)
                    printf("Student not found.\n");
                else
                    printf("Attendance marked for %s. Total attendance: %d\n", students[index].name, students[index].attendance);
                break;
            case 3:
                displayAttendance();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
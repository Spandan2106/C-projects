#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Expense {
    int id;
    char date[15];
    char category[30];
    float amount;
};

void addExpense() {
    struct Expense exp;
    FILE *fp = fopen("expenses.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    printf("Enter Expense ID: ");
    scanf("%d", &exp.id);
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", exp.date);
    printf("Enter Category (e.g., Food, Travel): ");
    scanf("%s", exp.category);
    printf("Enter Amount: ");
    scanf("%f", &exp.amount);

    fprintf(fp, "%d %s %s %.2f\n", exp.id, exp.date, exp.category, exp.amount);
    fclose(fp);
    printf("\n[Expense successfully added!]\n");
}

void viewExpenses() {
    FILE *fp = fopen("expenses.txt", "r");
    if (fp == NULL) {
        printf("\nNo expenses recorded yet.\n");
        return;
    }

    struct Expense exp;
    float total = 0;

    printf("\n=========================================\n");
    printf("           SAVED EXPENSES                \n");
    printf("=========================================\n");
    printf("ID\tDate\t\tCategory\tAmount\n");
    printf("-----------------------------------------\n");

    while (fscanf(fp, "%d %s %s %f", &exp.id, exp.date, exp.category, &exp.amount) == 4) {
        printf("%d\t%s\t%s\t\t$%.2f\n", exp.id, exp.date, exp.category, exp.amount);
        total += exp.amount;
    }

    printf("-----------------------------------------\n");
    printf("Total Spending: $%.2f\n", total);
    printf("=========================================\n");

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n=== PERSONAL EXPENSE TRACKER ===\n");
        printf("1. Add Expense\n");
        printf("2. View All Expenses & Total\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Please choose between 1 and 3.\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void calculate() {
    char operator;
    double num1, num2, result;

    printf("\n=========================================\n");
    printf("            SIMPLE CALCULATOR            \n");
    printf("=========================================\n");
    
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator);

    printf("Enter two operands: ");
    if (scanf("%lf %lf", &num1, &num2) != 2) {
        printf("Invalid input numbers!\n");
        while (getchar() != '\n');
        return;
    }

    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("Result: %.2lf + %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '-':
            result = num1 - num2;
            printf("Result: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '*':
            result = num1 * num2;
            printf("Result: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("Result: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
            } else {
                printf("Error! Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Error! Operator is not correct.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n=== CALCULATOR MENU ===\n");
        printf("1. Perform Calculation\n");
        printf("2. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                calculate();
                break;
            case 2:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Choose 1 or 2.\n");
        }
    }

    return 0;
}

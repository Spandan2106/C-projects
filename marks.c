#include <stdio.h>

int main(void) {
    int n, i;
    float marks, total = 0.0f, avg;

    printf("Enter number of subjects: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    for (i = 1; i <= n; i++) {
        printf("Enter marks for subject %d: ", i);
        scanf("%f", &marks);
        total += marks;
    }

    avg = total / n;
    printf("Total: %.2f\nAverage: %.2f\n", total, avg);

    if (avg >= 90) {
        printf("Grade: A\n");
    } else if (avg >= 75) {
        printf("Grade: B\n");
    } else if (avg >= 60) {
        printf("Grade: C\n");
    } else if (avg >= 40) {
        printf("Grade: D\n");
    } else {
        printf("Grade: F\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generatePassword(int length) {
    // Define character pools
    const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    const char numbers[] = "0123456789";
    const char symbols[] = "!@#$%^&*()_+[]{}|;:,.<>?";
    
    // Combine all characters into a single pool
    char allChars[200];
    snprintf(allChars, sizeof(allChars), "%s%s%s%s", uppercase, lowercase, numbers, symbols);
    
    int poolSize = sizeof(allChars) - 1;

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    printf("\nGenerated Password: ");
    for (int i = 0; i < length; i++) {
        int index = rand() % poolSize;
        putchar(allChars[index]);
    }
    printf("\n\n");
}

int main() {
    int length;

    printf("=========================================\n");
    printf("       SECURE PASSWORD GENERATOR         \n");
    printf("=========================================\n\n");

    printf("Enter desired password length (e.g., 8-32): ");
    if (scanf("%d", &length) != 1 || length <= 0) {
        printf("Invalid length specified. Exiting.\n");
        return 1;
    }

    if (length < 6) {
        printf("\n[Warning: Short passwords are less secure!]\n");
    }

    generatePassword(length);

    return 0;
}

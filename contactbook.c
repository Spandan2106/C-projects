#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[20];
    char email[50];
};

void addContact() {
    struct Contact c;
    FILE *fp = fopen("contacts.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]s", c.name); // Reads string with spaces
    printf("Enter Phone Number: ");
    scanf("%s", c.phone);
    printf("Enter Email: ");
    scanf("%s", c.email);

    fprintf(fp, "%s,%s,%s\n", c.name, c.phone, c.email);
    fclose(fp);
    printf("\n[Contact successfully saved!]\n");
}

void viewContacts() {
    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL) {
        printf("\nNo contacts found.\n");
        return;
    }

    char line[150];
    printf("\n=========================================\n");
    printf("            SAVED CONTACTS               \n");
    printf("=========================================\n");
    printf("Name\t\tPhone\t\tEmail\n");
    printf("-----------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, "\n");
        if (name && phone && email) {
            printf("%s\t%s\t%s\n", name, phone, email);
        }
    }
    printf("=========================================\n");
    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n=== CONTACT MANAGEMENT SYSTEM ===\n");
        printf("1. Add Contact\n");
        printf("2. View All Contacts\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Choose between 1 and 3.\n");
        }
    }

    return 0;
}

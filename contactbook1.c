#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 1000
#define NAME_LEN 100
#define PHONE_LEN 15
typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
} Contact;
Contact contacts[MAX];
int count = 0;
void addContact() {
    if (count >= MAX) {
        printf("Contact book is full!\n");
        return;
    }
    printf("Enter name: ");
    fgets(contacts[count].name, NAME_LEN, stdin);
    contacts[count].name[strcspn(contacts[count].name, "\n")] = 0; // remove newline
    while (1) {
        printf("Enter phone number: ");
        fgets(contacts[count].phone, PHONE_LEN, stdin);
        contacts[count].phone[strcspn(contacts[count].phone, "\n")] = 0; // remove newline
        int valid = 1;
        int len = strlen(contacts[count].phone);
        if (len < 7 || len > 14) valid = 0;
        for (int i = 0; i < len; i++) {
            if (!isdigit(contacts[count].phone[i])) {
                valid = 0;
                break;
            }
        }
        if (valid) break;
        else printf("Invalid phone number! It must be 7-14 digits and contain only numbers.\n");
    }
    count++;
    printf("Contact added successfully!\n");
}

void displayContacts() {
    if (count == 0) {
        printf("No contacts to display.\n");
        return;
    }
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Name: %s, Phone: %s\n", i + 1, contacts[i].name, contacts[i].phone);
    }
}
int searchByName(int index, const char *name) {
    if (index >= count) return -1;
    if (strcmp(contacts[index].name, name) == 0) return index;
    return searchByName(index + 1, name);
}
int searchByPhone(int index, const char *phone) {
    if (index >= count) return -1;
    if (strcmp(contacts[index].phone, phone) == 0) return index;
    return searchByPhone(index + 1, phone);
}
void deleteContact() {
    char name[NAME_LEN];
    printf("Enter name of contact to delete: ");
    fgets(name, NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0; // remove newline
    int index = searchByName(0, name);
    if (index == -1) {
        printf("Contact not found.\n");
        return;
    }
    for (int i = index; i < count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    count--;
    printf("Contact deleted successfully.\n");
}

int main() {
    int choice;
    char query[100];
    int index;
    while (1) {
        printf("\n--- Contact Book Menu ---\n");
        printf("1. Add Contact\n");
        printf("2. Search by Name\n");
        printf("3. Search by Phone\n");
        printf("4. Display All Contacts\n");
        printf("5. Delete Contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                printf("Enter name to search: ");
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = 0; // remove newline
                index = searchByName(0, query);
                if (index == -1)
                    printf("Contact not found.\n");
                else
                    printf("Found: Name: %s, Phone: %s\n", contacts[index].name, contacts[index].phone);
                break;
            case 3:
                printf("Enter phone number to search: ");
                fgets(query, sizeof(query), stdin);
                query[strcspn(query, "\n")] = 0; // remove newline
                index = searchByPhone(0, query);
                if (index == -1)
                    printf("Contact not found.\n");
                else
                    printf("Found: Name: %s, Phone: %s\n", contacts[index].name, contacts[index].phone);
                break;
            case 4:
                displayContacts();
                break;
            case 5:
                deleteContact();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

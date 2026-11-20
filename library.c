#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 200
#define TITLE_LEN 100
#define AUTHOR_LEN 80
#define DATA_FILE "library_records.dat"

typedef struct {
    int id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    int issued;
} Book;

Book books[MAX_BOOKS];
int bookCount = 0;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void readLine(char *buf, int size) {
    if (fgets(buf, size, stdin) != NULL) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        } else {
            clearInputBuffer();
        }
    }
}

void saveBooks(void) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp == NULL) {
        printf("Error saving records.\n");
        return;
    }
    fwrite(&bookCount, sizeof(int), 1, fp);
    if (bookCount > 0) {
        fwrite(books, sizeof(Book), (size_t)bookCount, fp);
    }
    fclose(fp);
}

void loadBooks(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        bookCount = 0;
        return;
    }
    if (fread(&bookCount, sizeof(int), 1, fp) != 1 || bookCount < 0 || bookCount > MAX_BOOKS) {
        bookCount = 0;
        fclose(fp);
        return;
    }
    if (bookCount > 0) {
        size_t readItems = fread(books, sizeof(Book), (size_t)bookCount, fp);
        bookCount = (int)readItems;
    }
    fclose(fp);
}

int findBookIndexById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addBook(void) {
    if (bookCount >= MAX_BOOKS) {
        printf("Library capacity reached.\n");
        return;
    }

    Book b;
    printf("Enter Book ID: ");
    if (scanf("%d", &b.id) != 1) {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
    }
    clearInputBuffer();

    if (findBookIndexById(b.id) != -1) {
        printf("Book with ID %d already exists.\n", b.id);
        return;
    }

    printf("Enter Title: ");
    readLine(b.title, TITLE_LEN);

    printf("Enter Author: ");
    readLine(b.author, AUTHOR_LEN);

    b.issued = 0;
    books[bookCount++] = b;
    saveBooks();
    printf("Book added successfully.\n");
}

void issueOrReturnBook(int issueMode) {
    int id;
    printf("Enter Book ID: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
    }
    clearInputBuffer();

    int idx = findBookIndexById(id);
    if (idx == -1) {
        printf("Book not found.\n");
        return;
    }

    if (issueMode == 1) {
        if (books[idx].issued) {
            printf("Book is already issued.\n");
        } else {
            books[idx].issued = 1;
            saveBooks();
            printf("Book issued successfully.\n");
        }
    } else {
        if (!books[idx].issued) {
            printf("Book is already available.\n");
        } else {
            books[idx].issued = 0;
            saveBooks();
            printf("Book returned successfully.\n");
        }
    }
}

void searchBooks(void) {
    int mode;
    printf("Search by:\n1. ID\n2. Title\nChoice: ");
    if (scanf("%d", &mode) != 1) {
        clearInputBuffer();
        printf("Invalid choice.\n");
        return;
    }
    clearInputBuffer();

    int found = 0;
    if (mode == 1) {
        int id;
        printf("Enter ID: ");
        if (scanf("%d", &id) != 1) {
            clearInputBuffer();
            printf("Invalid ID.\n");
            return;
        }
        clearInputBuffer();

        int idx = findBookIndexById(id);
        if (idx != -1) {
            printf("ID: %d | Title: %s | Author: %s | Status: %s\n",
                   books[idx].id, books[idx].title, books[idx].author,
                   books[idx].issued ? "Issued" : "Available");
            found = 1;
        }
    } else if (mode == 2) {
        char query[TITLE_LEN];
        printf("Enter title keyword: ");
        readLine(query, TITLE_LEN);

        for (int i = 0; i < bookCount; i++) {
            if (strstr(books[i].title, query) != NULL) {
                printf("ID: %d | Title: %s | Author: %s | Status: %s\n",
                       books[i].id, books[i].title, books[i].author,
                       books[i].issued ? "Issued" : "Available");
                found = 1;
            }
        }
    } else {
        printf("Invalid option.\n");
        return;
    }

    if (!found) {
        printf("No matching books found.\n");
    }
}

void listBooks(int filterIssued) {
    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (filterIssued == -1 || books[i].issued == filterIssued) {
            printf("ID: %d | Title: %s | Author: %s | Status: %s\n",
                   books[i].id, books[i].title, books[i].author,
                   books[i].issued ? "Issued" : "Available");
            count++;
        }
    }
    if (count == 0) {
        printf("No books to display.\n");
    }
}

int main(void) {
    loadBooks();
    int choice;

    while (1) {
        printf("\n=== Library Book Management System ===\n");
        printf("1. Add Book\n");
        printf("2. Issue Book\n");
        printf("3. Return Book\n");
        printf("4. Search Book (ID / Title)\n");
        printf("5. View Available Books\n");
        printf("6. View Issued Books\n");
        printf("7. View All Books\n");
        printf("8. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Enter a number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                issueOrReturnBook(1);
                break;
            case 3:
                issueOrReturnBook(0);
                break;
            case 4:
                searchBooks();
                break;
            case 5:
                listBooks(0);
                break;
            case 6:
                listBooks(1);
                break;
            case 7:
                listBooks(-1);
                break;
            case 8:
                saveBooks();
                printf("Exiting.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}

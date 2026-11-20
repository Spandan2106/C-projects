#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAT_LEN 40
#define NOTE_LEN 100
#define DATA_FILE "budget_entries.dat"

typedef enum {
    ENTRY_INCOME = 1,
    ENTRY_EXPENSE = 2
} EntryType;

typedef struct {
    int id;
    EntryType type;
    double amount;
    char category[CAT_LEN];
    char note[NOTE_LEN];
} Entry;

typedef struct {
    Entry *items;
    size_t count;
    size_t capacity;
    int nextId;
} BudgetLedger;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void readLine(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin) != NULL) {
        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        } else {
            clearInputBuffer();
        }
    }
}

int initLedger(BudgetLedger *ledger) {
    ledger->capacity = 16;
    ledger->count = 0;
    ledger->nextId = 1;
    ledger->items = (Entry *)malloc(ledger->capacity * sizeof(Entry));
    return ledger->items != NULL;
}

void freeLedger(BudgetLedger *ledger) {
    free(ledger->items);
    ledger->items = NULL;
    ledger->count = 0;
    ledger->capacity = 0;
}

int ensureCapacity(BudgetLedger *ledger, size_t needed) {
    if (needed <= ledger->capacity) {
        return 1;
    }
    size_t newCap = ledger->capacity;
    while (newCap < needed) {
        newCap *= 2;
    }
    Entry *resized = (Entry *)realloc(ledger->items, newCap * sizeof(Entry));
    if (resized == NULL) {
        return 0;
    }
    ledger->items = resized;
    ledger->capacity = newCap;
    return 1;
}

void saveLedger(const BudgetLedger *ledger) {
    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp == NULL) {
        printf("Error: Could not save budget data.\n");
        return;
    }
    fwrite(&ledger->count, sizeof(size_t), 1, fp);
    fwrite(&ledger->nextId, sizeof(int), 1, fp);
    if (ledger->count > 0) {
        fwrite(ledger->items, sizeof(Entry), ledger->count, fp);
    }
    fclose(fp);
}

void loadLedger(BudgetLedger *ledger) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        return;
    }

    size_t count = 0;
    int nextId = 1;
    if (fread(&count, sizeof(size_t), 1, fp) != 1 || fread(&nextId, sizeof(int), 1, fp) != 1) {
        fclose(fp);
        return;
    }

    if (count > 0 && ensureCapacity(ledger, count)) {
        size_t readCount = fread(ledger->items, sizeof(Entry), count, fp);
        ledger->count = readCount;
        ledger->nextId = nextId > 1 ? nextId : (int)readCount + 1;
    }

    fclose(fp);
}

void addEntry(BudgetLedger *ledger, EntryType type) {
    if (!ensureCapacity(ledger, ledger->count + 1)) {
        printf("Error: Out of memory.\n");
        return;
    }

    Entry e;
    e.id = ledger->nextId++;
    e.type = type;

    printf("Enter amount: ");
    if (scanf("%lf", &e.amount) != 1 || e.amount <= 0.0) {
        clearInputBuffer();
        printf("Invalid amount. Must be greater than 0.\n");
        return;
    }
    clearInputBuffer();

    printf("Enter category (e.g., Food, Rent, Salary, Travel): ");
    readLine(e.category, CAT_LEN);
    if (e.category[0] == '\0') {
        snprintf(e.category, CAT_LEN, "General");
    }

    printf("Enter note (optional): ");
    readLine(e.note, NOTE_LEN);

    ledger->items[ledger->count++] = e;
    saveLedger(ledger);
    printf("%s recorded (#%d).\n", type == ENTRY_INCOME ? "Income" : "Expense", e.id);
}

void printSummary(const BudgetLedger *ledger) {
    double totalIncome = 0.0;
    double totalExpense = 0.0;

    for (size_t i = 0; i < ledger->count; i++) {
        if (ledger->items[i].type == ENTRY_INCOME) {
            totalIncome += ledger->items[i].amount;
        } else {
            totalExpense += ledger->items[i].amount;
        }
    }

    double balance = totalIncome - totalExpense;

    printf("\n=== Budget Summary Report ===\n");
    printf("Total Entries  : %zu\n", ledger->count);
    printf("Total Income   : %.2f\n", totalIncome);
    printf("Total Expense  : %.2f\n", totalExpense);
    printf("Net Balance    : %.2f\n", balance);

    if (ledger->count == 0) {
        return;
    }

    printf("\n--- Breakdown by Category ---\n");
    int *visited = (int *)calloc(ledger->count, sizeof(int));
    if (visited == NULL) {
        return;
    }

    for (size_t i = 0; i < ledger->count; i++) {
        if (visited[i]) {
            continue;
        }
        double catIncome = 0.0;
        double catExpense = 0.0;

        for (size_t j = i; j < ledger->count; j++) {
            if (!visited[j] && strcmp(ledger->items[i].category, ledger->items[j].category) == 0) {
                visited[j] = 1;
                if (ledger->items[j].type == ENTRY_INCOME) {
                    catIncome += ledger->items[j].amount;
                } else {
                    catExpense += ledger->items[j].amount;
                }
            }
        }

        printf("%-20s | Income: %10.2f | Expense: %10.2f\n",
               ledger->items[i].category, catIncome, catExpense);
    }

    free(visited);
}

void listEntries(const BudgetLedger *ledger) {
    if (ledger->count == 0) {
        printf("No entries found.\n");
        return;
    }

    printf("\nID   | Type    | Amount     | Category             | Note\n");
    printf("-----+---------+------------+----------------------+--------------------\n");
    for (size_t i = 0; i < ledger->count; i++) {
        const Entry *e = &ledger->items[i];
        printf("%-4d | %-7s | %10.2f | %-20s | %s\n",
               e->id,
               e->type == ENTRY_INCOME ? "Income" : "Expense",
               e->amount,
               e->category,
               e->note);
    }
}

void deleteEntry(BudgetLedger *ledger) {
    int id;
    printf("Enter Entry ID to delete: ");
    if (scanf("%d", &id) != 1) {
        clearInputBuffer();
        printf("Invalid ID.\n");
        return;
    }
    clearInputBuffer();

    size_t foundIdx = ledger->count;
    for (size_t i = 0; i < ledger->count; i++) {
        if (ledger->items[i].id == id) {
            foundIdx = i;
            break;
        }
    }

    if (foundIdx == ledger->count) {
        printf("Entry #%d not found.\n", id);
        return;
    }

    for (size_t i = foundIdx; i + 1 < ledger->count; i++) {
        ledger->items[i] = ledger->items[i + 1];
    }
    ledger->count--;
    saveLedger(ledger);
    printf("Entry #%d deleted.\n", id);
}

int main(void) {
    BudgetLedger ledger;
    if (!initLedger(&ledger)) {
        printf("Failed to initialize budget tracker.\n");
        return 1;
    }

    loadLedger(&ledger);
    int choice;

    while (1) {
        printf("\n=== Expense & Budget Tracker ===\n");
        printf("1. Add Income\n");
        printf("2. Add Expense\n");
        printf("3. View All Entries\n");
        printf("4. View Summary Report\n");
        printf("5. Delete Entry\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addEntry(&ledger, ENTRY_INCOME);
                break;
            case 2:
                addEntry(&ledger, ENTRY_EXPENSE);
                break;
            case 3:
                listEntries(&ledger);
                break;
            case 4:
                printSummary(&ledger);
                break;
            case 5:
                deleteEntry(&ledger);
                break;
            case 6:
                saveLedger(&ledger);
                freeLedger(&ledger);
                printf("Exiting.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}

// c code for bank management system
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_ACCOUNTS 1000
#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_TRANSACTION_HISTORY 1000
#define MAX_TRANSACTION_LENGTH 1000
struct Account {
    int account_number;
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    float balance;
    char transaction_history[MAX_TRANSACTION_HISTORY][MAX_TRANSACTION_LENGTH];
    int transaction_count;
};
struct Account accounts[MAX_ACCOUNTS];
int account_count = 0;
void clear_screen() {
    system("cls");
}
void add_account() {
    if (account_count >= MAX_ACCOUNTS) {
        printf("Account limit reached.\n");
        return;
    }
    struct Account new_account;
    new_account.account_number = account_count + 1; // Simple account number generation
    printf("Enter name: ");
    scanf("%s", new_account.name);
    printf("Enter password: ");
    scanf("%s", new_account.password);
    new_account.balance = 0.0f;
    new_account.transaction_count = 0;
    accounts[account_count++] = new_account;
    printf("Account created successfully. Account Number: %d\n", new_account.account_number);
}
void display_accounts() {
    if (account_count == 0) {
        printf("No accounts available.\n");
        return;
    }
    printf("Account Number\t\tName\t\tBalance\n\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < account_count; i++) {
        printf("%d\t  \t%s  \t\t%.2f\n", accounts[i].account_number, accounts[i].name, accounts[i].balance);
    }
}
void deposit() {
    int account_number;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &account_number);
    if (account_number < 1 || account_number > account_count) {
        printf("Invalid account number.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount <= 0) {
        printf("Invalid amount.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }
    accounts[account_number - 1].balance += amount;
    snprintf(accounts[account_number - 1].transaction_history[accounts[account_number - 1].transaction_count++],
             MAX_TRANSACTION_LENGTH, "Deposited: %.2f", amount);
    printf("Deposit successful. New balance: %.2f\n", accounts[account_number - 1].balance);
    printf("Press any key to continue...");
    getch();
}
void withdraw() {
    int account_number;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &account_number);
    if (account_number < 1 || account_number > account_count) {
        printf("Invalid account number.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > accounts[account_number - 1].balance) {
        printf("Invalid amount.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }
    accounts[account_number - 1].balance -= amount;
    snprintf(accounts[account_number - 1].transaction_history[accounts[account_number - 1].transaction_count++],
             MAX_TRANSACTION_LENGTH, "Withdrew: %.2f", amount);
    printf("Withdrawal successful. New balance: %.2f\n", accounts[account_number - 1].balance);
    printf("Press any key to continue...");
    getch();
}
void view_transaction_history() {
    int account_number;
    printf("Enter account number: ");
    scanf("%d", &account_number);
    if (account_number < 1 || account_number > account_count) {
        printf("Invalid account number.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }
    struct Account *acc = &accounts[account_number - 1];
    if (acc->transaction_count == 0) {
        printf("No transactions found for this account.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }
    printf("Transaction History for Account Number %d:\n", acc->account_number);
    for (int i = 0; i < acc->transaction_count; i++) {
        printf("%s\n", acc->transaction_history[i]);
    }
}
void menu() {
    int choice;
    do {
        clear_screen();
        printf("Bank Management System\n");
        printf("-----------------------\n");
        printf("1. Add Account\n");
        printf("2. Display Accounts\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. View Transaction History\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_account();
                break;
            case 2:
                display_accounts();
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                view_transaction_history();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        if (choice != 6) {
            printf("Press any key to continue...");
            getch();// Wait for user input
        }
    } while (choice != 6);
}
int main() {
    menu();
    return 0;
}

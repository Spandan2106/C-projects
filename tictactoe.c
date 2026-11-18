#include <stdio.h>
#include <stdlib.h>

char board[3][3];
char currentPlayer;

// Initialize the board with numbers 1 to 9
void resetBoard() {
    char initialChar = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = initialChar++;
        }
    }
    currentPlayer = 'X';
}

// Print the game board
void printBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Check if the board is full (Tie)
int checkTie() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0; // Not full
            }
        }
    }
    return 1; // Full (Tie)
}

// Check for a win condition
int checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;

    return 0;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    int choice;
    int moveValid;

    printf("=========================================\n");
    printf("         TIC-TAC-TOE CONSOLE GAME        \n");
    printf("=========================================\n");

    resetBoard();

    while (1) {
        printBoard();
        printf("Player %c, enter a slot number (1-9): ", currentPlayer);
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number between 1 and 9.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (choice < 1 || choice > 9) {
            printf("Invalid choice! Choose a number between 1 and 9.\n");
            continue;
        }

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        // Check if the slot is already taken
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Slot already taken! Choose another.\n");
            continue;
        }

        // Place the move
        board[row][col] = currentPlayer;

        // Check win condition
        if (checkWin()) {
            printBoard();
            printf("Congratulations! Player %c wins!\n", currentPlayer);
            break;
        }

        // Check tie condition
        if (checkTie()) {
            printBoard();
            printf("It's a tie!\n");
            break;
        }

        switchPlayer();
    }

    return 0;
}

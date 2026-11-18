#include <stdio.h>

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    printf("\n+-------+-------+-------+\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (col == 0) printf("| ");
            if (grid[row][col] == 0)
                printf(". ");
            else
                printf("%d ", grid[row][col]);
            if ((col + 1) % 3 == 0) printf("| ");
        }
        printf("\n");
        if ((row + 1) % 3 == 0) printf("+-------+-------+-------+\n");
    }
}

// Check if it's safe to place a number in a given row, col
int isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return 0;

    // Check column
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return 0;

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return 0;

    return 1;
}

// Backtracking function to solve Sudoku
int solveSudoku(int grid[N][N], int row, int col) {
    // If we have reached the 9th row and 10th column, the puzzle is solved
    if (row == N - 1 && col == N)
        return 1;

    // Move to next row if column reaches N
    if (col == N) {
        row++;
        col = 0;
    }

    // If current spot already contains a number, move to next
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            
            if (solveSudoku(grid, row, col + 1))
                return 1;
        }
        // Remove number if it leads to an invalid state (backtrack)
        grid[row][col] = 0;
    }
    return 0;
}

int main() {
    // Sample Sudoku puzzle (0 represents empty cells)
    int grid[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    printf("=========================================\n");
    printf("           SUDOKU SOLVER (C)             \n");
    printf("=========================================\n");
    
    printf("\nUnsolved Puzzle:");
    printGrid(grid);

    if (solveSudoku(grid, 0, 0)) {
        printf("\nSolved Puzzle:");
        printGrid(grid);
    } else {
        printf("\nNo solution exists for the given puzzle.\n");
    }

    return 0;
}

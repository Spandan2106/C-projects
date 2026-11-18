#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold quiz questions
struct Question {
    char questionText[256];
    char options[4][64];
    int correctOption;
};

void saveScore(int score, int total) {
    FILE *fp = fopen("highscores.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "Score: %d/%d\n", score, total);
        fclose(fp);
        printf("\n[Score successfully saved to highscores.txt]\n");
    } else {
        printf("\n[Error saving score to file!]\n");
    }
}

int main() {
    struct Question qList[3] = {
        {
            "What is the default return type of the main() function in C?",
            {"1. void", "2. int", "3. float", "4. char"},
            2
        },
        {
            "Which of the following is used to read formatted input in C?",
            {"1. printf()", "2. scanf()", "3. gets()", "4. puts()"},
            2
        },
        {
            "Which operator is used to access members of a structure using a pointer?",
            {".", "*", "->", "&"},
            3
        }
    };

    int score = 0;
    int totalQuestions = 3;
    int userChoice;

    printf("=========================================\n");
    printf("         WELCOME TO THE C QUIZ GAME      \n");
    printf("=========================================\n\n");

    for (int i = 0; i < totalQuestions; i++) {
        printf("Question %d: %s\n", i + 1, qList[i].questionText);
        for (int j = 0; j < 4; j++) {
            printf("%s\n", qList[i].options[j]);
        }
        
        printf("Enter your choice (1-4): ");
        if (scanf("%d", &userChoice) != 1) {
            printf("Invalid input. Skipping question.\n");
            while(getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (userChoice == qList[i].correctOption) {
            printf("Correct!\n\n");
            score++;
        } else {
            printf("Wrong! The correct option was %d.\n\n", qList[i].correctOption);
        }
    }

    printf("=========================================\n");
    printf("Quiz Finished! Your Final Score: %d/%d\n", score, totalQuestions);
    printf("=========================================\n");

    // Save score using file handling
    saveScore(score, totalQuestions);

    return 0;
}

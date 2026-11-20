#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR 512
#define STACK_SIZE 512

typedef struct {
    char data[STACK_SIZE];
    int top;
} CharStack;

typedef struct {
    double data[STACK_SIZE];
    int top;
} DoubleStack;

void initCharStack(CharStack *s) {
    s->top = -1;
}

int isCharEmpty(const CharStack *s) {
    return s->top == -1;
}

int pushChar(CharStack *s, char c) {
    if (s->top >= STACK_SIZE - 1) {
        return 0;
    }
    s->data[++(s->top)] = c;
    return 1;
}

char popChar(CharStack *s) {
    if (isCharEmpty(s)) {
        return '\0';
    }
    return s->data[(s->top)--];
}

char peekChar(const CharStack *s) {
    if (isCharEmpty(s)) {
        return '\0';
    }
    return s->data[s->top];
}

void initDoubleStack(DoubleStack *s) {
    s->top = -1;
}

int isDoubleEmpty(const DoubleStack *s) {
    return s->top == -1;
}

int pushDouble(DoubleStack *s, double val) {
    if (s->top >= STACK_SIZE - 1) {
        return 0;
    }
    s->data[++(s->top)] = val;
    return 1;
}

double popDouble(DoubleStack *s, int *ok) {
    if (isDoubleEmpty(s)) {
        *ok = 0;
        return 0.0;
    }
    return s->data[(s->top)--];
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int precedence(char op) {
    if (op == '^') {
        return 3;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

int isRightAssociative(char op) {
    return op == '^';
}

int infixToPostfix(const char *infix, char *postfix, size_t outSize) {
    CharStack ops;
    initCharStack(&ops);

    size_t outIdx = 0;
    int expectOperand = 1;

    for (size_t i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];

        if (isspace((unsigned char)c)) {
            continue;
        }

        if (isdigit((unsigned char)c) || c == '.') {
            int dotCount = (c == '.') ? 1 : 0;
            if (outIdx + 2 >= outSize) {
                return 0;
            }
            postfix[outIdx++] = c;
            i++;
            while (infix[i] != '\0' && (isdigit((unsigned char)infix[i]) || infix[i] == '.')) {
                if (infix[i] == '.') {
                    dotCount++;
                    if (dotCount > 1) {
                        return 0;
                    }
                }
                if (outIdx + 2 >= outSize) {
                    return 0;
                }
                postfix[outIdx++] = infix[i];
                i++;
            }
            postfix[outIdx++] = ' ';
            i--;
            expectOperand = 0;
        } else if (c == '(') {
            if (!pushChar(&ops, c)) {
                return 0;
            }
            expectOperand = 1;
        } else if (c == ')') {
            int foundOpen = 0;
            while (!isCharEmpty(&ops)) {
                char topOp = popChar(&ops);
                if (topOp == '(') {
                    foundOpen = 1;
                    break;
                }
                if (outIdx + 3 >= outSize) {
                    return 0;
                }
                postfix[outIdx++] = topOp;
                postfix[outIdx++] = ' ';
            }
            if (!foundOpen) {
                return 0;
            }
            expectOperand = 0;
        } else if (isOperator(c)) {
            if (expectOperand && (c == '+' || c == '-')) {
                if (outIdx + 3 >= outSize) {
                    return 0;
                }
                postfix[outIdx++] = '0';
                postfix[outIdx++] = ' ';
                expectOperand = 0;
            } else if (expectOperand) {
                return 0;
            }

            while (!isCharEmpty(&ops) && isOperator(peekChar(&ops))) {
                char topOp = peekChar(&ops);
                int pTop = precedence(topOp);
                int pCur = precedence(c);
                if ((!isRightAssociative(c) && pTop >= pCur) ||
                    (isRightAssociative(c) && pTop > pCur)) {
                    if (outIdx + 3 >= outSize) {
                        return 0;
                    }
                    postfix[outIdx++] = popChar(&ops);
                    postfix[outIdx++] = ' ';
                } else {
                    break;
                }
            }

            if (!pushChar(&ops, c)) {
                return 0;
            }
            expectOperand = 1;
        } else {
            return 0;
        }
    }

    if (expectOperand) {
        return 0;
    }

    while (!isCharEmpty(&ops)) {
        char topOp = popChar(&ops);
        if (topOp == '(') {
            return 0;
        }
        if (outIdx + 3 >= outSize) {
            return 0;
        }
        postfix[outIdx++] = topOp;
        postfix[outIdx++] = ' ';
    }

    if (outIdx > 0 && postfix[outIdx - 1] == ' ') {
        outIdx--;
    }
    postfix[outIdx] = '\0';
    return 1;
}

int evaluatePostfix(const char *postfix, double *result) {
    DoubleStack vals;
    initDoubleStack(&vals);

    size_t i = 0;
    while (postfix[i] != '\0') {
        if (isspace((unsigned char)postfix[i])) {
            i++;
            continue;
        }

        if (isdigit((unsigned char)postfix[i]) ||
            (postfix[i] == '.' && isdigit((unsigned char)postfix[i + 1]))) {
            char *endPtr = NULL;
            double num = strtod(&postfix[i], &endPtr);
            if (endPtr == &postfix[i]) {
                return 0;
            }
            if (!pushDouble(&vals, num)) {
                return 0;
            }
            i = (size_t)(endPtr - postfix);
        } else if (isOperator(postfix[i])) {
            char op = postfix[i];
            int ok = 1;
            double b = popDouble(&vals, &ok);
            if (!ok) {
                return 0;
            }
            double a = popDouble(&vals, &ok);
            if (!ok) {
                return 0;
            }

            double res = 0.0;
            if (op == '+') {
                res = a + b;
            } else if (op == '-') {
                res = a - b;
            } else if (op == '*') {
                res = a * b;
            } else if (op == '/') {
                if (b == 0.0) {
                    printf("Error: Division by zero.\n");
                    return 0;
                }
                res = a / b;
            } else if (op == '^') {
                res = pow(a, b);
            }

            if (!pushDouble(&vals, res)) {
                return 0;
            }
            i++;
        } else {
            return 0;
        }
    }

    int ok = 1;
    double finalAns = popDouble(&vals, &ok);
    if (!ok || !isDoubleEmpty(&vals)) {
        return 0;
    }

    *result = finalAns;
    return 1;
}

int main(void) {
    char infix[MAX_EXPR];
    char postfix[MAX_EXPR * 2];

    printf("Enter an infix expression (or 'q' to quit): ");
    while (fgets(infix, sizeof(infix), stdin) != NULL) {
        size_t len = strlen(infix);
        if (len > 0 && infix[len - 1] == '\n') {
            infix[len - 1] = '\0';
        }

        if (strcmp(infix, "q") == 0 || strcmp(infix, "Q") == 0) {
            break;
        }

        if (!infixToPostfix(infix, postfix, sizeof(postfix))) {
            printf("Invalid expression.\n");
        } else {
            double ans = 0.0;
            printf("Postfix: %s\n", postfix);
            if (evaluatePostfix(postfix, &ans)) {
                printf("Result: %.6g\n", ans);
            } else {
                printf("Could not evaluate expression.\n");
            }
        }

        printf("\nEnter an infix expression (or 'q' to quit): ");
    }

    return 0;
}

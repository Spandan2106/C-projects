// c code for binary tree visualizer in terminal
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_NODES 1000
#define NAME_LEN 100
typedef struct Node {
    char name[NAME_LEN];
    struct Node *left;
    struct Node *right;
} Node;
Node* createNode(const char *name) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strncpy(newNode->name, name, NAME_LEN);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void printTree(Node *root, int space) {
    if (root == NULL) return;
    space += 10;
    printTree(root->right, space);
    printf("\n");
    for (int i = 10; i < space - 5; i++) printf(" ");
    if (space > 10) printf("------");
    printf("%s\n", root->name);
    printTree(root->left, space);
}
void freeTree(Node *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
int main() {
    int choice;
    Node *root = NULL;
    while (1) {
        printf("\n--- Binary Tree Visualizer Menu ---\n");
        printf("1. Add Root Node\n");
        printf("2. Add Left Child\n");
        printf("3. Add Right Child\n");
        printf("4. Display Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline
        if (choice == 1) {
            if (root != NULL) {
                printf("Root already exists!\n");
                continue;
            }
            char name[NAME_LEN];
            printf("Enter root node name: ");
            fgets(name, NAME_LEN, stdin);
            name[strcspn(name, "\n")] = 0; // remove newline
            root = createNode(name);
            printf("Root node added successfully!\n");
        } else if (choice == 2 || choice == 3) {
            if (root == NULL) {
                printf("Please add a root node first!\n");
                continue;
            }
            char parentName[NAME_LEN], childName[NAME_LEN];
            printf("Enter parent node name: ");
            fgets(parentName, NAME_LEN, stdin);
            parentName[strcspn(parentName, "\n")] = 0; // remove newline
            printf("Enter child node name: ");
            fgets(childName, NAME_LEN, stdin);
            childName[strcspn(childName, "\n")] = 0; // remove newline
            // Simple BFS to find parent node
            Node *queue[MAX_NODES];
            int front = 0, rear = 0;
            queue[rear++] = root;
            int found = 0;
            while (front < rear) {
                Node *current = queue[front++];
                if (strcmp(current->name, parentName) == 0) {
                    if (choice == 2) {
                        if (current->left != NULL) {
                            printf("Left child already exists!\n");
                        } else {
                            current->left = createNode(childName);
                            printf("Left child added successfully!\n");
                        }
                    } else {
                        if (current->right != NULL) {
                            printf("Right child already exists!\n");
                        } else {
                            current->right = createNode(childName);
                            printf("Right child added successfully!\n");
                        }
                    }
                    found = 1;
                    break;
                }
                if (current->left != NULL) queue[rear++] = current->left;
                if (current->right != NULL) queue[rear++] = current->right;
            }
            if (!found) {
                printf("Parent node not found!\n");
            }
        } else if (choice == 4) {
            if (root == NULL) {
                printf("Tree is empty!\n");
            } else {
                printTree(root, 0);
            }
        } else if (choice == 5) {
            break;
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

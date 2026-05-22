#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

Node* top = NULL;

void push() {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return;

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = NULL;
    newNode->size = 0;

    // Tokenização para contar e armazenar os inteiros
    char *token = strtok(buffer, " \n");
    while (token != NULL) {
        newNode->data = realloc(newNode->data, sizeof(int) * (newNode->size + 1));
        newNode->data[newNode->size] = atoi(token);
        newNode->size++;
        token = strtok(NULL, " \n");
    }

    newNode->next = top;
    top = newNode;
}

void pop() {
    if (top == NULL) {
        printf("EMPTY STACK\n");
        return;
    }

    Node *temp = top;
    for (int i = 0; i < temp->size; i++) {
        printf("%d%c", temp->data[i], (i == temp->size - 1 ? '\n' : ' '));
    }

    top = top->next;
    free(temp->data);
    free(temp);
}

int main() {
    char command[10];
    while (scanf("%s", command) != EOF) {
        getchar(); // Limpa o buffer do '\n' após o comando
        if (strcmp(command, "PUSH") == 0) {
            push();
        } else if (strcmp(command, "POP") == 0) {
            pop();
        }
    }
    return 0;
}
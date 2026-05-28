#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int data;          
    struct node* next;
} node;

typedef struct stack {
    node* top;       
    int currentSize;     
} stack;

stack* create_stack() {
    stack* new_stack = (stack*) malloc(sizeof(stack));
    if (new_stack != NULL) {
        new_stack->top = NULL;
        new_stack->currentSize = 0;
    }
    return new_stack;
}

void push(stack* stack) {
    if (stack == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) { return; } 

    int inputData;
    scanf("%d", &inputData);

    new_node->data = inputData;
    new_node->next = stack->top; 
    
    stack->top = new_node;
    stack->currentSize++;
}
 
void pop(stack* stack) {
    node* temp = stack->top;     

    stack->top = temp->next;        
    free(temp);                 
    stack->currentSize--;
        
}

void printStack(stack* stack) {

    node* current = stack->top;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");

}

void freeStack(stack **stack) {
    if (stack == NULL || *stack == NULL) return;

    node* current = (*stack)->top;
    node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);              // Libera cada nó individualmente
        current = nextNode;
    }

    free(*stack);                   // Libera a estrutura de controle da pilha
    *stack = NULL;                  // Zera o ponteiro original por segurança
}

int main(){
    char commandInput[15];
    stack* s = create_stack();

    while (scanf("%s", commandInput) != EOF)
    {
        if (strcmp(commandInput, "Empilhar") == 0) { push(s); }
        else if (strcmp(commandInput, "Desempilhar") == 0) { pop(s); }
        else if (strcmp(commandInput, "Fim") == 0) { break; }

        printStack(s);
    }

    freeStack(&s);
    return 0;
}
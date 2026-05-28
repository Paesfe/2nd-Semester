#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int data;          
    struct node* next;   // Ponteiro para o próximo nó (abaixo na pilha)
} node;

// Estrutura de controle da Pilha
typedef struct stack {
    node* top;       
    int valueMax, valueMin, currentSize;     
} stack;


stack* create_stack() {
    stack* new_stack = (stack*) malloc(sizeof(stack));
    if (new_stack != NULL) {
        new_stack->top = NULL;
        new_stack->currentSize = 0;
        new_stack->valueMax = -1; 
        new_stack->valueMin = -1;
    }
    return new_stack;
}

bool stackEmpty(stack* stack) {
    if (stack == NULL) return true;
    return (stack->top == NULL);
}


// Inserir novo elemento; 
void push(stack* stack) {
    if (stack == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) { return; } 

    int inputData;
    scanf("%d", &inputData);

    new_node->data = inputData;
    new_node->next = stack->top;  // O novo nó aponta para o nó que estava no topo
    
    if(stack->valueMax < inputData || stack->valueMax == -1) {
        stack->valueMax = inputData;
    }

    if(stack->valueMin > inputData || stack->valueMin == -1) {
        stack->valueMin = inputData;
    }

    stack->top = new_node;        // O topo da pilha passa a ser o novo nó
    stack->currentSize++;
}

// Remove and return the pointer to the unstacked top node; 
void pop(stack* stack) {
    node* temp = stack->top;     
    int data = temp->data;

    stack->top = temp->next;        
    free(temp);                 
    stack->currentSize--;
    
    printf("%d\n", data);
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

void absValue(stack* stack) {
    printf("%d\n", (stack->valueMax == -1 || stack->valueMin == -1) ? 0 : (stack->valueMax - stack->valueMin));
}

int main(){
    char commandInput[15];
    stack* s = create_stack();

    while (scanf("%s", commandInput) != EOF)
    {
        if (strcmp(commandInput, "push") == 0) { push(s); }
        else if (strcmp(commandInput, "pop") == 0) { pop(s); }
        else if (strcmp(commandInput, "abs") == 0) { absValue(s); }

    }

    freeStack(&s);
    return 0;
}
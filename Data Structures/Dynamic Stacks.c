#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Apêndice de Funções: Pilha Dinâmica Genérica (Stack) em C
  
typedef struct data {
    void* variable;
} data;

// Estrutura de cada elemento (Nó) da pilha
typedef struct node {
    data data;          
    struct node* next;   // Ponteiro para o próximo nó (abaixo na pilha)
} node;

// Estrutura de controle da Pilha
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

bool stackEmpty(stack* stack) {
    if (stack == NULL) return true;
    return (stack->top == NULL);
}


int getStackSize(stack* stack) {
    if (stack == NULL) return 0;
    return stack->currentSize;
}

// Inserir novo elemento; 
void push(stack* stack, void* data) {
    if (stack == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) { return; } 

    new_node->data->variable = data;
    new_node->next = stack->top;  // O novo nó aponta para o nó que estava no topo
    
    stack->top = new_node;        // O topo da pilha passa a ser o novo nó
    stack->currentSize++;
}

// Remove and return the pointer to the unstacked top node; 
void* pop(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) { return NULL; }

    node* temp = stack->top;     
    void* data = temp->data;

    stack->top = temp->next;        
    free(temp);                 
    stack->currentSize--;

    return data;               
}

//Returns the top node without removing it
void* peek(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) { return NULL; }
    return stack->top->data;
}

//Print the stack from top to bottom, needing a aux function to convert void to a specific data type
void printStack(stack* stack, void (*printData)(void*)) {
    if (stack == NULL || stackEmpty(stack)) {
        printf("Pilha Vazia\n");
        return;
    }

    node* current = stack->top;
    while (current != NULL) {
        printData(current->data->variable);
        current = current->next;
    }
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
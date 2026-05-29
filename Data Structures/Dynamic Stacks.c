#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Apêndice de Funções: Pilha Dinâmica Genérica (Stack) em C CORRIGIDA

// Estrutura de cada elemento (Nó) da pilha
typedef struct node {
    int data;          
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

// Inserir novo elemento
void push(stack* stack, void* data) {
    if (stack == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) { return; } 

    new_node->data = data; // CORRIGIDO: de '->' para '.'
    new_node->next = stack->top;  
    
    stack->top = new_node;        
    stack->currentSize++;
}

// Remove e retorna o ponteiro do nó do topo
void* pop(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) { return NULL; }

    node* temp = stack->top;     
    void* data_ptr = temp->data; // CORRIGIDO: pegando o ponteiro interno

    stack->top = temp->next;        
    free(temp);                 
    stack->currentSize--;

    return data_ptr;               
}

// Retorna o nó do topo sem remover
void* peek(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) { return NULL; }
    return stack->top->data; // CORRIGIDO: de '->' para '.'
}

void freeStack(stack **stack) {
    if (stack == NULL || *stack == NULL) return;

    node* current = (*stack)->top;
    node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);              
        current = nextNode;
    }

    free(*stack);                   
    *stack = NULL;                  
}
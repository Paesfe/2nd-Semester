#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {         
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

// Inserir novo elemento; 
void push(stack* stack) {
    if (stack == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) { return; } 

    new_node->next = stack->top;  // O novo nó aponta para o nó que estava no topo
    
    stack->top = new_node;        // O topo da pilha passa a ser o novo nó
    stack->currentSize++;
}

// Remove and return the pointer to the unstacked top node; 
void pop(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) { return; }

    node* temp = stack->top;     

    stack->top = temp->next;        
    free(temp);                 
    stack->currentSize--;            
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
    stack* foward = create_stack();
    stack* back = create_stack();

    while (scanf("%s", commandInput) != EOF) {

        if (strcmp(commandInput, "ENTER") == 0) { 
            push(back); 
        } else if (strcmp(commandInput, "BACK") == 0) { 
            push(foward);
            pop(back);
        } else if (strcmp(commandInput, "FORWARD") == 0) { 
            push(back);
            pop(foward);
        }

    }

    printf("BACK: %d\n", back->currentSize);
    printf("FORWARD: %d\n", foward->currentSize);

    freeStack(&foward);
    freeStack(&back);
    
    return 0;
}
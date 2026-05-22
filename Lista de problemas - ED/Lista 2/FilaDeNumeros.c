#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct data {
    void* variable;
} data;

typedef struct node {
    data data;          
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

bool stackEmpty(stack* stack) {
    if (stack == NULL) return true;
    return (stack->top == NULL);
}

void push(stack* stack) {
    if (stack == NULL) return;

    int variable;
    scanf("%d", &variable);

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) return;

    new_node->data.variable = variable;
    new_node->next = stack->top;  
    
    stack->top = new_node;        
    stack->currentSize++;
}

void* pop(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) return;

    node* temp = stack->top;     
    int variable = temp->data.variable;

    stack->top = temp->next;        
    free(temp);                 
    stack->currentSize--;
    
    printf("%d\n", variable);
}


void printStack(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) {
        return;
    }

    node* current = stack->top;
    while (current != NULL) {
        printf("%d ", current->data.variable);
        current = current->next;
    }
    printf("\n");
}

void sumStack(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) {
        return;
    }

    node* current = stack->top;
    int temp = 0;
    while (current != NULL) {
        temp += *(int*) current->data.variable;
        current = current->next;
    }
    printf("%d\n", temp);
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

int main(){
    char comandInput[5];
    void* stack = create_stack();

    while (scanf("%s", &comandInput) != EOF)
    {
        if (comandInput == 'push') { push(stack); }
        else if (comandInput == 'pop') { pop(stack); }
        else if (comandInput == 'sum') { sumStack(stack); }
        else if (comandInput == 'print') { printStack(stack); }
        else if (comandInput == 'exit') { break; }
    }

    freeStack(stack);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int value;          
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

int getStackSize(stack* stack) {
    if (stack == NULL) return 0;
    return stack->currentSize;
}

void push(stack* stack) {
    if (stack == NULL) return;

    int val;
    scanf("%d", &val);

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) return;
    new_node->value = val;
    new_node->next = NULL;

    if (stackEmpty(stack)) {
        stack->top = new_node;
    } else {
        node* current = stack->top;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    stack->currentSize++;
}

void pop(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) return;

    node* current = stack->top;
    
    if (current->next == NULL) {
        stack->top = NULL;
        free(current);
    } else {
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
    stack->currentSize--;
}

void printStack(stack* stack) {
    if (!stackEmpty(stack)) {
        node* current = stack->top;
        while (current != NULL) {
            printf("%d ", current->value);
            current = current->next;
        }
    }
    printf("\n");
}

void powStack(stack* stack) {
    if (!stackEmpty(stack)) {
        node* current = stack->top;
        while (current != NULL) {
            printf("%d ", current->value * current->value);
            current = current->next;
        }
    }
    printf("\n");
}

void sumStack(stack* stack) {
    int total = 0;
    if (!stackEmpty(stack)) {
        node* current = stack->top;
        while (current != NULL) {
            total += current->value;
            current = current->next;
        }
    }
    printf("%d\n", total);
}

void averageStack(stack* stack) {
    if (stackEmpty(stack)) {
        printf("0.00\n");
        return;
    }

    float total = 0;
    node* current = stack->top;
    while (current != NULL) {
        total += current->value;
        current = current->next;
    }
    printf("%.2f\n", total / getStackSize(stack));
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
    char commandInput[15];
    stack* s = create_stack();

    while (scanf("%s", commandInput) != EOF)
    {
        if (strcmp(commandInput, "push") == 0) { push(s); }
        else if (strcmp(commandInput, "pop") == 0) { pop(s); }
        else if (strcmp(commandInput, "sum") == 0) { sumStack(s); }
        else if (strcmp(commandInput, "pow") == 0) { powStack(s); }
        else if (strcmp(commandInput, "average") == 0) { averageStack(s); }
        else if (strcmp(commandInput, "print") == 0) { printStack(s); }
        else if (strcmp(commandInput, "exit") == 0) { break; }
    }

    freeStack(&s);
    return 0;
}
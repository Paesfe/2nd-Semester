#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    char data;          
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

void push(stack* stack, char data) {
    if (stack == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) { return; } 

    new_node->data = data;
    new_node->next = stack->top;  
    
    stack->top = new_node;        
    stack->currentSize++;
}

char pop(stack* stack) {
    if (stack == NULL || stackEmpty(stack)) { return '\0'; }

    node* temp = stack->top;     
    char data = temp->data;

    stack->top = temp->next;        
    free(temp);                 
    stack->currentSize--;

    return data;           
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
    char stringInput[256];
    int numInput;
    
    if (scanf("%d", &numInput) != 1) return 0;
    getchar();

    for (int i = 0; i < numInput; i++){
        stack* s = create_stack();
        int flag = 1;
        
        if (fgets(stringInput, 256, stdin) == NULL) continue;
        
        stringInput[strcspn(stringInput, "\n")] = '\0';

        for(int j = 0; stringInput[j] != '\0'; j++){
            char current = stringInput[j];
            
            if (current == '(' || current == '[') {
                push(s, current);
            } 
            else if (current == ')' || current == ']') {
                if (stackEmpty(s)) {
                    flag = 0;
                    break;
                }
                
                char popped = pop(s);
                
                if ((current == ')' && popped != '(') || 
                    (current == ']' && popped != '[')) {
                    flag = 0;
                    break;
                }
            }
        }

        
        if (!stackEmpty(s)) {
            flag = 0;
        }

        printf("%s\n", flag ? "Yes" : "No");
        freeStack(&s);
    }
    
    return 0;
}
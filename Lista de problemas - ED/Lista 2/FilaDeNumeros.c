#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 

typedef struct node {
    int data; 
    struct node* next;
} node;

typedef struct queue {
    node* head;  
    node* tail;          
    int currentSize;     
} queue;

queue* create_queue() {
    queue* new_queue = (queue*) malloc(sizeof(queue));
    if (new_queue != NULL) {
        new_queue->head = NULL;
        new_queue->tail = NULL;
        new_queue->currentSize = 0;
    }
    return new_queue;
}

bool isQueueEmpty(queue* q) {
    if (q == NULL) return true;
    return (q->head == NULL);
}

void enqueue(queue* q, int data) {
    if (q == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) return; 

    new_node->data = data;
    new_node->next = NULL;
    
    if (isQueueEmpty(q)) { 
        q->head = new_node; 
    } else { 
        q->tail->next = new_node; 
    }
    
    q->tail = new_node;        
    q->currentSize++;
}

void dequeue(queue* q) {
    if (q == NULL || isQueueEmpty(q)) return;

    node* temp = q->head;     
    q->head = temp->next;
    
    if (q->head == NULL) { 
        q->tail = NULL; 
    }

    free(temp);                 
    q->currentSize--;           
}

void sumQueue(queue* q) {
    int total = 0;
    if (q != NULL && !isQueueEmpty(q)) {
        node* current = q->head;
        while (current != NULL) {
            total += current->data;
            current = current->next;
        }
    }
    printf("%d\n", total);
}

void printQueue(queue* q) {
    if (q == NULL || isQueueEmpty(q)) return;
        
    node* current = q->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeQueue(queue **q) {
    if (q == NULL || *q == NULL) return;

    node* current = (*q)->head;
    node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);              
        current = nextNode;
    }

    free(*q);               
    *q = NULL;                      
}

int main(){
    char commandInput[15];
    queue* q = create_queue();

    while (scanf("%s", commandInput) != EOF) {
        if (strcmp(commandInput, "push") == 0) { 
            int val;
            scanf("%d", &val);
            enqueue(q, val); 
        }
        else if (strcmp(commandInput, "pop") == 0) { dequeue(q); }
        else if (strcmp(commandInput, "sum") == 0) { sumQueue(q); }
        else if (strcmp(commandInput, "print") == 0) { printQueue(q); }
        else if (strcmp(commandInput, "exit") == 0) { break; }
    }

    freeQueue(&q);
    
    return 0;
}
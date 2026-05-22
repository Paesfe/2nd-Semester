#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
    void* data;          
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


bool isQueueEmpty(queue* queue) {
    if (queue == NULL) return true;
    return (queue->head == NULL);
}


int getQueueSize(queue* queue) {
    if (queue == NULL) return 0;
    return queue->currentSize;
}


void enqueue(queue* queue, void* data) {
    if (queue == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) { return; } 

    new_node->data = data;
    new_node->next = NULL;
    
    // Se a fila estava vazia, o novo nó é o começo e final
    if (isQueueEmpty(queue)) { queue->head = new_node; } 
    else { queue->tail->next = new_node; }
    
    // Atualiza o final da fila
    queue->tail = new_node;        
    queue->currentSize++;
}


void* dequeue(queue* queue) {
    if (queue == NULL || isQueueEmpty(queue)) { return NULL; }

    node* temp = queue->head;     
    void* data = temp->data;

    queue->head = temp->next;
    
    // Se esvaziar a fila, o tail é anulado
    if (queue->head == NULL) { queue->tail = NULL; }

    free(temp);                 
    queue->currentSize--;

    return data;               
}


void* peek(queue* queue) {
    if (queue == NULL || isQueueEmpty(queue)) { return NULL; }
    return queue->head->data;
}


// Imprime do começo para o final, usando função aux pra converter void
void printQueue(queue* queue, void (*printData)(void*)) {
    if (queue == NULL || isQueueEmpty(queue)) {
        printf("Fila Vazia\n");
        return;
    }

    node* current = queue->head;
    while (current != NULL) {
        printData(current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}


void freeQueue(queue **queue) {
    if (queue == NULL || *queue == NULL) return;

    node* current = (*queue)->head;
    node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);              
        current = nextNode;
    }

    free(*queue);               
    *queue = NULL;                      
}
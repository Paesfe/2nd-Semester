#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int id;
    int idade;          
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

void enqueue(queue* queue, int id, int idade) {
    if (queue == NULL) return;

    node* new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) { return; } 

    new_node->id = id;
    new_node->idade = idade;
    new_node->next = NULL;
    
    if (isQueueEmpty(queue)) { 
        queue->head = new_node; 
    } else { 
        queue->tail->next = new_node; 
    }
    
    queue->tail = new_node;        
    queue->currentSize++;
}

// Alterado para retornar void e apenas remover o nó cabeça
void dequeue(queue* queue) {
    if (queue == NULL || isQueueEmpty(queue)) return;

    node* temp = queue->head;     
    queue->head = queue->head->next;
    
    if (queue->head == NULL) { 
        queue->tail = NULL; 
    }

    free(temp);                 
    queue->currentSize--;
}

// Função de impressão ajustada ao padrão do problema
void printQueue(queue* queue) {
    if (queue == NULL || isQueueEmpty(queue)) {
        printf("fila vazia!\n");
        return;
    }

    node* current = queue->head;
    while (current != NULL) {
        printf("ID: %d IDADE: %d\n", current->id, current->idade);
        current = current->next;
    }
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

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    queue* filaComum = create_queue();
    queue* filaIdosos = create_queue();

    int idosos_atendidos_seguidos = 0;
    char commandInput; 

    while (scanf(" %c", &commandInput) != EOF) {
        if (commandInput == 'f') { 
            break; 
        }
    
        switch (commandInput) {
            case 'a': {
                int id, idade;
                scanf("%d %d", &id, &idade);
                
                if (idade > 60) { 
                    enqueue(filaIdosos, id, idade);
                } else { 
                    enqueue(filaComum, id, idade);
                }
                break;
            }
        
            case 'r': {
                if (isQueueEmpty(filaIdosos)) {
                    dequeue(filaComum);
                    idosos_atendidos_seguidos = 0;
                } 
                else if (isQueueEmpty(filaComum)) {
                    dequeue(filaIdosos);
                    idosos_atendidos_seguidos = 0;
                } 
                else {
                    // Ambas possuem pessoas aguardando
                    if (idosos_atendidos_seguidos < n) {
                        dequeue(filaIdosos);
                        idosos_atendidos_seguidos++;
                    } else {
                        // Atingiu o limite 'n', força atendimento do não-idoso
                        dequeue(filaComum);
                        idosos_atendidos_seguidos = 0;
                    }
                }
                break;
            }
        
            case 'i': {
                printf("fila de idosos:\n");
                printQueue(filaIdosos);
                printf("fila de nao-idosos:\n");
                printQueue(filaComum);
                printf("----------\n\n");
                break;
            }
        }
    }   
    
    freeQueue(&filaComum);
    freeQueue(&filaIdosos);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _deque deque_t;
typedef struct _node   node_t;

// Guarda um ponteiro pro node anterior, para o proximo node e o valor guardado
struct _node {
    node_t *prev;
    node_t *next;
    int     value;
};

// Guarda um ponteiro para o primeiro node, um ponteiro para o ultimo node, e o tamanho do deque
struct _deque {
    node_t *front;
    node_t  *rear;
    int      size;
};

// Protótipos das funções
node_t* node_new     (int value);
deque_t* construct    ();
void     destruct     (deque_t *deque);
int      size         (deque_t *deque);
bool     empty        (deque_t *deque);
int      front        (deque_t *deque);
int      rear         (deque_t *deque);
void     enqueue_rear (deque_t *deque, int value);
void     enqueue_front(deque_t *deque, int value);
void     dequeue_rear (deque_t *deque);
void     dequeue_front(deque_t *deque);
void     erase        (deque_t *deque);
void     print        (deque_t *deque);

int main() {
    int i, num;
    if (scanf("%d", &num) != 1) return 0;
  
    deque_t* deque = construct();
  
    int vector[num];
    for(i = 0; i < num; ++i) {
        if (scanf("%d", &vector[i]) != 1) return 0;
    }
  
    for(i = 0; i < num; ++i)
        enqueue_rear(deque, vector[i]);
  
    printf("%d\n", front(deque));
    printf("%d\n", rear (deque));
  
    if(!empty(deque))
        printf("The size of the deque %d\n", size(deque));
    else
        printf("The deque is empty\n");
    
    if (scanf("%d", &num) != 1) return 0;
    for(i = 0; i < num; ++i)
       enqueue_front(deque, i);
    print(deque);
    dequeue_front(deque);
    print(deque);
    dequeue_rear (deque);
    print(deque);
    
    erase(deque);
    for(i = 0; i < 3; ++i)
        enqueue_rear(deque, i);
        
    print(deque);
    destruct(deque);
       
    return 0;
}

deque_t* construct() {
    deque_t* new_queue = (deque_t*) malloc(sizeof(deque_t));
    if (new_queue != NULL) {
        new_queue->front = NULL;
        new_queue->rear = NULL;
        new_queue->size = 0;
    }
    return new_queue;
}

void destruct (deque_t *deque){
    if (deque == NULL) return;
    erase(deque); // Reutiliza a função erase para limpar os nós
    free(deque);  // Libera a estrutura do deque
}

bool empty(deque_t* queue) {
    if (queue == NULL) return true;
    return (queue->size == 0);
}

int size(deque_t* queue) {
    if (queue == NULL) return 0;
    return queue->size;
}


int front(deque_t* queue) {
    if (queue == NULL || empty(queue)) return INT_MIN;
    return queue->front->value;
}

int rear(deque_t* queue) {
    if (queue == NULL || empty(queue)) return INT_MIN;
    return queue->rear->value;
}

node_t* node_new (int value){
    node_t* new_node = (node_t*) malloc(sizeof(node_t));
    if (new_node != NULL) {
        new_node->value = value;
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    return new_node;
}

void enqueue_front (deque_t *deque, int value){
    if (deque == NULL) return;

    node_t* new_node = node_new(value);
    if (new_node == NULL) return;

    if (empty(deque)) {
        // Se a fila estava vazia, o novo nó é o primeiro e o último
        deque->front = new_node;
        deque->rear = new_node;
    } else {
        new_node->next = deque->front;
        deque->front->prev = new_node;
        deque->front = new_node;
    }
           
    deque->size++;
}

void enqueue_rear (deque_t *deque, int value){
    if (deque == NULL) return;

    node_t* new_node = node_new(value);
    if (new_node == NULL) return;

    if (empty(deque)) {
        // Se a fila estava vazia, o novo nó é o primeiro e o último
        deque->front = new_node;
        deque->rear = new_node;
    } else {
        new_node->prev = deque->rear;
        deque->rear->next = new_node;
        deque->rear = new_node;
    }

    deque->size++;
}

void dequeue_rear (deque_t *deque){
    if (deque == NULL || empty(deque)) { return; }

    node_t* temp = deque->rear;     

    deque->rear = temp->prev;
    if (deque->rear == NULL) { deque->front = NULL; } 
    else { deque->rear->next = NULL; }

    free(temp);                 
    deque->size--;             
}

void dequeue_front(deque_t *deque){
    if (deque == NULL || empty(deque)) { return; }

    node_t* temp = deque->front;     

    deque->front = temp->next;
    if (deque->front == NULL) { deque->rear = NULL; } 
    else { deque->front->prev = NULL; }

    free(temp);                 
    deque->size--;              
}

void erase (deque_t* deque){
    if (deque == NULL) return;

    node_t* current = deque->front;
    node_t* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);              
        current = nextNode;
    }

    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
}

void print (deque_t *deque){
    if (deque == NULL) { return; } 
    
    node_t* current = deque->front;
    while (current != NULL) {
        printf("%d", current->value);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}
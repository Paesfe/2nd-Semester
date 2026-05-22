#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    void *data;
    struct node *next;
} node;

node* create_linked_list(){}
void addNode(node **head, void* data){}
void appendNode(node **head, void* data){}
void removeNode(node **head, void *data){}
int getListSize(node *head){} 
node* searchNode(node *head, void* target, int (*compare)(void*, void*)){}
    int compareInt(void *a, void *b){}
    int compareFloat(void *a, void *b){}
void printList(node* head, void (*printData)(void*)){}
    void printInt(void *data){}
    void printFloat(void *data){}
void freeList(node **head){}


node* create_linked_list(){
    return NULL;
}

void addNode(node **head, void* data){
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->next = *head;
    
    *head = new_node;
}

void appendNode(node **head, void* data){
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new_node;
}

void removeNode(node **head, void *data){
    node *previous = NULL;
    node *current = head;
    while (current != NULL && current->data != data){
        previous = current;
        current = current->next;
    }

    if (current == NULL){ return;}

    if (previous == NULL){ *head = current->next; } 
    else { previous->next = current->next; }

    free(current);
    
}

int getListSize(node *head) {
    int count = 0;
    node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

//Compare = função usada para comparar tipos voids 
node* searchNode(node *head, void* target, int (*compare)(void*, void*)) {
    node *current = head;
    while (current != NULL) {
        if (compare(current->data, target) == 0) return current;
        current = current->next;
    }
    return NULL;
}

// Funções auxiliares para o SeachNode
int compareInt(void *a, void *b) {
    return (*(int*)a == *(int*)b);
}

int compareFloat(void *a, void *b) {
    return (*(float*)a == *(float*)b);
}


void printList(node* head, void (*printData)(void*)) {
    node* temp = head;
    while (temp != NULL) {
        printData(temp->data);
        if (temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Funções auxiliares para o printList
void printInt(void *data) {
    printf("%d", *(int*)data);
}

void printFloat(void *data) {
    printf("%.2f", *(float*)data);
}

void freeList(node **head) {
    node *current = *head;
    node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);            
        current = nextNode;       
    }
    
    *head = NULL; // Zera a cabeça da lista por segurança
}
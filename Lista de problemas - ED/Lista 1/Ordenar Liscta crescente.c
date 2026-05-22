#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void *data;
    struct node *next;
} node;

void addNode(node **head, void* data){
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) return;

    new_node->data = data;
    new_node->next = *head;
    
    *head = new_node;
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

void printInt(void *data) {
    printf("%d", *(int*)data);
}

int compareInt(void *a, void *b) {
    return (*(int*)a - *(int*)b);
}

void sortList(node *head, int (*compare)(void*, void*)) {
    if (head == NULL) return;
    
    int swapped;
    node *ptr1;
    node *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (compare(ptr1->data, ptr1->next->data) > 0) {
                void *temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1; 
    } while (swapped);
}

void freeList(node **head) {
    node *current = *head;
    node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current->data);
        free(current);
        current = nextNode;
    }
    *head = NULL;
}

int main() {
    node *head = NULL;
    int num;

    while (scanf("%d", &num) != EOF) {
        int *val = (int*)malloc(sizeof(int));
        *val = num;
        addNode(&head, val);
    }

    sortList(head, compareInt);
    printList(head, printInt);
    freeList(&head);

    return 0;
}
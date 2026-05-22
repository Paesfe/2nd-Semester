#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    void *data;
    int   prior;
    struct node *next;
} node;

node* create_linked_list(){
    return NULL;
}

void addNode(node **head, void* data, int prior){
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) return;

    new_node->data = (char*) malloc((strlen((char*)data) + 1) * sizeof(char));
    strcpy((char*)new_node->data, (char*)data);
    
    new_node->prior = prior;
    new_node->next = *head;
    
    *head = new_node;
}

void organizarLista(node *head) {
    if (head == NULL) return;

    int trocou;
    node *atual;
    node *limite = NULL;

    do {
        trocou = 0;
        atual = head;

        while (atual->next != limite) {
            if (atual->prior > atual->next->prior) {
                int temp_prior = atual->prior;
                atual->prior = atual->next->prior;
                atual->next->prior = temp_prior;

                void *temp_data = atual->data;
                atual->data = atual->next->data;
                atual->next->data = temp_data;

                trocou = 1;
            }
            atual = atual->next;
        }
        limite = atual; 
    } while (trocou);
}

void printList(node* head) {
    printf("\n"); 
    
    node* temp = head;
    while (temp != NULL) {
        printf("%d. %s\n", temp->prior, (char*)temp->data);
        temp = temp->next;
    }
}

void registrarTarefa(node **list){
    int prior; 
    char tarefa[500];

    int c;
    while ((c = getchar()) != '\n' && c != EOF); 

    if (fgets(tarefa, sizeof(tarefa), stdin) != NULL) {
        tarefa[strcspn(tarefa, "\n")] = '\0';
    }

    scanf("%d", &prior);
    addNode(list, tarefa, prior);
}

void mostrarTarefa(node **list){
    organizarLista(*list);
    printList(*list);
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
    node *list = create_linked_list(); 
    int input;

    while (scanf("%d", &input) != EOF) {
        if (input == 0) { break; }
        else if(input == 1){ registrarTarefa(&list); }
        else if(input == 2){ mostrarTarefa(&list); }  
    }

    freeList(&list);
    return 0;
}
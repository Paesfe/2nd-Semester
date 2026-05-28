#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Armazena o primeiro item da fila
typedef struct _stack STACK;

//Armazena o conteudo do no e um ponteiro para o proximo no da fila
typedef struct _node NODE;

struct _stack
{
    NODE* head;
};
struct _node
{
    int element;
    NODE* next;
};

//Cria uma stack com o a head NULL
STACK* Create_stack();

//Verifica se a pilha esta vazia
int IS_EMPTY(STACK* stack);

//Recebe uma pilha e Retorna o elemento que esta no topo da fila
int POP(STACK* stack);

//Recebe uma pilha e um inteiro e retorna a nova pilha
//Adiciona um novo node no topo da pilha
void PUSH(STACK* stack, int element);

//Recebe a pilha e a operacao a ser feita
//faz a operacao da calculadora
void result(STACK* stack, char operation);

//Recebe uma pilha vazia e quantas strings serao lidas
//Le as n strings que vao seguir e resolve as expressoes
void Calculadora(STACK* calculadora, int size);

int main()
{
    STACK* calculadora = Create_stack();
    int k;
    if (scanf("%d", &k) == 1) {
        Calculadora(calculadora, k);
        printf("Coordenada 1: %d\n", POP(calculadora));
    }
    if (scanf("%d", &k) == 1) {
        Calculadora(calculadora, k);
        printf("Coordenada 2: %d\n", POP(calculadora));
    }

    free(calculadora);
    return 0;
}

STACK* Create_stack(){
    STACK* new_stack = (STACK*) malloc(sizeof(STACK));
    if (new_stack != NULL) {
        new_stack->head = NULL;
    }
    return new_stack;
}

int IS_EMPTY(STACK* stack){
    if (stack == NULL) return 1;
    return (stack->head == NULL);
}

// Inserir novo elemento; 
void PUSH(STACK* stack, int element){
    if (stack == NULL) return;

    NODE* new_node = (NODE*) malloc(sizeof(NODE));
    if (new_node == NULL) { return; } 

    new_node->element = element;
    new_node->next = stack->head;
    stack->head = new_node;    
}

// Remove and return the top node element; 
int POP(STACK* stack){
    if (stack == NULL || IS_EMPTY(stack)) { return 0; }

    NODE* temp = stack->head;     
    int data = temp->element;

    stack->head = temp->next;        
    free(temp);                

    return data;               
}

void result(STACK* stack, char operation){
    if (stack == NULL || IS_EMPTY(stack)) return;
    
    // O primeiro a sair é o segundo operando (direita da operação)
    int operand2 = POP(stack);
    
    if (IS_EMPTY(stack)) return; // Garante que há um segundo número
    int operand1 = POP(stack);
    
    int res = 0;
    switch (operation) {
        case '+': res = operand1 + operand2; break;
        case '-': res = operand1 - operand2; break;
        case '*': res = operand1 * operand2; break;
        case '/': 
            if (operand2 != 0) {
                res = operand1 / operand2; 
            } else {
                res = 0; // Evita divisão por zero
            }
            break;
        default: return;
    }
    
    PUSH(stack, res); // Empilha o resultado de volta
}

void Calculadora(STACK* calculadora, int size){
    char input[50];
    
    for (int i = 0; i < size; i++) {
        scanf("%s", input);
        
        // Verifica se a string lida é um dos operadores válidos
        if (strcmp(input, "+") == 0 || strcmp(input, "-") == 0 || 
            strcmp(input, "*") == 0 || strcmp(input, "/") == 0) {
            result(calculadora, input[0]);
        } else {
            // Caso contrário, assume que é um número e converte
            int num = atoi(input);
            PUSH(calculadora, num);
        }
    }
}
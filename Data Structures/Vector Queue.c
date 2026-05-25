#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ITEM char
#define TAM 50 // Tamanho máximo da fila. Em uma fila circular, o máximo de itens úteis será TAM - 1.

// Estrutura da fila estática
typedef struct fila {
    ITEM vet[TAM];
    int front; // Índice do item que está na frente (próximo a sair)
    int rear;  // Índice de onde o próximo item será inserido
} TFila;

// Inicializa a fila definindo inicio e fim no mesmo ponto (0)
void create(TFila *f) {
    f->front = 0;
    f->rear = 0;
}

// "Destrói" ou esvazia a fila logicamente igualando o início ao fim
void destroy(TFila *f) {
    f->front = f->rear;
}

// Função auxiliar vital para a Fila Circular: 
// Calcula o próximo índice, voltando a 0 se ultrapassar TAM-1
int next(int n) {
    return (n + 1) % TAM;
}

// Verifica se a fila está vazia
// Fila vazia ocorre quando o ponteiro front e rear apontam para o mesmo índice
bool isempty(TFila *f) {
    return (f->front == f->rear);
}

// Verifica se a fila está cheia
// Fila cheia ocorre quando o próximo índice após o rear "esbarra" no front.
// (Deixamos sempre 1 espaço vazio no vetor para diferenciar fila cheia de fila vazia).
bool isfull(TFila *f) {
    return (next(f->rear) == f->front);
}

// Enfileira (Insere) um item no final da fila
void enqueue(TFila *f, ITEM dado) {
    if (isfull(f)) {
        // Opcional: imprimir mensagem de erro ou apenas retornar
        // printf("Erro: Fila cheia!\n");
        return;
    }
    
    f->vet[f->rear] = dado;        // Insere o dado na posição livre do rear
    f->rear = next(f->rear);       // O rear avança circularmente para o próximo espaço livre
}

// Desenfileira (Remove e retorna) o item da frente da fila
ITEM dequeue(TFila *f) {
    if (isempty(f)) {
        // Tratamento de erro para fila vazia. Retornando um caractere nulo/vazio por segurança.
        // printf("Erro: Fila vazia!\n");
        return '\0'; 
    }
    
    ITEM dado = f->vet[f->front];  // Salva o item que está na frente
    f->front = next(f->front);     // O front avança circularmente, ignorando (removendo) o item anterior
    
    return dado;
}

// Retorna o item da frente sem removê-lo (opcional, útil para consultas)
ITEM peek(TFila *f) {
    if (isempty(f)) {
        return '\0'; 
    }
    return f->vet[f->front];
}

// Imprime os itens da fila, desde o front até chegar no rear
void printQueue(TFila *f) {
    if (isempty(f)) {
        return;
    }
    
    int i = f->front;
    while (i != f->rear) {
        printf("%c ", f->vet[i]);
        i = next(i); // Avança circularmente
    }
    printf("\n");
}
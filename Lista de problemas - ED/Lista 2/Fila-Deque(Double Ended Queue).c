#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct deque {
    ITEM vet[TAM];
    int front, rear;
} TDeque;

void create(TDeque *d) {
    d->front = 0;
    d->rear = -1;
}

void destroy(TDeque *d) {
    d->front = 0;
    d->rear = -1;
}


int isfull(TDeque *d) {
    return (d->rear + 1 == TAM);
}

int isempty(TDeque *d) {
    return (d->rear == -1);
}

void store(TDeque *d, int extremidade, ITEM x) {
    if(isfull(d)) return;
    if(extremidade == 1) { // Inserção no início
        for (int i = d->rear; i >= 0; i--) {
            d->vet[i + 1] = d->vet[i];
        }
        d->vet[0] = x;
        d->rear++;
    } else { // Inserção no fim
        d->rear++;
        d->vet[d->rear] = x;
    }
}

ITEM retrieve(TDeque *d, int extremidade) {
    if(isempty(d)) return '\0'; // Retorna um valor nulo se a fila estiver vazia
    if(extremidade == 1) { // Remoção do início
        ITEM item = d->vet[0];
        for (int i = 0; i < d->rear; i++) {
            d->vet[i] = d->vet[i + 1];
        }
        d->rear--;
        return item;
    } else { // Remoção do fim
        ITEM item = d->vet[d->rear];
        d->rear--;
        return item;
    }
}

void preenche(TDeque *d) {
    ITEM x;
    int qtd, extremidade, i;

    scanf("%d%*c", &qtd);

    for( i=0; i<qtd; i++ ) {
        scanf("%c %d%*c", &x, &extremidade);
        store(d, extremidade, x);
    }
}

void exibe(TDeque *d) {
    int extremidade;

    while( scanf("%d", &extremidade) != EOF ) {
		if( extremidade==1 )
        	printf("INICIO = %c\n", retrieve(d, extremidade));
		else
			printf("FIM = %c\n", retrieve(d, extremidade));
	}
}

int main(void) {
    TDeque d;

    create(&d);
    preenche(&d);
    exibe(&d);
    destroy(&d);

    return 0;
}
    
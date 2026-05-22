#include <stdio.h>
#include <stdlib.h>

void merge(int input[], int esquerda, int meio, int direita) {
    int i, j, k;
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;

    // Cria inputays temporários
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copia os dados para os inputays temporários L[] e R[]
    for (i = 0; i < n1; i++)
        L[i] = input[esquerda + i];
    for (j = 0; j < n2; j++)
        R[j] = input[meio + 1 + j];

    // Mescla os inputays temporários de volta no input[esquerda..direita]
    i = 0; // Índice inicial do primeiro sub-inputay
    j = 0; // Índice inicial do segundo sub-inputay
    k = esquerda; // Índice inicial do inputay mesclado
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            input[k] = L[i];
            i++;
        } else {
            input[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[]
    while (i < n1) {
        input[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[]
    while (j < n2) {
        input[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int input[], int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(input, esquerda, meio);
        mergeSort(input, meio + 1, direita);

        merge(input, esquerda, meio, direita);
    }
}

int main() {
    
}

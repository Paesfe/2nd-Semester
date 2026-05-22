#include <stdio.h>
#include <string.h>

void inverter(){
    int input;

    if (scanf("%d", &input) != EOF){
        inverter();
        printf("%d ", input);
    }
}

int main(){
    inverter();
    printf("\n");
    return 0;
}
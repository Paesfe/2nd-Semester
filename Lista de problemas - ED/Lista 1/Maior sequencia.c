#include <stdio.h>
#include <string.h>

void contador(char *str) {
    int maxSize = -1;
    int maxStart = 0; 
    int maxEnd = 0;
    
    int currentStart = 0;
    int currentSize = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        
        if (str[i] == '1') {
            currentSize = 0;
            continue;
        }
        
        if (currentSize == 0) {
            currentStart = i;
        }

        currentSize++;

        if (currentSize > maxSize) {
            maxSize = currentSize;
            maxStart = currentStart;
            maxEnd = i;
        }
    }

    if (maxSize != -1) {
        printf("%d %d\n", maxStart, maxEnd);
    }
}

int main(){
    char input[1000];

    while(scanf("%s", input) != -1){
        if (strcmp(input, "0") == 0){ break;}

        contador(input);
    }
    
    return 0;
}
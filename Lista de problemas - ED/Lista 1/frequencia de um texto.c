#include <stdio.h>
#include <string.h>

int main() {
    char texto[1000];
    int freq[256] = {0};

    if (fgets(texto, sizeof(texto), stdin)) {
        
        for (int i = 0; texto[i] != '\0'; i++) {
            if (texto[i] != '\n' && texto[i] != '\r') {
                freq[(char)texto[i]]++;
            }
        }

        for (int i = 255; i >= 0; i--) {
            if (freq[i] > 0) {
                printf("%c %d\n", (char)i, freq[i]);
            }
        }
    }

    return 0;
}
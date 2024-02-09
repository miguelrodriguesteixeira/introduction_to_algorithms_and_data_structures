/* iaed-23 - ist1103449 - lab09/ex02 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PALAVRAS 10000
#define MAX_TAM_PALAVRA 1001

char* copyString(char str[]) {
    char *p;
    char *copy;

    p = malloc(sizeof(char) * strlen(str) + 1);
    copy = p;
    while ((*p = *str) != '\0') {
        p++;
        str++;
    }
    return copy;
}


int main() {
    char palavra[MAX_TAM_PALAVRA];
    char* palavras[MAX_PALAVRAS];
    int n = 0, i;

    while ((n < MAX_PALAVRAS) && (scanf("%s", palavra) == 1)) {
        palavras[n++] = copyString(palavra);

    }

    for (i = n - 1; i >= 0; i--) {
        printf("%s\n", palavras[i]);
    }

    for (i = 0; i < n; i++) {
        free(palavras[i]);
    }

    return 0;
}


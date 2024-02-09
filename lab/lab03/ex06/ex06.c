/* iaed-23 - ist1103449 - lab03/ex06 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char N[101];
    int i,st;
    int soma = 0;

    scanf("%s", N);

    st = strlen(N);

    for (i = 0; i < st; i++) {
        soma += N[i] - '0'; /* converter para codigoasciiiii*/
    }

    if (soma % 9 == 0) {
        printf("yes\n");
    }
    else {
        printf("no\n");
    }
    return 0;
}


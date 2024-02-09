/* iaed-23 - ist1103449 - lab02/ex10 */

#include <stdio.h>

int main() {
    int N, i, alg;
    int contador = 0, soma = 0;

    scanf("%d", &N);
    for (i = 0; N > 0; i++) {
        alg = N % 10;
        N = N / 10;
        contador += 1;
        soma += alg;
    }

    printf("%d\n", contador);
    printf("%d\n", soma);

    return 0;
}

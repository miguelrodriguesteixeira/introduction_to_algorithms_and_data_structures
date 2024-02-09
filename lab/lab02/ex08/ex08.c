/* iaed-23 - ist1103449 - lab02/ex08 */

#include <stdio.h>

int main() {
    int N = 0;
    float num, media, soma = 0;
    int i;

    scanf("%d", &N);

    for (i = 1; i <= N; i++) {
        scanf("%f", &num);
        soma += num;
    }

    media = soma / N;
    printf("%.2f\n", media);

    return 0;
}


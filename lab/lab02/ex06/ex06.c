/* iaed-23 - ist1103449 - lab02/ex06 */

#include <stdio.h>

int main() {
    int N, i;
    float num, num1;
    float maior = 0, menor = 0;

    scanf("%d", &N);
    scanf("%f", &num1);
    maior = menor = num1;
    for (i = 0; i < N - 1; i++) {
        scanf("%f", &num);
        if (num > maior) {
            maior = num;
        }
        if (num < menor) {
            menor = num;
        }
    }   
    printf("min: %f, max: %f\n", menor, maior);
    
    return 0;
}

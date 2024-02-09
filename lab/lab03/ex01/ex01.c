/* iaed-23 - ist1103449 - lab03/ex01 */

#include <stdio.h>

void quadrado(int N){
    int i,j;

    for (j = 1; j <= N; j++) {
        for (i = j; i <= N + j - 2; i++){
            printf("%d\t", i);
        }
        printf("%d", i);
        printf("\n");
    }
}

int main() {
    int N = 0;
    scanf("%d", &N);
    quadrado(N);

    return 0;
}

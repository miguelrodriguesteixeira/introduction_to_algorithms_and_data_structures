/* iaed-23 - ist1103449 - lab03/ex03 */

#include <stdio.h>

void cruz(int N){
    int i,j;
    for (j = 1; j <= N; j++) {
        for (i = 1; i <= N; i++) {
            if (i == j || i + j == N + 1) {
                printf("* ");  
            }
            else {
                printf("- ");
            }
        }
        printf("\n");
    }
}

int main() {
    int N;
    scanf("%d", &N);
    cruz(N);
    return 0;
}

/* iaed-23 - ist1103449 - lab02/ex07 */

#include <stdio.h>

int main() {
    int N, i, div = 0;

    scanf("%d", &N);

    for (i = 1; i <= N; i++) {
        if ((N % i) == 0) {
            div += 1;
        }
    }

    printf("%d\n", div);
    return 0;
}

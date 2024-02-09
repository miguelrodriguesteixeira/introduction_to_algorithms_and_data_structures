/* iaed-23 - ist1103449 - lab04/ex01 */

#include <stdio.h>

#define VEC_MAX 100

int main() {
    int n;
    int i, j;
    int _vec[VEC_MAX];

    scanf("%d", &n);
    if (n > VEC_MAX || n < 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &_vec[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < _vec[i]; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}

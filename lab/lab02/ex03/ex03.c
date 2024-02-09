/* iaed-23 - ist1103449 - lab02/ex03 */

#include <stdio.h>

int main() {
    int n1, n2;

    scanf("%d %d", &n1, &n2);

    if (n1 % n2 == 0){
        printf("yes\n");
    }
    else {
        printf("no\n");
    }
    return 0;
}

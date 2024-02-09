/* iaed-23 - ist1103449 - lab09/ex01 */

#include <stdio.h>
#include <string.h>

int main() {
    char palavra[1001];
    char *p;
    int len, i;

    scanf("%s", palavra);
    len = strlen(palavra);

    for (i = 0; i < len; i++) {
        p = &palavra[i];
        printf("%s\n", p);
    }

    return 0;
}



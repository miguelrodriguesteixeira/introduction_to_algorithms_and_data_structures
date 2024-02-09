/* iaed-23 - ist1103449 - lab04/ex04 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 80

int main() {
    char s[MAX];
    int t;
    int i,j;

    s[0] = '\0'; /* por causa do \0 no final */

    scanf("%s", s);

    t = strlen(s);


    for (i = 0, j = t-1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            printf("no\n");
            return 0;
        }
        
    }

    printf("yes\n");
    return 0;
}

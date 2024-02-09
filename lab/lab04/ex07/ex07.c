/* iaed-23 - ist1103449 - lab04/ex07 */

#include <string.h>
#include <stdio.h>


void apagaCaracter(char s[], char c) {
    int i,j;
    
    for (i = 0, j = 0; s[i] != '\n'; i++) {
        if (s[i] != c) {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
    printf("%s\n", s);
}

int main() {
    char s[101];
    char c  = '\0';

    fgets(s, 101, stdin);
    scanf("%c", &c);

    apagaCaracter(s,c);
    return 0;
}

/* iaed-23 - ist1103449 - lab03/ex05 */

#include <stdio.h>

enum state {IN, OUT, ESC};

int main() {
    int c;
    enum state current = OUT;

    while((c = getchar())!= EOF){
        switch (current) {
        
        case ESC:
            putchar(c);
            current = IN;
            break;

        case OUT:
            if (c == '"') {
                current = IN;
            }
            break;
        
        case IN:
            if (c == '"') {
                current = OUT;
                printf("\n");
            }
            else if (c == '\\'){
                current = ESC;
            }
            else {
                putchar(c);
            }
            break;
            }
        }
    return 0;
}

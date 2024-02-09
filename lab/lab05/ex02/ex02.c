/* iaed-23 - ist1103449 - lab05/ex02 */

#include <stdio.h>

typedef struct {
    float real;
    float imaginario;
} Complexo;


Complexo le_complexo() {
    Complexo c;
    char sinal;

    scanf("%f%c%fi", &c.real,&sinal,&c.imaginario);

    if (sinal == '-'){
        c.imaginario = 0 - c.imaginario;
    }

    return c;
}

int main() {
    Complexo c1, c2;
    double real, imagina;
    char sinal;

    c1 = le_complexo();
    c2 = le_complexo();

    real = c1.real + c2.real;
    imagina = c1.imaginario + c2.imaginario;

    if (imagina < 0){
        sinal = '-';
    }

    else {
        sinal = '+';
    }

    printf("%.2f%c%.2fi\n", real,sinal, imagina);
    return 0;
}


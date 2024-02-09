/* iaed-23 - ist1103449 - lab02/ex04 */

#include <stdio.h>

int max(int a, int b, int c) {
    if (a > b && a > c){
        return a;
    }
    if (b > a && b > c){
        return b;
    }
    return c;
}

int min(int a, int b, int c) {
    if (a < b && a < c){
        return a;
    }
    if (b < a && b < c){
        return b;
    }
    return c;
}

int mid(int a, int b, int c) {
    if (max(a, b, c) != a && min(a, b, c) != a){
        return a;
    }
    if (max(a, b, c) != b && min(a, b, c) != b){
        return b;
    }
    return c;
}

int main(){
    int n1, n2, n3;
    int maior = 0, menor = 0, meio = 0;
    
    scanf("%d %d %d", &n1, &n2, &n3);
    maior = max(n1, n2, n3);
    menor = min(n1, n2, n3);
    meio = mid(n1, n2, n3);

    printf("%d %d %d\n", menor, meio, maior);
    return 0;
}


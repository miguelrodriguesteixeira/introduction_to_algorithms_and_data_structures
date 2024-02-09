## Exercício 04

(Números) Escreva um programa que leia uma sequência de números separados por espaços e novas linhas,
e imprima a mesma sequência, mas os números no output não deverão conter 0 no início, por exemplo, `007` deverá imprimir `7`.

A excepção é o número 0, que se deverá imprimir como 0.
A sequência no input termina com `EOF`.

*Atenção:* Os valores dos números poderão ser superiores ao valor máximo do tipo `int` ou qualquer tipo primitivo em C.

*Dica:* a função `int getchar()` pode ser usada para ler um carácter.

**Input**
```
01 3 02 000 027770
```

**Output**
```
1 3 2 0 27770
```


# Evaluation

2023-03-03T14:45:03

## [- Compile Time Error-].


Your code will not be reevaluated if you submit before 2023-03-03 14:46:03 @ Lisbon, Portugal. You need to wait 1 minute(s).



- Compiler Output:


```
ex04.c: In function 'main':
ex04.c:7:1: error: control reaches end of non-void function [-Werror=return-type]
 }
 ^
cc1: all warnings being treated as errors

```

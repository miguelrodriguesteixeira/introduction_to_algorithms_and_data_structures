/*---------------------------------------------------------------------------------------------*/
/* Projeto 2 - IAED 2021/2022                                                                  */
/* Miguel Teixeira - ist1103449;                                                               */
/*---------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comandos.c"

int main() {
	int c;
	/* obtemos o input do utilizador que e comparado com os comando disponiveis */
	while ((c = getchar()) != EOF) {
		switch (c) {
		case 'q': return 0;
		case 'a': adicionaAeroporto();
			break;
		case 'l': listaAeroportos();
			break;
		case 'v': adicionaListaVoos();
			break;
		case 'p': listaVoosPartida();
			break;
		case 'c': listaVoosChegada();
			break;
		case 't': alteraData();
			break;
		case 'r': adicionaReserva();
			break;
		/* case 'e': delreserva();
			break; */
		default: printf("Invalid comand: %c\n", c); 
		/* caso o input seja invalido */
		}
	}
	return 0;
}

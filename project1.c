/* iaed-23 - ist1103449 - project2 
 * Ficheiro: project2.c 
 * Autor: Miguel Teixeira 
 * Descricao: construcao de um sistema de gestao de carreiras de 
   transporte publico. 
*/

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "project2.h"

/****************************************************************************/
/* Funcoes Paragem */

/* Imprime as informacoes da paragem. */
void mostraParagem(Paragem* p) {
    printf("%s: %16.12f %16.12f %d\n", p->nome, p->latitude, 
    p->longitude, p->num_carreiras);
}

/* Imprime a latitude e longitude da paragem. */
void listaParagem(Paragem* p) {
    printf("%16.12f %16.12f\n", p->latitude, p->longitude);
}

/* Adiciona a paragem ao fim da lista. */
void adicionaParagem(Paragem** root, Paragem* novaParagem) {
    Paragem* curr = *root;
    /* encontrar o ultimo elemento */
    while (curr->prox != NULL) {
        curr = curr->prox;
    }
    curr->prox = novaParagem;
}

/* Cria a nova paragem e adiciona-a ao fim da lista. */
void criaParagem(Paragem** root, char* nome, double latitude, 
    double longitude) {
    Paragem* novaParagem = malloc(sizeof(Paragem));
    if (novaParagem == NULL) {
        printf("No memory.\n");
        exit(0);
    }

    /* inicializa os valores */
    novaParagem->prox = NULL;
    novaParagem->nome = malloc(strlen(nome) + 1);
    if (novaParagem->nome == NULL) {
        printf("No memory.\n");
        free(novaParagem->nome);
        exit(0);
    }
    strcpy(novaParagem->nome, nome);
    novaParagem->latitude = latitude;
    novaParagem->longitude = longitude;
    novaParagem->num_carreiras = 0;

    /* adiciona ao fim da lista */
    if (*root == NULL) {
        *root = novaParagem;
    } 
    else {
        adicionaParagem(root, novaParagem);
    }
}

/* Encontra a paragem pelo seu nome. Retorna a paragem se encontrar, 
caso contrario, retorna NULL. */
Paragem* encontraParagem(Paragem** root, char* nome) {
    Paragem* p = *root;
    while (p != NULL) {
        if (strcmp(p->nome, nome) == 0)
            return p;
        p = p->prox;
    }
    return NULL;
}

/* Funcao principal do comando p. */
void adicionaListaParagens(Paragem** root) {
    char buffer[BUFFERSIZE];
    char nome[BUFFERSIZE], latitude[MAX_NUM_DOUBLE];
    char longitude[MAX_NUM_DOUBLE];
    int num_arg;
    char aspas = '\0';

    Paragem* curr;

    fgets(buffer, BUFFERSIZE, stdin);
    
    if (buffer[1] == '"') {
        num_arg = sscanf(&buffer[2], "%[^\"]%c %s %s", nome, &aspas, 
        latitude, longitude);
    } 
    else {
        num_arg = sscanf(buffer, "%s %s %s", nome, latitude, longitude);
    }

    /* Lista todas as paragens - sem argumentos */
    if (num_arg == -1) {
        for (curr = *root; curr != NULL; curr = curr->prox) {
            mostraParagem(curr);
        }
        return;
    }

   /* Lista uma paragem - um argumento */
    if (num_arg == 1) {
        Paragem *p = encontraParagem(root, nome);
        if (p != NULL) {
            listaParagem(p);
        } 
        else {
            printf("%s: no such stop.\n", nome);
        }
        return;
    }

    /* Adiciona a paragem - tres argumentos */
    if ((num_arg == 3) || (num_arg == 4)) {
        double lat = atof(latitude);
        double lon = atof(longitude);
        if (encontraParagem(root, nome) != NULL) {
            printf("%s: stop already exists.\n", nome);
        }
        else {
            criaParagem(root, nome, lat, lon);
        }
        return;
    }

    return;
}

/****************************************************************************/
/* Funcoes Carreira */

/* Imprime as informacoes da carreira. */
void mostraCarreira(Carreira* c) {
    /* as paragens sao omitidas para carreiras sem ligacoes */
	if ((c->origem.nome == NULL)&& (c->destino.nome == NULL)) {
		printf("%s %d %.2f %.2f\n", c->nome, 
		c->numParagens, c->custo, c->duracao);
		return;
	}
	printf("%s %s %s %d %.2f %.2f\n", c->nome, 
	c->origem.nome, c->destino.nome, 
	c->numParagens, c->custo, 
	c->duracao);
}

/* Imprime as paragens da carreira dada, pela ordem inversa do percurso. */
void imprimeParagensDaCarreiraInverso(Carreira* c) {
    Ligacao* ligacao_atual = c->_ligacoesParagens;
    if (c->numParagens == 0) {
        return;
    }
    printf("%s, ", c->destino.nome);
    while (ligacao_atual != NULL) {
        if ((strcmp(ligacao_atual->paragemLigacao.nome, c->origem.nome) != 0)
        && (strcmp(ligacao_atual->paragemLigacao.nome, c->destino.nome) != 0)
        && (strcmp(ligacao_atual->paragemLigacao.nome, "") != 0)) {
            printf("%s, ", ligacao_atual->paragemLigacao.nome);
        }
        ligacao_atual = ligacao_atual->prox;
    }
    printf("%s\n", c->origem.nome);
}

/* Imprime as paragens da carreira dada, pela ordem do percurso */
void imprimeParagensDaCarreira(Carreira* c) {
    Ligacao* ligacaoAtual = c->_ligacoesParagens;
    if (c->numParagens == 0) {
        return;
    }
    printf("%s, ", c->origem.nome);
    while (ligacaoAtual != NULL) {
        if ((strcmp(ligacaoAtual->paragemLigacao.nome, c->origem.nome) != 0)
        && (strcmp(ligacaoAtual->paragemLigacao.nome, c->destino.nome) != 0)
        && (strcmp(ligacaoAtual->paragemLigacao.nome, "") != 0)) {
                printf("%s, ", ligacaoAtual->paragemLigacao.nome);
        }
        ligacaoAtual = ligacaoAtual->prox;
    }
    printf("%s\n", c->destino.nome);
}

/* Adiciona a carreira ao fim da lista. */
void adicionaCarreira(Carreira** root, Carreira* novaCarreira) {
    Carreira* curr = *root;
    /* encontrar o ultimo elemento */
    while (curr->prox != NULL) {
        curr = curr->prox;
    }
    curr->prox = novaCarreira;
}

/* Cria a nova Carreira e adiciona-a ao fim da lista. */
void criaCarreira(Carreira** root, char* nome) {
    Carreira* novaCarreira = malloc(sizeof(Carreira));
    if (novaCarreira == NULL) {
        printf("No memory.\n");
        exit(0);
    }

    /* inicializa os valores */
    novaCarreira->prox = NULL;
    novaCarreira->nome = malloc(strlen(nome) + 1);
    if (novaCarreira->nome == NULL) {
        printf("No memory.\n");
        free(novaCarreira->nome);
        exit(0);
    }
    strcpy(novaCarreira->nome, nome);
    novaCarreira->numParagens = 0;
    novaCarreira->custo = 0;
    novaCarreira->duracao = 0;

    /* adiciona ao fim da lista */
    if (*root == NULL) {
        *root = novaCarreira;
    } else {
        adicionaCarreira(root, novaCarreira);
    }
}

/* Encontra a carreira pelo seu nome. Retorna a carreira se encontrar,
caso contrario, retorna NULL. */
Carreira* encontraCarreira(Carreira** root, char* nome) {
    Carreira* c = *root;
    while (c != NULL) {
        if (strcmp(c->nome, nome) == 0)
            return c;
        c = c->prox;
    }
    return NULL;
}

/* Funcao principal do comando c. */
void adicionaListaCarreira(Carreira** root) {
	char buffer[BUFFERSIZE], nome[BUFFERSIZE];
	int num_arg;
	char ehInverso[8];

    Carreira* curr;

	fgets(buffer, BUFFERSIZE, stdin);
	num_arg = sscanf(buffer, "%s %s", nome, ehInverso);
    
	/* Lista todas as carreiras - sem argumentos */
	if (num_arg == -1) {
		for (curr = *root; curr != NULL; curr = curr->prox) {
            mostraCarreira(curr);
        }
        return;
	}

	/* cria-se uma nova carreira se ainda nao existir */
	if (encontraCarreira(root, nome) == NULL) {
		criaCarreira(root, nome);
        return;
	}

	else {
		/* parametro inverso - impressao das paragens por ordem inversa */
		if (strcmp(ehInverso, "inverso") == 0 || 
		strcmp(ehInverso, "invers") == 0 || 
		strcmp(ehInverso, "inver") == 0 || 
		strcmp(ehInverso, "inve") == 0 || 
		strcmp(ehInverso, "inv") == 0) {
			imprimeParagensDaCarreiraInverso(encontraCarreira(root, nome));
            return;
		}

		/* sem parametro inverso */
		if (num_arg == 1) {
			imprimeParagensDaCarreira(encontraCarreira(root, nome));
            return;
		}

		/* depois do nome da carreira existe uma palavra que nao 
		e inverso ou uma das suas abreviaturas */
		else {
			printf("incorrect sort option.\n");
		}
	}
}

/****************************************************************************/
/* Funcoes Ligacoes */

/* Devolve se existe a paragem no percurso da carreira, retorna 0 se falso */
int encontraParagensNaCarreira(char* nome, Carreira* c) {
    Ligacao* ligacaoAtual = c->_ligacoesParagens;
    if (c->_ligacoesParagens == NULL) {
        return 0;
    }
    while(ligacaoAtual != NULL) {
        char* nomeParagemAtual = ligacaoAtual->paragemLigacao.nome;
        if (strcmp(nome, nomeParagemAtual) == 0) {
            /* se existir na carreira retorna 1 */
            return 1;
        }
        ligacaoAtual = ligacaoAtual->prox;
    }
    /* se nao existir na carreira retorna 0 */
    return 0;
}

/* Insere a paragem no inicio do percurso da carreira. */
void insereParagemNoInicio(Carreira* c, Paragem* paragem) {
    Ligacao *novaLigacao = malloc(sizeof(Ligacao));
    if (novaLigacao == NULL) {
        printf("No memory.\n");
        exit(0);
    }
    novaLigacao->paragemLigacao = *paragem;
    novaLigacao->prox = c->_ligacoesParagens;
    c->_ligacoesParagens = novaLigacao;
    c->numParagens++;
    paragem->num_carreiras++;
}

/* Adiciona a paragem no percurso da carreira. */
void adicionaNaCarreira(Carreira *c, Paragem *p) {
    Ligacao *novaLigacao = (Ligacao*) malloc(sizeof(Ligacao));
    novaLigacao->paragemLigacao = *p;
    novaLigacao->prox = NULL;
    if (c->_ligacoesParagens == NULL) {
        c->_ligacoesParagens = novaLigacao;
    } 
    else {
        Ligacao *ultimaLigacao = c->_ligacoesParagens;
        while (ultimaLigacao->prox != NULL) {
            ultimaLigacao = ultimaLigacao->prox;
        }
        ultimaLigacao->prox = novaLigacao;
    }
    c->numParagens++;
    p->num_carreiras++;
}

/* Funcao principal do comando l. */
void adicionaLigacoes(Carreira** c_root, Paragem** p_root) {
	char buffer[BUFFERSIZE], nome[BUFFERSIZE];
	char paragem1[BUFFERSIZE], paragem2[BUFFERSIZE];
	char custo[MAX_NUM_REALFLOAT], duracao[MAX_NUM_REALFLOAT];
	int t_nome, t_nome_origem;
	float custo1, duracao1;
	char aspas = '\0';

    Carreira* c;
    Paragem* ciclo;

	fgets(buffer, BUFFERSIZE, stdin);

	sscanf(buffer, "%s", nome);
	t_nome = strlen(nome);

	/* a paragem1 tem aspas */
	if (buffer[t_nome+2] == '"') {
		sscanf(&buffer[t_nome+3], "%[^\"]%c", paragem1, &aspas);
		t_nome_origem = strlen(paragem1);

		/* a paragem2 tem aspas */
		if (buffer[t_nome+t_nome_origem+5] == '"') { 
			sscanf(&buffer[t_nome+t_nome_origem+6], "%[^\"]%c %s %s", 
			paragem2, &aspas, custo, duracao);
		}
		/* a paragem2 nao tem aspas */
		else { 
			sscanf(&buffer[t_nome+t_nome_origem+4], "%s %s %s", 
			paragem2, custo, duracao);
		}
	}

	/* a paragem1 nao tem aspas */
	else {
		sscanf(&buffer[t_nome+2], "%s", paragem1);
		t_nome_origem = strlen(paragem1);

		/* a paragem2 tem aspas */
		if (buffer[t_nome+t_nome_origem+3] == '"') { 
			sscanf(&buffer[t_nome+t_nome_origem+4], "%[^\"]%c %s %s", 
			paragem2, &aspas, custo, duracao);
		}
		/* a paragem2 nao tem aspas */
		else {
			sscanf(&buffer[t_nome+t_nome_origem+3], "%s %s %s", 
			paragem2, custo, duracao);
		}
	}

    c = encontraCarreira(c_root, nome);
	/* nao existe uma carreira com o nome indicado */
	if (c == NULL) {
		printf("%s: no such line.\n", nome);
		return;
	}

	/* nao existe uma paragem com o nome indicado, origem */
	if (encontraParagem(p_root, paragem1) == NULL) {
		printf("%s: no such stop.\n", paragem1);
		return;
	}

	/* nao existe uma paragem com o nome indicado, destino */
	if (encontraParagem(p_root, paragem2) == NULL) {
		printf("%s: no such stop.\n", paragem2);
		return;
	}

	if (c->origem.nome != NULL) {
		/* no caso das paragens da ligacao, origem ou destino, 
		nao corresponderem a um dos extremos da carreira */
		if ((strcmp(c->origem.nome,paragem1) != 0) && 
		(strcmp(c->origem.nome,paragem2) != 0) && 
		(strcmp(c->destino.nome,paragem1) != 0) && 
		(strcmp(c->destino.nome,paragem2) != 0)) {
			printf("link cannot be associated with bus line.\n");
			return;
		}
	}

	/* a paragem origem nao corresponde a um dos extremos da carreira */
	if ((encontraParagensNaCarreira(paragem1, c) == 1) && 
	(strcmp(c->origem.nome,paragem1) == 0) && (c->numParagens > 1)) {
		printf("link cannot be associated with bus line.\n");
		return;
	}

	/* a paragem destino nao corresponde a um dos extremos da carreira */
	if ((encontraParagensNaCarreira(paragem2, c) == 1) && 
	(strcmp(c->destino.nome,paragem2) == 0) && (c->numParagens > 1)) {
		printf("link cannot be associated with bus line.\n");
		return;
	}

	/* o custo ou duracao sao valores negativos */
	if (atof(custo) < 0 || atof(duracao) < 0) {
		printf("negative cost or duration.\n");
		return;
	}

	/* adiciona-se a ligacao */
	else { 
		/* paragem1 existe e paragem2 nao, no percurso da carreira */
		if ((encontraParagensNaCarreira(paragem1, c) == 1) &&
		(encontraParagensNaCarreira(paragem2, c) == 0)) { 
			c->destino = *encontraParagem(p_root, paragem2);
			adicionaNaCarreira(c, encontraParagem(p_root, paragem2));
		}

		/* paragem2 existe e paragem1 nao, no percurso da carreira */
		else if ((encontraParagensNaCarreira(paragem1, c) == 0) 
		&& (encontraParagensNaCarreira(paragem2, c) == 1)) {
			c->origem = *encontraParagem(p_root, paragem1);
			insereParagemNoInicio(c, encontraParagem(p_root, paragem1));
		}

		/* paragem1 e paragem2 existem no percurso da carreira */
		else if ((encontraParagensNaCarreira(paragem1, c) == 1) &&
		(encontraParagensNaCarreira(paragem2, c) == 1)) {
			c->origem = *encontraParagem(p_root, paragem2);
			c->numParagens += 1;
			c->destino = *encontraParagem(p_root, paragem2);
		}

		/* nenhuma das paragens existe no percurso da carreira */
		else {
			c->origem = *encontraParagem(p_root, paragem1);
			adicionaNaCarreira(c, encontraParagem(p_root, paragem1));
            c->destino = *encontraParagem(p_root, paragem2);
			adicionaNaCarreira(c, encontraParagem(p_root, paragem2));
            ciclo = encontraParagem(p_root, paragem1);
            if (strcmp(paragem1, paragem2) == 0) {
                ciclo->num_carreiras--;
            }
		}

		custo1 = c->custo + atof(custo);
		c->custo = custo1;

		duracao1 = c->duracao + atof(duracao);
		c->duracao = duracao1;
	}
	
	return;
}

/****************************************************************************/
/* Funcoes Intersecoes */

/* Algoritmo de ordenacao BubbleSort. */ 
void bubbleSort(char** carreiras, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(carreiras[j], carreiras[j+1]) > 0) {
                char* temp = carreiras[j];
                carreiras[j] = carreiras[j+1];
                carreiras[j+1] = temp;
            }
        }
    }
}

/* Imprime as intersecoes entre carreiras, por cada paragem. */
void mostraIntersecao(Paragem* paragem, Carreira** c_root) {
    Carreira* carreira_atual = *c_root;
    int i;
    
    /* imprime as carreiras da paragem se tiver mais do que uma */
    if (paragem->num_carreiras > 1) {
        char** carreirasDaParagem = (char**) malloc(paragem->num_carreiras
        * sizeof(char*));
        int num_carreirasDaParagem = 0;

        while (carreira_atual != NULL) {
            if (encontraParagensNaCarreira(paragem->nome, 
            carreira_atual) == 1) {
                carreirasDaParagem[num_carreirasDaParagem] = 
                (char*) malloc(strlen(carreira_atual->nome) + 1);
                strcpy(carreirasDaParagem[num_carreirasDaParagem],
                 carreira_atual->nome);
                num_carreirasDaParagem++; 
            }
            carreira_atual = carreira_atual->prox;
        }

        if (num_carreirasDaParagem > 1) {
            bubbleSort(carreirasDaParagem, num_carreirasDaParagem);
            printf("%s %d: ", paragem->nome, num_carreirasDaParagem);
            for (i = 0; i < num_carreirasDaParagem; i++) {
                printf("%s", carreirasDaParagem[i]);
                if (i != num_carreirasDaParagem - 1) { 
                    printf(" ");
                }
                free(carreirasDaParagem[i]); 
            }
            printf("\n");
        }

        free(carreirasDaParagem);
    }
}

/* Funcao principal do comando i. */
void listaIntersecoesEntreCarreiras(Carreira** c_root, Paragem** p_root) {
	Paragem* paragem_atual = *p_root;
    /* imprime as carreiras associadas a cada paragem */
	while (paragem_atual != NULL) {
		mostraIntersecao(paragem_atual, c_root);
		paragem_atual = paragem_atual->prox;
	}
	return;
}

/****************************************************************************/

/* Funcao principal do comando r. */
void removeCarreira(Carreira** root) {
    char buffer[BUFFERSIZE], nome[BUFFERSIZE];
    Carreira* curr = *root;
    Carreira* prev = NULL;

    fgets(buffer, BUFFERSIZE, stdin);
    sscanf(buffer, "%s", nome);

    while (curr != NULL) {
        if (strcmp(curr->nome, nome) == 0) {
            if (prev == NULL) {
                *root = curr->prox;
            } else {
                prev->prox = curr->prox;
            }
            free(curr->nome);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->prox;
    }
    printf("%s: no such line.\n", nome);
}

/****************************************************************************/

/* Remove a ligacao da paragem associada a carreira */
void removeLigacao(Carreira* carreira, Paragem* paragem, Paragem** p_root) {
    Ligacao* anterior = NULL;
    Ligacao* atual = carreira->_ligacoesParagens;

    while (atual != NULL) {
        if (encontraParagem(p_root, atual->paragemLigacao.nome) == paragem) {
            if (anterior == NULL) {
                carreira->_ligacoesParagens = atual->prox;
                if (strcmp(carreira->origem.nome, paragem->nome) == 0) {
                    if (carreira->_ligacoesParagens != NULL) {
                        carreira->origem = 
                        carreira->_ligacoesParagens->paragemLigacao;
                    } 
                    else {
                        carreira->origem = carreira->destino;
                    }
                }
            }
            else {
                anterior->prox = atual->prox;
            }
            if (encontraParagem(p_root, carreira->destino.nome) == paragem) {
                Ligacao* l = carreira->_ligacoesParagens;
                while (l != NULL && l->prox != NULL) {
                    l = l->prox;
                }
                if (l != NULL) {
                    carreira->destino = l->paragemLigacao;
                } 
                else {
                    carreira->destino = 
                    carreira->_ligacoesParagens->paragemLigacao;
                }
            }
            atual = atual->prox;
            carreira->numParagens--;
            return; 
        } 
        else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}

/* Funcao principal do comando e. */
void eliminaParagem(Paragem** p_root, Carreira** c_root) {
    char buffer[BUFFERSIZE], nome[BUFFERSIZE];
    char aspas = '\0';
    Carreira* curr_carreira = *c_root;
    Paragem* paragem_apagada;
    Paragem* curr = *p_root;
    Paragem* prev = NULL;

    fgets(buffer, BUFFERSIZE, stdin);

    if (buffer[1] == '"') {
        sscanf(&buffer[2], "%[^\"]%c", nome, &aspas);
    } 
    else {
        sscanf(buffer, "%s", nome);
    }

    paragem_apagada = encontraParagem(p_root, nome);
    if (paragem_apagada == NULL) {
        printf("%s: no such stop.\n", nome);
        return;
    }

    while (curr_carreira != NULL) {
        removeLigacao(curr_carreira, paragem_apagada, p_root);
        curr_carreira = curr_carreira->prox;
    }

    while (curr != NULL) {
        if (curr == paragem_apagada) {
            if (prev == NULL) {
                *p_root = curr->prox;
            } else {
                prev->prox = curr->prox;
            }
            free(curr->nome);
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->prox;
    }
}

/****************************************************************************/

/* Funcao principal do comando a - apaga todos os dados */
void apagaTudo(Carreira** c_root, Paragem** p_root) {
    Carreira* curr = *c_root;
    /* apagar todas as ligacoes */
    while (curr != NULL) {
        Ligacao* ligacao = curr->_ligacoesParagens;
        while (ligacao != NULL) {
            Ligacao* next = ligacao->prox;
            free(ligacao);
            ligacao = next;
        }
        free(curr->nome);
        free(curr);
        curr = curr->prox;
    }
    /* apagar a lista de carreiras e paragens */
    *c_root = NULL;
    *p_root = NULL;
}

/****************************************************************************/

/* Funcao Principal */
int main() {
	int c;
    Paragem* p_root = NULL;
    Carreira* c_root = NULL;

	while ((c = getchar()) != EOF) {
		switch (c) {
		case 'q': return 0;
			break;
		case 'c': adicionaListaCarreira(&c_root);
			break;
        case 'p': adicionaListaParagens(&p_root);
			break;
		case 'l': adicionaLigacoes(&c_root, &p_root);
			break;
		case 'i': listaIntersecoesEntreCarreiras(&c_root, &p_root);
			break;
        case 'r': removeCarreira(&c_root);
			break;
        case 'e': eliminaParagem(&p_root, &c_root);
			break;
        case 'a': apagaTudo(&c_root, &p_root);
			break;
		}
	}
	return 0;
}

/****************************************************************************/
/* para ler carreiras com aspas - editar c r l */

char aspas = '\0';

if (buffer[1] == '"') {
    num_arg = sscanf(&buffer[2], "%[^\"]%c %s", nome, &aspas, 
    ehInverso);
} 
else {
    num_arg = sscanf(buffer, "%s %s", nome, ehInverso);
}

/****************************************************************************/
/* sem parametro inverso */
	if (num_arg == 1 || num_arg == 2) {

/****************************************************************************/
char aspas1 = '\0';

if (buffer[1] == '"') {
    sscanf(&buffer[2], "%[^\"]%c ", nome, &aspas1);
    t_nome = strlen(nome) + 2;
} 
else {
    sscanf(buffer, "%s", nome);
    t_nome = strlen(nome);
}
/****************************************************************************/
char aspas = '\0';

if (buffer[1] == '"') {
    sscanf(&buffer[2], "%[^\"]%c", nome, &aspas);
} 
else {
    sscanf(buffer, "%s", nome);
}
/****************************************************************************/
/****************************************************************************/

void inverteLista(No **head) {
    No *prev = NULL;
    No *current = *head;
    No *next = NULL;

    while (current != NULL) {
        next = current->prox;
        current->prox = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}

int contaElementos(No *head) {
    int count = 0;
    No *current = head;

    while (current != NULL) {
        count++;
        current = current->prox;
    }

    return count;
}

/****************************************************************************/

void ordenarPorCustoMin(Carreira* root) {
    Carreira *i, *j, *min, *s;
    if( root == NULL ) {
        return;
    }
    for (i = root; i->prox != NULL; i = i->prox) {
        min = i;
        for (j = i->prox; j != NULL; j = j->prox) {
            if (j->custo < min->custo) {
                min = j;
            }
        }
        if (min != i) {
            Carreira temp = *min;
            min->nome = i->nome;
            min->origem = i->origem;
            min->destino = i->destino;
            min->numParagens = i->numParagens;
            min->_ligacoesParagens = i->_ligacoesParagens;
            min->custo = i->custo;
            min->duracao = i->duracao;
            i->nome = temp.nome;
            i->origem = temp.origem;
            i->destino = temp.destino;
            i->numParagens = temp.numParagens;
            i->_ligacoesParagens = temp._ligacoesParagens;
            i->custo = temp.custo;
            i->duracao = temp.duracao;
        }
    }
    for (s = root; s != NULL; s = s->prox) {
        mostraCarreira(s);
    }
}

void ordenarPorCustoMax(Carreira* root) {
    Carreira *i, *j, *max, *s;
    if( root == NULL ) {
        return;
    }
    for (i = root; i->prox != NULL; i = i->prox) {
        max = i;
        for (j = i->prox; j != NULL; j = j->prox) {
            if (j->custo > max->custo) {
                max = j;
            }
        }
        if (max != i) {
            Carreira temp = *max;
            max->nome = i->nome;
            max->origem = i->origem;
            max->destino = i->destino;
            max->numParagens = i->numParagens;
            max->_ligacoesParagens = i->_ligacoesParagens;
            max->custo = i->custo;
            max->duracao = i->duracao;
            i->nome = temp.nome;
            i->origem = temp.origem;
            i->destino = temp.destino;
            i->numParagens = temp.numParagens;
            i->_ligacoesParagens = temp._ligacoesParagens;
            i->custo = temp.custo;
            i->duracao = temp.duracao;
        }
    }
    for (s = root; s != NULL; s = s->prox) {
        mostraCarreira(s);
    }
}

/****************************************************************************/

Carreira* carreiraMaxCusto(Carreira* root) {
    if (root == NULL) {
        return NULL;
    }

    Carreira* max = root;
    Carreira* cur = root->prox;

    while (cur != NULL) {
        if (cur->custo > max->custo) {
            max = cur;
        }
        cur = cur->prox;
    }

    return max;
}

/****************************************************************************/

/* iaed-23 - ist1103449 - project2 
 * Ficheiro: project2.h 
 * Autor: Miguel Teixeira 
 * Descricao: construcao de um sistema de gestao de carreiras de 
   transporte publico. 
*/

/* Definicao de constantes */
#define BUFFERSIZE 65536	/* tamanho de leitura */
#define MAX_NUM_DOUBLE 17	/* tamanho de leitura do double */
#define MAX_NUM_REALFLOAT 12	/* tamanho de leitura do float */

/* Estruturas de tipos de dados */
typedef struct Paragem {
    char *nome;
    double latitude, longitude;
    int num_carreiras;
    struct Paragem *prox;
} Paragem;

typedef struct Ligacao {
    Paragem paragemLigacao;
    struct Ligacao *prox;
} Ligacao;

typedef struct Carreira {
	char *nome;
    Paragem origem, destino;
	int numParagens;
	Ligacao* _ligacoesParagens;
	double custo, duracao;
    struct Carreira *prox;
} Carreira;

/****************************************************************************/

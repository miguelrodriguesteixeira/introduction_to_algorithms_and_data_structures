/*---------------------------------------------------------------------------------------------*/
/* Projeto 1 - IAED 2021/2022                                                                  */
/* Miguel Teixeira - ist1103449;                                                               */
/*---------------------------------------------------------------------------------------------*/

/* Bibliotecas */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Definicao de constantes */
#define Max_Voos 30000
#define Max_Aeroportos 40
#define Max_id 3
#define Max_pais 30
#define Max_cidade 50

/* Definicao de Estruturas de Dados */
struct Aeroporto{
   char id[Max_id + 1];
   char cidade[Max_cidade + 1];
   char pais[Max_pais + 1];
   char voo[Max_Voos + 1];
};
struct Aeroporto listAero[Max_Aeroportos];

struct Voo{
   char voocode[6+1];
   char idpart[Max_id + 1];
   char idcheg[Max_id + 1];
   char datpart[10+1];
   char horapart[5+1];
   char duration[5+1];
   char capacidade[3+1];
};
struct Voo listVoos[Max_Voos];

/* Prototipos */
int valid_id(char IDAeroporto[]);
int same_id(char IDAeroporto[]);
int valid_code(char CodVoo[]);
int sort_alpha(char listadeids[]);
int same_code(char CodVoo[], char dataPart[]);
int valid_capacity(char capacidade[]);
int valid_duration(char duration[]);
int valid_date(char dataPart[]);
int l_coisa(char listadeids[]);
void bubble(struct Aeroporto aux[], int r);
void sortdatahora(struct Voo aux[], int r, char IDAeroporto[]);
void sortdatahoracheg(struct Voo aux[], int r, char IDAeroporto[]);
int l_sozinho();
int same_id2(char IDAeroporto[]);

int numero_ae = 0;
int numero_voos = 0;
char* token;
char dataog[10+1] = "01-01-2022";

/* Codigo */
int main(){
   char letra[2], IDAeroporto[Max_id+1], pais[Max_pais+1], cidade[Max_cidade+1];
   char listadeids[160+1];
   char escolha[100000];
   char CodVoo[6+1], IDAeroportoPart[3+1], IDAeroportoCheg[3+1];
   char dataPart[10+1], horaPart[5+1], duration[5+1], capacidade[3+1];
   char datanova[10+1];

   while (1){
   fgets(escolha, 100000 - 1, stdin);
   switch(escolha[0]){

      case('q'): /* comando == 'q' */
      /* quando 'q' e introduzido o programa termina */
         exit(0);
         break;
      
      case('a'): /* comando == 'a' */
      /* adiciona um novo aeroporto ao sistema */
         sscanf(escolha, "%s %s %s %[^\n]", letra, IDAeroporto, pais, cidade);
         strcpy(listAero[numero_ae].id, IDAeroporto);
         strcpy(listAero[numero_ae].pais, pais);
         strcpy(listAero[numero_ae].cidade, cidade);

         if (valid_id(IDAeroporto) == 0){
            /* o identificador de aeroporto nao e uma string apenas com maiusculas */
            printf("invalid airport ID\n");
            continue;
         }
         
         else if (numero_ae == 40){
            /* no caso de o aeroporto, se criado, exceder o limite maximo de aeroportos 
            permitidos pelo sistema */
            printf("too many airports\n");
            continue;
         }

         else if (same_id(IDAeroporto) != -1){
            /* no caso de ja existir um aeroporto com o mesmo identificador */
            printf("duplicate airport\n");
            continue;
         }
         
         else {
            printf("airport %s\n", IDAeroporto);
            numero_ae++;
            continue;
         }
      
      case('l'): /* comando == 'l' */
      /* lista os aeroportos */
         sscanf(escolha,"%s %[^\n]", letra, listadeids);

         if (strlen(escolha) == 2){
            l_sozinho();
            continue;
         }
         else {
            l_coisa(listadeids);
            continue;
         }

      case('v'): /* comando == 'v' */
      /* adiciona um voo ou lista todos os voos */
         sscanf(escolha, "%s %s %s %s %s %s %s %s", 
         letra, CodVoo, IDAeroportoPart, IDAeroportoCheg, dataPart, 
         horaPart, duration, capacidade);
         
         strcpy(listVoos[numero_voos].voocode, CodVoo);
         strcpy(listVoos[numero_voos].idpart, IDAeroportoPart);
         strcpy(listVoos[numero_voos].idcheg, IDAeroportoCheg);
         strcpy(listVoos[numero_voos].datpart, dataPart);
         strcpy(listVoos[numero_voos].horapart, horaPart);
         strcpy(listVoos[numero_voos].duration, duration);
         strcpy(listVoos[numero_voos].capacidade, capacidade);


         if (strlen(escolha) == 2){
            int x;
            for (x = 0; x < numero_voos; x++) {
               printf("%s %s %s %s %s\n", listVoos[x].voocode, listVoos[x].idpart, 
               listVoos[x].idcheg, listVoos[x].datpart, listVoos[x].horapart);
            }
         }
         else if (valid_code(CodVoo) == 0){
            printf("invalid flight code\n");
         }
         else if (same_code(CodVoo, dataPart) == 0){
            printf("flight already exists\n");
         }
         else if (same_id(IDAeroportoPart) == -1){
            printf("%s: no such airport ID\n", IDAeroportoPart);
         }
         else if (same_id(IDAeroportoCheg) == -1){
            printf("%s: no such airport ID\n", IDAeroportoCheg);
         }
         else if (numero_voos == 30000){
            printf("too many flights\n");
         }
         else if (valid_date(dataPart) == 0){
            printf("invalid date\n");
         }
         else if (valid_duration(duration) == 0){
            printf("invalid duration\n");
         }
         else if (valid_capacity(capacidade) == 0){
            printf("invalid capacity\n");
         }
         else {
            numero_voos++;
         }
         continue;
      
      case('p'): /* comando == 'p' */
      /* lista os voos com partida de um aeroporto */
         sscanf(escolha,"%s %s", letra, IDAeroporto);

         if (same_id2(IDAeroporto) == -1){
            printf("%s: no such airport ID\n", IDAeroporto);
         }
         else {
            sortdatahora(listVoos, numero_voos, IDAeroporto);
         }
         continue;

      case('c'): /* comando == 'c' */
      /* lista os voos com chegada a um aeroporto */
         sscanf(escolha,"%s %s", letra, IDAeroporto);

         if (same_id2(IDAeroporto) == -1){
            printf("%s: no such airport ID\n", IDAeroporto);
         }
         else {
            sortdatahoracheg(listVoos, numero_voos, IDAeroporto);
         }
         continue;

      case('t'): /* comando == 't' */
      /* avança a data do sistema */
         sscanf(escolha,"%s %s", letra, datanova);
         if (valid_date(datanova) != 0){
            printf("%s\n", datanova);
            strcpy(dataog, datanova);
         }
         else {
            printf("invalid date\n");
         }
      continue;
  }
   return 0;
}
}


/* o identificador de aeroporto e uma string apenas com maiusculas */
int valid_id(char IDAeroporto[]){
   int contador = 0;
   while (contador < 3){
      if ('A' <= IDAeroporto[contador] && IDAeroporto[contador] <= 'Z'){
         contador++;
      }
      else {
         return 0;
      }
   }
   return 1;
}

/* ja existe um aeroporto com o mesmo identificador */
int same_id(char IDAeroporto[]){
   int i;
   for (i = 0; i < numero_ae; i++){
      if (strcmp(IDAeroporto,listAero[i].id) == 0){
         return i;
      }
   }
   return -1;
}

/* ja existe um id de voo (partida) com o mesmo identificador */
int same_id2(char IDAeroporto[]){
   int i;
   for (i = 0; i < numero_voos; i++){
      if (strcmp(IDAeroporto,listVoos[i].idpart) == 0){
         return i;
      }
   }
   return -1;
}

/* ja existe um voo com o mesmo codigo para o mesmo dia */
int same_code(char CodVoo[], char dataPart[]){
   int i;
   for (i = 0; i < numero_voos; i++){
      if (strcmp(CodVoo,listVoos[i].voocode) == 0){
         if (strcmp(dataPart,listVoos[i].datpart) == 0){
            return 0;
         }
      }
   }
   return 1;
}

/* o codigo do voo e uma string com duas maiusculas seguida por 
digitos (entre 1 a 4 digitos) */
int valid_code(char CodVoo[]){
   int contador = 0;
   int len;
   len = (strlen(CodVoo) - 2);
   while (contador < len){
      if (('A' <= CodVoo[0] && CodVoo[0] <= 'Z') && ('A' <= CodVoo[1] && CodVoo[1] <= 'Z') 
      && ('1' <= CodVoo[contador + 2] && CodVoo[contador + 2] <= '9') 
      && (2 < strlen(CodVoo)) && (strlen(CodVoo) < 7)){
         contador++;
      }
      else {
         return 0;
      }
   }
   return 1;
}

/* no caso de ser uma data no passado ou mais de um ano no futuro */
int valid_date(char dataPart[]){
   int monthsToDays[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
   int dia, mes, ano;
   int dia_og, mes_og, ano_og;
   int totaldias,totaldias_og;
 
   sscanf(dataPart,"%d-%d-%d", &dia, &mes, &ano);
   sscanf(dataog,"%d-%d-%d", &dia_og, &mes_og, &ano_og);

   totaldias_og = (dia_og) + monthsToDays[mes_og-1] + (ano_og*365);
   totaldias = (dia) + monthsToDays[mes-1] + (ano*365);

   if (((totaldias_og) <= totaldias) && 
   (totaldias <= (totaldias_og + 365))){
      return totaldias;
   }
   else {
      return 0;
   }
}

/* o voo tem duracao inferior a 12 horas */
int valid_duration(char duration[]){
   int totalmin;
   int hora, minutos;
   sscanf(duration,"%d:%d", &hora, &minutos);
   totalmin = (minutos) + (hora*24);
   if ((1 <= totalmin) && (totalmin <= 288)){
      return 1;
   }
   else {
      return 0;
   }
}

/* a capacidade do voo e um inteiro entre 10 e 100 (inclusive) */
int valid_capacity(char capacidade[]){
   int capa;
   sscanf(capacidade,"%d", &capa);
   if ((10 <= capa) && (capa <= 100)){
      return 1;
   }
   else {
      return 0;
   }
}

/* se o comando for invocado sem argumentos, todos os aeroportos sao listados */
int l_sozinho(){
   bubble(listAero, numero_ae);
   return 0;
}


/* se o comando for invocado com uma lista de identificadores de aeroportos, os 
aeroportos devem ser listados pela ordem dos respetivos identificadores no comando */
int l_coisa(char listadeids[]){
   char* token = strtok(listadeids," \n");
   int indice;
   while (token != NULL){
      indice = same_id(token);
         if (indice == -1){
            printf("%s: no such airport ID\n", token);
         }
         else {
            printf("%s %s %s %d\n", listAero[indice].id, listAero[indice].cidade, 
            listAero[indice].pais, numero_voos);
         }
   token = strtok(NULL, " \n");
   }
return 0;
}

/* os aeroportos sao listados por ordem alfabetica do codigo */
void bubble(struct Aeroporto aux[], int r){
   int i, j, f;
   struct Aeroporto temp;
   for (i = 0; i < r-1; i++){
      for (j = 0; j < r-i-1; j++){
         if (strcmp(aux[j].id, aux[j+1].id) > 0){
            temp = aux[j]; 
            aux[j] = aux[j+1];
            aux[j+1] = temp;
         }
      }
   }
   for (f = 0; f < r; f++){
      printf("%s %s %s %d\n", aux[f].id, aux[f].cidade, 
      aux[f].pais, numero_voos);
   }
}

/* os voos sao ordenados da data e hora (de partida) mais antigas para a mais recente */
void sortdatahora(struct Voo aux[], int r, char IDAeroporto[]){
   int i, j, f;
   struct Voo temp;
   int obx, obx2;

   for (f = 0; f < r; f++){
      if ((strcmp(IDAeroporto, listVoos[f].idcheg) == 0) || 
      (strcmp(IDAeroporto, listVoos[f].idpart) != 0)){
         continue;
      }
      else {
         for (i = 0; i < r-1; i++){
            for (j = 0; j < r-i-1; j++){
               obx = valid_date(aux[j].datpart);
               obx2 = valid_date(aux[j+1].datpart);

               if (strcmp(aux[j].datpart, aux[j+1].datpart) == 0){
                  if (strcmp(aux[j].horapart, aux[j+1].horapart) > 0){
                     temp = aux[j]; 
                     aux[j] = aux[j+1];
                     aux[j+1] = temp;
                  }
               }
               else {
                  if (obx  > obx2){
                     temp = aux[j]; 
                     aux[j] = aux[j+1];
                     aux[j+1] = temp;
                  }
               }
            }
         }
         printf("%s %s %s %s\n", listVoos[f].voocode, 
         listVoos[f].idcheg, listVoos[f].datpart, listVoos[f].horapart);
      }
   }
}

/* os voos sao ordenados da data e hora (de chegada) mais antigas para a mais recente */
void sortdatahoracheg(struct Voo aux[], int r, char IDAeroporto[]){
   int i, j, f;
   struct Voo temp;

   for (f = 0; f < r; f++){
      if ((strcmp(IDAeroporto, listVoos[f].idpart) == 0) || 
      (strcmp(IDAeroporto, listVoos[f].idcheg) != 0)){
         continue;
      }
      else {
         for (i = 0; i < r-1; i++){
            for (j = 0; j < r-i-1; j++){
               if (strcmp(aux[j].datpart, aux[j+1].datpart) == 0){
                  if (strcmp(aux[j].duration, aux[j+1].duration) > 0){
                     temp = aux[j]; 
                     aux[j] = aux[j+1];
                     aux[j+1] = temp;
                  }
               }
               else {
                  if (strcmp(aux[j].datpart, aux[j+1].datpart) > 0){
                     temp = aux[j]; 
                     aux[j] = aux[j+1];
                     aux[j+1] = temp;
                  }
               }
            }
         }
         printf("%s %s %s %s\n", listVoos[f].voocode, 
         listVoos[f].idpart, listVoos[f].datpart, listVoos[f].horapart);
      }
   }
}

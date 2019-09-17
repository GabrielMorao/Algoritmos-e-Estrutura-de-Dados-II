#ifndef REGISTROS_H_INCLUDED
#define REGISTROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

/*Definição da struct*/
typedef struct{
    char removido[1]; /*Nao sera utilizado neste trabalho, deve ser iniciado com -*/
    int encadeamento; /*Nao sera utilizado neste trabalho, dece ser iniciado com -1*/
    int nroInscricao; /*Nao aceita valor repetido ou nulo*/
    double nota;
    char data[10]; /*nao tem \0*/
    int tam1;
    char tagCampo4[1];
    char cidade[25];
    int tam2;
    char tagCampo5[1];
    char nomeEscola[23];
}Reg_de_Dados;

/*Cabeçalhos das funções*/
char* strtoke(char *str, const char *s);
void LeArquivo(Reg_de_Dados conteudo, Reg_de_Cabecalho new_cab[], FILE *arq1, FILE *arq2);
void LerBin (FILE *arq2, Reg_de_Dados *new_data, Reg_de_Cabecalho *le_cab);
void Procura_Campo(FILE *arq2, Reg_de_Dados *ler_campo);
void LerRRN(FILE *arq2, Reg_de_Dados *ler_rrn);

#endif // REGISTROS_H_INCLUDED


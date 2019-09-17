#ifndef REGISTROS_H_INCLUDED
#define REGISTROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

/*Definição da struct*/
typedef struct{
    char removido;
    int encadeamento;
    int nroInscricao; /*Não aceita valor repetido ou nulo*/
    double nota;
    char data[10]; /*Não tem \0*/
    int tam1;
    char tagCampo4;
    char cidade[25];
    int tam2;
    char tagCampo5;
    char nomeEscola[25];
}Reg_de_Dados;

/*Cabeçalhos das funções*/
void LeArquivo(Reg_de_Dados conteudo, Reg_de_Cabecalho new_cab, FILE *arq1, FILE *arq2);
void LerBin (FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *le_cab);
void Procura_Campo(FILE *arq2);
void LerRRN(FILE *arq2, Reg_de_Dados *ler_rrn);
void Remover_reg(FILE *arq2, Reg_de_Dados *ler_campo);
void Add_reg(FILE *arq2, Reg_de_Dados *ler_campo);
void Atualiza_reg(FILE *arq2, Reg_de_Dados *ler_campo);
void Ordena_reg(FILE *arq1, FILE *arq2, Reg_de_Cabecalho new_cab);
void Merging_reg(FILE *arq1, FILE *arq2, FILE *arq3,Reg_de_Cabecalho new_cab);
void Matching_reg(FILE *arq1, FILE *arq2, FILE *arq3,Reg_de_Cabecalho new_cab);

#endif // REGISTROS_H_INCLUDED


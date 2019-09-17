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
    int nroInscricao; /*Nao aceita valor repetido ou nulo*/
    double nota;
    char data[10]; /*nao tem \0*/
    int tam1;
    char tagCampo4;
    char cidade[50];
    int tam2;
    char tagCampo5;
    char nomeEscola[50];
}Reg_de_Dados;

/*Cabeçalhos das funções*/
char* strtoke(char *str, const char *s);
void LeArquivo(Reg_de_Dados conteudo, Reg_de_Cabecalho new_cab[], FILE *arq1, FILE *arq2);
void LerBin (FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *le_cab);
void Procura_Campo(FILE *arq2, Reg_de_Dados *ler_campo);
void LerRRN(FILE *arq2, Reg_de_Dados *ler_rrn);
void Remover_reg(FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *set_status, int n);
void Add_reg(FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *set_status, int n);
void Atualiza_reg(FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *set_status, int n);
void binarioNaTela1(FILE *ponteiroArquivoBinario);
void scan_quote_string(char *str);

#endif // REGISTROS_H_INCLUDED

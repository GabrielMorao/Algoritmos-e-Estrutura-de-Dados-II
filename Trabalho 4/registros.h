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

typedef struct{
    char chaveBusca[28];
    int RRN;
}Registro_de_Indice;


/*Cabeçalhos das funções*/
void LeArquivo(Reg_de_Dados conteudo, Reg_de_Cabecalho new_cab, FILE *arq1, FILE *arq2);
void LerBin (FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *le_cab);
void Procura_Campo(FILE *arq2, char opcao_campo[], char valor_campo[], int *num_pdisc);
void LerRRN(FILE *arq2, Reg_de_Dados *ler_rrn);
void Remover_reg(FILE *arq2, Reg_de_Dados *ler_campo, int *guarda_rrn);
void Add_reg(FILE *arq2, Reg_de_Dados *ler_campo, Registro_de_Indice pega_campo[]);
void Atualiza_reg(FILE *arq2, Reg_de_Dados *ler_campo);
void Ordena_reg(FILE *arq1, FILE *arq2, Reg_de_Cabecalho new_cab);
void Merging_reg(FILE *arq1, FILE *arq2, FILE *arq3,Reg_de_Cabecalho new_cab);
void Matching_reg(FILE *arq1, FILE *arq2, FILE *arq3,Reg_de_Cabecalho new_cab);
void ind_secfl(FILE *arq1, FILE *arq2, Cabecalho_de_Indice cab_ind);
void busca_indice(FILE *arq1, FILE *arq2, char opcao_campo[], char escola[], int *num_pdisc, int *num_pcab);
void remove_indice(FILE *arq1, FILE *arq2, int n, char *nome_arq2, Cabecalho_de_Indice cab_ind);
void insere_indice(FILE *arq1, FILE *arq2, int n);
void recupera_estat(FILE *arq1, FILE *arq2);

#endif // REGISTROS_H_INCLUDED


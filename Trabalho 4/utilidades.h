#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"
#include "registros.h"

/*Cabeçalhos das funções*/
char* strtoke(char *str, const char *s);
void escreve_cab(Reg_de_Cabecalho new_cab, FILE *arq2);
void escreve_cabind(Cabecalho_de_Indice cab_ind, FILE *arquivo);
void reseta_campos(Reg_de_Dados *res_camp);
void reseta_campindice(Registro_de_Indice *res_camp);
void binarioNaTela1(FILE *ponteiroArquivoBinario);
void scan_quote_string(char *str);
void quick_sort(int *a, int lo, int hi);
void troca(int a[], int i, int j);
void escreve_registro(FILE *arquivo, Reg_de_Dados escreve_reg);
void escreve_indice(FILE *arquivo, Registro_de_Indice reg_ind2[], int tam_nome, int i);
void le_registro(FILE *arquivo, Reg_de_Dados *ler_reg);
void le_regindice(FILE *arquivo, Registro_de_Indice *ler_reg);
void imprime_reg(Reg_de_Dados ler_reg);
void selecsortchar(Registro_de_Indice reg_ind2[], int max_reg2);
void busca_binaria(FILE *arq2, char *escola, Registro_de_Indice *reg_ind, int *salva_reg, int max_reg, int *n_reg);
#endif // UTILIDADES_H_INCLUDED

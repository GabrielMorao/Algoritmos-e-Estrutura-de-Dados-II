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
void reseta_campos(Reg_de_Dados *res_camp);
void binarioNaTela1(FILE *ponteiroArquivoBinario);
void scan_quote_string(char *str);
void quick_sort(int *a, int lo, int hi);
void troca(int a[], int i, int j);
void escreve_registro(FILE *arquivo, Reg_de_Dados escreve_reg);
void le_registro(FILE *arquivo, Reg_de_Dados *ler_reg);
void imprime_reg(Reg_de_Dados ler_reg);
#endif // UTILIDADES_H_INCLUDED

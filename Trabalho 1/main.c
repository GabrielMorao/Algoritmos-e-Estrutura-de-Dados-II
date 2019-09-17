/*  Nome: Gabriel Muniz Morão NºUSP: 7236785  */

/*Cada página de disco deve ter tamanho fixo = 16.000 bytes*/

/* Bibliotecas Utilizdas */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"
#include "registros.h"

/*define tamanho da pagina como 16.000*/
#define TAMMAX 16000

/*programa principal*/
int main(int argc, char * argv[])
{
    char line[80]; /*char para pegar linha do arquivo csv*/
    int funcionalidade; /*int para receber a funcionalidade escolhida pelo usuario*/
    char nome_arq[50]; /*char para receber nome do arquivo que usuario quer utilizar*/
    Reg_de_Cabecalho new_cab[1600], le_cab; /*variaveis do tipo registro de cabeçalho*/
    Reg_de_Dados conteudo, new_data, ler_rrn, ler_campo; /*variaveis do tipo registro de dados*/
    FILE *arq1, *arq2; /*variaveis do tipo arquivo*/

    scanf("%d %s", &funcionalidade, nome_arq); /*pega nuemro da funcionalidade e o nome do arquivo requerido*/

    switch(funcionalidade){
        case(1):  /*Gerar arquivo binário com o arquivo de entrada, na tela.*/

            arq1 = fopen(nome_arq, "r"); /*abre o arquivo csv para leitura*/
            if(arq1==NULL){ /*testa se conseguiu abrir*/
                printf("Falha no carregamento do arquivo.");
                exit(0);
            }
            arq2 = fopen("arquivoTrab1si.bin", "wb"); /*abre arquivo dito para escrita binaria*/
            if(arq2==NULL){ /*testta se conseguiu gerar o arquivo*/
                printf("Falha na criação do arquivo.");
                exit(0);
            }

            fgets(line, sizeof(line), arq1); /*pega a primeira linha do arquivo*/
            cabecalho(new_cab); /*funcção para instanciar o registro de cabeçalho*/
            LeArquivo(conteudo, new_cab, arq1, arq2); /*le o arquivo 1 (csv) e grava as informações no arquivo 2 (binario)*/
        break;

       case (2): /*Recuperação dos dados*/
            arq2 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
            if(arq2==NULL){ /*testa se conseguiu abrir*/
                    printf("Registro inexistente");
                    exit(0);
            }
            LerBin (arq2, &new_data, &le_cab); /*le o arquivo binario e imprime as informações na tela*/
        break;

        case (3): /*Recuperação dos dados por critério de busca*/
            arq2 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
            if(arq2==NULL){ /*testa se conseguiu abrir*/
                    printf("Registro inexistente");
                    exit(0);
            }
            Procura_Campo(arq2, &ler_campo);
        break;

        case (4): /*Recuperação dos dados por critério de numero relativo de registro*/
             arq2 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Registro inexistente");
                exit(0);
             }
             LerRRN(arq2, &ler_rrn);

        break;
    }
	/*fim do programa*/
    return 0;
}

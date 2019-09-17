#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

/*Fun��o que seta as informa��es do cabe�alho*/
void cabecalho(Reg_de_Cabecalho new_cab[]){
            /*Aloca o cabe�alho e atribui os valores*/
            strcpy(new_cab->status, "0");

            new_cab->topoPilha = -1; /*N�o h� registros removidos*/

            strcpy(new_cab->tagCampo1, "1");

            strcpy(new_cab->desCampo1, "numero de inscricao do participante do ENEM");
            for(int i = 44; i<55; i++){
                new_cab->desCampo1[i] = '@';
            }

            strcpy(new_cab->tagCampo2, "2");

            strcpy(new_cab->desCampo2, "nota do participante do ENEM na prova de matematica");
            for(int i = 52; i<55; i++){
                new_cab->desCampo2[i] = '@';
            }

            strcpy(new_cab->tagCampo3, "3");

            strcpy(new_cab->desCampo3, "data");
            for(int i = 5; i<55; i++){
                new_cab->desCampo3[i] = '@';
            }

            strcpy(new_cab->tagCampo4, "4");

            strcpy(new_cab->desCampo4, "cidade na qual o participante do ENEM mora");
            for(int i = 43; i<55; i++){
                new_cab->desCampo4[i] = '@';
            }

            strcpy(new_cab->tagCampo5, "5");

            strcpy(new_cab->desCampo5, "nome da escola de ensino medio");
            for(int i = 31; i<55; i++){
                new_cab->desCampo5[i] = '@';
            }
}

/*Fun��o que le as informa��es do cabe�alho*/
void LeCabecalho(Reg_de_Cabecalho *new_cab, FILE *arq1){
    char line[80];
    /*Leitura da primeira linha do arquivo, o cabe�alho*/
            fgets(line, sizeof(line), arq1);
            /*Chama a fun��o que alloca e seta as informa��es do cabe�alho*/
            cabecalho(new_cab);
}

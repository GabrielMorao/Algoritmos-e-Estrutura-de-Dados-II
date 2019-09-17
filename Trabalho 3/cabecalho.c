#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

/*Função que seta as informações do cabeçalho*/
void cabecalho(Reg_de_Cabecalho *new_cab){
            /*Aloca o cabeçalho e atribui os valores*/
            new_cab->status = '1';

            new_cab->topoPilha = -1; /*Não há registros removidos*/

            new_cab->tagCampo1 = '1';

            strcpy(new_cab->desCampo1, "numero de inscricao do participante do ENEM");
            for(int i = 44; i<55; i++){
                new_cab->desCampo1[i] = '@';
            }

            new_cab->tagCampo2 = '2';

            strcpy(new_cab->desCampo2, "nota do participante do ENEM na prova de matematica");
            for(int i = 52; i<55; i++){
                new_cab->desCampo2[i] = '@';
            }

            new_cab->tagCampo3 = '3';

            strcpy(new_cab->desCampo3, "data");
            for(int i = 5; i<55; i++){
                new_cab->desCampo3[i] = '@';
            }

            new_cab->tagCampo4 = '4';

            strcpy(new_cab->desCampo4, "cidade na qual o participante do ENEM mora");
            for(int i = 43; i<55; i++){
                new_cab->desCampo4[i] = '@';
            }

            new_cab->tagCampo5 = '5';

            strcpy(new_cab->desCampo5, "nome da escola de ensino medio");
            for(int i = 31; i<55; i++){
                new_cab->desCampo5[i] = '@';
            }
}

#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED

/*Definição da struct*/
typedef struct{
    char status[1];
    int topoPilha;
    char tagCampo1[1];
    char desCampo1[55]; /*numero de inscricao do participante do ENEM*/
    char tagCampo2[1];
    char desCampo2[55]; /*nota do participante do ENEM na prova de matematica*/
    char tagCampo3[1];
    char desCampo3[55]; /*data*/
    char tagCampo4[1];
    char desCampo4[55]; /*cidade na qual o participante do ENEM mora*/
    char tagCampo5[1];
    char desCampo5[55]; /*nome da escola de ensino medio*/
}Reg_de_Cabecalho;

/*Cabeçalhos das funções*/
void cabecalho(Reg_de_Cabecalho new_cab[]);
void LeCabecalho(Reg_de_Cabecalho *new_cab, FILE *arq1);

#endif // CABECALHO_H_INCLUDED

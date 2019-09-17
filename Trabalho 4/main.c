/*
	Nome: Gabriel Muniz Mor�o Nro USP: 7236785
	*/

/*Cada página de disco deve ter tamanho fixo = 16.000 bytes*/

/* Bibliotecas Utilizdas */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "cabecalho.h"
#include "registros.h"
#include "utilidades.h"

/*define tamanho da pagina como 16.000*/
#define TAMMAX 16000

/*programa principal*/
int main(int argc, char * argv[])
{
    char line[80]; /*char para pegar linha do arquivo csv*/
    int num_vezes = 0, num_pagdisc = 0, num_pcab = 0; /*numero de interações a serem realizadas*/
    int funcionalidade, n, salva_rrn[100]; /*int para receber a funcionalidade escolhida pelo usuario e o número de vezes que a funcionalidade rodara, serve apenas para alguns casos*/
    char nome_arq[50], nome_arq2[50], nome_saida[50]; /*char para receber nome do arquivo que usuario quer utilizar*/
    char guarda_status, guarda_status2;
    char escola[23], opcao_campo[33], valor_campo[28];
    Reg_de_Cabecalho set_status, new_cab, le_cab; /*variaveis do tipo registro de cabeçalho*/
    Cabecalho_de_Indice cab_ind;/*variaveis do tipo cabeçalho de indice*/
    Reg_de_Dados conteudo, ler_rrn, ler_campo; /*variaveis do tipo registro de dados*/
    Registro_de_Indice pega_campo;
    FILE *arq1, *arq2, *arq3; /*variaveis do tipo arquivo*/

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
            cabecalho(&new_cab); /*funcção para instanciar o registro de cabeçalho*/
            LeArquivo(conteudo, new_cab, arq1, arq2); /*le o arquivo 1 (csv) e grava as informações no arquivo 2 (binario)*/
        break;

       case (2): /*Recuperação dos dados*/
            arq2 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
            if(arq2==NULL){ /*testa se conseguiu abrir*/
                    printf("Registro inexistente");
                    exit(0);
            }
            LerBin (arq2, &ler_campo, &le_cab); /*le o arquivo binario e imprime as informações na tela*/
        break;

        case (3): /*Recuperação dos dados por critério de busca*/
            arq2 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
            if(arq2==NULL){ /*testa se conseguiu abrir*/
                    printf("Registro inexistente");
                    exit(0);
            }
            scanf("%s", opcao_campo);
            getchar();
            scanf("%[^\n]s", valor_campo);

            Procura_Campo(arq2, opcao_campo, valor_campo, &num_pagdisc);
            printf("Número de páginas de disco acessadas: %d\n", num_pagdisc);
            rewind(arq2);
            /*Passa o status de cada arquivo para pois serão fechados*/
            cab_ind.status = '1';
            fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);
            /*fecha o arquivo*/
            fclose(arq2);
        break;

        case (4): /*Recuperação dos dados por critério de numero relativo de registro*/
             arq2 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Registro inexistente");
                exit(0);
             }
             LerRRN(arq2, &ler_rrn);;
        break;

        case (5): /*Remoção lógica de registros*/
            scanf("%d", &n);
             arq2 = fopen(nome_arq, "r+b"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Registro inexistente");
                exit(0);
             }
            fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
            guarda_status = set_status.status; /*Guarda o status na variável designada*/
            rewind(arq2); /*Retorna ao inicio do arquivo*/
            /*Seta o status do arquivo para 0 pois abriu e será utilizado*/
            set_status.status = '0';
            fwrite(&set_status.status, sizeof(set_status.status), 1, arq2);
             do{
                Remover_reg(arq2, &ler_campo, salva_rrn); /*Chamada da função que remove registros*/
                num_vezes++; /*incrementa variavel de quantas vezes a funcionalidade rodou*/
             }while(num_vezes < n);
            /*Volta arquivo para inicio para alterar o status novamente para 1, pois o arquivo será fechado*/
            rewind(arq2);
            /*Retorna o status do arquivo para 1, pois vai fechar*/
            set_status.status = '1';
            fwrite(&set_status.status, sizeof(set_status.status), 1, arq2);
            if(guarda_status == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                }
            else if(guarda_status == '1'){ /*Caso seja 1, o correto*/
                /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
                binarioNaTela1(arq2);
            }
            /*fecha o arquivo*/
            fclose(arq2);
            num_vezes = 0;
        break;

        case (6): /*Inserção de registros*/
             scanf("%d", &n);
             arq2 = fopen(nome_arq, "r+b"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Registro inexistente");
                exit(0);
             }
            fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
            guarda_status = set_status.status; /*Guarda o status na variável designada*/
            if(guarda_status == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                fclose(arq2);
                exit(0);
                }
            /*Seta o status do arquivo para 0 pois abriu e será utilizado*/
            set_status.status = '0';
            fwrite(&set_status.status, sizeof(set_status.status), 1, arq2);
            do{
                Add_reg(arq2, &ler_campo, &pega_campo); /*Chamada da função que insere registros*/
                num_vezes++; /*incrementa variavel de quantas vezes a funcionalidade rodou*/
            }while(num_vezes < n);
            /*Volta arquivo para inicio para alterar o status novamente para 1, pois o arquivo será fechado*/
            rewind(arq2);
            set_status.status = '1';
            fwrite(&set_status.status, sizeof(set_status.status), 1, arq2);
            /*Imprime o binário na tela*/
            //binarioNaTela1(arq2);

            /*fecha o arquivo*/
            fclose(arq2);
            num_vezes = 0;
        break;

        case (7): /*Atualização de registro*/
             scanf("%d", &n);
             arq2 = fopen(nome_arq, "r+b"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Registro inexistente");
                exit(0);
             }
            /*Seta o status do arquivo para 0 pois abriu e será utilizado*/
            set_status.status = '0';
            fwrite(&set_status.status, sizeof(set_status.status), 1, arq2);
            do{
                Atualiza_reg(arq2, &ler_campo); /*Chamada da função que atualiza registros*/
                num_vezes++; /*incrementa variavel de quantas vezes a funcionalidade rodou*/
            }while(num_vezes < n);
            /*Volta arquivo para inicio para alterar o status novamente para 1, pois o arquivo será fechado*/
            rewind(arq2);
            set_status.status = '1';
            fwrite(&set_status.status, sizeof(set_status.status), 1, arq2);
            /*Imprime o binário na tela*/
            binarioNaTela1(arq2);

            /*fecha o arquivo*/
            fclose(arq2);
            num_vezes = 0;
        break;

        case (8): /*Ordenação de registro*/
             scanf("%s", nome_saida);

             arq1 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
             if(arq1==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq2 = fopen(nome_saida, "w+b"); /*abre arquivo binario para escrita*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
            fread(&set_status.status, sizeof(char), 1, arq1); /*Ler o status do arquivo*/
            guarda_status = set_status.status; /*Guarda o status na variável designada*/
            rewind(arq1); /*Retorna ao inicio do arquivo*/
            cabecalho(&new_cab); /*funcção para instanciar o registro de cabeçalho*/
            Ordena_reg(arq1, arq2, new_cab); /*Chamada da função que atualiza registros*/
               /*Retorna os 3 arquivos para o inicio*/
             rewind(arq1);
             rewind(arq2);
             /*Passa o status de cada arquivo para pois serão fechados*/
             new_cab.status = '1';
             fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq1);
             fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq2);
             if(guarda_status == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                fclose(arq1);
                fclose(arq2);
                exit(0);
                }
             else if(guarda_status == '1'){ /*Caso seja 1, o correto*/
                /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
                binarioNaTela1(arq2);
            }
             /*Fecha os arquivos*/
             fclose(arq1);
             fclose(arq2);

        break;

        case (9): /*Merging dos registros*/
             scanf("%s %s", nome_arq2, nome_saida);
             arq1 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
             if(arq1==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq2 = fopen(nome_arq2, "rb"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq3 = fopen(nome_saida, "w+b"); /*abre arquivo binario para escrita*/
             if(arq3==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             fread(&set_status.status, sizeof(char), 1, arq1); /*Ler o status do arquivo*/
             guarda_status = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq1); /*Retorna ao inicio do arquivo*/
             fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
             guarda_status2 = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq2); /*Retorna ao inicio do arquivo*/

             cabecalho(&new_cab); /*funcção para instanciar o registro de cabeçalho*/
             Merging_reg(arq1, arq2, arq3, new_cab); /*Chamada da função que faz merging dos registros*/
             /*Retorna os 3 arquivos para o inicio*/
             rewind(arq1);
             rewind(arq2);
             rewind(arq3);
             /*Passa o status de cada arquivo para pois serão fechados*/
             new_cab.status = '1';
             fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq1);
             fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq2);
             fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq3);
             if(guarda_status == '0' || guarda_status2 == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                fclose(arq1);
                fclose(arq2);
                fclose(arq3);
                exit(0);
                }
             else if(guarda_status == '1' && guarda_status2 == '1'){ /*Caso seja 1, o correto*/
                /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
                binarioNaTela1(arq3);
            }
             /*Fecha os arquivos*/
             fclose(arq1);
             fclose(arq2);
             fclose(arq3);
        break;

        case (10): /*Matching dos registros*/
             scanf("%s %s", nome_arq2, nome_saida);
             arq1 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
             if(arq1==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq2 = fopen(nome_arq2, "rb"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq3 = fopen(nome_saida, "w+b"); /*abre arquivo binario para escrita*/
             if(arq3==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             fread(&set_status.status, sizeof(char), 1, arq1); /*Ler o status do arquivo*/
             guarda_status = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq1); /*Retorna ao inicio do arquivo*/
             fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
             guarda_status2 = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq2); /*Retorna ao inicio do arquivo*/

             cabecalho(&new_cab); /*funcção para instanciar o registro de cabeçalho*/
             Matching_reg(arq1, arq2, arq3, new_cab); /*Chamada da função que faz matching dos registros*/
             /*Retorna os 3 arquivos para o inicio*/
             rewind(arq1);
             rewind(arq2);
             rewind(arq3);
             /*Passa o status de cada arquivo para pois serão fechados*/
             new_cab.status = '1';
             fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq1);
             fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq2);
             fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq3);
             if(guarda_status == '0' || guarda_status2 == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                fclose(arq1);
                fclose(arq2);
                fclose(arq3);
                exit(0);
             }
             else if(guarda_status == '1' && guarda_status2 == '1'){ /*Caso seja 1, o correto*/
                /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
                binarioNaTela1(arq3);
            }
             /*Fecha os arquivos*/
             fclose(arq1);
             fclose(arq2);
             fclose(arq3);
        break;

         case (11): /*Cria arquivo de indices*/
             scanf("%s", nome_arq2);
             arq1 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
             if(arq1==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq2 = fopen(nome_arq2, "w+b"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo2.");
                exit(0);
             }
             fread(&set_status.status, sizeof(char), 1, arq1); /*Ler o status do arquivo*/
             guarda_status = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq1); /*Retorna ao inicio do arquivo*/
             fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
             guarda_status2 = set_status.status; /*Guarda o status na variável designada*/
             if(guarda_status == '0' || guarda_status2 == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                fclose(arq1);
                fclose(arq2);
                exit(0);
            }

             rewind(arq2); /*Retorna ao inicio do arquivo*/
             cabecalho_indice(&cab_ind); /*funcção para instanciar o registro de cabeçalho*/
             ind_secfl(arq1, arq2, cab_ind); /*Chamada da função que faz matching dos registros*/

             /*Retorna os 3 arquivos para o inicio*/
             rewind(arq1);
             rewind(arq2);
             /*Passa o status de cada arquivo para pois serão fechados*/
             cab_ind.status = '1';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);

             /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
             binarioNaTela1(arq2);
             /*Fecha os arquivos*/
             fclose(arq1);
             fclose(arq2);
        break;

        case (12): /*busca no arquivo de indices*/
             scanf("%s %s", nome_arq2, opcao_campo);
            // printf("%s\n", opcao_campo);
             arq1 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
             if(arq1==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq2 = fopen(nome_arq2, "rb"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo2.");
                exit(0);
             }
             fread(&set_status.status, sizeof(char), 1, arq1); /*Ler o status do arquivo*/
             guarda_status = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq1); /*Retorna ao inicio do arquivo*/
             fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
             guarda_status2 = set_status.status; /*Guarda o status na variável designada*/
             if(guarda_status == '0' || guarda_status2 == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                fclose(arq1);
                fclose(arq2);
                exit(0);
            }

             rewind(arq2); /*Retorna ao inicio do arquivo*/
            // scanf("%s", opcao_campo);
             if(strcmp(opcao_campo, "nomeEscola") == 0){
               getchar();
               // scanf("%[^\n]s", valor_campo);
               scan_quote_string(valor_campo);
            }
             /*Escreve 0 nos status pois vai usar os arquivos*/
             cab_ind.status = '0';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);

             busca_indice(arq1, arq2, opcao_campo, valor_campo, &num_pagdisc, &num_pcab); /*Chamada da função que busca registros*/
             /*Retorna os 3 arquivos para o inicio*/
             rewind(arq1);
             rewind(arq2);
             /*Passa o status de cada arquivo para pois serão fechados*/
             cab_ind.status = '1';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);
             /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
             printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", num_pcab);
             printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", num_pagdisc);
             /*Fecha os arquivos*/
             fclose(arq1);
             fclose(arq2);
        break;

        case (13): /*Remoção lógica e física*/
             scanf("%s %d", nome_arq2, &n);
             arq1 = fopen(nome_arq, "r+b"); /*abre arquivo binario para leitura*/
             if(arq1==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo1.");
                exit(0);
             }
             arq2 = fopen(nome_arq2, "rb"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo2.");
                exit(0);
             }
             fread(&set_status.status, sizeof(char), 1, arq1); /*Ler o status do arquivo*/
             guarda_status = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq1); /*Retorna ao inicio do arquivo*/
             fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
             guarda_status2 = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq2); /*Retorna ao inicio do arquivo*/
             if(guarda_status == '0' || guarda_status2 == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                fclose(arq1);
                fclose(arq2);
                exit(0);
                }
             /*Escreve status 0 nos arquivos pois vai usar*/
             cab_ind.status = '0';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);
             /*Instancia um cabeçalho de indice*/
             cabecalho_indice(&cab_ind);

             remove_indice(arq1, arq2, n, nome_arq2, cab_ind); /*Chamada da função que faz matching dos registros*/
             /*Retorna os 3 arquivos para o inicio*/
             rewind(arq1);
             rewind(arq2);
             arq2 = fopen(nome_arq2, "r+b"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo2.");
                exit(0);
             }
             /*Passa o status de cada arquivo para pois serão fechados*/
             cab_ind.status = '1';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);

             /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
             binarioNaTela1(arq2);
             /*Fecha os arquivos*/
             fclose(arq1);
             fclose(arq2);
        break;

        case (14): /*Inserção*/
             scanf("%s %d", nome_arq2, &n);
             arq1 = fopen(nome_arq, "r+b"); /*abre arquivo binario para leitura*/
             if(arq1==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq2 = fopen(nome_arq2, "r+b"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo2.");
                exit(0);
             }

             fread(&set_status.status, sizeof(char), 1, arq1); /*Ler o status do arquivo*/
             guarda_status = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq1); /*Retorna ao inicio do arquivo*/
             fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
             guarda_status2 = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq2); /*Retorna ao inicio do arquivo*/
             if(guarda_status == '0' || guarda_status2 == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                fclose(arq1);
                fclose(arq2);
                exit(0);
                }
             cab_ind.status = '0';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);

             insere_indice(arq1, arq2, n); /*Chamada da função que insere registros*/
             /*Retorna os 2 arquivos para o inicio*/
             rewind(arq1);
             rewind(arq2);
             /*Passa o status de cada arquivo para pois serão fechados*/
             cab_ind.status = '1';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);
             /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
             binarioNaTela1(arq2);
             /*Fecha os arquivos*/
             fclose(arq1);
             fclose(arq2);
        break;

        case (15): /*Análise estatistica*/
             scanf("%s", nome_arq2);
             arq1 = fopen(nome_arq, "rb"); /*abre arquivo binario para leitura*/
             if(arq1==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo.");
                exit(0);
             }
             arq2 = fopen(nome_arq2, "rb"); /*abre arquivo binario para leitura*/
             if(arq2==NULL){  /*testa se conseguiu abrir*/
                printf("Falha no processamento do arquivo2.");
                exit(0);
             }
             fread(&set_status.status, sizeof(char), 1, arq1); /*Ler o status do arquivo*/
             guarda_status = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq1); /*Retorna ao inicio do arquivo*/
             fread(&set_status.status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
             guarda_status2 = set_status.status; /*Guarda o status na variável designada*/
             rewind(arq2); /*Retorna ao inicio do arquivo*/
             if(guarda_status == '0' || guarda_status2 == '0'){
                printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
                break;
             }
             cab_ind.status = '0';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);

             recupera_estat(arq1, arq2); /*Chamada da função que faz recupera os registros*/
             /*Retorna os 3 arquivos para o inicio*/
             rewind(arq1);
             rewind(arq2);
             /*Passa o status de cada arquivo para pois serão fechados*/
             cab_ind.status = '1';
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq1);
             fwrite(&cab_ind.status, sizeof(cab_ind.status), 1, arq2);
             /*Fecha os arquivos*/
             fclose(arq1);
             fclose(arq2);
        break;
    }
	/*fim do programa*/
    return 0;
}

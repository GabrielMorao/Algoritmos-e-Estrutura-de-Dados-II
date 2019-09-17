/* Bibliotecas Utilizadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registros.h"
#include "utilidades.h"

///////////////////////////////////////////////////////  FUNCIONALIDADES DO TRABALHO 1 - CRIAÇÃO, IMPRESSÃO E BUSCA !! //////////////////////////////////////////////////////////////////////////

/*FuncÃ£o utilizada para a funcionalidade 1*/
void LeArquivo(Reg_de_Dados conteudo, Reg_de_Cabecalho new_cab, FILE *arq1, FILE *arq2){
    char *tmp;
    char fim_cab[1] = "@";
    char fim_stri[1] = "\0";
    char line[80], preenche_final[80];
    const char s[2] = ",";
    int cont_lin = 1;

            /* CabeÃ§alho se encontra na primeira pagina de disco, os demais registros da segunda em diante*/
            escreve_cab(new_cab, arq2);
            for (int j = 0; j<80; j++){
                preenche_final[j] = '@';
            }
			/*pega linha por linha do arquivo csv*/
            while (cont_lin <= 5000){

                fgets(line, sizeof(line), arq1);

                //strcpy(conteudo.removido,"-");
                conteudo.removido = '-';
                fwrite(&conteudo.removido, sizeof(char), 1, arq2);

                conteudo.encadeamento = -1;
                fwrite(&conteudo.encadeamento, sizeof(int), 1, arq2);

                tmp = strtoke(line, s);
                if(strcmp(tmp, "") != 0){
                    conteudo.nroInscricao = atoi(tmp); //atoi for int*/
                }
                else{
                    conteudo.nroInscricao = -1;
                }
                fwrite(&conteudo.nroInscricao, sizeof(int), 1, arq2);

                /*Pega a nota e usa atof para transformar em double*/
                tmp = strtoke(NULL, s);
                if(strcmp(tmp, "") != 0){
                conteudo.nota = atof(tmp); //atof for double
                }
                else{
                    conteudo.nota = -1;
                }
                fwrite(&conteudo.nota, sizeof(double), 1, arq2);

                /*pega a data e verifica se Ã© nula, caso sim, completa com @*/
                tmp = strtoke(NULL, s);
                if(strlen(tmp)){ /*se tamanho for diferente de 0, copia o char e passa pro arquivo*/
                    strcpy(conteudo.data,tmp);
                    fwrite(&conteudo.data, 10, 1, arq2);
                }
                else{ /*caso contrÃ¡rio, preenche um vetor de 10 posiÃ§Ãµes e passa pro arquivo */
                   strcpy(conteudo.data, "@@@@@@@@@@");
                    conteudo.data[0] = '\0';
                     fwrite(conteudo.data, sizeof(char), 10, arq2);
                }

                /*Pega e aloca a cidade, o tamanho da string e a tag do campo*/
                tmp = strtoke(NULL, s);
                conteudo.tam1 = strlen(tmp);
                //strcpy(conteudo.tagCampo4, "4");
                conteudo.tagCampo4 = '4';
                if(conteudo.tam1 != 0){
                    conteudo.tam1 =  conteudo.tam1 + 2;
                    strcpy(conteudo.cidade,tmp);
                }
                else{
                    strcpy(conteudo.cidade, "@@@@@@@@@@");
                    conteudo.cidade[0] = '\0';
                }

                /*Pega e aloca o nome da Escola, o tamanho da string e a tag do campo*/
                    tmp = strtoke(NULL, s);
                    conteudo.tam2 = strlen(tmp) + 1;
                    //printf("%d\n", conteudo.tam2);
                    //strcpy(conteudo.tagCampo5, "5");
                    conteudo.tagCampo5 = '5';
                    if(conteudo.tam2 != 2){
                        strcpy(conteudo.nomeEscola,tmp);
                        conteudo.nomeEscola[conteudo.tam2-1] = '\0';
                    }
                    else{
                        strcpy(conteudo.nomeEscola, "@@@@@@@@@@");
                        conteudo.nomeEscola[0] = '\0';
                    }

                    /*Verifica se teremos nomeEscola e/ou cidade impressos e completa o restante do registro com @*/
                    if(conteudo.tam2 ==2 && conteudo.tam1 ==0){
                        fwrite(&preenche_final, sizeof(char), 53, arq2);
                    }
                    else if(conteudo.tam2 !=2 && conteudo.tam1 ==0){
                        fwrite(&conteudo.tam2, sizeof(int), 1, arq2);
                        fwrite(&conteudo.tagCampo5, sizeof(char), 1, arq2);
                        fwrite(&conteudo.nomeEscola, sizeof(char), conteudo.tam2-2, arq2);
                        fwrite(&fim_stri, sizeof(char), 1, arq2);
                        fwrite(&preenche_final, sizeof(char), 49 - conteudo.tam2,arq2);
                    }
                    else if(conteudo.tam2 ==2 && conteudo.tam1 != 0){
                        fwrite(&conteudo.tam1, sizeof(int), 1, arq2);
                        fwrite(&conteudo.tagCampo4, sizeof(char), 1, arq2);
                        fwrite(conteudo.cidade, sizeof(char), conteudo.tam1-1, arq2);
                        fwrite(&preenche_final, sizeof(char), 49 - conteudo.tam1, arq2);
                    }
                    else{
                        fwrite(&conteudo.tam1, sizeof(int), 1, arq2);
                        fwrite(&conteudo.tagCampo4, sizeof(char), 1, arq2);
                        fwrite(conteudo.cidade, sizeof(char), conteudo.tam1-1, arq2);
                        fwrite(&conteudo.tam2, sizeof(int), 1, arq2);
                        fwrite(&conteudo.tagCampo5, sizeof(char), 1, arq2);
                        fwrite(conteudo.nomeEscola, sizeof(char), conteudo.tam2-2, arq2);
                        fwrite(&fim_stri, sizeof(char), 1, arq2);
                        fwrite(&preenche_final, sizeof(char), 42-(conteudo.tam1-2) - (conteudo.tam2-1),arq2);
                    }
                    /*Zerando as variaveis que receberÃ£o os campos*/
                   conteudo.nroInscricao = 0;
                   conteudo.nota = 0;
                   memset(conteudo.data, 0, strlen(conteudo.data));
                   conteudo.tam1 = 0;
                   conteudo.tagCampo4 = '0';
                   //memset(conteudo.tagCampo4, 0, strlen(conteudo.tagCampo4));
                   memset(conteudo.cidade, 0, 25);
                   conteudo.tam2 = 0;
                   //memset(conteudo.tagCampo5, 0, strlen(conteudo.tagCampo5));
                   conteudo.tagCampo5 = '0';
                   memset(conteudo.nomeEscola, 0, 23);
                   cont_lin++;
            }
            rewind(arq2);
            new_cab.status = '1';
            fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq2);
			/*Fecha os dois arquivos*/
            fclose(arq1);
            fclose(arq2);
            /*imprime em tela o nome do arquivo gerado*/
            printf("arquivoTrab1si.bin");
}

/*FuncÃ£o utilizada para a funcionalidade 2*/
void LerBin (FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *le_cab){
    int cont = 0, num_reg = 0;
    int num_pagdisc = 0;
    ler_campo->tam1 = 0;
    ler_campo->tam2 = 0;
    int pega_tag, pega_tag2, pega_tag3;
    int tam_arq, tam_pag; /*inteiro para o tamanho do arquivo*/
    int numero = 1;


    /*Encontra o tamanho total do arquivo acessado e utiliza rewind para "resetar' o ponteiro para o inicio do aruqivo novamente*/
    fseek(arq2, 0L, SEEK_END);
    tam_pag = ftell(arq2);
    tam_arq = (ftell(arq2)-16000)/80;
    rewind(arq2);

    /*Verifica o campo status do cabeÃ§alho do arquivo, um arquivo escrito deve possuir 1, caso esteja como 0, o arquivo apresenta erro*/
    fread(&le_cab->status, sizeof(le_cab->status), 1, arq2);
    num_pagdisc++;
        if(le_cab->status == '0'){
            printf("Falha no processamento do arquivo.");
            fclose(arq2);
            exit(0);
        }

    num_pagdisc++; /*Passou pela primeira pagina, a do registro de cabeÃ§alho*/

	/*passa registro a registro lendo a informaÃ§Ã£o, passando para um registro e imprimindo na tela, verificando se Ã© nulo ou nÃ£o*/
    do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*le todos os dados com o tamanho das variaveis e imprime na tela*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            if(ler_campo->removido != '*'){
                fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
                fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
                printf("%d", ler_campo->nroInscricao);
                fread(&ler_campo->nota, sizeof(double), 1, arq2);
                if(ler_campo->nota != -1){
                        printf(" %.1f", ler_campo->nota);
                        }
                fread(&pega_tag2, sizeof(int),1,arq2);
                fseek(arq2, -4, SEEK_CUR);
                 fread(&ler_campo->data,sizeof(char), 10, arq2);
                if(pega_tag2 != 1077952512){
                    printf(" %s", ler_campo->data);
                }
                fread(&pega_tag3, sizeof(int),1,arq2);
                fseek(arq2, -4, SEEK_CUR);
                if(pega_tag3 != 1077952576 && pega_tag3 != 1077952510){
                    fread(&ler_campo->tam1, sizeof(int), 1, arq2);
                    fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                    fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                    printf(" %d ", ler_campo->tam1-2);
                    printf("%s ", ler_campo->cidade);
                    getc(arq2);
                }
                fread(&pega_tag, sizeof(int),1,arq2);
                fseek(arq2, -4, SEEK_CUR);
                if(pega_tag != 1077952576 ){
                     fread(&ler_campo->tam2, sizeof(int), 1, arq2);
                     fread(&ler_campo->tagCampo5, sizeof(char),1, arq2);
                     fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2, arq2);
                     printf("%d ", ler_campo->tam2-2);
                     printf("%s", ler_campo->nomeEscola);
                }
                     printf("\n");
            }
                /*incrementa o contador para prÃ³ximo registro*/
                cont = cont + 80;
                /*incrementa o nÃºmero de registros*/
                num_reg++;
                numero++;
                /* Considerando numero total de bytes por pagina e o numero de bytes de cada registro, pode-se calcular quantos registros existem por pÃ¡gina e assim o nÃºmero de pÃ¡ginas*/
                if(num_reg > (16000/80)){
                        num_reg = 0;
                        num_pagdisc++;
                    }
                    /*Zera as variÃ¡veis que receberÃ£o os campos, para nÃ£o haver sobreposiÃ§Ã£o de informaÃ§Ãµes*/
                    ler_campo->nroInscricao = 0;
                    ler_campo->nota = 0;
                    memset(ler_campo->data, 0, strlen(ler_campo->data));
                    ler_campo->tam1 = 0;
                    ler_campo->tagCampo4 = '0';
                    memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                    ler_campo->nota = 0;
                    ler_campo->tam2 = 0;
                    ler_campo->tagCampo5 = '0';
                    memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
        }while(cont < (tam_pag-16000));
        printf("Número de páginas de disco acessadas: %d",num_pagdisc); /*imprime nÃºmero total de pÃ¡ginas acessadas*/
            /*reseta ponteiro para inicio do arquivo*/
            rewind(arq2);
            /*fecha o arquivo*/
            fclose(arq2);
}

/*FuncÃ£o utilizada para a funcionalidade 3 */
void Procura_Campo(FILE *arq2, char opcao_campo[], char valor_campo[], int *num_pdisc){
   // char opcao_campo[33]; /*String para recolher a opÃ§Ã£o de campo do usuario*/
    char proc_data[10], proc_cidade[27], proc_nomeEscola[33]; /* strings para recolher o valor dentro da opÃ§Ã£o anterior*/
    int cont = 0,num_reg = 0, proc_insc = 0, reg_encontrado = 0, contador = 0, num_pagdisc = 0; /*contadores utilizados*/
    int tam_arq, tam_pag; /*inteiro para o tamanho do arquivo*/
    double proc_nota; /*double para recolher o valor dentro da opÃ§Ã£o de campo*/
    int pega_tag, pega_tag2, pega_tag3;
    Reg_de_Dados pega_campo;

    /*Encontra o tamanho total do arquivo acessado e utiliza rewind para "resetar' o ponteiro para o inicio do aruqivo novamente*/
    fseek(arq2, 0L, SEEK_END);
    tam_pag = ftell(arq2);
    tam_arq = (ftell(arq2)-16000)/80;
    int max_rrn = tam_arq;
    rewind(arq2);
    reseta_campos(&pega_campo);
    /* Os if e else if abaixo representama  comparaÃ§Ã£o do campo de entrada do usuario com o nome de cada campo do arquivo*/
    /*verifica a opÃ§Ã£o nroInscriÃ§Ã£o*/
    if(strcmp(opcao_campo, "nroInscricao") == 0){
        proc_insc = atoi(valor_campo);
        num_pagdisc += 2;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            le_registro(arq2, &pega_campo);
           // printf("%d\n", pega_campo.nroInscricao);
             if(pega_campo.nroInscricao == proc_insc){
                imprime_reg(pega_campo);
                /*incrementa o nÃºmero de registros encontrados*/
                reg_encontrado++;
                /*se encontrou uma vez, sai do loop, pois nroInscriÃ§Ã£o Ã© um campo que nÃ£o aceita repetiÃ§Ãµes*/
                break;
             }
             reseta_campos(&pega_campo);
              //incrementa o contador para prÃ³ximo registro
            cont = cont + 80;
            contador++;
            if(num_reg >= (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(contador < max_rrn);
        *num_pdisc = num_pagdisc;
        contador = 0;
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
    }

    /*verifica a opÃ§Ã£o nota*/
    else if(strcmp(opcao_campo, "nota") == 0){
        proc_nota = atof(valor_campo);
        num_pagdisc = num_pagdisc +2;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            le_registro(arq2, &pega_campo);
            if(pega_campo.nota == proc_nota){
                    imprime_reg(pega_campo);
                /*incrementa o nÃºmero de registros encontrados*/
                reg_encontrado++;
            }
            reseta_campos(&pega_campo);
            contador++;
            /*incrementa o contador para prÃ³ximo registro*/
            cont+= 80;
            /*incrementa o nÃºmero de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(contador < max_rrn);
        *num_pdisc = num_pagdisc;
        contador = 0;
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
     }

    /*verifica a opÃ§Ã£o data*/
    else if(strcmp(opcao_campo, "data") == 0){
        strcpy(proc_data, valor_campo);
        num_pagdisc = num_pagdisc +2 ;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            le_registro(arq2, &pega_campo);
            if(strcmp(pega_campo.data, proc_data)==0){
                    imprime_reg(pega_campo);
                /*incrementa o nÃºmero de registros encontrados*/
                reg_encontrado++;
            }
            reseta_campos(&pega_campo);
            contador++;
            /*incrementa o contador para prÃ³ximo registro*/
            cont+= 80;
            /*incrementa o nÃºmero de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(contador < max_rrn);
        *num_pdisc = num_pagdisc;
        contador = 0;
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
    }
    /*verifica a opÃ§Ã£o cidade*/
    else if(strcmp(opcao_campo, "cidade") == 0){
        strcpy(proc_cidade, valor_campo);
        num_pagdisc = num_pagdisc +2 ;
         do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            le_registro(arq2, &pega_campo);
            if(strcmp(pega_campo.cidade, proc_cidade)==0){
                    imprime_reg(pega_campo);
                /*incrementa o nÃºmero de registros encontrados*/
                reg_encontrado++;
            }
            reseta_campos(&pega_campo);
            contador++;
            /*incrementa o contador para prÃ³ximo registro*/
            cont+= 80;
            /*incrementa o nÃºmero de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(contador < max_rrn);
        *num_pdisc = num_pagdisc;
        contador = 0;
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
    }
    /*verifica a opÃ§Ã£o NomeEscola*/
    else if(strcmp(opcao_campo, "nomeEscola") == 0){
        strcpy(proc_nomeEscola, valor_campo);
        num_pagdisc = num_pagdisc+2 ;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            le_registro(arq2, &pega_campo);
            if(strcmp(pega_campo.nomeEscola, proc_nomeEscola)==0){
                   // printf("%s\n", pega_campo.nomeEscola);
                    imprime_reg(pega_campo);
                /*incrementa o nÃºmero de registros encontrados*/
                reg_encontrado++;
            }
            reseta_campos(&pega_campo);
            contador++;
            /*incrementa o contador para prÃ³ximo registro*/
            cont+= 80;
            /*incrementa o nÃºmero de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(contador < max_rrn);
        *num_pdisc = num_pagdisc;
        contador = 0;
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
     }
}

/*FuncÃ£o utilizada para a funcionalidade 4 */
void LerRRN(FILE *arq2, Reg_de_Dados *ler_rrn){
    int rrn = 0, boset,tam_arq, num_pag = 0;

    scanf("%d", &rrn); /*pega o rrn que usuario deseja buscar*/
            boset = rrn * 80; /* 80 Ã© o tamanho fixo do registro*/
            fseek(arq2, 0L, SEEK_END);
            tam_arq = (ftell(arq2)-16000)/80;
            rewind(arq2);
            if(rrn > tam_arq){
                printf("Registro inexistente.");
            }
            else{
                fseek(arq2, 16000 + boset, SEEK_SET); /*seta ponteiro para a primeira linha do registro de dados desejada.*/
                num_pag++; /*Passou pela pagina de cabeÃ§alho*/

                /*le o arquivo e imprime na tela a linha (campo a campo) pedida pelo usuario*/
                fread(&ler_rrn->removido, sizeof(char), 1, arq2);
                fread(&ler_rrn->encadeamento, sizeof(int), 1, arq2);
                fread(&ler_rrn->nroInscricao, sizeof(int), 1, arq2);
                printf("%d ", ler_rrn->nroInscricao);
                fread(&ler_rrn->nota, sizeof(double), 1, arq2);
                if(ler_rrn->nota != -1){
                    printf("%.1f ", ler_rrn->nota);
                }

                fread(&ler_rrn->data,sizeof(char), 10, arq2);
                if(ler_rrn->data != NULL){
                    printf("%s ", ler_rrn->data);
                }

                fread(&ler_rrn->tam1, sizeof(int), 1, arq2);
                if(ler_rrn->tam1 != 0){
                    printf("%d ", ler_rrn->tam1-2);
                }
                fread(&ler_rrn->tagCampo4, sizeof(char), 1, arq2);
                fread(&ler_rrn->cidade, sizeof(char), ler_rrn->tam1-2, arq2);
                if(ler_rrn->cidade != NULL){
                    printf("%s ", ler_rrn->cidade);
                }
                getc(arq2);
                fread(&ler_rrn->tam2, sizeof(int), 1, arq2);
                fread(&ler_rrn->tagCampo5, sizeof(char),1, arq2);
                if(ler_rrn->tagCampo5 == '5'){
                    printf("%d ", ler_rrn->tam2-2);
                    fread(&ler_rrn->nomeEscola, sizeof(char), ler_rrn->tam2-2, arq2);
                    if(ler_rrn->nomeEscola != NULL){
                        printf("%s\n", ler_rrn->nomeEscola);
                    }
                }
                else{
                    printf("\n");
                }
                printf("oi");
                num_pag++;
                printf("Número de páginas de disco acessadas: %d",num_pag); /*imprime o nÃºmerdo de pÃ¡ginas acessadas*/
            }
            /*fecha o arquivo*/
            fclose(arq2);
}


//////////////////////////////////  FUNCIONALIDADES DO TRABALHO 2 - REMOÇÃO, INSERÇÃO e ATUALIZAÇÃO !! //////////////////////////////////////////////////////////////////////////////////////////

/*Funcionalidade para remover do arquivo os registros que usuário deseja através do nome e valor de campo*/
void Remover_reg(FILE *arq2, Reg_de_Dados *ler_campo, int guarda_rrn[]){
    int tam_arq, cont = 0, reg_encontrado = 0; /* variáveis que guardam tamanho do arquivo, contador para o fseek e quantas vezes foi encontrado um registro*/
    int tam_pag, salva_topo, val_insc; /*variáveis que guardam tamanho de uma página e o valor que esta no topoPilha do cabeçalho*/
    double val_nota;
    char opcao_campo[20], valor_campo[25], preenche_final[80], stt = '0'; /*Variáveis de char para guardar a opção de campo, o valor que tal campo deve ser, @ para preencher fim do registro e o status do arquivo*/
    char proc_removido = '*'; /*Variáveis de char para guardar char de reg removido, guardar o status atual do arquivo*/
    int num_vezes = 0, verifica_reg, conta_rrn = 0;/*numero de interaÃ§Ãµes a serem realizadas*/
    Reg_de_Cabecalho set_status;

    for (int j = 0; j<80; j++){
        preenche_final[j] = '@'; /*Preenche o vetor de char com @ para finalização dos registros*/
    }

    /*Descobr o tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
     tam_arq = ftell(arq2);
    tam_pag= (ftell(arq2)-16000)/80;
    rewind(arq2);
    /*Atribui 0 ao status */
        fseek(arq2, 0, SEEK_SET);
        fread(&set_status.status, sizeof(set_status.status), 1, arq2);
        fread(&set_status.topoPilha, sizeof(set_status.topoPilha), 1, arq2);
        salva_topo = (set_status.topoPilha);
        rewind(arq2);

    /*Inicia o processo de remoção*/
         getchar();
        scanf("%s", opcao_campo); /*pega a opção de campo que o usuário deseja buscar*/
        /*Caso o campo seja número de Inscrição*/
        if(strcmp(opcao_campo, "nroInscricao") == 0){
            scanf("%d", &val_insc);
            do{
                fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
                /*leitura e impressÃ£o de campos*/
                fread(&ler_campo->removido, sizeof(char), 1, arq2);
                if(ler_campo->removido != '*'){
                    fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
                    fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
                    /*verifica a se a entrada Ã© igual ao campo recolhido*/
                    if(ler_campo->nroInscricao == val_insc){
                        rewind(arq2);
                        fseek(arq2, 16000+cont, SEEK_SET);
                        verifica_reg = (ftell(arq2)-16000)/80; /*Guarda a posição do registro*/
                        guarda_rrn[conta_rrn] = verifica_reg;
                        fwrite(&proc_removido, sizeof(char), 1 , arq2); /*Atualiza o campo removido com * */
                        fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                        fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                        reg_encontrado++; /*incrementa o numero de registros encontrados*/
                        rewind(arq2);
                        fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                        fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                        salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
                        conta_rrn++;
                    }
                }
                cont += 80; /*Incrementa o contador erm 80 para ir para próxima linha*/
                ler_campo->nroInscricao = 0; /*zera o valor da variavel para evitar sobreposições erradas*/
            }while(reg_encontrado == 0 && cont < (tam_arq-16000)); /*se encontrou uma vez, sai do loop, pois nroInscrição não um campo que não aceita repetições*/
            /*Se saiu do loop, zera o contador e o numero de registros encontrados para próxima busca*/
            reg_encontrado = 0;
            cont = 0;
            conta_rrn = 0;
        }
        /*Caso o campo seja Nota*/
        else if(strcmp(opcao_campo, "nota") == 0){
                scanf("%lf", &val_nota);
                do{
                    double val_campo = atof(valor_campo);
                    fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
                    /*leitura e impressÃ£o de campos*/
                    fread(&ler_campo->removido, sizeof(char), 1, arq2);
                    if(ler_campo->removido != '*'){
                        fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
                        fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
                        fread(&ler_campo->nota, sizeof(double), 1, arq2);
                        /*verifica a se a entrada Ã© igual ao campo recolhido*/
                        if(ler_campo->nota == val_nota){
                            rewind(arq2);
                            fseek(arq2, 16000+cont, SEEK_SET);
                            verifica_reg = (ftell(arq2)-16000)/80; /*Guarda a posição do registro*/
                            guarda_rrn[conta_rrn] = verifica_reg;
                            fwrite(&proc_removido, sizeof(char), 1 , arq2); /*Atualiza o campo removido com * */
                            fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                            fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                            rewind(arq2);
                            fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                            fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                            salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
                            conta_rrn++;
                        }
                        /*zera o valor das variaveis para evitar sobreposições erradas*/
                        ler_campo->nroInscricao = 0;
                        ler_campo->nota = 0;
                    }
                    /*Incrementa o contador erm 80 para ir para próxima linha*/
                    cont += 80;
                }while(cont < (tam_arq-16000));
                /*Se saiu do loop, zera o contador para próxima busca*/
                cont = 0;
                conta_rrn = 0;
        }
        /*Caso o campo seja Data*/
        else if(strcmp(opcao_campo, "data") == 0){
                scan_quote_string(valor_campo); /*pega o valor de entrada do usuário, verifica se é NULO e remove aspas caso as tenha*/
                do{
                    fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
                    /*leitura e impressÃ£o de campos*/
                    fread(&ler_campo->removido, sizeof(char), 1, arq2);
                    if(ler_campo->removido != '*'){
                        fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
                        fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
                        fread(&ler_campo->nota, sizeof(double), 1, arq2);
                        fread(&ler_campo->data, sizeof(char), 10, arq2);
                        /*verifica a se a entrada Ã© igual ao campo recolhido*/
                        if(strcmp(ler_campo->data, valor_campo)==0){
                            rewind(arq2);
                            fseek(arq2, 16000+cont, SEEK_SET);
                            verifica_reg = (ftell(arq2)-16000)/80; /*Guarda a posição do registro*/
                            guarda_rrn[conta_rrn] = verifica_reg;
                            fwrite(&proc_removido, sizeof(char), 1 , arq2);  /*Atualiza o campo removido com * */
                            fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                            fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                            rewind(arq2);
                            fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                            fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                            salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
                            conta_rrn++;
                        }
                    }
                    /*Incrementa o contador erm 80 para ir para próxima linha*/
                    cont += 80;
                    /*zera o valor das variaveis para evitar sobreposições erradas*/
                        ler_campo->nroInscricao = 0;
                        ler_campo->nota = 0;
                        memset(ler_campo->data, 0, strlen(ler_campo->data));
                        ler_campo->tam1 = 0;
                        ler_campo->tagCampo4 = '0';
                        memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                        ler_campo->tam2 = 0;
                        ler_campo->tagCampo5 = '0';
                        memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
                }while(cont <= (tam_arq-16000));
                cont = 0;
                conta_rrn = 0;
        }
        /*Caso o campo seja Cidade*/
        else if(strcmp(opcao_campo, "cidade") == 0){
              scan_quote_string(valor_campo); /*pega o valor de entrada do usuário, verifica se é NULO e remove aspas caso as tenha*/
                do{
                    fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
                    /*leitura e impressÃ£o de campos*/
                    fread(&ler_campo->removido, sizeof(char), 1, arq2);
                    if(ler_campo->removido != '*'){
                        fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
                        fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
                        fread(&ler_campo->nota, sizeof(double), 1, arq2);
                        fread(&ler_campo->data, sizeof(char), 10, arq2);
                        fread(&ler_campo->tam1, sizeof(int), 1, arq2);
                        fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                        if(ler_campo->tagCampo4 == '4'){
                            fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                        }
                        /*verifica a se a entrada Ã© igual ao campo recolhido*/
                        if(strcmp(ler_campo->cidade, valor_campo)==0){
                            rewind(arq2);
                            fseek(arq2, 16000+cont, SEEK_SET);
                            verifica_reg = (ftell(arq2)-16000)/80; /*Guarda a posição do registro*/
                            guarda_rrn[conta_rrn] = verifica_reg;
                            fwrite(&proc_removido, sizeof(char), 1 , arq2);  /*Atualiza o campo removido com * */
                            fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                            fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                            rewind(arq2);
                            fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                            fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                            salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
                            conta_rrn++;
                        }
                    }
                    /*Incrementa o contador erm 80 para ir para próxima linha*/
                    cont += 80;
                    /*zera o valor das variaveis para evitar sobreposições erradas*/
                       ler_campo->nroInscricao = 0;
                       ler_campo->nota = 0;
                       memset(ler_campo->data, 0, strlen(ler_campo->data));
                       ler_campo->tam1 = 0;
                       ler_campo->tagCampo4 = '0';
                       memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                       ler_campo->tam2 = 0;
                       ler_campo->tagCampo5 = '0';
                       memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
                }while(cont <= (tam_arq-16000));
                /*Se saiu do loop, zera o contador para próxima busca*/
                cont = 0;
                conta_rrn = 0;
        }
        /*Caso o campo seja nomeEscola*/
        else if(strcmp(opcao_campo, "nomeEscola") == 0){
            scan_quote_string(valor_campo); /*pega o valor de entrada do usuário, verifica se é NULO e remove aspas caso as tenha*/
                do{
                    fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
                    /*leitura e impressÃ£o de campos*/
                    fread(&ler_campo->removido, sizeof(char), 1, arq2);
                    if(ler_campo->removido != '*'){
                        fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
                        fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
                        fread(&ler_campo->nota, sizeof(double), 1, arq2);
                        fread(&ler_campo->data, sizeof(char), 10, arq2);
                        fread(&ler_campo->tam1, sizeof(int), 1, arq2);
                        fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                        if(ler_campo->tagCampo4 == '5'){
                            fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam1, arq2);
                        }
                        else if(ler_campo->tagCampo4 == '4' ){
                            fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                            getc(arq2);
                            fread(&ler_campo->tam2, sizeof(int), 1, arq2);
                            fread(&ler_campo->tagCampo5, sizeof(char),1, arq2);
                            if(ler_campo->tagCampo5 == '5'){
                                fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2, arq2);
                            }
                        }
                        /*verifica a se a entrada Ã© igual ao campo recolhido*/
                        if(strcmp(ler_campo->nomeEscola, valor_campo)==0){
                            rewind(arq2);
                            fseek(arq2, 16000+cont, SEEK_SET);
                            verifica_reg = (ftell(arq2)-16000)/80; /*Guarda a posição do registro*/
                            guarda_rrn[conta_rrn] = verifica_reg;
                            fwrite(&proc_removido, sizeof(char), 1 , arq2);  /*Atualiza o campo removido com * */
                            fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                            fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                            rewind(arq2);
                            fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                            fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                            salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
                            conta_rrn++;
                        }
                    }
                    /*Incrementa o contador erm 80 para ir para próxima linha*/
                    cont += 80;
                    /*zera o valor das variaveis para evitar sobreposições erradas*/
                       ler_campo->nroInscricao = 0;
                       ler_campo->nota = 0;
                       memset(ler_campo->data, 0, strlen(ler_campo->data));
                       ler_campo->tam1 = 0;
                       ler_campo->tagCampo4 = '0';
                       memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                       ler_campo->tam2 = 0;
                       ler_campo->tagCampo5 = '0';
                       memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
                }while(cont <= (tam_arq-16000));
                /*Se saiu do loop, zera o contador para próxima busca*/
                cont = 0;
                conta_rrn = 0;
        }
}


/*Funcionalidade para adicionar ao arquivo os registros que usuário deseja*/
void Add_reg(FILE *arq2, Reg_de_Dados *ler_campo, Registro_de_Indice pega_campo[]){
    int cont = 0, reg_encontrado = 0, add_em = 0; /*Variáveis para contadores e salvar o byte - ao inves do rrn - do próximo local de registro para inserção*/
    int tam_arq, tam_pag, salva_topo; /*Variaveis de tamanho de arquivo e página além de uma para salvar valor do topoPilha*/
    char  preenche_final[80], stt = '0'; /*Variáveis para guardar @ para fim de registro*/
    char add_data[10], add_cidade[25], add_nomeEscola[23], add_tag4 = '4', add_tag5 = '5', ins_nota[25], ins_insc[25]; /*Variáveis para receber a entrada do usuário de valor de campo*/
    int add_nroinsc, add_encad = -1, add_tam1, add_tam2; /*Variaveis inteiras para os valores dos campos*/
    double add_nota; /*Variavel double para os valor do campo*/
    int conta_rrn = 0;
    Reg_de_Cabecalho set_status;

    /*Preenche vetor de char com @ para preencher registros*/
    for (int j = 0; j<80; j++){
        preenche_final[j] = '@';
    }

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
    tam_arq = ftell(arq2);
    tam_pag = (ftell(arq2)-16000)/80;
    rewind(arq2);


        /*Salva o primeiro valor do topoPilha, onde o primeiro espaço de registro pode ser adicionado*/
        fread(&set_status.status, sizeof(set_status.status), 1, arq2);
        fread(&set_status.topoPilha, sizeof(set_status.topoPilha), 1, arq2);
        salva_topo = (set_status.topoPilha);
        add_em = salva_topo*80;
        rewind(arq2);
        /*Começa as inserções*/
             getchar();
            scan_quote_string(ins_insc);/*Recebe o numero de inscrição*/
            add_nroinsc = atoi(ins_insc); /*Passa numero de inscrição para variável int*/
            scan_quote_string(ins_nota); /*Recebe a nota*/
            if (strcmp(ins_nota, "")==0){
                add_nota = -1; /*Se nota retornar vazio, quer dizer que usuário digitou NULO, o valor então será -1*/
            }
            else{
                add_nota = atof(ins_nota); /*Caso contrário atribui para variável double*/
            }
            scan_quote_string(add_data); /*Recebe a data*/
            strcpy(ler_campo->data, add_data); /*Copia para a variável correta*/

            scan_quote_string(add_cidade); /*Recebe a cidade*/
            strcpy(ler_campo->cidade, add_cidade); /*Copia para a variável correta*/

            add_tam1 = strlen(ler_campo->cidade)+2; /*verifica o tamanho do campo e soma 2 para tag e \0*/

            scan_quote_string(add_nomeEscola); /*Recebe o nome Escola*/
            strcpy(ler_campo->nomeEscola, add_nomeEscola); /*Copia para a variável correta*/

            add_tam2 = strlen(ler_campo->nomeEscola)+2; /*verifica o tamanho do campo e soma 2 para tag e \0*/

            /*Se o topoPilha for -1, não há registros removidos, todas as inserções se darão ao fim do arquivo*/
            if(salva_topo == -1){
                fseek(arq2, 0L, SEEK_END); /*Vai até o fim do arquivo*/
                strcpy(pega_campo->chaveBusca, add_nomeEscola);
                pega_campo->RRN = (ftell(arq2)-16000 )/ 80;
                fwrite("-", sizeof(char), 1, arq2); /*Escreve o valor de registro existente no campo removido*/
                fwrite(&add_encad, sizeof(int), 1, arq2); /*Escreve o valor do encadeamento, neste caso -1*/
                fwrite(&add_nroinsc, sizeof(int), 1, arq2); /*Escreve o valor do número de inscrição*/
                fwrite(&add_nota, sizeof(double), 1, arq2); /*Escreve o valor da nota*/
                if(strcmp(ler_campo->data, "")!=0){
                    fwrite(&ler_campo->data, sizeof(char), 10, arq2); /*Se o valor de data não for vazio, escrever o valor da data*/
                }
                else{
                    strcpy(ler_campo->data, "@@@@@@@@@@");
                    ler_campo->data[0] = '\0';
                    fwrite(&ler_campo->data, sizeof(char), 10, arq2); /*Caso contrário, usuário digitou NULO, preenche com \0@'s e escreve*/
                }
                /*A verificação de NULO pode ser feito pelo tamanho dos campos, tam1 para cidade e tam2 para nomeEscola*/
                if(add_tam1 == 2 && add_tam2 == 2){
                    fwrite(&preenche_final, sizeof(char), 53, arq2); /*Se ambos forem NULO, preenche os 53 bytes restantes do registro com @*/
                }
               else if(add_tam1 == 2 && add_tam2 != 2){ /*Se apenas cidade for NULO*/
                    fwrite(&add_tam2, sizeof(int), 1, arq2); /*Escreve tamanho do campo nomeEscola*/
                    fwrite(&add_tag5, sizeof(char), 1, arq2); /*Escreve ta tag do campo*/
                    fwrite(&add_nomeEscola, sizeof(char), add_tam2-1, arq2); /*Escreve o campo nomeEscola*/
                    fwrite(&preenche_final, sizeof(char), 49 - (add_tam2), arq2); /*Escreve o restante dos bytes com @*/
                }
                 else if(add_tam1 != 2 && add_tam2 == 2){ /*Se apenas nomeEScola for NULO*/
                    fwrite(&add_tam1, sizeof(int), 1, arq2); /*Escreve tamanho do campo cidade*/
                    fwrite(&add_tag4, sizeof(char), 1, arq2); /*Escreve ta tag do campo*/
                    fwrite(&ler_campo->cidade, sizeof(char), add_tam1-1, arq2); /*Escreve o campo cidade*/
                    fwrite(&preenche_final, sizeof(char), 49 - (add_tam1), arq2); /*Escreve o restante dos bytes com @*/
                }
                else{ /*Se ambos forem não NULO*/
                    fwrite(&add_tam1, sizeof(int), 1, arq2); /*Escreve tamanho do campo cidade*/
                    fwrite(&add_tag4, sizeof(char), 1, arq2); /*Escreve ta tag do campo*/
                    fwrite(&ler_campo->cidade, sizeof(char), add_tam1-1, arq2); /*Escreve o campo cidade*/
                    fwrite(&add_tam2, sizeof(int), 1, arq2); /*Escreve tamanho do campo nomeEscola*/
                    fwrite(&add_tag5, sizeof(char), 1, arq2); /*Escreve ta tag do campo*/
                    fwrite(&ler_campo->nomeEscola, sizeof(char), add_tam2-1, arq2); /*Escreve o campo nomeEscola*/
                    fwrite(&preenche_final, sizeof(char), 45 - (add_tam1) - (add_tam2), arq2); /*Escreve o restante dos bytes com @*/
                }
            }
            /*Se o topoPilha não for -1, há registros removidos, as inserções se dão de acordo com os valores encontrados nos encadeamentos*/
            else{
                strcpy(pega_campo->chaveBusca, add_nomeEscola);
                pega_campo->RRN = salva_topo;
                fseek(arq2, 16000+add_em, SEEK_SET); /*Vai até o primeiro registro da "pílha" para inserir novo registro*/
                fread(&ler_campo->removido, sizeof(char), 1, arq2);
                fread(&salva_topo, sizeof(int), 1, arq2); /*Salva qual será o próximo topoPilha, o próximo que está removido*/
                rewind(arq2);
                fseek(arq2, 16000+add_em, SEEK_SET); /*Vai até o primeiro registro da "pílha" para inserir novo registro*/
                fwrite("-", sizeof(char), 1, arq2); /*Escreve o valor de registro existente no campo removido*/
                fwrite(&add_encad, sizeof(int), 1, arq2); /*Escreve o valor do encadeamento*/
                fwrite(&add_nroinsc, sizeof(int), 1, arq2); /*Escreve o valor do número de inscrição*/
                fwrite(&add_nota, sizeof(double), 1, arq2); /*Escreve o valor da nota*/
                if(strcmp(ler_campo->data, "")!=0){
                    fwrite(&ler_campo->data, sizeof(char), 10, arq2); /*Se o valor de data não for vazio, escrever o valor da data*/
                }
                else{
                    strcpy(ler_campo->data, "@@@@@@@@@@");
                    ler_campo->data[0] = '\0';
                    fwrite(&ler_campo->data, sizeof(char), 10, arq2); /*Caso contrário, usuário digitou NULO, preenche com \0@'s e escreve*/
                }
                /*A verificação de NULO pode ser feito pelo tamanho dos campos, tam1 para cidade e tam2 para nomeEscola*/
                if(add_tam1 == 2 && add_tam2 == 2){
                    fwrite(&preenche_final, sizeof(char), 53, arq2); /*Se ambos forem NULO, preenche os 53 bytes restantes do registro com @*/
                }
                else if(add_tam1 == 2 && add_tam2 != 2){ /*Se apenas cidade for NULO*/
                    fwrite(&add_tam2, sizeof(int), 1, arq2); /*Escreve tamanho do campo nomeEscola*/
                    fwrite(&add_tag5, sizeof(char), 1, arq2); /*Escreve ta tag do campo*/
                    fwrite(&ler_campo->nomeEscola, sizeof(char), add_tam2-1, arq2); /*Escreve o campo nomeEscola*/
                    fwrite(&preenche_final, sizeof(char), 47 - (add_tam2), arq2);
                }
                 else if(add_tam1 != 2 && add_tam2 == 2){ /*Se apenas nomeEScola for NULO*/
                    fwrite(&add_tam1, sizeof(int), 1, arq2); /*Escreve tamanho do campo cidade*/
                    fwrite(&add_tag4, sizeof(char), 1, arq2); /*Escreve ta tag do campo*/
                    fwrite(&ler_campo->cidade, sizeof(char), add_tam1-1, arq2); /*Escreve o campo cidade*/
                    fwrite(&preenche_final, sizeof(char), 47 - (add_tam1), arq2);
                }
                else{ /*Se ambos forem não NULO*/
                    fwrite(&add_tam1, sizeof(int), 1, arq2); /*Escreve tamanho do campo cidade*/
                    fwrite(&add_tag4, sizeof(char), 1, arq2); /*Escreve ta tag do campo*/
                    fwrite(&ler_campo->cidade, sizeof(char), add_tam1-1, arq2); /*Escreve o campo cidade*/
                    fwrite(&add_tam2, sizeof(int), 1, arq2); /*Escreve tamanho do campo nomeEscola*/
                    fwrite(&add_tag5, sizeof(char), 1, arq2); /*Escreve ta tag do campo*/
                    fwrite(&ler_campo->nomeEscola, sizeof(char), add_tam2-1, arq2); /*Escreve o campo nomeEscola*/
                    fwrite(&preenche_final, sizeof(char), 45 - (add_tam1) - (add_tam2), arq2); /*Escreve o restante dos bytes com @*/
                }
            /*Retorna ao inicio do arquivo, certifica que status é 0, atualiza o topoPilha com seu novo encademanto*/
                rewind(arq2);
                fwrite(&stt, sizeof(char), 1, arq2);
                fwrite(&salva_topo, sizeof(int), 1, arq2);
                add_em = salva_topo*80;
            }
            /*Reseta as variaveis para que não haja risco de sobreposição errada de valores*/
            add_nroinsc = 0;
            add_nota = 0;
            memset(add_data, 0, strlen(ler_campo->data));
            add_tam1 = 0;
            add_tag4 = '4';
            memset(add_cidade, 0, strlen(add_cidade));
            add_tam2 = 0;
            add_tag5 = '5';
            memset(add_nomeEscola, 0, strlen(add_nomeEscola));
}

/*Funcionalidade para atualizar os registros que usuário deseja*/
void Atualiza_reg(FILE *arq2, Reg_de_Dados *ler_campo){
    int rrn = 0, boset,tam_arq;
    int  tam_pag;
    char opcao_campo[12], atualizacao[25], preenche_final[80], fim_str = '\0';
    char proc_data[10], proc_cidade[25], proc_nomeEscola[23];
    int proc_insc;
    double proc_nota;


    /*Preenche vetor de char com @ para preencher registros*/
    for (int j = 0; j<80; j++){
        preenche_final[j] = '@';
    }

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
     tam_pag = ftell(arq2);
    tam_arq = (ftell(arq2)-16000)/80;
    rewind(arq2);
    /*Começa as atualizações*/
         getchar();
        scanf("%d %s", &rrn, opcao_campo); /*pega o rrn que usuario deseja buscar*/
        scan_quote_string(atualizacao); /*Recebe qual  a atualização será realizada*/
            boset = rrn * 80; /* 80 é o tamanho fixo do registro*/
        if(rrn < tam_arq){ /*Se o rrn obito for menor que o tamanho do arquivo*/
            fseek(arq2, 16000+boset, SEEK_SET);
            /*leitura dos campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
        if(ler_campo->removido != '*'){
                fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
                fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
                fread(&ler_campo->nota, sizeof(double), 1, arq2);
                fread(&ler_campo->data,sizeof(char), 10, arq2);
                fread(&ler_campo->tam1, sizeof(int), 1, arq2);
                fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                if(ler_campo->tagCampo4 == '4'){
                    fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                    getc(arq2);
                    fread(&ler_campo->tam2, sizeof(int), 1, arq2);
                    fread(&ler_campo->tagCampo5, sizeof(char),1, arq2);
                    fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2);
                }
                else if(ler_campo->tagCampo4 == '5'){
                    ler_campo->tam2 = ler_campo->tam1;
                    ler_campo->tam1 = 0;
                    ler_campo->tagCampo5 = ler_campo->tagCampo4;
                    fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2);
                }
                rewind(arq2);
                fseek(arq2, 16000+boset, SEEK_SET);

                /* Os if e else if abaixo representama  comparação do campo de entrada do usuario com o nome de cada campo do arquivo*/

        /*verifica a opção nroInscriÃ§Ã£o*/
            if(strcmp(opcao_campo, "nroInscricao") == 0){

                if (strcmp(atualizacao, "")==0){
                    proc_insc = -1; /*Se numero Inscrição retornar vazio, quer dizer que usuário digitou NULO, o valor então será -1*/
                }
                else{
                proc_insc = atoi(atualizacao);
                }
                    fwrite(&ler_campo->removido, sizeof(char), 1, arq2); /*Escreve o valor do campo removido*/
                    fwrite(&ler_campo->encadeamento, sizeof(int), 1, arq2);  /*Escreve o valor do campo encadeamento*/
                    fwrite(&proc_insc, sizeof(int), 1, arq2);  /*Escreve o novo valor do campo numeroInscricao*/
                    fwrite(&ler_campo->nota, sizeof(double), 1, arq2);  /*Escreve o valor do campo nota*/
                    fwrite(&ler_campo->data,sizeof(char), 10, arq2);  /*Escreve o valor do campo data*/
                    fwrite(&ler_campo->tam1, sizeof(int), 1, arq2);  /*Escreve o valor do campo tamanho Cidade*/
                    if(ler_campo->tagCampo4 == '4'){ /*Se a primeira tag lida for 4, temos o campo cidade*/
                        fwrite(&ler_campo->tagCampo4, sizeof(char), 1, arq2);  /*Escreve o valor do campo tag Cidade*/
                        fwrite(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);  /*Escreve o valor do campo cidade*/
                        fwrite(&ler_campo->tam2, sizeof(int), 1, arq2);  /*Escreve o valor do campo tamanho nomeEscola*/
                        fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2);  /*Escreve o valor do campo tag nomeEscola*/
                        fwrite(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2);  /*Escreve o valor do campo nomeEscola*/
                    }
                    else if(ler_campo->tagCampo4 == '5'){ /*Caso a tag seja 5, cidade é nula e campoEscola não*/
                        fwrite(&ler_campo->tam2, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho nomeEscola*/
                        fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                        fwrite(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2); /*Escreve o valor do campo nomeEscola*/
                    }
                     //Zera as varia¡veis que receberão os campos, para não haver sobreposição de informações
                           ler_campo->nroInscricao = 0;
                           ler_campo->nota = 0;
                           memset(ler_campo->data, 0, strlen(ler_campo->data));
                           ler_campo->tam1 = 0;
                           ler_campo->tagCampo4 = '0';
                           memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                           ler_campo->nota = 0;
                           ler_campo->tagCampo5 = '0';
                           memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
            }
            /*verifica a opção nota*/
            else if(strcmp(opcao_campo, "nota") == 0){

                if (strcmp(atualizacao, "")==0){
                    proc_nota = -1; /*Se nota retornar vazio, quer dizer que usuário digitou NULO, o valor então será -1*/
                }
                else{
                proc_nota = atof(atualizacao);
                }
                    fwrite(&ler_campo->removido, sizeof(char), 1, arq2); /*Escreve o valor do campo removido*/
                    fwrite(&ler_campo->encadeamento, sizeof(int), 1, arq2); /*Escreve o valor do campo encadeamento*/
                    fwrite(&ler_campo->nroInscricao, sizeof(int), 1, arq2); /*Escreve o novo valor do campo numeroInscricao*/
                    fwrite(&proc_nota, sizeof(double), 1, arq2);  /*Escreve o novo valor do campo nota*/
                    fwrite(&ler_campo->data,sizeof(char), 10, arq2); /*Escreve o valor do campo data*/
                    if(ler_campo->tagCampo4 == '4'){ /*Se a primeira tag lida for 4, temos o campo cidade*/
                        fwrite(&ler_campo->tam1, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho Cidade*/
                        fwrite(&ler_campo->tagCampo4, sizeof(char), 1, arq2); /*Escreve o valor do campo tag Cidade*/
                        fwrite(&ler_campo->cidade, sizeof(char), ler_campo->tam1-1, arq2); /*Escreve o valor do campo cidade*/
                        fwrite(&ler_campo->tam2, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho nomeEscola*/
                        fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                        fwrite(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2); /*Escreve o valor do campo nomeEscola*/
                    }
                    else if(ler_campo->tagCampo4 == '5'){ /*Caso a tag seja 5, cidade é nula e campoEscola não*/
                        fwrite(&ler_campo->tam2, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho nomeEscola*/
                        fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                        fwrite(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2); /*Escreve o valor do campo nomeEscola*/
                    }
                         //Zera as variá¡veis que receberão os campos, para não haver sobreposição de informações
                           ler_campo->nroInscricao = 0;
                           ler_campo->nota = 0;
                           memset(ler_campo->data, 0, strlen(ler_campo->data));
                           ler_campo->tam1 = 0;
                           ler_campo->tagCampo4 = '0';
                           memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                           ler_campo->nota = 0;
                           ler_campo->tagCampo5 = '0';
                           memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
            }
            /*verifica a opção data*/
            else if(strcmp(opcao_campo, "data") == 0){
                if (strcmp(atualizacao, "")==0){
                    strcpy(proc_data, "@@@@@@@@@@"); /*Se data retornar vazio, quer dizer que usuário digitou NULO, o valor então será \0@'s*/
                    proc_data[0] = '\0';
                }
                else{
                strcpy(proc_data, atualizacao); /*Senão, copia o valor para a variável correta*/
                }

                    fwrite(&ler_campo->removido, sizeof(char), 1, arq2); /*Escreve o valor do campo removido*/
                    fwrite(&ler_campo->encadeamento, sizeof(int), 1, arq2); /*Escreve o valor do campo encadeamento*/
                    fwrite(&ler_campo->nroInscricao, sizeof(int), 1, arq2); /*Escreve o novo valor do campo numeroInscricao*/
                    fwrite(&ler_campo->nota, sizeof(double), 1, arq2); /*Escreve o valor do campo nota*/
                    fwrite(&proc_data,sizeof(char), 10, arq2); /*Escreve o novo valor do campo data*/
                    if(ler_campo->tagCampo4 == '4'){ /*Se a primeira tag lida for 4, temos o campo cidade*/
                        fwrite(&ler_campo->tam1, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho Cidade*/
                        fwrite(&ler_campo->tagCampo4, sizeof(char), 1, arq2); /*Escreve o valor do campo tag Cidade*/
                        fwrite(&ler_campo->cidade, sizeof(char), ler_campo->tam1-1, arq2); /*Escreve o valor do campo cidade*/
                        fwrite(&ler_campo->tam2, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho nomeEscola*/
                        fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                        fwrite(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2); /*Escreve o valor do campo nomeEscola*/
                    }
                    else if(ler_campo->tagCampo4 == '5'){ /*Caso a tag seja 5, cidade é nula e campoEscola não*/
                        fwrite(&ler_campo->tam2, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho nomeEscola*/
                        fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                        fwrite(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2); /*Escreve o valor do campo nomeEscola*/
                    }
                         //Zera as variá¡veis que receberão os campos, para não haver sobreposição de informações
                           ler_campo->nroInscricao = 0;
                           ler_campo->nota = 0;
                           memset(ler_campo->data, 0, strlen(ler_campo->data));
                           ler_campo->tam1 = 0;
                           ler_campo->tagCampo4 = '0';
                           memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                           ler_campo->nota = 0;
                           ler_campo->tagCampo5 = '0';
                           memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
            }
            /*verifica a opção cidade*/
            else if(strcmp(opcao_campo, "cidade") == 0){
                strcpy(proc_cidade, atualizacao);
                int new_tam = strlen(proc_cidade)+2;
                   ler_campo->tagCampo4 = '4';
                   int dif = ler_campo->tam1 - new_tam;
                    fwrite(&ler_campo->removido, sizeof(char), 1, arq2); /*Escreve o valor do campo removido*/
                    fwrite(&ler_campo->encadeamento, sizeof(int), 1, arq2); /*Escreve o valor do campo encadeamento*/
                    fwrite(&ler_campo->nroInscricao, sizeof(int), 1, arq2); /*Escreve o novo valor do campo numeroInscricao*/
                    fwrite(&ler_campo->nota, sizeof(double), 1, arq2); /*Escreve o valor do campo nota*/
                    fwrite(&ler_campo->data,sizeof(char), 10, arq2); /*Escreve o valor do campo data*/
                    if(strcmp(atualizacao, "")!=0){ /*Verifica se a atualização é NULO*/
                        fwrite(&new_tam, sizeof(int), 1, arq2); /*Escreve o novo valor do campo tamanho Cidade*/
                        fwrite(&ler_campo->tagCampo4, sizeof(char), 1, arq2); /*Escreve o valor do campo tag Cidade*/
                        fwrite(&proc_cidade, sizeof(char), new_tam-1, arq2); /*Escreve o novo valor do campo cidade*/
                        fwrite(&ler_campo->tam2, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho nomeEscola*/
                        fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                        fwrite(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2); /*Escreve o valor do campo nomeEscola*/
                        fwrite(&fim_str, sizeof(char), 1, arq2); /*Finaliza a string com \0*/
                        if(dif >=0){
                        fwrite(&preenche_final, sizeof(char), 45 - (ler_campo->tam1) - (ler_campo->tam2) + dif, arq2); /*Preenche resto do registro se a diferença entre o antigo tamanho e novo for positivo*/
                        }
                    }
                    else{
                        fwrite(&ler_campo->tam2, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho nomeEscola*/
                        fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                        fwrite(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2); /*Escreve o valor do campo nomeEscola*/
                        fwrite(&fim_str, sizeof(char), 1, arq2);/*Finaliza a string com \0*/
                        fwrite(&preenche_final, sizeof(char), ler_campo->tam2+5, arq2); /*Preenche resto do registro*/
                    }
                        //Zera as variá¡veis que receberão os campos, para não haver sobreposição de informações
                           ler_campo->nroInscricao = 0;
                           ler_campo->nota = 0;
                           memset(ler_campo->data, 0, strlen(ler_campo->data));
                           ler_campo->tam1 = 0;
                           ler_campo->tagCampo4 = '0';
                           memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                           ler_campo->nota = 0;
                           ler_campo->tagCampo5 = '0';
                           memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
            }
            /*verifica a opção nomeEscola*/
            else if(strcmp(opcao_campo, "nomeEscola") == 0){
                strcpy(proc_nomeEscola, atualizacao);
                int new_tam = strlen(proc_nomeEscola)+2;

                    int dif = ler_campo->tam2 - new_tam;
                    ler_campo->tagCampo5 = '5';
                    fwrite(&ler_campo->removido, sizeof(char), 1, arq2); /*Escreve o valor do campo removido*/
                    fwrite(&ler_campo->encadeamento, sizeof(int), 1, arq2); /*Escreve o valor do campo encadeamento*/
                    fwrite(&ler_campo->nroInscricao, sizeof(int), 1, arq2); /*Escreve o novo valor do campo numeroInscricao*/
                    fwrite(&ler_campo->nota, sizeof(double), 1, arq2); /*Escreve o valor do campo nota*/
                    fwrite(&ler_campo->data,sizeof(char), 10, arq2); /*Escreve o valor do campo data*/
                    if(ler_campo->tagCampo4 == '4'){ /*Se a primeira tag lida for 4, temos o campo cidade*/
                        fwrite(&ler_campo->tam1, sizeof(int), 1, arq2); /*Escreve o valor do campo tamanho Cidade*/
                        fwrite(&ler_campo->tagCampo4, sizeof(char), 1, arq2); /*Escreve o valor do campo tag Cidade*/
                        fwrite(&ler_campo->cidade, sizeof(char), ler_campo->tam1-1, arq2); /*Escreve o valor do campo cidade*/
                        if(strcmp(atualizacao, "")!=0){ /*Verifica se a atualização é NULO*/
                            fwrite(&new_tam, sizeof(int), 1, arq2); /*Escreve o novo valor do campo tamanho nomeEscola*/
                            fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                            fwrite(&proc_nomeEscola, sizeof(char), new_tam-2, arq2); /*Escreve o novo valor do campo nomeEscola*/
                            fwrite(&fim_str, sizeof(char), 1, arq2); /*Finaliza a string com \0*/
                            fwrite(&preenche_final, sizeof(char), 45 - (ler_campo->tam1) - (ler_campo->tam2) + dif, arq2); /*Preenche resto do registro*/
                        }
                        else{
                            fwrite(&fim_str, sizeof(char), 1, arq2); /*Finaliza a string com \0*/
                            fwrite(&preenche_final, sizeof(char), ler_campo->tam2+5, arq2); /*Preenche resto do registro*/
                        }
                    }
                    else if(ler_campo->tagCampo4 == '5'){ /*Caso a tag seja 5, cidade é nula e campoEscola não*/
                        if(strcmp(atualizacao, "")!=0){ /*Verifica se a atualização é NULO*/
                            fwrite(&new_tam, sizeof(int), 1, arq2); /*Escreve o novo valor do campo tamanho nomeEscola*/
                            fwrite(&ler_campo->tagCampo5, sizeof(char),1, arq2); /*Escreve o valor do campo tag nomeEscola*/
                            fwrite(&proc_nomeEscola, sizeof(char), new_tam-2, arq2); /*Escreve o novo valor do campo nomeEscola*/
                            fwrite(&fim_str, sizeof(char), 1, arq2); /*Finaliza a string com \0*/
                            fwrite(&preenche_final, sizeof(char), ler_campo->tam2+4, arq2); /*Preenche resto do registro*/
                    }
            }
            //Zera as variá¡veis que receberão os campos, para não haver sobreposição de informações
                           ler_campo->nroInscricao = 0;
                           ler_campo->nota = 0;
                           memset(ler_campo->data, 0, strlen(ler_campo->data));
                           ler_campo->tam1 = 0;
                           ler_campo->tagCampo4 = '0';
                           memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                           ler_campo->nota = 0;
                           ler_campo->tagCampo5 = '0';
                           memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
            }
        }
    }
}

//////////////////////////////////  FUNCIONALIDADES DO TRABALHO 3 - ORDENAÇÃO INTERNA, CONSEQUENCIAL MERGING e CONSEQUENCIAL MATCHING !! ////////////////////////////////////////////////////////
/*Funcionalidade para ordenar os registros*/
void Ordena_reg(FILE *arq1, FILE *arq2, Reg_de_Cabecalho new_cab){
    int tam_arq, max_reg; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int cont = 0, contador = 0, salva_rrn = 0, conta_remov = 0, contador2 = 0;
    Reg_de_Dados ler_reg, aux;
    int j =0;

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq1, 0L, SEEK_END);
    tam_arq = ftell(arq1);
    max_reg = (ftell(arq1)-16000)/80;
    rewind(arq1);
    Reg_de_Dados vet_regs[max_reg];
    int ordena_insc[max_reg];
    int salva_insc[max_reg];
    /*Escreve cabeçalho no novo arquivo*/
    escreve_cab(new_cab, arq2);
    /*Salva os registros do arq1*/
    while(contador < max_reg){
        fseek(arq1, 16000+cont, SEEK_SET);
        /*Leitura de um registro*/
        le_registro(arq1, &ler_reg);
        if(ler_reg.removido == '*'){
            conta_remov++; /*Se for um registro removido, não salva nos vetores e incrementa váriavel de removidos*/
        }
        /*Caso não seja removido, salva o registro no vetor e o número de inscrição do mesmo em outros 2 vetores, um que será ordenado e um que funcionará como indice*/
        else{
            vet_regs[contador2] = ler_reg;
            salva_insc[contador2] = ler_reg.nroInscricao;
            ordena_insc[contador2] = ler_reg.nroInscricao;
            contador2++;
        }
        /*Incrementa os contadores e zera os campos para evitar sobreposições erradas*/
        cont += 80;
        contador++;
        reseta_campos(&ler_reg);
    }
    /*Zera o contador e cria uma nova váriavel de tamanho, desconsiderando agora os campos removidos*/
    cont = 0;
    int max_reg2 = max_reg-conta_remov;
    /*Criação de novos vetores de tamanho novo*/
    Reg_de_Dados vet_regs2[max_reg2];
    int ordena_insc2[max_reg2];
    int salva_insc2[max_reg2];
    /*Loop para transferir as informações dos vetores antigos para os novos*/
    for(int k = 0; k<max_reg2;k++){
        ordena_insc2[k] = ordena_insc[k];
        salva_insc2[k] = salva_insc[k];
        vet_regs2[k] = vet_regs[k];
    }
    /*Inicialização dos campos par quicksort e chamada da função que ordenará*/
    int lo = 0, hi = max_reg2-1, num;
    quick_sort(ordena_insc2, lo, hi);

    /*Escreve os registros no arq2*/
    for(int i = 0; i<max_reg2; i++){
        num = ordena_insc2[i]; /*Seleciona cada registro do vetor ordenado*/
        while(num != salva_insc2[j]){
            j++; /*Enquanto o valor não for encontrado no vetor "indice", incrementa a posição*/
        }
        /*Salva a posição/rrn do registro a ser escrito, pega o registro e o escreve no novo arquivo*/
        salva_rrn = j;
        ler_reg = vet_regs2[salva_rrn];
        escreve_registro(arq2, ler_reg);
        /*Incrementa contador do ponteiro, zera os campos e o contador de posição*/
        cont+=80;
        reseta_campos(&ler_reg);
        j=0;
    }
}

/*Funcionalidade para  os registros*/
void Merging_reg(FILE *arq1, FILE *arq2, FILE *arq3,Reg_de_Cabecalho new_cab){
    int tam_arq1, max_rrn1; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int tam_arq2, max_rrn2; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int nroinsc1, nroinsc2, aux;
    int contador1 = 0, contador2 = 0;
    int salva_bt1 = 16000, salva_bt2 = 16000;
    char preenche_fim = '@';
    Reg_de_Dados ler_reg1, ler_reg2;

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq1, 0L, SEEK_END);
    tam_arq1 = ftell(arq1);
    max_rrn1 = (ftell(arq1)-16000)/80;
    rewind(arq1);
    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
    tam_arq2 = ftell(arq2);
    max_rrn2 = (ftell(arq2)-16000)/80;
    rewind(arq2);

    escreve_cab(new_cab, arq3);

    /*Le os registros do arq1 e do arq2*/
    fseek(arq1, salva_bt1, SEEK_SET);
    le_registro(arq1, &ler_reg1);

    fseek(arq2, salva_bt2, SEEK_SET);
    le_registro(arq2, &ler_reg2);

     /*Compara os valores de nroInscricao e escreve os registros no arq3*/
    while(contador1 < max_rrn1 && contador2 < max_rrn2){
        /*Se nroInscricao do primeiro arquivo for maior que do segundo*/
        if(ler_reg1.nroInscricao < ler_reg2.nroInscricao){
            escreve_registro(arq3, ler_reg1);
            /*Reseta todos os campos para evitar sobreposições erradas*/
            reseta_campos(&ler_reg1);

            /*Avança nos registros*/
            salva_bt1+= 80;
            fseek(arq1, salva_bt1, SEEK_SET);

            /*Leitura do novo registro*/
           le_registro(arq1, &ler_reg1);

            /*Avança o contador*/
            contador1++;
        }
        /*Se nroInscricao do segundo arquivo for maior que do primeiro*/
        else if (ler_reg1.nroInscricao > ler_reg2.nroInscricao){
            escreve_registro(arq3, ler_reg2);

            /*Reseta todos os campos para evitar sobreposições erradas*/
            reseta_campos(&ler_reg2);

            /*Avança nos registros*/
            salva_bt2+= 80;
            fseek(arq2, salva_bt2, SEEK_SET);

            /*Leitura do novo registro*/
            le_registro(arq2, &ler_reg2);

            /*Avança o contador*/
            contador2++;
        }
        /*Se os nroInscrições forem iguais, escreve o do arquivo1 e passa para próximo registro de ambos*/
        else{
            /*Escreve no arquivo3*/
            escreve_registro(arq3, ler_reg1);

            /*Reseta todos os campos para evitar sobreposições erradas*/
            reseta_campos(&ler_reg1);

            /*Avança nos registros*/
            salva_bt1+= 80;
            fseek(arq1, salva_bt1, SEEK_SET);

            /*Leitura do novo registro*/
            le_registro(arq1, &ler_reg1);

            /*Avança nos registros*/
            salva_bt2+= 80;
            fseek(arq2, salva_bt2, SEEK_SET);

            /*Leitura do novo registro*/
            le_registro(arq2, &ler_reg2);

            /*Avança os contadores*/
            contador1++;
            contador2++;
        }
    }
    /*Se um dos arquivos acabou programa sai do loop*/
    /*Se o arquivo 2 acabou mas o 1 não*/
    if(contador2 == max_rrn2 && contador1 < max_rrn1){
        while(contador1 < max_rrn1){
            escreve_registro(arq3, ler_reg1);
            /*Reseta todos os campos para evitar sobreposições erradas*/
            reseta_campos(&ler_reg1);

            /*Avança nos registros*/
            salva_bt1+= 80;
            fseek(arq1, salva_bt1, SEEK_SET);

            /*Leitura do novo registro*/
            le_registro(arq1, &ler_reg1);

            /*Avança o contador*/
            contador1++;
        }
    }
    /*Se o arquivo 1 acabou mas o 2 não*/
    else if(contador1 == max_rrn1 && contador2 < max_rrn2){
        while(contador2 < max_rrn2){
            escreve_registro(arq3, ler_reg2);

            /*Reseta todos os campos para evitar sobreposições erradas*/
            reseta_campos(&ler_reg2);

            /*Avança nos registros*/
            salva_bt2+= 80;
            fseek(arq2, salva_bt2, SEEK_SET);

            /*Leitura do novo registro*/
           le_registro(arq2, &ler_reg2);

            /*Avança o contador*/
            contador2++;
        }
    }
}

/*Funcionalidade para os registros*/
void Matching_reg(FILE *arq1, FILE *arq2, FILE *arq3,Reg_de_Cabecalho new_cab){
    int tam_arq1, max_rrn1; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int tam_arq2, max_rrn2; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int nroinsc1, nroinsc2, aux;
    int contador1 = 0, contador2 = 0;
    int salva_bt1 = 16000, salva_bt2 = 16000;
    char preenche_fim = '@';
    Reg_de_Dados ler_reg1, ler_reg2;

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq1, 0L, SEEK_END);
    tam_arq1 = ftell(arq1);
    max_rrn1 = (ftell(arq1)-16000)/80;
    rewind(arq1);
    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
    tam_arq2 = ftell(arq2);
    max_rrn2 = (ftell(arq2)-16000)/80;
    rewind(arq2);

    escreve_cab(new_cab, arq3);

    /*Le os registros do arq1 e do arq2*/
    fseek(arq1, salva_bt1, SEEK_SET);
    le_registro(arq1, &ler_reg1);

    fseek(arq2, salva_bt2, SEEK_SET);
    le_registro(arq2, &ler_reg2);

     /*Compara os valores de nroInscricao e escreve os registros no arq3*/
    while(contador1 < max_rrn1 && contador2 < max_rrn2){
        /*Se nroInscricao do primeiro arquivo for maior que do segundo*/
        if(ler_reg1.nroInscricao < ler_reg2.nroInscricao){
            /*Reseta todos os campos para evitar sobreposições erradas*/
           reseta_campos(&ler_reg1);

            /*Avança nos registros*/
            salva_bt1+= 80;
            fseek(arq1, salva_bt1, SEEK_SET);

            /*Leitura do novo registro*/
           le_registro(arq1, &ler_reg1);

            /*Avança o contador*/
            contador1++;
        }
        /*Se nroInscricao do segundo arquivo for maior que do primeiro*/
        else if (ler_reg1.nroInscricao > ler_reg2.nroInscricao){
            /*Reseta todos os campos para evitar sobreposições erradas*/
            reseta_campos(&ler_reg2);

            /*Avança nos registros*/
            salva_bt2+= 80;
            fseek(arq2, salva_bt2, SEEK_SET);

            /*Leitura do novo registro*/
            le_registro(arq2, &ler_reg2);

            /*Avança o contador*/
            contador2++;
        }
        /*Se os nroInscrições forem iguais, escreve o do arquivo1 e passa para próximo registro de ambos*/
        else{
            /*Escreve no arquivo3*/
            escreve_registro(arq3, ler_reg1);

            /*Reseta todos os campos para evitar sobreposições erradas*/
            reseta_campos(&ler_reg1);
            reseta_campos(&ler_reg2);

            /*Avança nos registros*/
            salva_bt1+= 80;
            salva_bt2+= 80;
            fseek(arq1, salva_bt1, SEEK_SET);
            fseek(arq2, salva_bt2, SEEK_SET);

            /*Leitura do novo registro*/
    fseek(arq1, salva_bt1, SEEK_SET);
    le_registro(arq1, &ler_reg1);

    fseek(arq2, salva_bt2, SEEK_SET);
    le_registro(arq2, &ler_reg2);

            /*Avança os contadores*/
            contador1++;
            contador2++;
        }
    }
}
///////////////////////////////////////////////////////  FUNCIONALIDADES DO TRABALHO 4 - CRIAÇÃO, IMPRESSÃO E BUSCA !! //////////////////////////////////////////////////////////////////////////
void ind_secfl(FILE *arq1, FILE *arq2, Cabecalho_de_Indice cab_ind){
    int tam_arq, max_reg; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int cont = 0, contador = 0, pega_rrn = 0, conta_remov = 0, contador2 = 0, tam_nome = 0, j = 0; /*Contadores utilizados*/
    Reg_de_Dados ler_reg; /*Variavel do tipo registro de dados para salvar os registros*/
    char escola[23], preenche_fim = '@', fim_string = '\0'; /*Variáveis para pegar a chave e preencher o restante do registro*/

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq1, 0L, SEEK_END);
    tam_arq = ftell(arq1);
    max_reg = (ftell(arq1)-16000)/80;
    rewind(arq1);
    Registro_de_Indice reg_ind[max_reg];
    Registro_de_Indice regaux_ind[max_reg];
    Reg_de_Dados vet_regs[max_reg];
    char ordena_escola[max_reg];
    char salva_escola[max_reg];
    int salva_rrn[max_reg];
    /*Escreve cabeçalho no novo arquivo*/
    escreve_cabind(cab_ind, arq2);
    reseta_campos(&ler_reg);
    /*Salva os registros do arq1*/
    while(contador < max_reg){
        fseek(arq1, 16000+cont, SEEK_SET);
        /*Leitura de um registro*/
        le_registro(arq1, &ler_reg);
        if(ler_reg.removido == '*'){
            conta_remov++; /*Se for um registro removido, não salva nos vetores e incrementa váriavel de removidos*/
        }
        /*Caso não seja removido, salva o registro no vetor e o número de inscrição do mesmo em outros 2 vetores, um que será ordenado e um que funcionará como indice*/
        else{
            if(ler_reg.tagCampo5 == '5'){ /*Se campo nomeEscola não for nulo*/
                strcpy(reg_ind[contador2].chaveBusca, ler_reg.nomeEscola);
                reg_ind[contador2].RRN = contador;
                contador2++;
            }
            else{ /*Caso contrário, incrementar váriavel com número de removidos no arquivo*/
                conta_remov++;
            }
        }
        /*Incrementa os contadores e zera os campos para evitar sobreposições erradas*/
        cont += 80;
        contador++;
        reseta_campos(&ler_reg);
    }
    /*Zera o contador e cria uma nova váriavel de tamanho, desconsiderando agora os campos removidos*/
    cont = 0;
    int max_reg2 = max_reg-conta_remov;

    /*Criação de novos vetores de tamanho novo*/
    Registro_de_Indice reg_ind2[max_reg2];
    Reg_de_Dados vet_regs2[max_reg2];
    char ordena_insc2[max_reg2];
    char salva_insc2[max_reg2];
    int salva_rrn2[max_reg2];
    /*Loop para transferir as informações dos vetores antigos para os novos*/
    for(int k = 0; k<max_reg2;k++){
        strcpy(reg_ind2[k].chaveBusca, reg_ind[k].chaveBusca);
        reg_ind2[k].RRN = reg_ind[k].RRN;
    }
        /*Ordena vetor de nomeEscola*/
        selecsortchar(reg_ind2, max_reg2);

    /*Escreve os registros no arq2*/
    for(int i = 0; i<max_reg2; i++){
        strcpy(escola, reg_ind2[i].chaveBusca);
        tam_nome = strlen(escola);
        if(tam_nome > 23){
            tam_nome = 23; /*Como tamanho maximo das chaves eh 23, se por acaso pegar mais que 23 bytes, seta em 23*/
        }
        fwrite(&reg_ind2[i].chaveBusca, sizeof(char), tam_nome, arq2); /*Escreve a chave*/
        fwrite(&fim_string, sizeof(char), 1, arq2); /*\0*/
        for(int j = 0; j < 27-tam_nome; j++){
            fwrite(&preenche_fim, sizeof(char), 1, arq2); /*Preenche com @ o restante*/
        }
        fwrite(&reg_ind2[i].RRN, sizeof(int), 1, arq2); /*Escreve o rrn*/
    }
    /*Escreve quantidade de registros no cabeçalho*/
    rewind(arq2);
    fseek(arq2, 1, SEEK_CUR);
    fwrite(&max_reg2, sizeof(cab_ind.nroRegistro), 1, arq2);

}
/*Função referente à funcionalidade 12*/
void busca_indice(FILE *arq1, FILE *arq2, char opcao_campo[], char escola[], int *num_pdisc, int *num_pcab){
    int tam_arq, max_reg, tam_arq2, max_reg2; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int cont = 0, contador = 0, pega_rrn = 0, conta_remov = 0, contador2 = 0, tam_nome = 0, conta_pagind = 0, conta_pagreg = 0; /*contadores de quantidade e tamanho*/
    int num_regpag = 0, qtd_reg = 0, n_reg = 0, verifica_rrn = 0; /*contadores de registro/paginas e variavel para verificar rrn*/
    Registro_de_Indice ler_reg; /*Variavel do tipo registro de indice*/
    Reg_de_Dados pega_reg; /*Variavel do tipo registro de dados*/
    int j =0, antes_rrn = 0, depois_rrn = 0, cont_rrn = 0, reg_ppag = 200; /* Variáveis como contadores e numero de registros por pagina*/

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
    tam_arq2 = ftell(arq2);
    max_reg2 = (ftell(arq2)-16000)/32;
    rewind(arq2);
    fseek(arq2, 1, SEEK_CUR);
    fread(&qtd_reg, sizeof(int), 1, arq2);
    num_regpag = 16000/32;

    /*Variaveis vetoriais para salvar registros*/
    Registro_de_Indice reg_ind[max_reg2];
    int salva_reg[max_reg2];

    /*Zera os campos para evitar sobreposições erradas*/
    reseta_campindice(&ler_reg);
    reseta_campos(&pega_reg);
    conta_pagind++; /*Acesso ao arquivo de indice*/

    /*Salva os registros*/
    while(contador < max_reg2){
        fseek(arq2, 16000+cont, SEEK_SET);
        /*Leitura de um registro*/
        le_regindice(arq2, &ler_reg);
        strcpy(reg_ind[contador2].chaveBusca, ler_reg.chaveBusca);
        reg_ind[contador2].RRN = ler_reg.RRN;
        contador2++;
        if(contador%num_regpag == 0){
            conta_pagind++; /*Incriementa numero de páginas*/
        }
        /*Incrementa os contadores e zera os campos para evitar sobreposições erradas*/
        cont += 32;
        contador++;
        reseta_campindice(&ler_reg);
    }

    cont = 0;
    contador2 = 0;
    contador = 0;
    /*Faz busca binaria*/
    busca_binaria(arq2, escola, reg_ind, salva_reg, max_reg2, &n_reg);
    if(n_reg != 0){
        for(int j = 0; j < n_reg;j++){
            verifica_rrn = salva_reg[j]; /*Recupera o rrn*/
            fseek(arq1, 16000+(80*verifica_rrn), SEEK_SET); /*Avança até o rrn para acesso direto*/
            le_registro(arq1, &pega_reg); /*Le o registro*/
            imprime_reg(pega_reg); /*Imprime o registro*/
        }
    }
    else{
        printf("Registro inexistente.");
        fclose(arq1);
        fclose(arq2);
        exit(0);
    }

    conta_pagreg++; /*Soma 1 na quantidade de página de disco pelo primeiro acesso*/
    int min = 0, max = 199;
    for(int j = 1; j<= n_reg; j++){
        for (int i = 0; i<25; i++){
            if(salva_reg[j-1] <= 199*(i+1) && salva_reg[j-1] >= 0+(200*i)) /*Se valor de rrn da posição anterior está nessa faixa*/
                if(salva_reg[j] >= 199*(i+1)){ /*Se o próximo não está*/
                conta_pagreg++; /*Acesso à nova página*/
            }
        }
    }

    /*Seta os valores de acesso à paginas de disco*/
    *num_pdisc = conta_pagreg+1; /*O +1 é pelo acesso inicial ao registro de cabeçalho*/
    *num_pcab = conta_pagind;
}

/*Função referente à funcionalidade 13*/
void remove_indice(FILE *arq1, FILE *arq2, int n, char *nome_arq2, Cabecalho_de_Indice cab_ind){
    int tam_arq2, max_reg2; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int cont = 0, contador = 0, conta_remov = 0, contador2 = 0, contador3 = 0, tam_nome = 0, conta_pagind = 0;
    int num_regpag = 0, qtd_reg = 0, qtd_regin = 0; /*Variaveis para quantidade de paginas e registros*/
    int no_reg = -2, p = 0, j =0; /*Contadores*/
    char preenche_fim = '@', escola[28], fim_string = '\0'; /*Variáveis para pegar a chave e preencher o restante do registro*/
    Registro_de_Indice ler_reg; /*Variavel para ler os registros de indice*/
    Reg_de_Dados pega_reg, ler_campo; /*Variavel para ler os registros*/

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
    tam_arq2 = ftell(arq2);
    max_reg2 = (ftell(arq2)-16000)/32;
    rewind(arq2);
    /*Busca a quantidade de registros existentes*/
    fseek(arq2, 1, SEEK_CUR);
    fread(&qtd_reg, sizeof(int), 1, arq2);
    num_regpag = 16000/32;

    /*Variáveis vetor para salvar registros e rrns*/
    Registro_de_Indice reg_ind[max_reg2];
    int salva_reg[max_reg2];
    for(int i =0; i<max_reg2; i++){
        salva_reg[i] = no_reg;
    }
    /*Zera os campos para evitar sobreposição errada*/
    reseta_campindice(&ler_reg);
    reseta_campos(&pega_reg);
    conta_pagind++;

    /*Lê o arquivo de indice e passa tudo para um vetor em ram*/
    while(contador < max_reg2){
        fseek(arq2, 16000+cont, SEEK_SET);
        /*Leitura de um registro*/
        le_regindice(arq2, &ler_reg);
        strcpy(reg_ind[contador2].chaveBusca, ler_reg.chaveBusca);
        reg_ind[contador2].RRN = ler_reg.RRN;
        contador2++;
        if(contador%num_regpag == 0){
            conta_pagind++; /*Incriementa numero de páginas*/
        }
        /*Incrementa os contadores e zera os campos para evitar sobreposições erradas*/
        cont += 32;
        contador++;
        reseta_campindice(&ler_reg);
    }
    contador = 0;
    /*Loop para remover os registros e salvar as informações. Os valores dos campos já são passados na funcionalidade 5 de de remoção*/
    do{
        Remover_reg(arq1, &ler_campo, salva_reg);
        contador++;
        while(salva_reg[p] != -2){ /*Enquanto o valor de cada posição de vetor for diferente do valor marcado para não utilizado*/
           while(contador3<max_reg2){ /*Enquanto um contador for menor que numero de registros*/
                if (reg_ind[contador3].RRN == salva_reg[p]){/*Se valor da posição igual ao valor recuperado da remoção*/
                    reg_ind[contador3].RRN = -3; /*Seta o novo rrn como outro valor não utilizado, -3, para não encontrar -2 naquela posição durante nova busca*/
                    conta_remov++; /*Incrementa variável para saber quantos valores foram removidos*/
                    contador3 = 0; /*Zera o contador para começar busca do inicio pois registros são ordenados em rodem alfabética, não númerica*/
                    p++; /*Incrementa contador para andar no vetor de rrn utilizado na remoção*/
                }
                contador3++; /*Incrementa contador do vetor de registros*/
           }
           contador3 = 0; /*Zera o caontador para vetor de registros*/
            for(int i =0; i<max_reg2; i++){
                salva_reg[i] = no_reg; /*Preenche o vetor novamente com valores que não são utilizados*/
            }
        }
        p = 0; /*Zera o caontador para vetor de rrn*/
    }while(contador < n);

    /*Fecha arquivo para reabertura e reescrita*/
    fclose(arq2);
    /*Abre um novo arquivo de mesmo nome para reescrever os indices*/
    arq2 = fopen(nome_arq2, "wb"); /*abre arquivo binario para leitura*/
    if(arq2==NULL){  /*testa se conseguiu abrir*/
        printf("Falha no processamento do arquivo.");
        fclose(arq2);
        exit(0);
    }

    /*Escreve cabeçalho no novo arquivo*/
    escreve_cabind(cab_ind,arq2);

    rewind(arq2);
    fseek(arq2, 16000, SEEK_CUR);
    /*Escreve os registros no arq2*/
    for(int i = 0; i<max_reg2; i++){
        if(reg_ind[i].RRN != -3){
            strcpy(escola, reg_ind[i].chaveBusca);
            tam_nome = strlen(escola);
            if(tam_nome > 23){
                tam_nome = 23; /*Como tamanho máximo  de nomeEscola é 23, seta para 23*/
            }
            /*Escreve no arq2*/
            fwrite(&reg_ind[i].chaveBusca, sizeof(char), tam_nome, arq2); /*Escreve a chave*/
            fwrite(&fim_string, sizeof(char), 1, arq2); /*\0*/
            for(int j = 0; j < 27-tam_nome; j++){
                fwrite(&preenche_fim, sizeof(char), 1, arq2); /*Preenche com @*/
            }
            fwrite(&reg_ind[i].RRN, sizeof(int), 1, arq2); /*Escreve o rrn*/
        }
    }
    qtd_regin = qtd_reg - conta_remov; /*Seta nova quantidade de registros*/
    rewind(arq2);
    /*Escreve nova quantidade de registros*/
    fseek(arq2, 1, SEEK_CUR);
    fwrite(&qtd_regin, sizeof(int), 1, arq2);
}

/*Função referente à funcionalidade 14*/
void insere_indice(FILE *arq1, FILE *arq2, int n){
    int tam_arq2 = 0, max_reg2; /*tamanho de bytes do arquivo e quantidade de registros em uma página de disco*/
    int cont = 0, contador = 0, conta_remov = 0, contador2 = 0, contador3 = 0, tam_nome = 0, conta_pagind = 0, soma_rrn = 0; /*Contadores*/
    int num_regpag = 0, qtd_reg = 0, qtd_regin = 0; /*Contadores de quantidade de página e registro*/
    int no_reg = -2, p = 0, j =0; /*Contadores e numero utilizado para indicar indice não presente*/
    char preenche_fim = '@', escola[28], fim_string = '\0'; /*Variáveis para pegar a chave e preencher o restante do registro*/
    Registro_de_Indice ler_reg; /*Variavel para ler os registros de indice*/
    Reg_de_Dados pega_reg, ler_campo; /*Variavel para ler os registros*/

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
    tam_arq2 = ftell(arq2);
    max_reg2 = (ftell(arq2)-16000)/32;
    rewind(arq2);
    /*Busca a quantidade de registros existentes*/
    fseek(arq2, 1, SEEK_CUR);
    fread(&qtd_reg, sizeof(int), 1, arq2);
    num_regpag = 16000/32;

    /*Variáveis vetor para salvar registros e rrns*/
    Registro_de_Indice reg_ind[max_reg2];
    Registro_de_Indice insere_reg[5000];
    int salva_reg[max_reg2];
    for(int i =0; i<max_reg2; i++){
        salva_reg[i] = no_reg;
    }

    /*Zera os campos para evitar sobreposição errada*/

    reseta_campindice(&ler_reg);
    reseta_campos(&pega_reg);
    conta_pagind++;

    /*Lê o arquivo de indice e passa tudo para um vetor em ram*/
    if(max_reg2 !=0){
        while(contador < max_reg2){
            fseek(arq2, 16000+cont, SEEK_SET);
            /*Leitura de um registro*/
            le_regindice(arq2, &ler_reg);
            strcpy(reg_ind[contador2].chaveBusca, ler_reg.chaveBusca);
            reg_ind[contador2].RRN = ler_reg.RRN;
            contador2++;
            if(contador%num_regpag == 0){
                conta_pagind++; /*Incriementa numero de páginas*/
            }
            /*Incrementa os contadores e zera os campos para evitar sobreposições erradas*/
            cont += 32;
            contador++;
            reseta_campindice(&ler_reg);
        }
        contador = 0;
        cont = 0;
    }

    /*Loop para adicionar os registros e salvar as informações. Os valores dos campos já são passados na funcionalidade 6 de inserção*/
    do{
        Add_reg(arq1, &ler_campo, &ler_reg);
        if(strcmp(ler_reg.chaveBusca, "") != 0){ /*Se a chave for diferente de NULO*/
            strcpy(insere_reg[contador3].chaveBusca, ler_reg.chaveBusca);
            insere_reg[contador3].RRN = ler_reg.RRN;
            soma_rrn++;
            contador3++;
        }
        /*Reseta os campos para evitar sobreposição errada*/
         reseta_campos(&ler_campo);
         reseta_campindice(&ler_reg);
        contador++;
    }while(contador < n);

    contador3 = 0;
    /*Seta o novo tamanho de vetor necessário e adiciona os valores anteriores e novos*/
    int novo_maxreg = max_reg2 + soma_rrn;
    Registro_de_Indice add_ind[novo_maxreg];

    /*Se tamanho do arquivo de indices !- 0, copia para vetor em RAM*/
    if(max_reg2 != 0){
        for(int i =0; i<max_reg2; i++){
            strcpy(add_ind[i].chaveBusca, reg_ind[i].chaveBusca);
            add_ind[i].RRN = reg_ind[i].RRN;
        }
    }
    contador3 = 0;
    /*Copia o registros adicionados*/
    for(int j = max_reg2; j< novo_maxreg; j++){
            strcpy(add_ind[j].chaveBusca, insere_reg[contador3].chaveBusca);
            add_ind[j].RRN = insere_reg[contador3].RRN;
            contador3++;
    }

    /*Ordena vetor de nomeEscola*/
    selecsortchar(add_ind, novo_maxreg);
    rewind(arq2);
    fseek(arq2, 16000, SEEK_CUR);
    /*Escreve os registros no arq2*/
    for(int i = 0; i<novo_maxreg; i++){
            strcpy(escola, add_ind[i].chaveBusca);
            tam_nome = strlen(escola);
            if(tam_nome > 23){
                tam_nome = 23; /*Como tamanho máixmo das chaves é 23, se for maior que isso, seta em 23*/
            }
                fwrite(&add_ind[i].chaveBusca, sizeof(char), tam_nome, arq2); /*Escreve a chave*/
                fwrite(&fim_string, sizeof(char), 1, arq2); /*\0*/
                for(int j = 0; j < 27-tam_nome; j++){
                    fwrite(&preenche_fim, sizeof(char), 1, arq2); /*Preenche com @*/
                }
                fwrite(&add_ind[i].RRN, sizeof(int), 1, arq2); /*Escreve o rrn*/
    }
    qtd_regin = qtd_reg + soma_rrn; /*Seta a nova quantidade de registros*/
    rewind(arq2);
    fseek(arq2, 1, SEEK_CUR);
    fwrite(&qtd_regin, sizeof(int), 1, arq2); /*Escreve a nova quantidade de registros*/
}

/*Função referente à funcionalidade 15*/
void recupera_estat(FILE *arq1, FILE *arq2){
    int num_pagdisc3 = 0, num_pagdisc12 = 0, dif_pagdisc = 0, num_pagcab3 = 0, num_pagcab12 = 0; /*Variaveis para quantidade de páginas*/
    char opcao_campo[28], valor_campo[28]; /*Variaveis para pegar input de campo e chave*/
    scanf("%s", opcao_campo); /*input do campo*/
    if(strcmp(opcao_campo, "nomeEscola") == 0){
               getchar();
                scan_quote_string(valor_campo); /*Se for nomeEscola, input da chave*/
            }
    printf("*** Realizando a busca sem o auxílio de índice\n");
    /*saída funcionalidade 3*/
    Procura_Campo(arq1, opcao_campo, valor_campo, &num_pagdisc3);
    /*numero de páginas acessadas na func3*/
    printf("Número de páginas de disco acessadas: %d\n", num_pagdisc3);
    /*pular uma linha em branco*/
    printf("\n");
    printf("*** Realizando a busca com o auxílio de um índice secundário fortemente ligado\n");
    /*saída funcionalidade 12*/
    busca_indice(arq1, arq2, opcao_campo, valor_campo, &num_pagdisc12, &num_pagcab12);
    /*numero de páginas para carregar arquivo de indice*/
    printf("Número de páginas de disco para carregar o arquivo de índice: %d\n", num_pagcab12);
    /*numero de páginas para acessar arquivo de dados*/
    printf("Número de páginas de disco para acessar o arquivo de dados: %d\n", num_pagdisc12);
    /*calculo da diferença do número de páginas acessadas em disco*/
    dif_pagdisc = num_pagdisc3 - num_pagdisc12;
    /*pular uma linha em branco*/
    printf("\n");
    /*diferença numero de páginas de disco acessadas func3-acessardados*/
    printf("Diferença no número de páginas de disco acessadas: %d", dif_pagdisc);

}

/* Bibliotecas Utilizadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registros.h"

/*função que separa as strings em campos do arquivo csv*/
char* strtoke(char *str, const char *s)
{
  static char *start = NULL; /*variavel para marcar onde a nova string começa*/
  char *token = NULL; /* variavel para salvar a string separada*/
  /*seta o novo começo*/
  if (str){
        start = str;
  }
  /*verifica se há bytes não vistos para trás*/
  if (!start){
        return NULL;
  }
  /*seta o novo inicio*/
  token = start;
  /*encontra proxima ocorrência de s, o separador no arquivo csv*/
  start = strpbrk(start, s);
  /*se inicio, termina a string e começa a nova*/
  if (start){
        *start++ = '\0';
  }
  /* retorna a string separada*/
  return token;
}

/*Funcão utilizada para a funcionalidade 1*/
void LeArquivo(Reg_de_Dados conteudo, Reg_de_Cabecalho new_cab[], FILE *arq1, FILE *arq2){
    char *tmp;
    char fim_cab[1] = "@";
    char fim_stri[1] = "\0";
    char line[80], preenche[10], preenche_final[80];
    const char s[2] = ",";
    int cont_lin = 1;

            /* Cabeçalho se encontra na primeira pagina de disco, os demais registros da segunda em diante*/
            strcpy(new_cab->status, "1");

                    fwrite(&new_cab->status, sizeof(new_cab->status), 1, arq2);
                    fwrite(&new_cab->topoPilha, sizeof(new_cab->topoPilha), 1, arq2);
                    fwrite(&new_cab->tagCampo1, sizeof(new_cab->tagCampo1), 1, arq2);
                    fwrite(new_cab->desCampo1, sizeof(new_cab->desCampo1), 1, arq2);
                    fwrite(&new_cab->tagCampo2, sizeof(new_cab->tagCampo2), 1, arq2);
                    fwrite(new_cab->desCampo2, sizeof(new_cab->desCampo2), 1, arq2);
                    fwrite(&new_cab->tagCampo3, sizeof(new_cab->tagCampo3), 1, arq2);
                    fwrite(new_cab->desCampo3, sizeof(new_cab->desCampo3), 1, arq2);
                    fwrite(&new_cab->tagCampo4, sizeof(new_cab->tagCampo4), 1, arq2);
                    fwrite(new_cab->desCampo4, sizeof(new_cab->desCampo4), 1, arq2);
                    fwrite(&new_cab->tagCampo5, sizeof(new_cab->tagCampo5), 1, arq2);
                    fwrite(new_cab->desCampo5, sizeof(new_cab->desCampo5), 1, arq2);
                    /*completa o restante da primeira pagina com o @*/
                    for(int cont = 0; cont< 15715; cont++){
                        fwrite(&fim_cab, sizeof(char),1 ,arq2);
                    }
                    for (int j = 0; j<80; j++){
                        preenche_final[j] = '@';
                    }
			/*pega linha por linha do arquivo csv*/
            while (cont_lin <= 5000){

                fgets(line, sizeof(line), arq1);
                strcpy(conteudo.removido,"-");
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

                /*pega a data e verifica se é nula, caso sim, completa com @*/
                tmp = strtoke(NULL, s);
                if(strlen(tmp)){ /*se tamanho for diferente de 0, copia o char e passa pro arquivo*/
                    strcpy(conteudo.data,tmp);
                    fwrite(&conteudo.data, 10, 1, arq2);
                }
                else{ /*caso contrário, preenche um vetor de 10 posições e passa pro arquivo */
                   strcpy(conteudo.data, "@@@@@@@@@@");
                    conteudo.data[0] = '\0';
                     fwrite(conteudo.data, sizeof(char), 10, arq2);
                }

                /*Pega e aloca a cidade, o tamanho da string e a tag do campo*/
                tmp = strtoke(NULL, s);
                conteudo.tam1 = strlen(tmp);
                strcpy(conteudo.tagCampo4, "4");
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
                    strcpy(conteudo.tagCampo5, "5");
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
                        fwrite(conteudo.nomeEscola, sizeof(char), conteudo.tam2-2, arq2);
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
                    /*Zerando as variaveis que receberão os campos*/
                   conteudo.nroInscricao = 0;
                   conteudo.nota = 0;
                   memset(conteudo.data, 0, strlen(conteudo.data));
                   conteudo.tam1 = 0;
                   memset(conteudo.tagCampo4, 0, strlen(conteudo.tagCampo4));
                   memset(conteudo.cidade, 0, 25);
                   conteudo.tam2 = 0;
                   memset(conteudo.tagCampo5, 0, strlen(conteudo.tagCampo5));
                   memset(conteudo.nomeEscola, 0, 23);
                   cont_lin++;
            }

			/*Fecha os dois arquivos*/
            fclose(arq1);
            fclose(arq2);
            /*imprime em tela o nome do arquivo gerado*/
            printf("arquivoTrab1si.bin");
}

/*Funcão utilizada para a funcionalidade 2*/
void LerBin (FILE *arq2, Reg_de_Dados *new_data, Reg_de_Cabecalho *le_cab){
    int cont = 0, num_reg = 0;
    int num_pagdisc = 0;
    new_data->tam1 = 0;
    new_data->tam2 = 0;
    int pega_tag, pega_tag2, pega_tag3, pega_fim;
    char pega_end[1];
    int tam_arq, tam_pag; /*inteiro para o tamanho do arquivo*/
    int numero = 1;


    /*Encontra o tamanho total do arquivo acessado e utiliza rewind para "resetar' o ponteiro para o inicio do aruqivo novamente*/
    fseek(arq2, 0L, SEEK_END);
    tam_pag = ftell(arq2);
    tam_arq = (ftell(arq2)-16000)/80;
    rewind(arq2);

    /*Verifica o campo status do cabeçalho do arquivo, um arquivo escrito deve possuir 1, caso esteja como 0, o arquivo apresenta erro*/
    fread(&le_cab->status, sizeof(le_cab->status), 1, arq2);
        if(strcmp(le_cab->status, "0") == 0){
            printf("Falha no processamento do arquivo.");
            fclose(arq2);
            exit(0);
        }

    num_pagdisc++; /*Passou pela primeira pagina, a do registro de cabeçalho*/

	/*passa registro a registro lendo a informação, passando para um registro e imprimindo na tela, verificando se é nulo ou não*/
    do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*le todos os dados com o tamanho das variaveis e imprime na tela*/
            fread(&new_data->removido, sizeof(char), 1, arq2);
            fread(&new_data->encadeamento, sizeof(int), 1, arq2);
            fread(&new_data->nroInscricao, sizeof(int), 1, arq2);
            printf("%d", new_data->nroInscricao);
            fread(&new_data->nota, sizeof(double), 1, arq2);
            if(new_data->nota != -1){
                    printf(" %.1f", new_data->nota);
                    }
            fread(&pega_tag2, sizeof(int),1,arq2);
            fseek(arq2, -4, SEEK_CUR);
             fread(&new_data->data,sizeof(char), 10, arq2);
            if(pega_tag2 != 1077952512){
                printf(" %s", new_data->data);
            }
            fread(&pega_tag3, sizeof(int),1,arq2);
            fseek(arq2, -4, SEEK_CUR);
            if(pega_tag3 != 1077952576 && pega_tag3 != 1077952510){
                fread(&new_data->tam1, sizeof(int), 1, arq2);
                fread(&new_data->tagCampo4, sizeof(char), 1, arq2);
                fread(&new_data->cidade, sizeof(char), new_data->tam1-2, arq2);
                printf(" %d ", new_data->tam1-2);
                printf("%s ", new_data->cidade);
                getc(arq2);
            }
            fread(&pega_tag, sizeof(int),1,arq2);
            fseek(arq2, -4, SEEK_CUR);
            if(pega_tag != 1077952576 ){
                 fread(&new_data->tam2, sizeof(int), 1, arq2);
                 fread(&new_data->tagCampo5, sizeof(char),1, arq2);
                 fread(&new_data->nomeEscola, sizeof(char), new_data->tam2, arq2);
                 printf("%d ", new_data->tam2-2);
                 printf("%s", new_data->nomeEscola);
            }

          /*imprimindo todas as inforações ao verificar valor das tags*/
      /*      printf("%d", new_data->nroInscricao);
                    if(new_data->nota != -1){
                        printf(" %.1f", new_data->nota);
                    }
                    if(pega_tag2 != 1077952512){
                        printf(" %s", new_data->data);
                    }
                    if(pega_tag3 != 1077952576){
                        printf(" %d ", new_data->tam1-2);
                        printf("%s", new_data->cidade);
                    }
                    if(pega_tag != 1077952576  && pega_tag != 1397703712 && pega_tag != 1347242316 && pega_tag != 1179603536 && pega_tag != 1330782291
                       && pega_tag != 1397706829 && pega_tag != 1380271648 && pega_tag != 1312902738 && pega_tag != 1430738241 && pega_tag != 1077952512){
                        printf(" %d ", new_data->tam2-2);
                        printf("%s", new_data->nomeEscola);
                    }*/
                        printf("\n");
            /*incrementa o contador para próximo registro*/
            cont = cont + 80;
            /*incrementa o número de registros*/
            num_reg++;
            numero++;
            /* Considerando numero total de bytes por pagina e o numero de bytes de cada registro, pode-se calcular quantos registros existem por página e assim o número de páginas*/
            if(num_reg >= (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
                /*Zera as variáveis que receberão os campos, para não haver sobreposição de informações*/
                new_data->nroInscricao = 0;
                new_data->nota = 0;
                memset(new_data->data, 0, strlen(new_data->data));
                new_data->tam1 = 0;
                memset(new_data->tagCampo4, 0, strlen(new_data->tagCampo4));
                memset(new_data->cidade, 0, strlen(new_data->cidade));
                new_data->nota = 0;
                new_data->tam2 = 0;
                memset(new_data->tagCampo5, 0, strlen(new_data->tagCampo5));
                memset(new_data->nomeEscola, 0, strlen(new_data->nomeEscola));

        }while(cont < (tam_pag-16000));
        printf("Número de páginas de disco acessadas: %d",num_pagdisc); /*imprime número total de páginas acessadas*/
            /*reseta ponteiro para inicio do arquivo*/
            rewind(arq2);
            /*fecha o arquivo*/
            fclose(arq2);
}

/*Funcão utilizada para a funcionalidade 3 */
void Procura_Campo(FILE *arq2, Reg_de_Dados *ler_campo){
    char opcao_campo[33]; /*String para recolher a opção de campo do usuario*/
    char proc_data[10], proc_cidade[27], proc_nomeEscola[33]; /* strings para recolher o valor dentro da opção anterior*/
    int cont = 0,num_reg = 0, num_pagdisc = 0, proc_insc, reg_encontrado = 0; /*contadores utilizados*/
    int tam_arq, tam_pag; /*inteiro para o tamanho do arquivo*/
    double proc_nota; /*double para recolher o valor dentro da opção de campo*/
    int pega_tag, pega_tag2, pega_tag3;

    /*Encontra o tamanho total do arquivo acessado e utiliza rewind para "resetar' o ponteiro para o inicio do aruqivo novamente*/
    fseek(arq2, 0L, SEEK_END);
    tam_pag = ftell(arq2);
    tam_arq = (ftell(arq2)-16000)/80;
    rewind(arq2);

    /*pega a opção de campo*/
    scanf("%s", opcao_campo);

    /* Os if e else if abaixo representama  comparação do campo de entrada do usuario com o nome de cada campo do arquivo*/
    /*verifica a opção nroInscrição*/
    if(strcmp(opcao_campo, "nroInscricao") == 0){
        scanf("%d", &proc_insc);
        num_pagdisc = num_pagdisc +2;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressão de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(ler_campo->encadeamento), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(ler_campo->nroInscricao), 1, arq2);
            /*verifica a se a entrada é igual ao campo recolhido*/
            if(ler_campo->nroInscricao == proc_insc){
                printf("%d", ler_campo->nroInscricao);
                fread(&ler_campo->nota, sizeof(double), 1, arq2);
                if(ler_campo->nota != -1){
                    printf(" %.1f", ler_campo->nota);
                }

                fread(&ler_campo->data,sizeof(ler_campo->data), 1, arq2);
                if(ler_campo->data != NULL){
                    printf(" %s", ler_campo->data);
                }

                fread(&ler_campo->tam1, sizeof(ler_campo->tam1), 1, arq2);
                if(ler_campo->tam1 != 0){
                    printf(" %d", ler_campo->tam1-2);
                }
                fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                if(ler_campo->cidade != NULL){
                    printf(" %s", ler_campo->cidade);
                }
                if(getc(arq2) != 0){
                    fread(&ler_campo->tam2, sizeof(int), 1, arq2);
                    if(ler_campo->tam2 != 0){
                        printf(" %d", ler_campo->tam2-2);
                    }
                    fread(&ler_campo->tagCampo5, sizeof(char),1, arq2);
                    fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2);
                    if(ler_campo->nomeEscola != NULL){
                        printf(" %s\n", ler_campo->nomeEscola);
                    }
                }
                    printf("\n");
                    /*incrementa o número de registros encontrados*/
                    reg_encontrado++;
                    /*se encontrou uma vez, sai do loop, pois nroInscrição é um campo que não aceita repetições*/
                    break;
            }

             //Zera as variáveis que receberão os campos, para não haver sobreposição de informações
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   memset(ler_campo->tagCampo4, 0, strlen(ler_campo->tagCampo4));
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   memset(ler_campo->tagCampo5, 0, strlen(ler_campo->tagCampo5));
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));

            //incrementa o contador para próximo registro
            cont = cont + 80;
            if(num_reg >= (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont < (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se não encontrou registros retorna a mensagem*/
        }
        else{
        printf("Número de páginas de disco acessadas: %d",num_pagdisc); /*caso contrário imprime o númerdo de páginas acessadas*/
        }
    }
    /*verifica a opção nota*/
    else if(strcmp(opcao_campo, "nota") == 0){
        scanf("%lf", &proc_nota);
        num_pagdisc = num_pagdisc +2;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressão de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(ler_campo->encadeamento), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(ler_campo->nroInscricao), 1, arq2);
            fread(&ler_campo->nota, sizeof(double), 1, arq2);
            /*verifica a se a entrada é igual ao campo recolhido*/
            if(ler_campo->nota == proc_nota){
                    reg_encontrado++;
                    printf("%d", ler_campo->nroInscricao);
                    if(ler_campo->nota != -1){
                        printf(" %.1f", ler_campo->nota);
                    }

                    fread(&ler_campo->data,sizeof(ler_campo->data), 1, arq2);
                    if(ler_campo->data != NULL){
                        printf(" %s", ler_campo->data);
                    }
                    fread(&ler_campo->tam1, sizeof(ler_campo->tam1), 1, arq2);
                    if(ler_campo->tam1 != 0){
                        printf(" %d", ler_campo->tam1-2);
                    }
                    fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                    fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                    if(ler_campo->cidade != NULL){
                        printf(" %s", ler_campo->cidade);
                    }
                    getc(arq2);
                        fread(&ler_campo->tam2, sizeof(ler_campo->tam2), 1, arq2);
                        if(ler_campo->tam2 != 0){
                              printf(" %d", ler_campo->tam2-2);
                        }
                        fread(&ler_campo->tagCampo5, sizeof(ler_campo->tagCampo5),1, arq2);
                        fread(&ler_campo->nomeEscola, sizeof(ler_campo->nomeEscola), 1, arq2);
                        if(ler_campo->nomeEscola != NULL){
                            printf(" %s\n", ler_campo->nomeEscola);
                        }
                }
                //Zera as variáveis que receberão os campos, para não haver sobreposição de informações
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   memset(ler_campo->tagCampo4, 0, strlen(ler_campo->tagCampo4));
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   memset(ler_campo->tagCampo5, 0, strlen(ler_campo->tagCampo5));
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
            /*incrementa o contador para próximo registro*/
            cont+= 80;
            /*incrementa o número de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont <= (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se não encontrou registros retorna a mensagem*/
        }
         printf("Número de páginas de disco acessadas: %d",num_pagdisc); /*caso contrário imprime o númerdo de páginas acessadas*/
    }
    /*verifica a opção data*/
    else if(strcmp(opcao_campo, "data") == 0){
        scanf("%s", proc_data);
        num_pagdisc = num_pagdisc +2 ;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressão de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(ler_campo->encadeamento), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(ler_campo->nroInscricao), 1, arq2);
            fread(&ler_campo->nota, sizeof(double), 1, arq2);
            fread(&ler_campo->data,sizeof(ler_campo->data), 1, arq2);
            /*verifica a se a entrada é igual ao campo recolhido*/
                if(strcmp(ler_campo->data,proc_data)==0){
                        printf("%d", ler_campo->nroInscricao);
                        if(ler_campo->nota != -1){
                            printf(" %.1f", ler_campo->nota);
                        }
                        if(ler_campo->data != NULL){
                        printf(" %s", ler_campo->data);
                             }

                        fread(&ler_campo->tam1, sizeof(ler_campo->tam1), 1, arq2);
                        if(ler_campo->tam1 != 0){
                            printf(" %d", ler_campo->tam1-2);
                        }
                        fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                        fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                        if(ler_campo->cidade != NULL){
                            printf(" %s", ler_campo->cidade);
                        }
                        getc(arq2);
                            fread(&ler_campo->tam2, sizeof(ler_campo->tam2), 1, arq2);
                            if(ler_campo->tam2 != 0){
                                printf(" %d", ler_campo->tam2-2);
                            }
                            fread(&ler_campo->tagCampo5, sizeof(ler_campo->tagCampo5),1, arq2);
                            fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2);
                            if(ler_campo->nomeEscola != NULL){
                                printf(" %s\n", ler_campo->nomeEscola);
                            }
                            /*incrementa o número de registros encontrados*/
                            reg_encontrado++;
                        }
             //Zera as variáveis que receberão os campos, para não haver sobreposição de informações
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   memset(ler_campo->tagCampo4, 0, strlen(ler_campo->tagCampo4));
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   memset(ler_campo->tagCampo5, 0, strlen(ler_campo->tagCampo5));
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));

            cont+= 80;
            /*incrementa o número de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont <= (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se não encontrou registros retorna a mensagem*/
        }
        else{
        printf("Número de páginas de disco acessadas: %d",num_pagdisc); /*caso contrário imprime o númerdo de páginas acessadas*/
        }
    }
    /*verifica a opção cidade*/
    else if(strcmp(opcao_campo, "cidade") == 0){
        getchar();
        scanf("%[^\n]s", proc_cidade);
        num_pagdisc = num_pagdisc +2 ;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressão de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(ler_campo->encadeamento), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(ler_campo->nroInscricao), 1, arq2);
            fread(&ler_campo->nota, sizeof(double), 1, arq2);
            fread(&pega_tag2, sizeof(int),1,arq2);
            fseek(arq2, -4, SEEK_CUR);
            fread(&ler_campo->data,sizeof(char), 10, arq2);
            fread(&pega_tag3, sizeof(int),1,arq2);
            fseek(arq2, -4, SEEK_CUR);
            fread(&ler_campo->tam1, sizeof(int), 1, arq2);
            fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
            fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-1, arq2);
            fread(&pega_tag, sizeof(int),1,arq2);
            fseek(arq2, -4, SEEK_CUR);
            fread(&ler_campo->tam2, sizeof(int), 1, arq2);
            fread(&ler_campo->tagCampo5, sizeof(char),1, arq2);
            fread(&ler_campo->nomeEscola, sizeof(ler_campo->nomeEscola), 1, arq2);
            /*verifica a se a entrada é igual ao campo recolhido*/
             if(strcmp(ler_campo->cidade, proc_cidade)==0){
                    printf("%d", ler_campo->nroInscricao);
                    if(ler_campo->nota != -1){
                        printf(" %.1f", ler_campo->nota);
                    }
                    if(pega_tag2 != 1077952512){
                        printf(" %s", ler_campo->data);
                    }
                    if(ler_campo->tam1 != 0){
                        printf(" %d", ler_campo->tam1-2);
                    }
                    if(pega_tag3 != 1077952576){
                        printf(" %s", ler_campo->cidade);
                    }
                    if(pega_tag != 1077952576){
                        printf(" %d", ler_campo->tam2-2);
                        printf(" %s\n", ler_campo->nomeEscola);
                    }
                    else{
                        printf("\n");
                    }
                    /*incrementa o número de registros encontrados*/
                reg_encontrado++;
                        }
                    /*Zera as variáveis que receberão os campos, para não haver sobreposição de informações*/
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   memset(ler_campo->tagCampo4, 0, strlen(ler_campo->tagCampo4));
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   memset(ler_campo->tagCampo5, 0, strlen(ler_campo->tagCampo5));
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
                /*incrementa o número de registros*/
            cont+= 80;
            /*incrementa o número de registros*/
            num_reg++;
             if(num_reg > 16000/80){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont <= (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se não encontrou registros retorna a mensagem*/
        }
        else{
         printf("Número de páginas de disco acessadas: %d",num_pagdisc); /*caso contrário imprime o númerdo de páginas acessadas*/
        }
    }
    /*verifica a opção NomeEscola*/
    else if(strcmp(opcao_campo, "nomeEscola") == 0){
        getchar();
        scanf("%[^\n]s", proc_nomeEscola);
        num_pagdisc = num_pagdisc +2 ;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressão de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(ler_campo->encadeamento), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(ler_campo->nroInscricao), 1, arq2);
            fread(&ler_campo->nota, sizeof(double), 1, arq2);
            fread(&ler_campo->data,sizeof(ler_campo->data), 1, arq2);
            fread(&ler_campo->tam1, sizeof(ler_campo->tam1), 1, arq2);
            fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
            fread(&ler_campo->cidade, sizeof(char), 9, arq2);
            getc(arq2);
            fread(&ler_campo->tam2, sizeof(ler_campo->tam2), 1, arq2);
            fread(&ler_campo->tagCampo5, sizeof(ler_campo->tagCampo5),1, arq2);
            fread(&ler_campo->nomeEscola, sizeof(ler_campo->nomeEscola), 1, arq2);
            /*verifica a se a entrada é igual ao campo recolhido*/
            if(strcmp(ler_campo->nomeEscola, proc_nomeEscola)==0){
                    printf("%d", ler_campo->nroInscricao);
            if(ler_campo->nota != -1){
                    printf(" %.1f", ler_campo->nota);
            }
            if(ler_campo->data != NULL){
                    printf(" %s", ler_campo->data);
            }
            if(ler_campo->tam1 != 0){
                    printf(" %d", ler_campo->tam1-2);
            }
            if(ler_campo->cidade != NULL){
                    printf(" %s", ler_campo->cidade);
            }
            if(ler_campo->tam2 != 0){
                    printf(" %d", ler_campo->tam2-2);
            }
            if(ler_campo->nomeEscola != NULL){
                    printf(" %s\n", ler_campo->nomeEscola);
            }
            /*incrementa o número de registros encontrados*/
                    reg_encontrado++;
            }

             //Zera as variáveis que receberão os campos, para não haver sobreposição de informações
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   memset(ler_campo->tagCampo4, 0, strlen(ler_campo->tagCampo4));
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   memset(ler_campo->tagCampo5, 0, strlen(ler_campo->tagCampo5));
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));

            cont+= 80;
            /*incrementa o número de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont <= (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se não encontrou registros retorna a mensagem*/
        }
        else{
        printf("Número de páginas de disco acessadas: %d",num_pagdisc); /*caso contrário imprime o númerdo de páginas acessadas*/
        }
    }
    /*reseta o ponteiro do arquivo para o inicio*/
    rewind(arq2);
    /*fecha o arquivo*/
    fclose(arq2);
}

/*Funcão utilizada para a funcionalidade 3 */
void LerRRN(FILE *arq2, Reg_de_Dados *ler_rrn){
    int rrn = 0, boset,tam_arq, num_pag = 0;

    scanf("%d", &rrn); /*pega o rrn que usuario deseja buscar*/
            boset = rrn * 80; /* 80 é o tamanho fixo do registro*/
            fseek(arq2, 0L, SEEK_END);
            tam_arq = (ftell(arq2)-16000)/80;
            rewind(arq2);
            if(rrn > tam_arq){
                printf("Registro inexistente.");
            }
            else{
                fseek(arq2, 16000 + boset, SEEK_SET); /*seta ponteiro para a primeira linha do registro de dados desejada.*/
                num_pag++; /*Passou pela pagina de cabeçalho*/
                int localizacao = ftell(arq2); /*verifica em qual byte se encontra*/

                /*le o arquivo e imprime na tela a linha (campo a campo) pedida pelo usuario*/
                fread(&ler_rrn->removido, sizeof(char), 1, arq2);
                fread(&ler_rrn->encadeamento, sizeof(ler_rrn->encadeamento), 1, arq2);
                fread(&ler_rrn->nroInscricao, sizeof(ler_rrn->nroInscricao), 1, arq2);
                printf("%d ", ler_rrn->nroInscricao);
                fread(&ler_rrn->nota, sizeof(double), 1, arq2);
                if(ler_rrn->nota != -1){
                    printf("%.1f ", ler_rrn->nota);
                }

                fread(&ler_rrn->data,sizeof(ler_rrn->data), 1, arq2);
                if(ler_rrn->data != NULL){
                    printf("%s ", ler_rrn->data);
                }

                fread(&ler_rrn->tam1, sizeof(ler_rrn->tam1), 1, arq2);
                if(ler_rrn->tam1 != 0){
                    printf("%d ", ler_rrn->tam1-2);
                }
                fread(&ler_rrn->tagCampo4, sizeof(char), 1, arq2);
                fread(&ler_rrn->cidade, sizeof(char), ler_rrn->tam1-2, arq2);
                if(ler_rrn->cidade != NULL){
                    printf("%s ", ler_rrn->cidade);
                }
                getc(arq2);
                fread(&ler_rrn->tam2, sizeof(ler_rrn->tam2), 1, arq2);
                fread(&ler_rrn->tagCampo5, sizeof(ler_rrn->tagCampo5),1, arq2);
                if(strcmp(ler_rrn->tagCampo5, "5") == 0){
                    printf("%d ", ler_rrn->tam2-2);
                    fread(&ler_rrn->nomeEscola, sizeof(char), ler_rrn->tam2-2, arq2);
                    if(ler_rrn->nomeEscola != NULL){
                        printf("%s\n", ler_rrn->nomeEscola);
                    }
                }
                else{
                    printf("\n");
                }
                if(ferror(arq2)){
                    perror("Falha no processamento do arquivo.\n"); /*verifica se hovue algum erro ao processar o arquivo*/
                    fclose(arq2);
                    exit(0);
                }
                num_pag++;
                printf("Número de páginas de disco acessadas: %d",num_pag); /*imprime o númerdo de páginas acessadas*/
            }
            /*reseta o ponteiro do arquivo para o inicio*/
            rewind(arq2);
            /*fecha o arquivo*/
            fclose(arq2);
}

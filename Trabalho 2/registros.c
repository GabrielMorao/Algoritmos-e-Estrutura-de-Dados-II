/* Bibliotecas Utilizadas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "registros.h"

/*funÃ§Ã£o que separa as strings em campos do arquivo csv*/
char* strtoke(char *str, const char *s)
{
  static char *start = NULL; /*variavel para marcar onde a nova string comeÃ§a*/
  char *token = NULL; /* variavel para salvar a string separada*/
  /*seta o novo comeÃ§o*/
  if (str){
        start = str;
  }
  /*verifica se hÃ¡ bytes nÃ£o vistos para trÃ¡s*/
  if (!start){
        return NULL;
  }
  /*seta o novo inicio*/
  token = start;
  /*encontra proxima ocorrÃªncia de s, o separador no arquivo csv*/
  start = strpbrk(start, s);
  /*se inicio, termina a string e comeÃ§a a nova*/
  if (start){
        *start++ = '\0';
  }
  /* retorna a string separada*/
  return token;
}

/*FuncÃ£o utilizada para a funcionalidade 1*/
void LeArquivo(Reg_de_Dados conteudo, Reg_de_Cabecalho new_cab[], FILE *arq1, FILE *arq2){
    char *tmp;
    char fim_cab[1] = "@";
    char fim_stri[1] = "\0";
    char line[80], preenche_final[80];
    const char s[2] = ",";
    int cont_lin = 1;

            /* CabeÃ§alho se encontra na primeira pagina de disco, os demais registros da segunda em diante*/
            //strcpy(new_cab->status, "1");
            new_cab->status = '0';

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
            new_cab->status = '1';
            fwrite(&new_cab->status, sizeof(new_cab->status), 1, arq2);
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
void Procura_Campo(FILE *arq2, Reg_de_Dados *ler_campo){
    char opcao_campo[33]; /*String para recolher a opÃ§Ã£o de campo do usuario*/
    char proc_data[10], proc_cidade[27], proc_nomeEscola[33]; /* strings para recolher o valor dentro da opÃ§Ã£o anterior*/
    int cont = 0,num_reg = 0, num_pagdisc = 0, proc_insc, reg_encontrado = 0; /*contadores utilizados*/
    int tam_arq, tam_pag; /*inteiro para o tamanho do arquivo*/
    double proc_nota; /*double para recolher o valor dentro da opÃ§Ã£o de campo*/
    int pega_tag, pega_tag2, pega_tag3;

    /*Encontra o tamanho total do arquivo acessado e utiliza rewind para "resetar' o ponteiro para o inicio do aruqivo novamente*/
    fseek(arq2, 0L, SEEK_END);
    tam_pag = ftell(arq2);
    tam_arq = (ftell(arq2)-16000)/80;
    rewind(arq2);

    /*pega a opÃ§Ã£o de campo*/
    scanf("%s", opcao_campo);

    /* Os if e else if abaixo representama  comparaÃ§Ã£o do campo de entrada do usuario com o nome de cada campo do arquivo*/
    /*verifica a opÃ§Ã£o nroInscriÃ§Ã£o*/
    if(strcmp(opcao_campo, "nroInscricao") == 0){
        scanf("%d", &proc_insc);
        num_pagdisc = num_pagdisc +2;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
            /*verifica a se a entrada Ã© igual ao campo recolhido*/
            if(ler_campo->nroInscricao == proc_insc){
                printf("%d", ler_campo->nroInscricao);
                fread(&ler_campo->nota, sizeof(double), 1, arq2);
                if(ler_campo->nota != -1){
                    printf(" %.1f", ler_campo->nota);
                }

                fread(&ler_campo->data,sizeof(char), 10, arq2);
                if(strcmp(ler_campo->cidade, "")!=0){
                    printf(" %s", ler_campo->data);
                }

                fread(&ler_campo->tam1, sizeof(int), 1, arq2);
                if(ler_campo->tam1 != 0){
                    printf(" %d", ler_campo->tam1-2);
                }
                fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                if(strcmp(ler_campo->cidade, "")!=0){
                    printf(" %s", ler_campo->cidade);
                }
                if(getc(arq2) != 0){
                    fread(&ler_campo->tam2, sizeof(int), 1, arq2);
                    if(ler_campo->tam2 != 0){
                        printf(" %d", ler_campo->tam2-2);
                    }
                    fread(&ler_campo->tagCampo5, sizeof(char),1, arq2);
                    fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2);
                    if(strcmp(ler_campo->nomeEscola, "")!=0){
                        printf(" %s\n", ler_campo->nomeEscola);
                    }
                }
                    printf("\n");
                    /*incrementa o nÃºmero de registros encontrados*/
                    reg_encontrado++;
                    /*se encontrou uma vez, sai do loop, pois nroInscriÃ§Ã£o Ã© um campo que nÃ£o aceita repetiÃ§Ãµes*/
                    break;
            }

             //Zera as variÃ¡veis que receberÃ£o os campos, para nÃ£o haver sobreposiÃ§Ã£o de informaÃ§Ãµes
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   ler_campo->tagCampo4 = '0';
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   ler_campo->tagCampo5 = '0';
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));

            //incrementa o contador para prÃ³ximo registro
            cont = cont + 80;
            if(num_reg >= (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont < (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
        else{
        printf("NÃºmero de pÃ¡ginas de disco acessadas: %d",num_pagdisc); /*caso contrÃ¡rio imprime o nÃºmerdo de pÃ¡ginas acessadas*/
        }
    }
    /*verifica a opÃ§Ã£o nota*/
    else if(strcmp(opcao_campo, "nota") == 0){
        scanf("%lf", &proc_nota);
        num_pagdisc = num_pagdisc +2;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(ler_campo->encadeamento), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(ler_campo->nroInscricao), 1, arq2);
            fread(&ler_campo->nota, sizeof(double), 1, arq2);
            /*verifica a se a entrada Ã© igual ao campo recolhido*/
            if(ler_campo->nota == proc_nota){
                    reg_encontrado++;
                    printf("%d", ler_campo->nroInscricao);
                    if(ler_campo->nota != -1){
                        printf(" %.1f", ler_campo->nota);
                    }

                    fread(&ler_campo->data,sizeof(ler_campo->data), 1, arq2);
                    if(strcmp(ler_campo->data, "")!=0){
                        printf(" %s", ler_campo->data);
                    }
                    fread(&ler_campo->tam1, sizeof(ler_campo->tam1), 1, arq2);
                    if(ler_campo->tam1 != 0){
                        printf(" %d", ler_campo->tam1-2);
                    }
                    fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                    fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                    if(strcmp(ler_campo->cidade, "")!=0){
                        printf(" %s", ler_campo->cidade);
                    }
                    getc(arq2);
                        fread(&ler_campo->tam2, sizeof(ler_campo->tam2), 1, arq2);
                        if(ler_campo->tam2 != 0){
                              printf(" %d", ler_campo->tam2-2);
                        }
                        fread(&ler_campo->tagCampo5, sizeof(ler_campo->tagCampo5),1, arq2);
                        fread(&ler_campo->nomeEscola, sizeof(ler_campo->nomeEscola), 1, arq2);
                        if(strcmp(ler_campo->nomeEscola, "")!=0){
                            printf(" %s\n", ler_campo->nomeEscola);
                        }
                }
                //Zera as variÃ¡veis que receberÃ£o os campos, para nÃ£o haver sobreposiÃ§Ã£o de informaÃ§Ãµes
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   ler_campo->tagCampo4 = '0';
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   ler_campo->tagCampo5 = '0';
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
            /*incrementa o contador para prÃ³ximo registro*/
            cont+= 80;
            /*incrementa o nÃºmero de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont <= (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
         printf("NÃºmero de pÃ¡ginas de disco acessadas: %d",num_pagdisc); /*caso contrÃ¡rio imprime o nÃºmerdo de pÃ¡ginas acessadas*/
    }
    /*verifica a opÃ§Ã£o data*/
    else if(strcmp(opcao_campo, "data") == 0){
        scanf("%s", proc_data);
        num_pagdisc = num_pagdisc +2 ;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(ler_campo->encadeamento), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(ler_campo->nroInscricao), 1, arq2);
            fread(&ler_campo->nota, sizeof(double), 1, arq2);
            fread(&ler_campo->data,sizeof(ler_campo->data), 1, arq2);
            /*verifica a se a entrada Ã© igual ao campo recolhido*/
                if(strcmp(ler_campo->data,proc_data)==0){
                        printf("%d", ler_campo->nroInscricao);
                        if(ler_campo->nota != -1){
                            printf(" %.1f", ler_campo->nota);
                        }
                        if(strcmp(ler_campo->data, "")!=0){
                        printf(" %s", ler_campo->data);
                             }

                        fread(&ler_campo->tam1, sizeof(ler_campo->tam1), 1, arq2);
                        if(ler_campo->tam1 != 0){
                            printf(" %d", ler_campo->tam1-2);
                        }
                        fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
                        fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
                        if(strcmp(ler_campo->cidade, "")!=0){
                            printf(" %s", ler_campo->cidade);
                        }
                        getc(arq2);
                            fread(&ler_campo->tam2, sizeof(ler_campo->tam2), 1, arq2);
                            if(ler_campo->tam2 != 0){
                                printf(" %d", ler_campo->tam2-2);
                            }
                            fread(&ler_campo->tagCampo5, sizeof(ler_campo->tagCampo5),1, arq2);
                            fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2-2, arq2);
                            if(strcmp(ler_campo->nomeEscola, "")!=0){
                                printf(" %s\n", ler_campo->nomeEscola);
                            }
                            /*incrementa o nÃºmero de registros encontrados*/
                            reg_encontrado++;
                        }
             //Zera as variÃ¡veis que receberÃ£o os campos, para nÃ£o haver sobreposiÃ§Ã£o de informaÃ§Ãµes
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   ler_campo->tagCampo4 = '0';
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   ler_campo->tagCampo5 = '0';
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));

            cont+= 80;
            /*incrementa o nÃºmero de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont <= (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
        else{
        printf("NÃºmero de pÃ¡ginas de disco acessadas: %d",num_pagdisc); /*caso contrÃ¡rio imprime o nÃºmerdo de pÃ¡ginas acessadas*/
        }
    }
    /*verifica a opÃ§Ã£o cidade*/
    else if(strcmp(opcao_campo, "cidade") == 0){
        getchar();
        scanf("%[^\n]s", proc_cidade);
        num_pagdisc = num_pagdisc +2 ;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
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
            /*verifica a se a entrada Ã© igual ao campo recolhido*/
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
                    /*incrementa o nÃºmero de registros encontrados*/
                reg_encontrado++;
                        }
                    /*Zera as variÃ¡veis que receberÃ£o os campos, para nÃ£o haver sobreposiÃ§Ã£o de informaÃ§Ãµes*/
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   ler_campo->tagCampo4 = '0';
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   ler_campo->tagCampo5 = '0';
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));
                /*incrementa o nÃºmero de registros*/
            cont+= 80;
            /*incrementa o nÃºmero de registros*/
            num_reg++;
             if(num_reg > 16000/80){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont <= (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
        else{
         printf("NÃºmero de pÃ¡ginas de disco acessadas: %d",num_pagdisc); /*caso contrÃ¡rio imprime o nÃºmerdo de pÃ¡ginas acessadas*/
        }
    }
    /*verifica a opÃ§Ã£o NomeEscola*/
    else if(strcmp(opcao_campo, "nomeEscola") == 0){
        getchar();
        scanf("%[^\n]s", proc_nomeEscola);
        num_pagdisc = num_pagdisc +2 ;
        do{
            fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
            /*leitura e impressÃ£o de campos*/
            fread(&ler_campo->removido, sizeof(char), 1, arq2);
            fread(&ler_campo->encadeamento, sizeof(ler_campo->encadeamento), 1, arq2);
            fread(&ler_campo->nroInscricao, sizeof(ler_campo->nroInscricao), 1, arq2);
            fread(&ler_campo->nota, sizeof(double), 1, arq2);
            fread(&ler_campo->data,sizeof(ler_campo->data), 1, arq2);
            fread(&ler_campo->tam1, sizeof(ler_campo->tam1), 1, arq2);
            fread(&ler_campo->tagCampo4, sizeof(char), 1, arq2);
            fread(&ler_campo->cidade, sizeof(char), ler_campo->tam1-2, arq2);
            getc(arq2);
            fread(&ler_campo->tam2, sizeof(ler_campo->tam2), 1, arq2);
            fread(&ler_campo->tagCampo5, sizeof(ler_campo->tagCampo5),1, arq2);
            fread(&ler_campo->nomeEscola, sizeof(ler_campo->nomeEscola), ler_campo->tam1-2, arq2);
            /*verifica a se a entrada Ã© igual ao campo recolhido*/
            if(strcmp(ler_campo->nomeEscola, proc_nomeEscola)==0){
                    printf("%d", ler_campo->nroInscricao);
            if(ler_campo->nota != -1){
                    printf(" %.1f", ler_campo->nota);
            }
            if(strcmp(ler_campo->data, "")!=0){
                    printf(" %s", ler_campo->data);
            }
            if(ler_campo->tam1 != 0){
                    printf(" %d", ler_campo->tam1-2);
            }
            if(strcmp(ler_campo->cidade, "")!=0){
                    printf(" %s", ler_campo->cidade);
            }
            if(ler_campo->tam2 != 0){
                    printf(" %d", ler_campo->tam2-2);
            }
            if(strcmp(ler_campo->nomeEscola, "")!=0){
                    printf(" %s\n", ler_campo->nomeEscola);
            }
            /*incrementa o nÃºmero de registros encontrados*/
                    reg_encontrado++;
            }

             //Zera as variÃ¡veis que receberÃ£o os campos, para nÃ£o haver sobreposiÃ§Ã£o de informaÃ§Ãµes
                   ler_campo->nroInscricao = 0;
                   ler_campo->nota = 0;
                   memset(ler_campo->data, 0, strlen(ler_campo->data));
                   ler_campo->tam1 = 0;
                   ler_campo->tagCampo4 = '0';
                   memset(ler_campo->cidade, 0, strlen(ler_campo->cidade));
                   ler_campo->nota = 0;
                   ler_campo->tagCampo5 = '0';
                   memset(ler_campo->nomeEscola, 0, strlen(ler_campo->nomeEscola));

            cont+= 80;
            /*incrementa o nÃºmero de registros*/
            num_reg++;
             if(num_reg > (16000/80)){
                    num_reg = 0;
                    num_pagdisc++;
                }
        }while(cont <= (tam_pag-16000));
        if(reg_encontrado == 0){
            printf("Registro inexistente."); /*se nÃ£o encontrou registros retorna a mensagem*/
        }
        else{
        printf("NÃºmero de pÃ¡ginas de disco acessadas: %d",num_pagdisc); /*caso contrÃ¡rio imprime o nÃºmerdo de pÃ¡ginas acessadas*/
        }
    }
    /*reseta o ponteiro do arquivo para o inicio*/
    rewind(arq2);
    /*fecha o arquivo*/
    fclose(arq2);
}

/*FuncÃ£o utilizada para a funcionalidade 3 */
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
                printf("NÃºmero de pÃ¡ginas de disco acessadas: %d",num_pag); /*imprime o nÃºmerdo de pÃ¡ginas acessadas*/
            }
            /*fecha o arquivo*/
            fclose(arq2);
}


//////////////////////////////////  FUNCIONALIDADES DO TRABALHO 2 - REMOÇÃO, INSERÇÃO e ATUALIZAÇÃO !! //////////////////////////////////////////////////////////////////////////////////////////

/*Funcionalidade para remover do arquivo os registros que usuário deseja através do nome e valor de campo*/
void Remover_reg(FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *set_status, int n){
    int tam_arq, cont = 0, reg_encontrado = 0; /* variáveis que guardam tamanho do arquivo, contador para o fseek e quantas vezes foi encontrado um registro*/
    int tam_pag, salva_topo; /*variáveis que guardam tamanho de uma página e o valor que esta no topoPilha do cabeçalho*/
    char opcao_campo[20], valor_campo[25], preenche_final[80], stt = '0'; /*Variáveis de char para guardar a opção de campo, o valor que tal campo deve ser, @ para preencher fim do registro e o status do arquivo*/
    char proc_removido = '*', guarda_status; /*Variáveis de char para guardar char de reg removido, guardar o status atual do arquivo*/
    int num_vezes = 0, verifica_reg;/*numero de interaÃ§Ãµes a serem realizadas*/

    fread(&set_status->status, sizeof(char), 1, arq2); /*Ler o status do arquivo*/
    guarda_status = set_status->status; /*Guarda o status na variável designada*/
    rewind(arq2); /*Retorna ao inicio do arquivo*/

    for (int j = 0; j<80; j++){
        preenche_final[j] = '@'; /*Preenche o vetor de char com @ para finalização dos registros*/
    }

    /*Descobr o tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
     tam_arq = ftell(arq2);
    tam_pag= (ftell(arq2)-16000)/80;
    rewind(arq2);

    /*Atribui 0 ao status */
        set_status->status = '0';
        fseek(arq2, 0, SEEK_SET);
        fread(&set_status->status, sizeof(set_status->status), 1, arq2);
        fread(&set_status->topoPilha, sizeof(set_status->topoPilha), 1, arq2);
        salva_topo = (set_status->topoPilha);
        rewind(arq2);

    /*Inicia o processo de remoção*/
      do{
         getchar();
        scanf("%s", opcao_campo); /*pega a opção de campo que o usuário deseja buscar*/
        scan_quote_string(valor_campo); /*pega o valor de entrada do usuário, verifica se é NULO e remove aspas caso as tenha*/

        /*Caso o campo seja número de Inscrição*/
        if(strcmp(opcao_campo, "nroInscricao") == 0){
            do{
                int val_campo = atoi(valor_campo); /*passa a variável para int*/
                fseek(arq2, 16000+cont, SEEK_SET); /*a cada leitura seta para o inicio da proxima linha*/
                /*leitura e impressÃ£o de campos*/
                fread(&ler_campo->removido, sizeof(char), 1, arq2);
                if(ler_campo->removido != '*'){
                    fread(&ler_campo->encadeamento, sizeof(int), 1, arq2);
                    fread(&ler_campo->nroInscricao, sizeof(int), 1, arq2);
                    /*verifica a se a entrada Ã© igual ao campo recolhido*/
                    if(ler_campo->nroInscricao == val_campo){
                        rewind(arq2);
                        fseek(arq2, 16000+cont, SEEK_SET);
                        verifica_reg = (ftell(arq2)-16000)/80; /*Guarda a posição do registro*/
                        fwrite(&proc_removido, sizeof(char), 1 , arq2); /*Atualiza o campo removido com * */
                        fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                        fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                        reg_encontrado++; /*incrementa o numero de registros encontrados*/
                        rewind(arq2);
                        fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                        fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                        salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
                    }
                }
                cont += 80; /*Incrementa o contador erm 80 para ir para próxima linha*/
                ler_campo->nroInscricao = 0; /*zera o valor da variavel para evitar sobreposições erradas*/
            }while(reg_encontrado == 0); /*se encontrou uma vez, sai do loop, pois nroInscrição não um campo que não aceita repetições*/
            /*Se saiu do loop, zera o contador e o numero de registros encontrados para próxima busca*/
            reg_encontrado = 0;
            cont = 0;
        }
        /*Caso o campo seja Nota*/
        else if(strcmp(opcao_campo, "nota") == 0){
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
                        if(ler_campo->nota == val_campo){
                            rewind(arq2);
                            fseek(arq2, 16000+cont, SEEK_SET);
                            verifica_reg = (ftell(arq2)-16000)/80; /*Guarda a posição do registro*/
                            fwrite(&proc_removido, sizeof(char), 1 , arq2); /*Atualiza o campo removido com * */
                            fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                            fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                            rewind(arq2);
                            fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                            fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                            salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
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
        }
        /*Caso o campo seja Data*/
        else if(strcmp(opcao_campo, "data") == 0){
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
                            fwrite(&proc_removido, sizeof(char), 1 , arq2);  /*Atualiza o campo removido com * */
                            fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                            fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                            rewind(arq2);
                            fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                            fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                            salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
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
        }
        /*Caso o campo seja Cidade*/
        else if(strcmp(opcao_campo, "cidade") == 0){
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
                            fwrite(&proc_removido, sizeof(char), 1 , arq2);  /*Atualiza o campo removido com * */
                            fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                            fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                            rewind(arq2);
                            fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                            fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                            salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
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
        }
        /*Caso o campo seja nomeEscola*/
        else if(strcmp(opcao_campo, "nomeEscola") == 0){
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
                            fread(&ler_campo->nomeEscola, sizeof(char), ler_campo->tam2, arq2);
                        }
                        /*verifica a se a entrada Ã© igual ao campo recolhido*/
                        if(strcmp(ler_campo->nomeEscola, valor_campo)==0){
                            rewind(arq2);
                            fseek(arq2, 16000+cont, SEEK_SET);
                            verifica_reg = (ftell(arq2)-16000)/80; /*Guarda a posição do registro*/
                            fwrite(&proc_removido, sizeof(char), 1 , arq2);  /*Atualiza o campo removido com * */
                            fwrite(&salva_topo, sizeof(int), 1, arq2); /*Atualiza o campo encadeamento com o valor do topoPilha*/
                            fwrite(&preenche_final, sizeof(char), 75, arq2); /*Remove logicamente, preenchendo todo o registro com @*/
                            rewind(arq2);
                            fwrite(&stt, sizeof(char), 1, arq2); /*Certifica que o status continue 0*/
                            fwrite(&verifica_reg, sizeof(int), 1, arq2); /*Atualiza o campo topoPilha com a posição do registro removido*/
                            salva_topo = verifica_reg; /*Atualiza a variável que salva topoPilha para ser usada na próxima remoção*/
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
        }
        num_vezes++; /*Incrementa variável que verifica quantas vezes aconteceu a funcionalidade*/
      }while(num_vezes < n); /*Enquanto a variável contadora  for menor que o valor entrado pelo usuário*/

    rewind(arq2);
    /*Retorna o status do arquivo para 1, pois vai fechar*/
    set_status->status = '1';
    fwrite(&set_status->status, sizeof(set_status->status), 1, arq2);
    if(guarda_status == '0'){
        printf("Falha no processamento do arquivo."); /*Se o status original do arquivo for 0, ele apresenta erro e mensagem de falha é atribuida*/
        }
    else if(guarda_status == '1'){ /*Caso seja 1, o correto*/
        /*Chamada da função que imprime o aruivo binário em tela - fornecdi pelo docente e monitores/estagiários PAE*/
        binarioNaTela1(arq2);
    }
    /*fecha o arquivo*/
    fclose(arq2);
}


/*Funcionalidade para adicionar ao arquivo os registros que usuário deseja*/
void Add_reg(FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *set_status, int n){
    int cont = 0, reg_encontrado = 0, add_em = 0; /*Variáveis para contadores e salvar o byte - ao inves do rrn - do próximo local de registro para inserção*/
    int tam_arq, tam_pag, salva_topo; /*Variaveis de tamanho de arquivo e página além de uma para salvar valor do topoPilha*/
    char  preenche_final[80], stt = '0'; /*Variáveis para guardar @ para fim de registro*/
    char add_data[10], add_cidade[25], add_nomeEscola[23], add_tag4 = '4', add_tag5 = '5', ins_nota[25], ins_insc[25]; /*Variáveis para receber a entrada do usuário de valor de campo*/
    int add_nroinsc, add_encad = -1, add_tam1, add_tam2; /*Variaveis inteiras para os valores dos campos*/
    double add_nota; /*Variavel double para os valor do campo*/
    int num_vezes = 0; /*numero de interações a serem realizadas*/

    /*Seta o status do arquivo para 0 pois abriu e será utilizado*/
    set_status->status = '0';
    fwrite(&set_status->status, sizeof(set_status->status), 1, arq2);

    /*Preenche vetor de char com @ para preencher registros*/
    for (int j = 0; j<80; j++){
        preenche_final[j] = '@';
    }

    /*Verifica tamanho do arquivo e de uma página*/
    fseek(arq2, 0L, SEEK_END);
    tam_arq = ftell(arq2);
    tam_pag = (ftell(arq2)-16000)/80;
    rewind(arq2);

    /*Verifica o status do arquivo, se for diferente de 0 durante utilização, há algum erro*/
    fseek(arq2, 0, SEEK_SET);
        fread(&set_status->status, sizeof(set_status->status), 1, arq2);
        if(set_status->status == 1){
            printf("Falha no processamento do arquivo");
            exit(0);
        }
        /*Salva o primeiro valor do topoPilha, onde o primeiro espaço de registro pode ser adicionado*/
        fread(&set_status->topoPilha, sizeof(set_status->topoPilha), 1, arq2);
        salva_topo = (set_status->topoPilha);
        add_em = salva_topo*80;
        rewind(arq2);
        /*Começa as inserções*/
        do{
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
            num_vezes++;
            add_nroinsc = 0;
            add_nota = 0;
            memset(add_data, 0, strlen(ler_campo->data));
            add_tam1 = 0;
            add_tag4 = '4';
            memset(add_cidade, 0, strlen(add_cidade));
            add_tam2 = 0;
            add_tag5 = '5';
            memset(add_nomeEscola, 0, strlen(add_nomeEscola));
        }while(num_vezes < n); /*Verifica se já antingiu número de vezes que usuário pediu*/

        /*Atualiza status para 1 pois vai fechar o arquivo*/
    rewind(arq2);
    set_status->status = '1';
    fwrite(&set_status->status, sizeof(set_status->status), 1, arq2);
    /*Escreve o arquivo binário na tela*/
    binarioNaTela1(arq2);

    /*fecha o arquivo*/
    fclose(arq2);
}

/*Funcionalidade para atualizar os registros que usuário deseja*/
void Atualiza_reg(FILE *arq2, Reg_de_Dados *ler_campo, Reg_de_Cabecalho *set_status, int n){
    int rrn = 0, boset,tam_arq;
    int  tam_pag;
    char opcao_campo[12], atualizacao[25], preenche_final[80], fim_str = '\0';
    char proc_data[10], proc_cidade[25], proc_nomeEscola[23];
    int proc_insc;
    int num_vezes = 0; /*numero de interações a serem realizadas*/
    double proc_nota;

    /*Seta o status do arquivo para 0 pois abriu e será utilizado*/
    set_status->status = '0';
    fwrite(&set_status->status, sizeof(set_status->status), 1, arq2);

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
    do{
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
        num_vezes++; /*incrementa variavel de quantas vezes a funcionalidade rodou*/
    }while(num_vezes < n); /*verifica se já chegamos no valor de vezes dado pelo usuário*/

    /*Volta arquivo para inicio para alterar o status novamente para 1, pois o arquivo será fechado*/
    rewind(arq2);
    set_status->status = '1';
    fwrite(&set_status->status, sizeof(set_status->status), 1, arq2);
    /*Imprime o binário na tela*/
    binarioNaTela1(arq2);

    /*fecha o arquivo*/
    fclose(arq2);
}

void binarioNaTela1(FILE *ponteiroArquivoBinario) {

	/* Escolha essa funÃ§Ã£o se vocÃª ainda tem o ponteiro de arquivo 'FILE *' aberto.
	*  Lembrando que vocÃª tem que ter aberto ele no fopen para leitura tambÃ©m pra funcionar (exemplo: rb, rb+, wb+, ...) */

	unsigned char *mb;
	unsigned long i;
	size_t fl;
	fseek(ponteiroArquivoBinario, 0, SEEK_END);
	fl = ftell(ponteiroArquivoBinario);
	fseek(ponteiroArquivoBinario, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, ponteiroArquivoBinario);
	for(i = 0; i < fl; i += sizeof(unsigned char)) {
		printf("%02X ", mb[i]);
		if((i + 1) % 16 == 0)	printf("\n");
	}
	free(mb);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa funÃ§Ã£o para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada estÃ¡ da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings jÃ¡ alocadas str1 e str2 do seu programa, vocÃª faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaÃ§os, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler atÃ© o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tÃ¡ tentando ler uma string que nÃ£o tÃ¡ entre aspas! Fazer leitura normal %s entÃ£o...
		str[0] = R;
		scanf("%s", &str[1]);
	 }else { // EOF
		strcpy(str, "");
	}
}

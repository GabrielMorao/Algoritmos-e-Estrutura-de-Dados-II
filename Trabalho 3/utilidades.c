#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilidades.h"


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

/*Função que escreve o cabeçalho nos arquivos*/
void escreve_cab(Reg_de_Cabecalho new_cab, FILE *arq2){
    char fim_cab = '@';
     new_cab.status = '0';

                    fwrite(&new_cab.status, sizeof(new_cab.status), 1, arq2);
                    fwrite(&new_cab.topoPilha, sizeof(new_cab.topoPilha), 1, arq2);
                    fwrite(&new_cab.tagCampo1, sizeof(new_cab.tagCampo1), 1, arq2);
                    fwrite(new_cab.desCampo1, sizeof(new_cab.desCampo1), 1, arq2);
                    fwrite(&new_cab.tagCampo2, sizeof(new_cab.tagCampo2), 1, arq2);
                    fwrite(new_cab.desCampo2, sizeof(new_cab.desCampo2), 1, arq2);
                    fwrite(&new_cab.tagCampo3, sizeof(new_cab.tagCampo3), 1, arq2);
                    fwrite(new_cab.desCampo3, sizeof(new_cab.desCampo3), 1, arq2);
                    fwrite(&new_cab.tagCampo4, sizeof(new_cab.tagCampo4), 1, arq2);
                    fwrite(new_cab.desCampo4, sizeof(new_cab.desCampo4), 1, arq2);
                    fwrite(&new_cab.tagCampo5, sizeof(new_cab.tagCampo5), 1, arq2);
                    fwrite(new_cab.desCampo5, sizeof(new_cab.desCampo5), 1, arq2);
                    /*completa o restante da primeira pagina com o @*/
                    for(int cont = 0; cont< 15715; cont++){
                        fwrite(&fim_cab, sizeof(char),1 ,arq2);
                    }
}

/*Função parar zerar os campos e evitar sobreposições erradas*/
void reseta_campos(Reg_de_Dados *res_camp){
    res_camp->removido = '-';
    res_camp->encadeamento = 0;
    res_camp->nroInscricao = 0;
    res_camp->nota = 0;
    memset(res_camp->data, 0, 10);
    res_camp->tam1 = 0;
    res_camp->tagCampo4 = '0';
    memset(res_camp->cidade, 0, 25);
    res_camp->nota = 0;
    res_camp->tagCampo5 = '0';
    memset(res_camp->nomeEscola, 0, 25);
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
/*Função quicksorte para ordenação*/
void quick_sort(int *a, int lo, int hi){

    int r = (rand()%(hi-lo+1))+lo;
    int p = a[r];
    int i = lo;
    int j = hi;

    while(i <= j){
        while(a[i] < p){
            i++;
        }
        while(a[j] > p){
            j--;
        }
        if(j >= i){
            troca (a, i, j);
            i++;
            j--;
        }
    }

    if(lo < j){
        quick_sort(a, lo, j);
    }
    if (i<hi){
         quick_sort(a,i,hi);
    }
}

/*Função que realiza trocas durante o quicksort*/
void troca(int a[], int i, int j){
    int tmp;

    tmp = a[j];
    a[j] = a[i];
    a[i] = tmp;
}

/*Função para escrever o registro no arquivo*/
void escreve_registro(FILE *arquivo, Reg_de_Dados escreve_reg){
    char preenche_fim = '@';
    char fim_string = '\0';

    fwrite(&escreve_reg.removido, sizeof(char), 1, arquivo);
    fwrite(&escreve_reg.encadeamento, sizeof(int), 1, arquivo);
    fwrite(&escreve_reg.nroInscricao, sizeof(int), 1, arquivo);
    fwrite(&escreve_reg.nota, sizeof(double), 1, arquivo);
    fwrite(&escreve_reg.data, sizeof(char), 10, arquivo);
        if(escreve_reg.tagCampo4 == '4'){
            fwrite(&escreve_reg.tam1, sizeof(int), 1, arquivo);
            fwrite(&escreve_reg.tagCampo4, sizeof(char), 1, arquivo);
            fwrite(&escreve_reg.cidade, sizeof(char), escreve_reg.tam1-2, arquivo);
            fwrite(&fim_string, sizeof(char), 1, arquivo);
            if(escreve_reg.tagCampo5 == '5'){
                fwrite(&escreve_reg.tam2, sizeof(int), 1, arquivo);
                fwrite(&escreve_reg.tagCampo5, sizeof(char), 1, arquivo);
                fwrite(&escreve_reg.nomeEscola, sizeof(char), escreve_reg.tam2-2, arquivo);
                fwrite(&fim_string, sizeof(char), 1, arquivo);
                for(int i = 0; i<45-(escreve_reg.tam2)-(escreve_reg.tam1);i++){
                    fwrite(&preenche_fim, sizeof(char), 1, arquivo);
                }
            }
            else{
                for(int i = 0; i<49-(escreve_reg.tam1);i++){
                    fwrite(&preenche_fim, sizeof(char), 1, arquivo);
                }
            }
        }
        else if(escreve_reg.tagCampo4 == '5'){
            fwrite(&escreve_reg.tam2, sizeof(int), 1, arquivo);
            fwrite(&escreve_reg.tagCampo5, sizeof(char), 1, arquivo);
            fwrite(&escreve_reg.nomeEscola, sizeof(char), escreve_reg.tam2-2, arquivo);
            fwrite(&fim_string, sizeof(char), 1, arquivo);
            for(int i = 0; i<49-(escreve_reg.tam2);i++){
                fwrite(&preenche_fim, sizeof(char), 1, arquivo);
            }
        }
        else{
           for(int i = 0; i<53;i++){
                fwrite(&preenche_fim, sizeof(char), 1, arquivo);
            }
        }
}

/*Função que lê um registro (campo a campo) de um arquivo*/
void le_registro(FILE *arquivo, Reg_de_Dados *ler_reg){
    fread(&ler_reg->removido, sizeof(char), 1, arquivo);
    fread(&ler_reg->encadeamento, sizeof(int), 1, arquivo);
    fread(&ler_reg->nroInscricao, sizeof(int), 1, arquivo);
    fread(&ler_reg->nota, sizeof(double), 1, arquivo);
    fread(&ler_reg->data, sizeof(char), 10, arquivo);
    fread(&ler_reg->tam1, sizeof(int), 1, arquivo);
    fread(&ler_reg->tagCampo4, sizeof(char), 1, arquivo);
    if(ler_reg->tagCampo4 == '4'){
        fread(&ler_reg->cidade, sizeof(char), ler_reg->tam1-1, arquivo);
        fread(&ler_reg->tam2, sizeof(int), 1, arquivo);
        fread(&ler_reg->tagCampo5, sizeof(char), 1, arquivo);
        if(ler_reg->tagCampo5 == '5'){
            fread(&ler_reg->nomeEscola, sizeof(char), ler_reg->tam2-2, arquivo);
        }
    }
    else if(ler_reg->tagCampo4 == '5'){
        ler_reg->tam2 = ler_reg->tam1;
        ler_reg->tagCampo5 = ler_reg->tagCampo4;
        fread(&ler_reg->nomeEscola, sizeof(char), ler_reg->tam2-2, arquivo);
    }
}

/*Função que imprime um registro salvo em variável do tipo registro de dados*/
void imprime_reg(Reg_de_Dados ler_reg){

    if(ler_reg.nroInscricao != -1){
        printf("%d ", ler_reg.nroInscricao);
    }
    if(ler_reg.nota != -1){
        printf("%.1f ", ler_reg.nota);
    }
    if(strcmp(ler_reg.data, "@@@@@@@@@@")!=0){
        printf("%s ", ler_reg.data);
    }
    if(ler_reg.tagCampo4 == '4'){
        printf("%d ", ler_reg.tam1-2);
        printf("%s ", ler_reg.cidade);
        if(ler_reg.tagCampo5 == '5'){
            printf("%d ", ler_reg.tam2-2);
            printf("%s\n", ler_reg.nomeEscola);
        }
        else{
            printf("\n");
        }
    }
    else if(ler_reg.tagCampo4 == '5'){
        printf("%d ", ler_reg.tam2-2);
        printf("%s\n", ler_reg.nomeEscola);
    }
}

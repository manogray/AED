#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "patricia.h"

TPatricia* getPalavra(char *diretorio){
	TPatricia* BigTree = criarPatricia();
	TNodo* raizBigTree = BigTree->dadosPatricia;

	char Palavra[20];
	int contaLinha = 0;

	FILE* arquivo = fopen(diretorio,"r");
    if(arquivo != NULL){
        while((fgets(Palavra,sizeof(Palavra),arquivo)) != NULL){
            Palavra[strlen(Palavra)-1] = '\0';
            strcpy(Palavra,strupr(Palavra));
            contaLinha = contaLinha + 1;
            raizBigTree = BigTree->inserirPatricia(raizBigTree,Palavra,contaLinha,0);
        }
    }else{
        printf("\n\n Arquivo '%s' Não Encontrado !\n\n",diretorio);
    }
    fclose(arquivo);

	return BigTree;
}


int main(int argc, char** argv){

    if(argc == 1){
        printf("Sem parametros!");
        exit(1);
    }

    FILE* arquivo = fopen("../../saida.txt","w");

    TPatricia* MegaTree = getPalavra(argv[1]);
    TNodo* raizMegaTree = MegaTree->dadosPatricia;

    MegaTree->imprimirPatricia(raizMegaTree,arquivo);

    return 0;
}

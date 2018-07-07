#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavra.h"

//CRIA OS DADOS DE UM TPALAVRA USANDO UMA STRING
static TDadosPalavra *criarDadosPalavra(char palavra[]){
	TDadosPalavra *aloca = malloc(sizeof(TDadosPalavra));
	if(aloca != NULL) {
        strcpy(aloca->palavra,palavra);
	}
	return aloca;
}

//FUNCAO DE COMPARA PALAVRA
static short ComparaPalavra(TPalavra* P1, TPalavra* P2){
    TDadosPalavra* DadoPalavra1 = P1->dadosPalavra;
    TDadosPalavra* DadoPalavra2 = P2->dadosPalavra;
    return strcmp(DadoPalavra1->palavra,DadoPalavra2->palavra);
}

TPalavra *criarPalavra(char palavra[]){
	TPalavra *word = malloc(sizeof(TPalavra));
	if(word != NULL){
		word->dadosPalavra = criarDadosPalavra(palavra);
		word->compara = ComparaPalavra;
	}
	return word;
}

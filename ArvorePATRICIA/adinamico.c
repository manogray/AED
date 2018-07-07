#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adinamico.h"
#include "palavra.h"
#include "comparavel.h"

//CRIA OS DADOS DE UM ARRAY DINÂMICO COM TAMANHO INICIAL
static TDadosADI *criarDadosADI(int tamanho){
	TDadosADI *aloca = malloc(sizeof(TDadosADI));
	if(aloca!= NULL){
		aloca->tamanho = tamanho;
		aloca->ocupacao = 0;
		aloca->vetor = malloc(sizeof(void*)*tamanho);
	}
	return aloca;
}

static int buscarADI(TArrayDinamico *vet, void *elem){
	TDadosADI *dadosVet = vet->dadosADI;
	TComparavel *compara = elem;

	int indice=0;
	while ((indice<dadosVet->ocupacao) && (compara->compara(elem,dadosVet->vetor[indice])!=0) )
		indice++;

	return (indice==dadosVet->ocupacao?-1:indice);

}

static void inserirADI(TArrayDinamico *vet, void* elem){
	TDadosADI *dadosVet = vet->dadosADI;

    //Verifica se o vetor est� cheio, para redimension�-lo caso precise
	if (dadosVet->ocupacao == dadosVet->tamanho){
		dadosVet->vetor = realloc(dadosVet->vetor,sizeof(void*)*(2*dadosVet->tamanho));
		dadosVet->tamanho = 2*dadosVet->tamanho;
	}

	dadosVet->vetor[dadosVet->ocupacao] = elem;
	dadosVet->ocupacao += 1;
};

static void* removerADI(TArrayDinamico *vet, void *procurado){
	TDadosADI *dadosVet = vet->dadosADI;

	int indice=buscarADI(vet,procurado);
	void *elem = NULL;
	if (indice!=-1){
		elem = dadosVet->vetor[indice];
		for(;indice<dadosVet->ocupacao;indice++)
			dadosVet->vetor[indice]=dadosVet->vetor[indice+1];
		dadosVet->ocupacao--;
	}

	return elem;
}

static void DestroiADI(TArrayDinamico* vet) {
    vet->ordenar = NULL;
    vet->inserir = NULL;
    vet ->buscar = NULL;
    vet->remover = NULL;
    vet->dadosADI = NULL;
    free(vet);
}


TArrayDinamico *criarADI(int tamanhoInicial){
	TArrayDinamico *adi = malloc(sizeof(TArrayDinamico));
	if(adi != NULL){
		adi->dadosADI = criarDadosADI(tamanhoInicial);
		adi->inserir = inserirADI;
		adi->buscar = buscarADI;
		adi->remover=removerADI;
		adi->ordenar=ordenarADI;
		adi->destruir=DestroiADI;
	}
	return adi;
}

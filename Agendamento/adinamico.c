#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adinamico.h"
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


static void inserirADI(TArrayDinamico *vet, void* elem){
	TDadosADI *dadosVet = vet->dadosADI;

    //Verifica se o vetor está cheio, para redimensioná-lo caso precise
	if (dadosVet->ocupacao == dadosVet->tamanho){
		dadosVet->vetor = realloc(dadosVet->vetor,sizeof(void*)*(2*dadosVet->tamanho));
		dadosVet->tamanho = 2*dadosVet->tamanho;
	}

	dadosVet->vetor[dadosVet->ocupacao] = elem;
	dadosVet->ocupacao += 1;
}

static void inserirADIposicao(TArrayDinamico* vet, void* elem, int posicao){
	TDadosADI* dadoVet = vet->dadosADI;

	if(dadoVet->vetor[posicao] == NULL){
		dadoVet->vetor[posicao] = elem;
		dadoVet->ocupacao += 1;
	}else{
		printf("\n\nHorario ocupado. Digite outro por favor: ");
		setbuf(stdin,NULL);
		scanf("%d",&posicao);
		inserirADIposicao(vet,elem,posicao);
	}
}

static int buscarADI(TArrayDinamico *vet, void *elem){
	TDadosADI *dadosVet = vet->dadosADI;
	TComparavel *compara = elem;

	int indice=0;
	while ((indice<dadosVet->ocupacao) && (compara->compara(elem,dadosVet->vetor[indice])!=0) )
		indice++;

	return (indice==dadosVet->ocupacao?-1:indice);

}

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
		adi->inserirposicao = inserirADIposicao;
		adi->buscar = buscarADI;
		adi->remover=removerADI;
		adi->destruir=DestroiADI;
	}
	return adi;
}

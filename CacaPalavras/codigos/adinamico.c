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

//FUNCAO QUE SEPARA OS ELEMENTOS MENORES QUE UM PIVÔ À ESQUERDA E OS MAIORES À DIREITA
static int separa (TArrayDinamico* vetor, int primeiro, int ultimo) {
   char c[200];
   TDadosADI* dadoVetor = vetor->dadosADI;
   TPalavra* elem1 = dadoVetor->vetor[primeiro];
   TDadosPalavra* dadosElem1 = elem1->dadosPalavra;
   strcpy(c,dadosElem1->palavra);
   int i = primeiro+1;
   int j = ultimo;
   char t[200];
   while (i <= j) {
        TPalavra* elementoI = dadoVetor->vetor[i];
        TDadosPalavra* dadoElementoI = elementoI->dadosPalavra;
        TPalavra* elementoJ = dadoVetor->vetor[j];
        TDadosPalavra* dadoElementoJ = elementoJ->dadosPalavra;
      if(strcmp(dadoElementoI->palavra,c) <= 0) {
          i += 1;
      }else if(strcmp(c,dadoElementoJ->palavra) < 0) {
          j -= 1;
      }else {
         strcpy(t,dadoElementoI->palavra);
         strcpy(dadoElementoI->palavra,dadoElementoJ->palavra);
         strcpy(dadoElementoJ->palavra,t);
         i += 1;
         j -= 1;
      }
   }
    TPalavra* elementoJ = dadoVetor->vetor[j];
    TDadosPalavra* dadoElementoJ = elementoJ->dadosPalavra;
    strcpy(dadosElem1->palavra,dadoElementoJ->palavra);
    strcpy(dadoElementoJ->palavra,c);
    return j;
}

//FUNCAO DE ORDENAÇÃO QUICKSORT
void quicksort (TArrayDinamico* vet, int primeiro, int ultimo) {
   int j;
   if (primeiro < ultimo) {
      j = separa (vet, primeiro, ultimo);
      quicksort (vet, primeiro, j-1);
      quicksort (vet, j+1, ultimo);
   }
}

static void ordenarADI (TArrayDinamico* vet,int primeiro) {
    TDadosADI* dadoVet = vet->dadosADI;

    quicksort(vet,primeiro,dadoVet->ocupacao-1);
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

    //Verifica se o vetor está cheio, para redimensioná-lo caso precise
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

#include <stdio.h>
#include <stdlib.h>
#include "palavra.h"
#include "Encadeada.h"
#include "DDinamico.h"
#include "adinamico.h"

static unsigned int FuncaoEspalhamento(char v[], int M) {
   int i;
   unsigned int h = v[0];
   for (i = 1; v[i] != '\0'; i++)
      h = (h * 251 + v[i]);

    unsigned int FINAL = (unsigned int) h%M;
   return FINAL;
}

static TDadoHash* criarDadoHash(int tamanho) {
	TDadoHash *aloca = malloc(sizeof(TDadoHash));
	if(aloca!= NULL){
		aloca->vetor = malloc(sizeof(void*)*tamanho);
		aloca->ocupacao = 0;
		aloca->tamanho = tamanho;
		aloca->entradas_usadas = 0;
		for(int i = 0; i < tamanho;i++)
            aloca->vetor[i] = CriarLista();
	}
	return aloca;
}

static void inserirnaHash(TDDinamico* Hash, void* Elem){
	TPalavra* Palavra = Elem;
	unsigned int i;
	TDadoHash* DadoHash = Hash->dadoHash;
	TDadoPalavra* DadoPalavra = Palavra->dadoPalavra;
	i = FuncaoEspalhamento(DadoPalavra->Palavra,DadoHash->tamanho);
	TDSemiDinamico* Lista = DadoHash->vetor[i];
	TDadoLista * DadoLista = Lista->dadoLista;
	if(DadoLista->Prim == NULL){
		DadoHash->entradas_usadas += 1;
	}
	Lista->inserir(Lista,Palavra);
	DadoHash->ocupacao += 1;
}

static void* buscarnaHash(TDDinamico* Hash, char Palavra[]){
	TDadoHash* DadoHash = Hash->dadoHash;
	TPalavra* PalavraN = criarPalavra(Palavra,1);
	TDadoPalavra* DadoPalavra = PalavraN->dadoPalavra;
	unsigned int i;
	i = FuncaoEspalhamento(DadoPalavra->Palavra,DadoHash->tamanho);
	TPalavra* NPalavra = NULL;
	if(DadoHash->vetor[i] != NULL){
		TDSemiDinamico * Lista = DadoHash->vetor[i];
		NPalavra = Lista->buscar(Lista,PalavraN);
	}

	return NPalavra;
}

static void RemoverHash(TDDinamico* Hash, char Palavra[]){
	TDadoHash* DadoHash = Hash->dadoHash;
	TPalavra* PalavraN = criarPalavra(Palavra,1);
	TDadoPalavra* DadoPalavra = PalavraN->dadoPalavra;
	unsigned int i;
	i = FuncaoEspalhamento(DadoPalavra->Palavra,DadoHash->tamanho);
	TPalavra* NPalavra = criarPalavra(Palavra,0);
	if(DadoHash->vetor[i] != NULL){
		TDSemiDinamico * Lista = DadoHash->vetor[i];
		Lista->remover(Lista,NPalavra);
		printf("\n\n A palavra %s foi removida do Indice\n\n",Palavra);
	}
}

static void DestroiHash(TDDinamico* Hash) {

    TDadoHash * DadoHash = Hash->dadoHash;
    Hash->buscar = NULL;
    Hash->inserir = NULL;
    Hash ->remover = NULL;
    for (int i = 0;i < DadoHash->tamanho;i++)
        DadoHash->vetor[i] = NULL;
    free(Hash);
}

TDDinamico* criarHash(int tamanho){
	TDDinamico* NovaHash = malloc(sizeof(TDDinamico));
	NovaHash->dadoHash = criarDadoHash(tamanho);
	NovaHash->inserir = inserirnaHash;
	NovaHash->buscar = buscarnaHash;
	NovaHash->remover = RemoverHash;
	NovaHash->destruir = DestroiHash;
	return NovaHash;
}

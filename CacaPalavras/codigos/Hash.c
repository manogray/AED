#include <stdio.h>
#include <stdlib.h>
#include "palavra.h"
#include "ABB.h"
#include "Hash.h"

//FUNCAO DE ESPALHAMENTO USADA NA HASH
static int FuncaoEspalhamento(char palavra[]) {
   int posicao = (int)palavra[0];
   posicao = posicao - 65;

   return posicao;
}

//CRIA OS DADOS DE UMA HASH
static TDadoHash* criarDadoHash(int tamanho) {
	TDadoHash *aloca = malloc(sizeof(TDadoHash));
	if(aloca!= NULL){
		aloca->vetor = malloc(sizeof(void*)*tamanho);
		aloca->ocupacao = 0;
		aloca->tamanho = tamanho;
		int indice = 0;
		while(indice < tamanho) {
            aloca->vetor[indice] = CriarABB();
            indice += 1;
		}
	}
	return aloca;
}

//INSERE UM ELEMENTO NA HASH
static void inserirnaHash(THash* Hash, void* Elem){
	TPalavra* Palavra = Elem;
	TDadoHash* DadoHash = Hash->dadoHash;
	TDadosPalavra* DadoPalavra = Palavra->dadosPalavra;
    int posicao = FuncaoEspalhamento(DadoPalavra->palavra);  //MAPEIA ELEMENTO PARA UMA POSIÇÃO DA HASH

	TABB* Arvore = DadoHash->vetor[posicao];
	TDadosABB* dadoArvore = Arvore->dadosABB;
	//A INSERE DA HASH CHAMA A FUNCAO INSERE DA ARVORE
	if(dadoArvore->Raiz == NULL) {
        dadoArvore->Raiz = Arvore->inserir(dadoArvore->Raiz,Elem);
	}else {
	    Arvore->inserir(dadoArvore->Raiz,Elem);
	}

	DadoHash->ocupacao += 1;
}

static void* buscarnaHash(THash* Hash, void* Elem){
	TDadoHash* DadoHash = Hash->dadoHash;
	TPalavra* palavra = Elem;
	TDadosPalavra* dadoPalavra = palavra->dadosPalavra;
	int posicao = FuncaoEspalhamento(dadoPalavra->palavra);
	TABB* arvore = DadoHash->vetor[posicao];
	TDadosABB* dadoArvore = arvore->dadosABB;

	return arvore->buscar(dadoArvore->Raiz,dadoPalavra->palavra);
}

static void DestroiHash(THash* Hash) {
    Hash->buscar = NULL;
    Hash->inserir = NULL;
    Hash->dadoHash = NULL;
    free(Hash);
}

THash* criarHash(int tamanho){
	THash* NovaHash = malloc(sizeof(THash));
	NovaHash->dadoHash = criarDadoHash(tamanho);
	NovaHash->inserir = inserirnaHash;
	NovaHash->buscar = buscarnaHash;
	NovaHash->destruir = DestroiHash;
	return NovaHash;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"

TDir* criarDirecionamento(int avanca, char compara){
    TDir* novoDir = malloc(sizeof(TDir));
    if(novoDir != NULL){
        novoDir->avanca = avanca;
        novoDir->compara = compara;
    }

    return novoDir;
}

TNoP* criarNo(char palavra[]){
    TNoP* novo = malloc(sizeof(TNoP));
    if(novo != NULL){
        novo->palavra = palavra;
        novo->filhoEsq = NULL;
        novo->filhoDir = NULL;
    }
}

TNoP* criarRaiz(int avanca, char compara, char palavra1[], char palavra2[]){
    TNoP* novo = malloc(sizeof(TNoP));
    if(novo != NULL){
        TDir* dd = criarDirecionamento(avanca, compara);
        novo->direcoes = dd;
        novo->palavra = NULL;
        if(palavra1[avanca] == compara){
            novo->filhoEsq = criarNo(palavra1);
            novo->filhoDir = criarNo(palavra2);
        }else {
            novo->filhoEsq = criarNo(palavra2);
            novo->filhoDir = criarNo(palavra1);
        }
    }

    return novo;
}

TDadosPat* criarDadosPatricia(){
    TDadosPat* dadPat = malloc(sizeof(TDadosPat));
    if(dadPat != NULL){
        dadosPat->ocupacao = 0;
        dadPat->Raiz = NULL;
    }

    return dadPat;
}

int retornaIndiceDiferente(char palavra1[], char palavra2[]){
    int contador = 0;
    while(palavra1[contador] == palavra2[contador]){
        contador = contador + 1;
    }

    return contador;
}

char menorChar(char palavra1[], char palavra2[], int indice){

    char resposta;

    if(palavra1[indice] < palavra2[indice]){
        resposta = palavra1[indice];
    }else {
        resposta = palavra2[indice];
    }

    return resposta;
}

void InsereVazia(TPatricia* arvore, char palavra1[], char palavra2[]){
    int ind;
    char comp;

    TDadosPat* dadoArvore = arvore->dadosPat;
    ind = retornaIndiceDiferente(palavra1,palavra2);
    ind = ind + 1;
    comp = menorChar(palavra1,palavra2,ind);
    dadoArvore->Raiz = criarRaiz(ind,comp,palavra1,palavra2);
    dadoArvore->ocupacao = 2;

}

TNoP* BuscaPat(TNoP* raiz, char palavra[], int apontador){

	 if(raiz == NULL){
    	 return raiz;
     }else{
    	if(raiz->direcoes != NULL){
    		TDir* dir = raiz->direcoes;
            apontador = apontador + dir->avanca;
            if(palavra[apontador] <= dir->compara){
                return BuscaPat(raiz->filhoEsq,palavra,apontador);
            }else{
                return BuscaPat(raiz->filhoDir,palavra,apontador);
            }
    	}else{
    		char* word = raiz->palavra;
    		if(strcmp(word,palavra) == 0){
    			return raiz;
    		}else{
    			return NULL;
    		}
    	}
     }
}

void InsereNormal(TNoP* raiz, char palavra[]){


}

TPatricia* criarPatricia(){
    TPatricia* novaArvore = malloc(sizeof(TPatricia));
    if(novaArvore != NULL){
        novaArvore->dadosPat = criarDadosPatricia();
        novaArvore->inserirVazia = InsereVazia;
        novaArvore->inserirNormal = InsereNormal;
        novaArvore->remover = RemovePat;
        novaArvore->buscar = BuscaPat;
    }

    return novaArvore;
}

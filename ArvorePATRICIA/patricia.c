#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patricia.h"

static TNodo* criarDadosPatricia(char caractere,int incrementador,char palavra[20],int linha){
	TNodo* aloca = malloc(sizeof(TNodo));
	if(aloca != NULL){
		aloca->caractere = caractere;
		aloca->incrementador = incrementador;
		strcpy(aloca->palavra,palavra);
		aloca->linha = linha;
		aloca->esquerda = NULL;
		aloca->direita = NULL;
	}

	return aloca;
}

static int comparaPalavra(char palavra1[20], char palavra2[20]){
    int contador = 0;
    while(contador < 20){
        if(palavra1[contador]!=palavra2[contador]){
            return contador;
        }
        contador = contador + 1;
    }

    return contador;
}

static TNodo* inserePatricia(TNodo* raiz, char inserido[20], int linha, int incrementador){
    int comparador = strcmp(raiz->palavra,inserido);
    if(raiz == NULL){
        raiz = criarDadosPatricia('%',-1,inserido,linha);
        return raiz;
    }else{
        if((strcmp(raiz->palavra,"%%%") != 0) && (comparador != 0)){
            int posicaoDiferente = comparaPalavra(raiz->palavra,inserido);
            int diferencaPosicao = posicaoDiferente - incrementador;

            if(comparador < 0){
                raiz->esquerda = criarDadosPatricia('%',-1,raiz->palavra,raiz->linha);
                raiz->direita = criarDadosPatricia('%',-1,inserido,linha);
                raiz->linha = 0;
                raiz->caractere = raiz->palavra[posicaoDiferente];
                raiz->incrementador = diferencaPosicao;
                strcpy(raiz->palavra,"%%%");
                return raiz;
            }else{
                raiz->direita = criarDadosPatricia('%',-1,raiz->palavra,raiz->linha);
                raiz->esquerda = criarDadosPatricia('%',-1,inserido,linha);
                raiz->linha = 0;
                raiz->caractere = inserido[posicaoDiferente];
                raiz->incrementador = diferencaPosicao;
                strcpy(raiz->palavra,"%%%");
                return raiz;
            }
        }else{
            if((inserido[incrementador + raiz->incrementador] < raiz->palavra[incrementador + raiz->incrementador]) || (inserido[incrementador + raiz->incrementador] == raiz->palavra[incrementador + raiz->incrementador])){
                raiz = inserePatricia(raiz->esquerda,inserido,linha,incrementador+raiz->incrementador);
                return raiz;
            }else{
                raiz = inserePatricia(raiz->direita,inserido,linha,incrementador+raiz->incrementador);
                return raiz;
            }
        }
    }
    return raiz;
}

static void imprimePatricia(TNodo* raiz, FILE* arquivo){
    if(raiz != NULL){
        imprimePatricia(raiz->esquerda,arquivo);
        if((raiz->esquerda == NULL) &&(raiz->direita == NULL)){
            fprintf(arquivo,"%s -- linha %d\n",raiz->palavra,raiz->linha);
        }
        imprimePatricia(raiz->direita,arquivo);
    }
}

TPatricia* criarPatricia(){
    TPatricia* arvore = malloc(sizeof(TPatricia));
    if(arvore!=NULL){
        arvore->dadosPatricia = NULL;
        arvore->inserirPatricia = inserePatricia;
        arvore->imprimirPatricia = imprimePatricia;
    }

    return arvore;
}

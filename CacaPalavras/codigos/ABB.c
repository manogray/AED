#include <stdio.h>
#include <stdlib.h>
#include "ABB.h"
#include "comparavel.h"
#include "palavra.h"
#include "string.h"

//CRIA ELEMENTO DO TIPO NÓ
TNo* criarNo(void* elem){
    TNo* NovoNo = malloc(sizeof(TNo));
    NovoNo->dadoNo = elem;
    NovoNo->filhoDireito = NULL;
    NovoNo->filhoEsquerdo = NULL;
    return NovoNo;
}

//CRIA OS DADOS DE UMA ÁRVORE BINÁRIA DE BUSCA
TDadosABB* criarDadosABB(){
    TDadosABB* dadoArvore = malloc(sizeof(TDadosABB));
    dadoArvore->Raiz = NULL;
    return dadoArvore;
}

//IMPRIME ABB DE FORMA CRESCENTE
static void ImprimeABBOrdenado(TNo* raiz,FILE *arquivo) {

    if(raiz != NULL) {
        TPalavra* palavra = raiz->dadoNo;
        TDadosPalavra* dadoPalavra = palavra->dadosPalavra;
        ImprimeABBOrdenado(raiz->filhoEsquerdo,arquivo);
        fprintf(arquivo,"%s - [%d][%d] %c\n",dadoPalavra->palavra,dadoPalavra->linha,dadoPalavra->coluna,dadoPalavra->orientacao);
        printf("%s - [%d][%d] %c\n",dadoPalavra->palavra,dadoPalavra->linha,dadoPalavra->coluna,dadoPalavra->orientacao);
        ImprimeABBOrdenado(raiz->filhoDireito,arquivo);
    }
}

//BUSCA BINÁRIA NA ABB
static TNo* BuscaABB(TNo* Raiz,char palavra[]){
    if(Raiz != NULL) {
        TPalavra* palav = Raiz->dadoNo;
        TDadosPalavra* dadoPalav = palav->dadosPalavra;
        int compara = strcmp(dadoPalav->palavra,palavra);
        if(compara == 0) {
            return Raiz;
        }else if(compara < 0) {
            BuscaABB(Raiz->filhoEsquerdo,palavra);
        }else if(compara > 0) {
            BuscaABB(Raiz->filhoDireito,palavra);
        }
    }

    return Raiz;
}


static TNo* InsereABB(TNo* Raiz,void* palavra) {

    if(Raiz == NULL) {
        Raiz = criarNo(palavra);
    }
    TComparavel* e1 = palavra;
    TComparavel* e2 = Raiz->dadoNo;

    if(e1->compara(e1,e2) > 0) {
        Raiz->filhoDireito = InsereABB(Raiz->filhoDireito,palavra);
    }else if(e1->compara(e1,e2) < 0) {
        Raiz->filhoEsquerdo = InsereABB(Raiz->filhoEsquerdo,palavra);
    }

    return Raiz;
}

TABB* CriarABB(){
    TABB* NovaArvore = malloc(sizeof(TABB));
    NovaArvore->dadosABB = criarDadosABB();
    NovaArvore->buscar = BuscaABB;
    NovaArvore->inserir = InsereABB;
    NovaArvore->imprime = ImprimeABBOrdenado;
    return NovaArvore;
}

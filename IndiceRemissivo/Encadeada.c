#include <stdio.h>
#include <stdlib.h>
#include "Encadeada.h"
#include "usuario.h"
#include "palavra.h"

TDadoLista* criarDadoLista(){
    TDadoLista* DL = malloc(sizeof(TDadoLista));
    DL->Prim = NULL;
    DL->NElementos = 0;
    return DL;
}

TElemento* criarElemento(void* dadoElem){
    TElemento* NovoElem = malloc(sizeof(TElemento));
    NovoElem->dadoElemento = dadoElem;
    NovoElem->prox = NULL;
    return NovoElem;
}

static void* BuscaNaLista(TDSemiDinamico* List,void* Elem){
    TDadoLista* DadoLista = List->dadoLista;
    if(DadoLista->Prim == NULL)
        return NULL;
    TElemento* Aux = DadoLista->Prim;
    TComparavel *e1 = Elem;
    int achou=0;
    void* retorno = NULL;
    while(Aux != NULL && !achou){
        TComparavel *e2 = Aux->dadoElemento;
        if(e1->compara(e1,e2) == 0){
            achou = 1;
            retorno = Aux->dadoElemento;
        }
        Aux = Aux->prox;
    }
   return retorno;
}

static void InserirNaLista(TDSemiDinamico* List,void* Elem){

    TDadoLista* DadoLista = List->dadoLista;
    TElemento *Aux = DadoLista->Prim;
    TPalavra* NovaPalavra = Elem;
    TDadoPalavra* DadoNPalavra = NovaPalavra->dadoPalavra;
    TPalavra* ElemEncontrado = BuscaNaLista(List,NovaPalavra);
    if(ElemEncontrado == NULL){
        TElemento *NovoElem = criarElemento(Elem);
        NovoElem->prox = Aux;
        DadoLista->Prim = NovoElem;
        DadoLista->NElementos += 1;
    }else{
        ElemEncontrado->atualizar(ElemEncontrado,DadoNPalavra->paginaAtual);
    }

}

static void ImprimirNaLista(TDSemiDinamico* Lista){
    TDadoLista* DadoLista =  Lista->dadoLista;
    TElemento* Aux = DadoLista->Prim;
    printf("\n\n Numero de Elementos na lista:%d\n",DadoLista->NElementos);
    for(;Aux!=NULL;Aux = Aux->prox){
    	TComparavel *e1 = Aux->dadoElemento;
    	e1->imprime(e1,e1);
    }
}

static void RemoverNaLista(TDSemiDinamico* Lista, void* elem){
     TDadoLista* DadoLista =  Lista->dadoLista;
     TElemento* Aux;
     TElemento* Aux2;
     Aux = DadoLista->Prim;
     Aux2 = Aux;
     TComparavel* e1 = elem;
     TComparavel* e2 = Aux->dadoElemento;
     if(e1->compara(e1,e2)==0){
        DadoLista->Prim = Aux->prox;
        free(Aux2);
    }
    while((Aux != NULL) && (e1->compara(e1,e2)!=0)){
        e2 = Aux->dadoElemento;
        Aux2 = Aux;
        Aux = Aux->prox;
    }
    if (Aux != NULL && e1->compara(e1,e2)==0){
        Aux2->prox = Aux->prox;
        free(Aux);
    }
}

TDSemiDinamico* CriarLista(){
    TDSemiDinamico* NovaLista = malloc(sizeof(TDSemiDinamico));
    NovaLista->dadoLista = criarDadoLista();
    NovaLista->buscar = BuscaNaLista;
    NovaLista->inserir = InserirNaLista;
    NovaLista->imprimir = ImprimirNaLista;
    NovaLista->remover = RemoverNaLista;
    return NovaLista;
}

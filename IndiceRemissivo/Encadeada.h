#ifndef ENCADEADA_H_INCLUDED
#define ENCADEADA_H_INCLUDED

typedef struct DSemiDinamico TDSemiDinamico;
typedef struct Elemento TElemento;
typedef void (*TInserirNLista)(TDSemiDinamico*,void*);
typedef void*(*TBuscarNLista)(TDSemiDinamico*,void*);
typedef void (*TImprimirNLista)(TDSemiDinamico*);
typedef void (*TRemoverNLista)(TDSemiDinamico*,void*);

typedef struct{
    TElemento* Prim;
    unsigned int NElementos;
}TDadoLista;

struct Elemento{
    void *dadoElemento;
    TElemento* prox;
};

struct DSemiDinamico{
    void *dadoLista;
    TInserirNLista inserir;
    TBuscarNLista buscar;
    TRemoverNLista remover;
    TImprimirNLista imprimir;
};

TDSemiDinamico* CriarLista();
#endif // ENCADEADA_H_INCLUDED

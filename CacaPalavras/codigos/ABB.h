#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED

typedef struct ABB TABB;
typedef struct No TNo;
typedef TNo* (*TInserirABB)(TNo* raiz, void* palav);
typedef TNo*(*TBuscarABB)(TNo* raiz, char palavra[]);
typedef void (*TImprimeABBTXT)(TNo* raiz,FILE*);

struct No{
    void *dadoNo;
    TNo* filhoEsquerdo;
    TNo* filhoDireito;
};

typedef struct{
    TNo* Raiz;
}TDadosABB;

struct ABB{
    void *dadosABB;
    TInserirABB inserir;
    TBuscarABB buscar;
    TImprimeABBTXT imprime;
};

TABB* CriarABB();
#endif // ABB_H_INCLUDED


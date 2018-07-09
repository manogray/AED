#ifndef PATRICIA_H_
#define PATRICIA_H_

typedef struct Patricia TPatricia;
typedef struct Nodo TNodo;

typedef TNodo* (*TInserePatricia)(TNodo* raiz,char palavra[20],int linha,int incrementador);
typedef void (*TImprimePatricia)(TNodo* trie, FILE* arquivo);

struct Nodo{
    char caractere;
    int incrementador;
    char palavra[20];
    int linha;
    TNodo* esquerda;
    TNodo* direita;
};

struct Patricia{
	TNodo* dadosPatricia;
	TInserePatricia inserirPatricia;
	TImprimePatricia imprimirPatricia;
};

TPatricia* criarPatricia();

#endif // PATRICIA_H_

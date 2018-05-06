#ifndef PALAVRA_H_INCLUDED
#define PALAVRA_H_INCLUDED

typedef struct Palavra TPalavra;
typedef short (*TComparaPalavra)(TPalavra*,TPalavra*);
typedef void (*TImprimePalavra)(TPalavra*,void*);
typedef void (*TAtualizaPalavra)(TPalavra*,int Pagina);

typedef struct DadoPalavra{
    char Palavra[200];
    int Paginas[700];
    int paginaAtual;
    float TFIDF[700];
}TDadoPalavra;

struct Palavra{
    void* dadoPalavra;
    TImprimePalavra imprimir;
    TComparaPalavra comparar;
    TAtualizaPalavra atualizar;
};

TPalavra* criarPalavra(char Palavra[],int pagina);

#endif // PALAVRA_H_INCLUDED

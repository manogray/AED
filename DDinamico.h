#ifndef DDINAMICO_H_INCLUDED
#define DDINAMICO_H_INCLUDED

typedef struct DDinamico TDDinamico;
typedef void (*TInsere)(TDDinamico*,void*);
typedef void* (*TBusca)(TDDinamico*, char*);
typedef void (*TRemove)(TDDinamico*,char*);
typedef void (*TDestroi) (TDDinamico*);

typedef struct DadoHash{
    void* *vetor;
     int tamanho;
     int ocupacao;
     int entradas_usadas;
}TDadoHash;

struct DDinamico{
    void* dadoHash;
    TInsere inserir;
    TBusca buscar;
    TRemove remover;
    TDestroi destruir;
};

TDDinamico* criarHash(int tamanho);

#endif // DDINAMICO_H_INCLUDED

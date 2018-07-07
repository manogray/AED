#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

typedef struct Hash THash;
typedef void (*TInsereHash)(THash* tab,void* ele);
typedef void* (*TBuscaHash)(THash* tab,void* ele);
typedef void (*TDestroiHash) (THash* tab);

typedef struct DadoHash{
    void* *vetor;
     int tamanho;
     int ocupacao;
}TDadoHash;

struct Hash{
    void* dadoHash;
    TInsereHash inserir;
    TBuscaHash buscar;
    TDestroiHash destruir;
};

THash* criarHash(int tamanho);

#endif // HASH_H_INCLUDED

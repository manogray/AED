#ifndef PATRICIA_H_
#define PATRICIA_H_

typedef struct Patricia TPatricia;

//Métodos do Tipo TPatricia
typedef void (*TinserirPatVazia)(TPatricia *arvore,void* elem, void elem);
typedef void (*TinserirPatNormal)(TNoP* raiz, void* elem);
typedef void* (*TremoverPat)(TNoP *raiz, void *elem);
typedef void* (*TbuscarPat)(TNoP *raiz, void* valor, int apontador);

typedef struct Dir{
    int avanca;
    char compara;
}TDir;

typedef struct NoP{
	TDir* direcoes;
    void* palavra;
    TNoP* filhoEsq;
    TNoP* filhoDir;
} TNoP;

//Dados do Tipo TPatricia
typedef struct dadosPat{
	int ocupacao;
	TNoP* Raiz;
} TDadosPat;

struct Patricia{
	void *dadosPat; //Dados encapsulados
	TinserirPatVazia inserirVazia;//Tipo Inserir com arvore vazia
	TinserirPatNormal inserirNormal; //insere com arvore com um elemento
	TremoverPat remover;//Tipo Remover
	TbuscarPat buscar;//Tipo Buscar
};

//Funcao construtor do TPatricia
TPatricia *criarPatricia();
#endif /* PATRICIA_H_ */

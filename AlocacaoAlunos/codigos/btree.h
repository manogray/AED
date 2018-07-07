#ifndef BTREE_H_
#define BTREE_H_

typedef struct Btree TBtree;
typedef struct Pagina TPagina;

struct Pagina{
	int ocupacao;
	int tamanho;
	int ordem;
	TPagina* pai;
	void ** vetor;
};

//Metodos da Arvore
typedef void (*TInsereB)(TPagina* raiz, void* elem);
typedef int (*TBuscaB)(TPagina* raiz, char pesquisa[200]);

//Dados do Tipo TBTree
typedef struct dadosBtree{
	TPagina* raiz;
} TDadosBtree;

struct Btree{
	void *dadosBtree; //Dados encapsulados
	TInsereB inserirB;
	TBuscaB buscarB;
};

//Funcao construtor do Arvore B
TBtree *criarBtree(int ordem);
#endif /* BTREE_H_ */

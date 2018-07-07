#ifndef PALAVRA_H_
#define PALAVRA_H_

typedef struct Palavra TPalavra;
typedef short (*TComparaPalavra)(TPalavra* P1,TPalavra* P2);

//Dados do Tipo TPalavra
typedef struct dadosPalavra{
	char palavra[200];
	int linha;
	int coluna;
	char orientacao;
} TDadosPalavra;

struct Palavra{
	void *dadosPalavra; //Dados encapsulados
	TComparaPalavra compara; //Compara duas Palavras
};

//Funcao construtor do TPalavra
TPalavra *criarPalavra(char palavra[]);
#endif /* PALAVRA_H_ */

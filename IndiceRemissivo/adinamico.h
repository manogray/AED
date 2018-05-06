#ifndef ADINAMICO_H_
#define ADINAMICO_H_

typedef struct DStatico TDStatico;

typedef void (*TinserirADI)(TDStatico *vet,void* elem);
typedef void* (*TremoverADI)(TDStatico *vet, void *elem);
typedef int (*TbuscarADI)(TDStatico *vet, void* valor);
typedef void (*TimprimirADI)(TDStatico *vet);

typedef struct dados{
	int tamanho;
	int ocupacao;
	int paginasDoLivro[700];
	int numerodePaginas;
	void* *vetor;
} TDadosADI;

struct DStatico{
	void *dados;
	TinserirADI inserir;//tipo inserir
	TremoverADI remover;//tipo remover
	TbuscarADI buscar;//tipo buscar
	TimprimirADI imprimir;//tipo imprime
};

TDStatico *criarADI(int tamanhoInicial);
#endif /* ADINAMICO_H_ */

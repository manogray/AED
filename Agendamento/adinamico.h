#ifndef ADINAMICO_H_
#define ADINAMICO_H_

typedef struct ArrayDinamico TArrayDinamico;

//Métodos do Tipo TArrayDinamico
typedef void (*TinserirADI)(TArrayDinamico *vet,void* elem);
typedef void (*TinserirADIposicao)(TArrayDinamico* vet, void* elem, int posicao);
typedef void* (*TremoverADI)(TArrayDinamico *vet, void *elem);
typedef int (*TbuscarADI)(TArrayDinamico *vet, void* valor);
typedef void (*TordenaADI) (TArrayDinamico* vet,int prim);
typedef void (*TDestroiADI) (TArrayDinamico* vet);

//Dados do Tipo TArrayDinamico
typedef struct dadosADI{
	int tamanho;
	int ocupacao;
	void* *vetor;
} TDadosADI;

struct ArrayDinamico{
	void *dadosADI; //Dados encapsulados
	TinserirADI inserir;//Tipo Inserir
	TinserirADIposicao inserirposicao; //Tipo insere na posicao
	TremoverADI remover;//Tipo Remover
	TbuscarADI buscar;//Tipo Buscar
	TordenaADI ordenar; //Tipo Ordena
	TDestroiADI destruir; //Tipo destroi
};

//Funcao construtor do TArrayDinamico
TArrayDinamico *criarADI(int tamanhoInicial);
#endif /* ADINAMICO_H_ */

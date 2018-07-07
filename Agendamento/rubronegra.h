#ifndef RUBRONEGRA_H_
#define RUBRONEGRA_H_

typedef struct RubroNegra TRubroNegra;
typedef struct No TNo;

//Métodos do Tipo TRubroNegra
typedef void (*TinserirRubroNegra)(TRubroNegra *arvore,void* elem);
typedef void* (*TremoverRubroNegra)(TRubroNegra *arvore, void *elem);
typedef TNo* (*TbuscarRubroNegra)(TNo* raiz, void* elem);
typedef void (*TimprimeRubroNegra) (TNo* raiz, FILE* arquivo);

struct No {
    void* chave;
    char cor;
    TNo* pai;
    TNo* filhoDir;
    TNo* filhoEsq;
};

//Dados do Tipo TRubroNegra
typedef struct dadoRubroNegra{
	int ocupacao;
	TNo* Raiz;
}TDadosRubroNegra;

struct RubroNegra{
	void *dadosRubroNegra; //Dados encapsulados
	TinserirRubroNegra inserir;//Tipo Inserir
	TremoverRubroNegra remover;//Tipo Remover
	TbuscarRubroNegra buscar;//Tipo Buscar
	TimprimeRubroNegra imprime; //Tipo imprime
};

TRubroNegra *criarRubroNegra();
#endif /* RUBRONEGRA_H_ */

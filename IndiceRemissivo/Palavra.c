#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "palavra.h"
#include "adinamico.h"

static void zerotristemesmo(TDadoPalavra* Palavra){
	int i;
	for(i=0;i<700;i++){
		Palavra->Paginas[i]=0;
	}
}
static void zeratristemesmoF(TDadoPalavra* NNPalavra){
	for(int i=0;i<700;i++){
		NNPalavra->TFIDF[i]=0.0;
	}
}
 int ContaTudoPagina(TPalavra* palavra) {						//EM QUANTAS PAGINAS UMA PALAVRA OCORRE
	TDadoPalavra* DadoPalavra = palavra->dadoPalavra;
	int i = 0;
	int contaPagina = 0;

	while (i < 700) {
		if(DadoPalavra->Paginas[i] != 0) {
			contaPagina++;
		}
		i++;
	}
	return contaPagina;
}

float TF(TDStatico* Livro, TPalavra* palavra, int pagina) {

	float vezesNaPagina;
	float PalavrasNaPagina;

	TDadoPalavra* DadoPalavra = palavra->dadoPalavra;
	TDadosADI* DadoLivro = Livro->dados;
	vezesNaPagina = DadoPalavra->Paginas[pagina];//repetições em uma pagina
    PalavrasNaPagina = DadoLivro->paginasDoLivro[pagina];//numero de palavras na pagina
    float TF = vezesNaPagina/PalavrasNaPagina;
	return TF;
}

float IDF(TPalavra* palavra, void* elem) {
	TDStatico* Livro = elem;
	TDadosADI* Dadolivro = Livro->dados;
	int numeroTotaldepaginasnolivro = Dadolivro->numerodePaginas;                                //SE FOR O LIVRO GUARANI SÃO 185 PÁGINAS
	float valor = log(numeroTotaldepaginasnolivro/(ContaTudoPagina(palavra) + 1));
	return valor;

}

float TFIDF(TPalavra* palavra, int pagina, TDStatico* LLivro) {

	return (TF(LLivro, palavra, pagina) * IDF(palavra, LLivro));

}

static TDadoPalavra* criarDadoPalavra(char Palavra[],int pagina){
    TDadoPalavra* NovoDadoPalavra = malloc(sizeof(TDadoPalavra));
    strcpy(NovoDadoPalavra->Palavra,Palavra);
    zerotristemesmo(NovoDadoPalavra);
    NovoDadoPalavra->Paginas[pagina] +=1;
    NovoDadoPalavra->paginaAtual = pagina;
    zeratristemesmoF(NovoDadoPalavra);
    return NovoDadoPalavra;
}

int MaiorIndice(TDadoPalavra* N2Palavra) {

	int i;
	float maior = 0.0;
	int indice = 0;

	for (i=0;i < 700;i++) {
		if(maior < N2Palavra->TFIDF[i]) {
			maior = N2Palavra->TFIDF[i];
			indice = i;
		}
	}

	return indice;
}

static void ImprimePalavra(TPalavra* Palavra,void* elem){

	TDStatico * Livro = elem;
    TDadoPalavra* DadoPalavra = Palavra->dadoPalavra;
    printf("\nPalavra : %s",DadoPalavra->Palavra);

    for(int i=0;i<700;i++){
    	if(DadoPalavra->Paginas[i] != 0){
			float tfidf = TFIDF(Palavra,i,Livro);
			DadoPalavra->TFIDF[i] = tfidf;
		}
    }

    int i = 0;
    while(i < 5) {
    	int p = MaiorIndice(DadoPalavra);
    	if (p != 0) {
            printf("\n\nPagina %d - TFIDF: %f",p,DadoPalavra->TFIDF[p]);
            DadoPalavra->TFIDF[p] = 0.0;
    	}
    	i++;
	}
}

static short ComparaPalavra(TPalavra* P1, TPalavra* P2){
    TDadoPalavra* DadoPalavra1 = P1->dadoPalavra;
    TDadoPalavra* DadoPalavra2 = P2->dadoPalavra;
    return strcmp(DadoPalavra1->Palavra,DadoPalavra2->Palavra);
}

static void AtualizaPalavra(TPalavra* Palavra, int Pagina){
	TDadoPalavra* DadoPalavra = Palavra->dadoPalavra;
	DadoPalavra->Paginas[Pagina]+=1;
}

TPalavra* criarPalavra(char Palavra[],int pagina){
    TPalavra* NovaPalavra = malloc(sizeof(TPalavra));
    NovaPalavra->dadoPalavra = criarDadoPalavra(Palavra,pagina);
    NovaPalavra->comparar = ComparaPalavra;
    NovaPalavra->imprimir = ImprimePalavra;
    NovaPalavra->atualizar = AtualizaPalavra;
    return NovaPalavra;
}

#include <stdio.h>
#include <stdlib.h>
#include "adinamico.h"
#include "usuario.h"


static void zerotristemesmo2(TDadosADI* paginas){
	int i;
	for(i=0;i<700;i++){
		paginas->paginasDoLivro[i]=0;
	}
}

static TDadosADI *criarDados(int tamanho){
	TDadosADI *aloca = malloc(sizeof(TDadosADI));
	if(aloca!= NULL){
		aloca->tamanho = tamanho;
		aloca->ocupacao = 0;
 		zerotristemesmo2(aloca);
		aloca->numerodePaginas =0;
		aloca->vetor = malloc(sizeof(void*)*tamanho);
	}
	return aloca;
}

static int buscarADI(TDStatico *vet, void *e){
	TDadosADI *d = vet->dados;
	TComparavel *c = e;

	int i=0;
	while ((i<d->ocupacao) && (c->compara(e,d->vetor[i])!=0) )
		i++;

	return (i==d->ocupacao?-1:i);

}

static void inserirADI(TDStatico *vet, void* elem){
	TDadosADI *d = vet->dados;

	if (d->ocupacao == d->tamanho){
		d->vetor = realloc(d->vetor,sizeof(void*)*(2*d->tamanho));
		d->tamanho = 2*d->tamanho;
	}

	d->vetor[d->ocupacao] = elem;
	d->ocupacao++;
};

static void imprimirADI(TDStatico *v){
	TDadosADI *d = v->dados;
	int i;
	for(i=0;i<d->ocupacao;i++){
		TComparavel *e1 = d->vetor[i];
		e1->imprime(e1,e1);
	}
	printf("\n");
}

static void* removerADI(TDStatico *v, void *procurado){
	TDadosADI *d = v->dados;

	int i=buscarADI(v,procurado);
	void *elem = NULL;
	if (i!=-1){
		elem = d->vetor[i];
		for(;i<d->ocupacao;i++)
			d->vetor[i]=d->vetor[i+1];
		d->ocupacao--;
	}

	return elem;
}

TDStatico *criarADI(int tamanhoInicial){
	TDStatico *adi = malloc(sizeof(TDStatico));
	if(adi != NULL){
		adi->dados = criarDados(tamanhoInicial);
		adi->inserir = inserirADI;
		adi->buscar = buscarADI;
		adi->imprimir=imprimirADI;
		adi->remover=removerADI;
	}
	return adi;
}

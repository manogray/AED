#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubronegra.h"
#include "paciente.h"
#define nulo criarNulo()

TNo* criarNulo() {
	TNo* nalo = malloc(sizeof(TNo));
	if(nalo != NULL){
		nalo->chave = NULL;
		nalo->cor = 'P';
		nalo->filhoDir = NULL;
		nalo->filhoEsq = NULL;
	}

	return nalo;
}


TNo* criarNo(void* elem) {
    TNo* NovoNo = malloc(sizeof(TNo));
    if(NovoNo != NULL) {
        NovoNo->chave = elem;
        NovoNo->cor = 'V';
        NovoNo->filhoDir = nulo;
        NovoNo->filhoEsq = nulo;
    }

    return NovoNo;
}

static TDadosRubroNegra* criarDadosRubroNegra() {
    TDadosRubroNegra* dado = malloc(sizeof(TDadosRubroNegra));
    if(dado != NULL) {
        dado->ocupacao = 0;
        dado->Raiz = NULL;
    }

    return dado;
}

static void RotacaoEsquerda(TRubroNegra* arvore, TNo* noEntrada){
    TNo* auxiliar = noEntrada->filhoDir;
    noEntrada->filhoDir = auxiliar->filhoEsq;
    TNo* esqAux = auxiliar->filhoEsq;

    if(esqAux != nulo){
        esqAux->pai = noEntrada;
    }

    auxiliar->pai = noEntrada->pai;
    TNo* paiDoNo = noEntrada->pai;

    if(paiDoNo == nulo){
        TDadosRubroNegra* dadoarvore = arvore->dadosRubroNegra;
        dadoarvore->Raiz = auxiliar;
    }else{
        if(noEntrada == paiDoNo->filhoEsq){
            paiDoNo->filhoEsq = auxiliar;
        }else{
            paiDoNo->filhoDir = auxiliar;
        }
    }
    auxiliar->filhoEsq = noEntrada;
    noEntrada->pai = auxiliar;
}

static void RotacaoDireita(TRubroNegra* arvore, TNo* noEntrada){
    TNo* auxiliar = noEntrada->filhoEsq;
    noEntrada->filhoEsq = auxiliar->filhoDir;
    TNo* dirAux = auxiliar->filhoDir;

    if(dirAux != nulo){
        dirAux->pai = noEntrada;
    }

    auxiliar->pai = noEntrada->pai;
    TNo* paiDoNo = noEntrada->pai;

    if(paiDoNo == nulo){
        TDadosRubroNegra* dadoarvore = arvore->dadosRubroNegra;
        dadoarvore->Raiz = auxiliar;
    }else{
        if(noEntrada == paiDoNo->filhoDir){
            paiDoNo->filhoDir = auxiliar;
        }else{
            paiDoNo->filhoEsq = auxiliar;
        }
    }
    auxiliar->filhoDir = noEntrada;
    noEntrada->pai = auxiliar;
}

int comparaChaves(void* elem1, void* elem2) {
    TPaciente* alguem1 = elem1;
    TPaciente* alguem2 = elem2;
    TDadosPaciente* dado1 = alguem1->dadoPaciente;
    TDadosPaciente* dado2 = alguem2->dadoPaciente;

    return strcmp(dado1->nome,dado2->nome);
}

static void regrasPaternidade(TRubroNegra* arvore, TNo* no) {
	TNo* paiDoNo = no->pai;
	while(paiDoNo->cor == 'V'){
		TNo* avoDoNo = paiDoNo->pai;
		if(paiDoNo == avoDoNo->filhoEsq){
			TNo* auxiliar = avoDoNo->filhoDir;
			if(auxiliar->cor == 'V') {
				paiDoNo->cor = 'P';
				auxiliar->cor = 'P';
				avoDoNo->cor = 'V';
				no = avoDoNo;
			}else {
				if(no == paiDoNo->filhoDir) {
					no = paiDoNo;
					RotacaoEsquerda(arvore, no);
				}
				paiDoNo->cor = 'P';
				avoDoNo->cor = 'V';
				RotacaoDireita(arvore, avoDoNo);
			}
		}else{
			TNo* auxiliar = avoDoNo->filhoEsq;
			if(auxiliar->cor == 'V') {
				paiDoNo->cor = 'P';
				auxiliar->cor = 'P';
				avoDoNo->cor = 'V';
				no = avoDoNo;
			}else {
				if(no == paiDoNo->filhoEsq) {
					no = paiDoNo;
					RotacaoEsquerda(arvore, no);
				}
				paiDoNo->cor = 'P';
				avoDoNo->cor = 'V';
				RotacaoDireita(arvore, avoDoNo);
			}
		}
	}
	TDadosRubroNegra* dadoArvore = arvore->dadosRubroNegra;
	TNo* raizArvore = dadoArvore->Raiz;
	raizArvore->cor = 'P';
}

static void InserirRubroNegra(TRubroNegra* arvore, void* elemento) {
    TDadosRubroNegra* dadoArvore = arvore->dadosRubroNegra;
    TNo* auxiliar = nulo;
    TNo* aponta = dadoArvore->Raiz;

    while(aponta != nulo) {
        auxiliar = aponta;
        if(comparaChaves(elemento,aponta->chave) == -1){
        	aponta = aponta->filhoEsq;
        }else {
        	aponta = aponta->filhoDir;
        }
    }
    TNo* Novo = criarNo(elemento);
    Novo->pai = auxiliar;
    if(auxiliar == nulo){
    	dadoArvore->Raiz = Novo;
    }else {
    	if(comparaChaves(Novo->chave,auxiliar->chave) == -1){
    		auxiliar->filhoEsq = Novo;
    	}else {
    		auxiliar->filhoDir = Novo;
    	}
    }
    Novo->filhoEsq = nulo;
    Novo->filhoDir = nulo;
    Novo->cor = 'V';

    regrasPaternidade(arvore, Novo);
}

static TNo* BuscarRubroNegra(TNo* raiz, void* elemento) {
	if(raiz != NULL){
		TPaciente* alguem = elemento;
		if(comparaChaves(raiz,alguem) == 0){
			return raiz;
		}else if(comparaChaves(raiz,alguem) < 0){
			BuscarRubroNegra(raiz->filhoEsq,alguem);
		}else {
			BuscarRubroNegra(raiz->filhoDir,alguem);
		}
	}

	return raiz;
}

static void ImprimeRubroNegra(TNo* raiz, FILE* arquivo){
	if(raiz != NULL){
		TPaciente* alguem = raiz->chave;
		TDadosPaciente* dadoAlguem = alguem->dadoPaciente;
		ImprimeRubroNegra(raiz->filhoEsq,arquivo);
		printf("nome: %s - telefone: %s\n",dadoAlguem->nome,dadoAlguem->telefone);
		fprintf(arquivo,"nome: %s - telefone: %s\n",dadoAlguem->nome,dadoAlguem->telefone);
		ImprimeRubroNegra(raiz->filhoDir,arquivo);
	}
}

TRubroNegra* criarRubroNegra() {
	TRubroNegra* NovaArvore = malloc(sizeof(TRubroNegra));
	if(NovaArvore != NULL){
		NovaArvore->dadosRubroNegra = criarDadosRubroNegra();
		NovaArvore->inserir = InserirRubroNegra;
		NovaArvore->buscar = BuscarRubroNegra;
		NovaArvore->imprime = ImprimeRubroNegra;
	}

	return NovaArvore;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "candidato.h"

TPagina* criarPagina(int ordem){
	TPagina* Dpag = malloc(sizeof(TPagina));
	if(Dpag != NULL){
		Dpag->ocupacao = ordem;
		Dpag->ordem = ordem;
		Dpag->tamanho = (ordem*2) - 1;
		Dpag->pai = NULL;
		Dpag->vetor = malloc(sizeof(void*)*Dpag->tamanho);
	}

	int contador = 0;
	while(contador < Dpag->tamanho){
		Dpag->vetor[contador] = NULL;
		contador = contador + 1;
	}

	return Dpag;
}

TDadosBtree* criarDadosBtree(int ordem){
	TDadosBtree* dadoB = malloc(sizeof(TDadosBtree));
	if(dadoB != NULL){
		dadoB->raiz = criarPagina(ordem);
	}

	return dadoB;
}

int EhImpar(int numero){
    int res = 0;

    if((numero%2) != 0){
        res = 1;
    }

    return res;
}

TPagina* split(TPagina* pag){

	int contador = 0;
	int contador2 = 0;
	int cont = 0;
	TPagina* novaPagina = criarPagina(pag->ordem);
	int parada = pag->ordem;

	while(contador < pag->tamanho){
		if(EhImpar(contador)){
			contador2 = contador2 + 1;
			if(contador2 >= ((parada/2)+1)){
				novaPagina->vetor[cont] = pag->vetor[contador];
				cont = cont + 1;
				novaPagina->ocupacao = novaPagina->ocupacao + 1;
			}
		}

		contador = contador + 1;
	}

	return novaPagina;
}

int maior(void* elem1, void* elem2){
    TCandidato* cand1 = elem1;
    TCandidato* cand2 = elem2;
    TDadosCandidato* dadoCand1 = cand1->dadosCandidato;
    TDadosCandidato* dadoCand2 = cand2->dadosCandidato;
    int retorno = 0;
    if(strcmp(dadoCand1->nome,dadoCand2->nome) == 1){
        retorno = 1;
    }

    return retorno;
}

int igualP(char elem1[], void* elem2){
    TCandidato* cand2 = elem2;
    TDadosCandidato* dadoCand2 = cand2->dadosCandidato;
    int retorno = 0;
    if(strcmp(dadoCand2->nome,elem1) == 0){
        retorno = 1;
    }

    return retorno;
}

int maiorP(char elem1[], void* elem2){
    TCandidato* cand2 = elem2;
    TDadosCandidato* dadoCand2 = cand2->dadosCandidato;
    int retorno = 0;
    if(strcmp(dadoCand2->nome,elem1) == 1){
        retorno = 1;
    }

    return retorno;
}

int paginaComEspaco(TPagina* pag, void* elem, int contador){
	int ok = 0;

    while(!ok){
			if(EhImpar(contador)){ //VERIFICA SE E UMA POSICAO DE CHAVE
				if(pag->vetor[contador] == NULL){
                    //POSICAO VAZIA
					pag->vetor[contador] = elem;
					pag->ocupacao = pag->ocupacao + 1;
					ok = 1;
				}else{
				    //POSICAO COM CHAVE
					if(maior(elem,pag->vetor[contador])){
					//ELEMENTO MAIOR QUE CHAVE DA POSICAO
                        contador = contador + 2;
                        ok = paginaComEspaco(pag,elem,contador);
					}else{
                    //ELEMENTO MENOR QUE CHAVE NA POSICAO
                        void* auxiliar = pag->vetor[contador];
                        pag->vetor[contador] = elem;
                        ok = paginaComEspaco(pag,auxiliar,contador+2);
					}
				}

			}else{
				contador = contador + 1;
			}
		}

    return ok;
}

void overflowDaPagina(TPagina* pag, TPagina* nova, void* elem){
    int contador = 3;
    TPagina* pai = criarPagina(pag->ordem);
    pai->vetor[1] = nova->vetor[1];
    while(contador < nova->tamanho){
        nova->vetor[contador - 2] = nova->vetor[contador];
        contador = contador + 2;
    }
    pag->pai = pai;
    nova->pai = pai;
    pai->vetor[0] = pag;
    pai->vetor[2] = nova;
}

void InsereB(TPagina* pag, void* elem){

	if(pag->ocupacao < pag->tamanho){
		paginaComEspaco(pag,elem,0);
		return;
	}

	if(pag->ocupacao == pag->tamanho){
        TPagina* Nova = split(pag);
        if(pag->pai == NULL){
            overflowDaPagina(pag,Nova,elem);
        }else {
            InsereB(pag->pai,Nova->vetor[1]);
        }
	}

}

int BuscaB(TPagina* pag, char pesquisa[]){
    int contador = 1;
    int ok = 0;
    while((contador < pag->tamanho) && ok == 0){
        if(igualP(pesquisa,pag->vetor[contador])){ //SE CHAVE FOR IGUAL A ELEMENTO DA PAGINA
            TCandidato* cand = pag->vetor[contador];
            cand->imprimeTela(cand);
            ok = 1;
        }else{
            if(maiorP(pesquisa,pag->vetor[contador])){ //SE A CHAVE E MAIOR QUE ELEMENTO DA PAGINA
                contador = contador + 2;
            }else {     //SE E MENOR QUE O ELEMENTO DA PAGINA
                if(pag->vetor[contador - 1] != NULL){
                   ok = BuscaB(pag->vetor[contador - 1],pesquisa);
                }else{
                    printf("Candidato nao inscrito!\n\n");
                    ok = 1;
                }
            }
        }
    }

    if(contador == (pag->tamanho-1)){
        printf("Candidato nao inscrito!\n\n");
        ok = 1;
    }

    return ok;

}

TBtree* criarBtree(int ordem){
	TBtree* pag = malloc(sizeof(TBtree));
	if(pag != NULL){
		pag->dadosBtree = criarDadosBtree(ordem);
		pag->inserirB = InsereB;
		pag->buscarB = BuscaB;
	}

	return pag;
}

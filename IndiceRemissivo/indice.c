/*
	Universidade Federal do Amazonas
		Instituto de Computação
			Algoritmos e Estruturas de Dados II
				Profº César

			Trabalho 2 - Índice Remissivo

			Al: Lucas de Lima Castro
				Luis de Gonzaga Mota Pinto Filho
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "adinamico.h"
#include "palavra.h"
#include "usuario.h"
#include "DDinamico.h"
#include "Encadeada.h"

short verificaCaractere(char Caractere,TDStatico* Carac){
	TDadosADI * DadoADI = Carac->dados;
	int achou = 0;
	int i=0;
	while(!achou && i < DadoADI->ocupacao){
		TPalavra * Palavra = DadoADI->vetor[i];
		TDadoPalavra* DadoPalavra = Palavra->dadoPalavra;
		if(Caractere == DadoPalavra->Palavra[0])
			achou = 1;
	i++;
	}
	return achou;
}

char* LimpaPalavra(char Palavra[],TDStatico* Carac){
	int i =0;
	int j= 0;
	char *PalavraLimpa = malloc(sizeof(char)*200);
	while((Palavra[i] != '\0') && (Palavra[i]!= ' ') && (Palavra[i]!= '\n')){
		if(verificaCaractere(Palavra[i],Carac)!= 1){
			PalavraLimpa[j] = Palavra[i];
			j++;
		}
		i++;
	}
	PalavraLimpa[j]= '\0';
	return PalavraLimpa;
}

short VerificaStopWords(char Palavra[],TDStatico *STOPWORDS){
	TDadosADI * DadoStop = STOPWORDS->dados;
	int i =0;
	int stop = 0;
	while(i < DadoStop->ocupacao && !stop){
		TPalavra* PalavraN = DadoStop->vetor[i];
		TDadoPalavra* DadoPalavra = PalavraN->dadoPalavra;
		if(strcmp(Palavra,DadoPalavra->Palavra) == 0){
			stop = 1;
		}
	i++;
	}
	return stop;
}


TDStatico* ObtemPalavras(char *arq,char *Meth,int N,TDStatico* Carar,TDStatico* STOPWORDS, int op){
	TDStatico* ADI = criarADI(N);
	char Palavra[200];
	FILE* aq = fopen(arq,"r");
	int i;
	int pagina = 0;
    if(aq != NULL){
	for(i=0;i<N;i++){
		fscanf(aq,Meth,Palavra);
		if(op == 1){
			ADI->inserir(ADI,criarPalavra(Palavra,pagina));
		}else{
			char *PalavraLimpa = malloc(sizeof(char)*200);
			PalavraLimpa = LimpaPalavra(Palavra,Carar);
			if(strcmp(PalavraLimpa,"PA") == 0) {
                pagina++;
            }
			if(VerificaStopWords(PalavraLimpa,STOPWORDS)!= 1){
                TDadosADI* DadoADI = ADI->dados;
                DadoADI->paginasDoLivro[pagina] += 1;
                DadoADI->numerodePaginas = pagina;
                ADI->inserir(ADI,criarPalavra(PalavraLimpa,pagina));
                free(PalavraLimpa);
			}
		}
	}
    }else{
        printf("\n\n Arquivo Não Encontrado!\n\n");
    }
	return ADI;
}

void Pause() {
	system("pause");
}

int verificaHash(TDDinamico* Hash, int fatorCarga) {
    int retorno = 0;
    TDadoHash * dadoHash = Hash->dadoHash;
    for(int i = 0;(i < dadoHash->tamanho) && (retorno == 0);i++) {
        TDSemiDinamico* lista = dadoHash->vetor[i];
        TDadoLista* dadolista = lista->dadoLista;
        if (dadolista->NElementos > fatorCarga) {
            retorno = 1;
        }
    }
    return retorno;
}

int main(){

	char meth1[10]= "%[^ ] ";
	char meth2[10]= "%[^\n]\n";


	TDStatico* AUX = criarADI(1);
	TDStatico* Caracteres = ObtemPalavras("Arquivos/Caracteres.txt",meth1,30,AUX,AUX,1);

	TDStatico* StopWords = ObtemPalavras("Arquivos/stopwords_Final.txt",meth2,801,AUX,AUX,1);

	//Pré-Processamento de dados

		printf("\n\nProcessando Livro Guarani");

		//LIVRO GUARANI
		TDStatico* LivroGuarani = ObtemPalavras("Arquivos/livro_baseGuarani.txt",meth1,106854,Caracteres,StopWords,2);

		printf("\n\nProcessando Livro Aventuras");

		//LIVRO AVENTURAS
		TDStatico* LivroAventuras = ObtemPalavras("Arquivos/livro_baseAventuras.txt",meth1,84732,Caracteres,StopWords,2);


		printf("\n\nProcessando Livro Paralelismo");

		//LIVRO PARALELISMO
		TDStatico* LivroParalelismo = ObtemPalavras("Arquivos/livro_baseParalelismo.txt",meth1,108361,Caracteres,StopWords,2);


	//MAPEANDO DADOS NA HASH


		TDadosADI* DadoGuarani = LivroGuarani->dados;
		TDadosADI* DadoAventuras = LivroAventuras->dados;
		TDadosADI* DadoParalelismo = LivroParalelismo->dados;

		TDDinamico* Hash1 = criarHash(55331);
		TDDinamico* Hash2 = criarHash(55331);
		TDDinamico* Hash3 = criarHash(71339);

		for (int i = 0; i < DadoGuarani->ocupacao;i++){
			TPalavra * NPalavra = DadoGuarani->vetor[i];
			TDadoPalavra * NDadoPalavra = NPalavra->dadoPalavra;
			if (strcmp(NDadoPalavra->Palavra,"") == 0 || strlen(NDadoPalavra->Palavra) < 2) {
             continue;
			}
			Hash1->inserir(Hash1,NPalavra);

		}
        printf("\n\nGuarani OK!\n\n");
        system("pause");
        system("cls");
		for (int i = 0; i < DadoAventuras->ocupacao;i++){

			TPalavra * NNPalavra = DadoAventuras->vetor[i];
			TDadoPalavra * NNDadoPalavra = NNPalavra->dadoPalavra;
			if (strcmp(NNDadoPalavra->Palavra,"") == 0 || strlen(NNDadoPalavra->Palavra) < 2)
                continue;
			Hash2->inserir(Hash2,NNPalavra);

		}
        printf("\n\nAventuras OK!");
        system("pause");
        system("cls");
		for (int i = 0; i < DadoParalelismo->ocupacao;i++){

			TPalavra * NNNPalavra = DadoParalelismo->vetor[i];
			TDadoPalavra * NNNDadoPalavra = NNNPalavra->dadoPalavra;
			if (strcmp(NNNDadoPalavra->Palavra,"") == 0 || strlen(NNNDadoPalavra->Palavra) < 2)
                continue;
			Hash3->inserir(Hash3,NNNPalavra);

		}
		printf("\n\nParalelismo OK");
		system("pause");
        int ocupacao[10] = {0};
		char palavraBuscada[200];
		int opcao;
		menu:
		system("cls");
		printf("            Indice Remissivo");
		printf("\n\nEscolha um dos livros com indices disponiveis:");
		printf("\n\nO Guarani                                   [1]");
		printf("\nThe Adventures Of Huckleberry Finn          [2]");
		printf("\nParalelismo em Visao Natural e Artificial   [3]");
		printf("\nSair                                        [0]\n\n");

		scanf("%d",&opcao);

		if(opcao == 1 ){
			int loop;
			for ( loop = 1;loop != 0;) {

			system("cls");
			printf("\n\nBusque uma palavra: ");
			scanf("%s",palavraBuscada);
			loop = strcmp(palavraBuscada,"-1");

			if(strcmp(palavraBuscada,"exit") == 0) {
				goto menu;
			}

			if(strcmp(palavraBuscada,"analytics") == 0) {

				system("cls");
				TDadoHash* DadoHash1 = Hash1->dadoHash;
				float percentagem = ((DadoHash1->ocupacao*100.0)/DadoHash1->tamanho*1.0);
                for(int i=0;i < DadoHash1->tamanho;i++) {
                    TDSemiDinamico * lista1 = DadoHash1->vetor[i];
                    TDadoLista * Dadolista1 = lista1->dadoLista;
                    if(Dadolista1->Prim != NULL){
                        ocupacao[Dadolista1->NElementos] +=1;
                    }else {
                        ocupacao[0] += 1;
                    }
                }
				printf("\n\nTamanho da Hash deste livro: %d",DadoHash1->tamanho);
				printf("\n\nOcupacao da Hash: %d",DadoHash1->ocupacao);
				printf("\n\nTaxa de Ocupacao da Hash deste livro: %f %%",percentagem);
				printf("\n\nOcupacao das Entradas: ");
				for(int i =0;i != 10;i++)
                    printf("%d ",ocupacao[i]);
				Pause();
				for(int i =0;i != 10;i++)
                    ocupacao[i] = 0;
                goto menu;
			}

			TPalavra* Pencontrada = Hash1->buscar(Hash1,palavraBuscada);


			if (Pencontrada == NULL) {
				printf("\n\nPalavra nao encontrada.\n\n");
				Pause();
			} else {
				Pencontrada->imprimir(Pencontrada, LivroGuarani);
				printf("\n\n");
				Pause();
			}

			}
		} else if (opcao == 2) {
			int loop;
			for (loop = 1;loop != 0;) {

			system("cls");
			printf("\n\nBusque uma palavra: ");
			scanf("%s",palavraBuscada);
			loop = strcmp(palavraBuscada,"-1");

			if(strcmp(palavraBuscada,"exit") == 0) {
				goto menu;
			}

			if(strcmp(palavraBuscada,"analytics") == 0) {
                system("cls");
				TDadoHash* DadoHash2 = Hash2->dadoHash;
				float percentagem = ((DadoHash2->ocupacao*100.0)/DadoHash2->tamanho*1.0);

                for(int i=0;i < DadoHash2->tamanho;i++) {
                    TDSemiDinamico * lista2 = DadoHash2->vetor[i];
                    if(lista2 != NULL){
                        TDadoLista * Dadolista2 = lista2->dadoLista;
                        ocupacao[Dadolista2->NElementos] +=1;
                    }
                }
				printf("\n\nTamanho da Hash deste livro: %d",DadoHash2->tamanho);
				printf("\n\nOcupacao da Hash: %d",DadoHash2->ocupacao);
				printf("\n\nTaxa de Ocupacao da Hash deste livro: %f %%",percentagem);
				printf("\n\nOcupacao das Entradas: ");
				for(int i =0;i != 10;i++)
                    printf("%d ",ocupacao[i]);
				Pause();
				for(int i =0;i != 10;i++)
                    ocupacao[i] = 0;
				goto menu;
			}

			TPalavra* Pencontrada = Hash2->buscar(Hash2,palavraBuscada);


			if (Pencontrada == NULL) {
				printf("\n\nPalavra nao encontrada.\n\n");
				Pause();
			} else {
				Pencontrada->imprimir(Pencontrada, LivroAventuras);
				printf("\n\n");
				Pause();
			}

			}

		} else if (opcao == 3) {
			int loop;
			for (loop = 1;loop != 0;) {

			system("cls");
			printf("\n\nBusque uma palavra: ");
			scanf("%s",palavraBuscada);
			loop = strcmp(palavraBuscada,"-1");

			if(strcmp(palavraBuscada,"exit") == 0) {
				goto menu;
			}

			if(strcmp(palavraBuscada,"analytics") == 0) {
                system("cls");
				TDadoHash* DadoHash3 = Hash3->dadoHash;
				float percentagem = ((DadoHash3->ocupacao*100.0)/DadoHash3->tamanho*1.0);

                for(int i=0;i < DadoHash3->tamanho;i++) {
                    TDSemiDinamico * lista3 = DadoHash3->vetor[i];
                    if(lista3 != NULL){
                       TDadoLista * Dadolista3 = lista3->dadoLista;
                        ocupacao[Dadolista3->NElementos] +=1;
                    }
                }

				printf("\n\nTamanho da Hash deste livro: %d",DadoHash3->tamanho);
				printf("\n\nOcupacao da Hash: %d",DadoHash3->ocupacao);
				printf("\n\nTaxa de Ocupacao da Hash deste livro: %f %%",percentagem);
				printf("\n\nOcupacao das Entradas: ");
				for(int i =0;i != 10;i++)
                    printf("%d ",ocupacao[i]);
				Pause();
				for(int i =0;i != 10;i++)
                    ocupacao[i] = 0;
				goto menu;
			}

			TPalavra* Pencontrada = Hash3->buscar(Hash3,palavraBuscada);


			if (Pencontrada == NULL) {
				printf("\n\nPalavra nao encontrada.\n\n");
				Pause();
			} else {
				Pencontrada->imprimir(Pencontrada, LivroParalelismo);
				printf("\n\n");
				Pause();
			}

			}

		} else if (opcao == 0) {
			Hash1->destruir(Hash1);
			Hash2->destruir(Hash2);
			Hash3->destruir(Hash3);
			exit(0);
		}else{
            printf("\n\n Digite uma opção valida!\n");
            goto menu;
		}
	return 0;

}

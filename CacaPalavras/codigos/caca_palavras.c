#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "adinamico.h"
#include "palavra.h"
#include "Hash.h"
#include "ABB.h"

#define TAM 200

//Lê palavras no arquivo e coloca num ArrayDinamico

TArrayDinamico* ObtemPalavras(char *diretorio,int tamanho){
	TArrayDinamico* ADI = criarADI(tamanho);
	char Palavra[200];
	FILE* arquivo = fopen(diretorio,"r");
    if(arquivo != NULL){
        while((fscanf(arquivo,"%s\n",Palavra)) != EOF){
            strcpy(Palavra,strupr(Palavra));
            TPalavra* Word = criarPalavra(Palavra);
            ADI->inserir(ADI,Word);
        }
    }else{
        printf("\n\n Arquivo '%s' Não Encontrado !\n\n",diretorio);
    }
    fclose(arquivo);
	return ADI;
}

//VERIFICA SE UMA PALAVRA PODE SER ESCRITA EM UMA LINHA DO TABULEIRO
int verificaLinha(char mat[TAM][TAM], char palavra[],int linha) {
    int tamPalavra;
    int retorno;
    tamPalavra = strlen(palavra);
    int contador = 0;
    int indice = 0;

    while((contador != tamPalavra) && indice < TAM) {
        if((mat[linha][indice] == '%') || mat[linha][indice] == palavra[contador]) {
            contador += 1;
        }else {
            contador = 0;
        }

        indice += 1;
    }


    if((indice == TAM) && contador != tamPalavra) {
        retorno = 300;
    }else {
        retorno = indice-(tamPalavra);
    }

    return retorno;

}

//VERIFICA SE UMA PALAVRA PODE SER ESCRITA EM UMA COLUNA DO TABULEIRO
int verificaColuna(char mat[TAM][TAM], char palavra[],int coluna) {
    int tamPalavra;
    int retorno;
    tamPalavra = strlen(palavra);
    int contador = 0;
    int indice = 0;

    while((contador != tamPalavra) && indice < TAM) {
        if((mat[indice][coluna] == '%') || mat[indice][coluna] == palavra[contador]) {
            contador += 1;
        }else {
            contador = 0;
        }

        indice += 1;
    }


    if((indice == TAM) && contador != tamPalavra) {
        retorno = 300;
    }else {
        retorno = indice-(tamPalavra);
    }

    return retorno;

}

//RETORNA UMA LETRA ALEATÓRIA
int Random() {
    int valor = rand() % TAM;

    return valor;
}

//RETORNA UMA LETRA ALEATÓRIA
char RandomLetra() {
    char valor = 'A' + (char)(rand()%26);

    return valor;
}

//RETORNA UMA ORIENTAÇÃO (VERTICAL OU HORIZONTAL)
int Orientacao() {
    int orientacao;
    int valor = rand();

    if((valor%2) == 0) {
        orientacao = 0;
    }else {
        orientacao = 1;
    }

    return orientacao;
}

//IMPRIME O TABULEIRO NA TELA
void ImprimeTabuleiro(char mat[TAM][TAM]) {
    int coluna = 0;
    int linha = 0;

    while(linha < TAM) {
        coluna = 0;
        while(coluna < TAM) {
            printf("%c ",mat[linha][coluna]);

            coluna += 1;
        }
        printf("\n");
        linha += 1;
    }
}

//PREENCHE TODAS AS CÉLULAS DO TABULEIRO COM '%'
void ZeraTabuleiro(char mat[TAM][TAM]) {
    int linha = 0;
    int coluna = 0;

    while (linha < TAM) {        //"ZERANDO" MATRIZ - '%' È CONSIDERADO VAZIO
        coluna = 0;
        while(coluna < TAM) {
            mat[linha][coluna] = '%';

            coluna++;
        }
        coluna = 0;
        linha++;
    }
}

//INSERE NO TABULEIRO UMA PALAVRA
void InsereTabuleiro(char mat[TAM][TAM],int orientacao, char palavra[]) {
    int inseriu = 0;
    srand(time(NULL));

    while(!inseriu) {
        int linhaRand = rand() % TAM;
        int colunaRand = linhaRand;
        if(orientacao) {

            if(verificaLinha(mat,palavra,linhaRand) != 300){
                inseriu = 1;
                int indice_palavra=0;
                int indice_coluna = verificaLinha(mat,palavra,linhaRand);
                while(palavra[indice_palavra] != '\0'){
                    mat[linhaRand][indice_coluna] = palavra[indice_palavra];
                    indice_coluna++;
                    indice_palavra++;
                }
            }
        }else {
            if(verificaColuna(mat,palavra,colunaRand) != 300){
                inseriu = 1;
                int indice_palavra = 0;
                int indice_linha = verificaColuna(mat,palavra,colunaRand);
                while(palavra[indice_palavra] != '\0'){
                    mat[indice_linha][colunaRand] = palavra[indice_palavra];
                    indice_linha++;
                    indice_palavra++;
                }
            }

        }
    }
}

//IMPRIME O TABULEIRO EM UM ARQUIVO .TXT
void ImprimeTabuleiroTXT(char mat[TAM][TAM]) {
    int coluna = 0;
    int linha = 0;

    FILE* arquivo;

    arquivo = fopen("saida/tabuleiro.txt","w");

    if(arquivo != NULL) {

        while(linha < TAM) {
            coluna = 0;
            while(coluna < TAM) {
                fprintf(arquivo,"%c ",mat[linha][coluna]);

                coluna += 1;
            }
            fprintf(arquivo,"\n");
            linha += 1;
        }

    }else {
        printf("\n\nArquivo 'tabuleiro.txt' nao gerado!\n\n");

    }
    printf("\n\nArquivo 'tabuleiro.txt' gerado com sucesso\n\n");
    fclose(arquivo);
}

//IMPRIME AS PALAVRAS NAO ENCONTRADAS NO ARQUIVO TXT
void ImprimeNaoEncontradasTXT(TArrayDinamico* vetor) {

    FILE* arquivo;
    int indice = 0;

    arquivo = fopen("saida/Nao_Encontradas.txt","w");

    if(arquivo != NULL) {
        vetor->ordenar(vetor,0);
        TDadosADI* dadoVetor = vetor->dadosADI;
        fprintf(arquivo,"Palavras Nao Encontradas\n\n");
        while(indice < dadoVetor->ocupacao) {
            TPalavra* palavra = dadoVetor->vetor[indice];
            TDadosPalavra* dadosPalavra = palavra->dadosPalavra;
            fprintf(arquivo,"%s\n",dadosPalavra->palavra);

            indice += 1;
        }
    }else {
        printf("\n\nArquivo 'Nao_Encontradas.txt' nao gerado!\n\n");

    }
    printf("\n\nArquivo 'Nao_Encontradas.txt' gerado com sucesso\n\n");
    fclose(arquivo);
}

//IMPRIME AS PALAVRAS E SUAS POSIÇÕES NO ARQUIVO TXT
void ImprimeEncontradasTXT(THash* tabela) {

    FILE* arquivo;
    int indice = 0;

    arquivo = fopen("saida/Encontradas.txt","a");

    if(arquivo != NULL) {
        TDadoHash* dadoTabela = tabela->dadoHash;
        fprintf(arquivo,"Palavras Encontradas\n\n"); //ARQUIVO
        printf("Palavras Encontradas\n\n"); //TELA
        while(indice < dadoTabela->tamanho) {
            TABB* arvore = dadoTabela->vetor[indice];
            TDadosABB* dadoArvore = arvore->dadosABB;
            arvore->imprime(dadoArvore->Raiz,arquivo);
            indice += 1;
        }
    }else {
        printf("\n\nArquivo 'Encontradas.txt' nao gerado!\n\n");

    }
    printf("\n\nArquivo 'Encontradas.txt' gerado com sucesso\n\n");
    fclose(arquivo);
}

//PREENCHE QUALQUER CÉLULA VAZIA COM UMA LETRA ALEATÓRIA
void CompletaTabuleiro(char mat[TAM][TAM]) {
    int coluna = 0;
    int linha = 0;
    while(linha < TAM) {
        coluna = 0;
        while(coluna < TAM) {
            if(mat[linha][coluna] == '%') {
                mat[linha][coluna] = RandomLetra();
            }
            coluna += 1;
        }
        linha += 1;
    }
}

//BUSCA PALAVRAS NO TABULEIRO
TPalavra* BuscaTabuleiro(char mat[TAM][TAM], char palavra[]) {
    int orientacao = 0;
    int contador = 0;
    int tamPalavra = strlen(palavra);
    int indice = 0;
    int linha = 0;
    int coluna = 0;

    TPalavra* Word = NULL;


    while((linha < TAM || coluna < TAM) && (Word == NULL)) {
        if(!orientacao) {
            while((contador != tamPalavra) && (indice < TAM)) {
                if((mat[linha][indice] == palavra[contador])) {
                    contador += 1;
                }else {
                    contador = 0;
                }

                indice += 1;
            }

            if(indice == TAM && contador != tamPalavra) {
                indice = 0;
                orientacao = 1;
                linha += 1;
            }else{
                Word = criarPalavra(palavra);
                TDadosPalavra* dadoWord = Word->dadosPalavra;
                dadoWord->coluna = (indice-tamPalavra);
                dadoWord->linha = linha;
                dadoWord->orientacao = 'H';
            }
        }else{
            while((contador != tamPalavra) && indice < TAM) {
                if((mat[indice][coluna] == palavra[contador])) {
                    contador += 1;
                }else {
                    contador = 0;
                }

                indice += 1;
            }
            if(indice == TAM && contador != tamPalavra) {
                indice = 0;
                orientacao = 0;
                coluna += 1;
            }else{
                Word = criarPalavra(palavra);
                TDadosPalavra* dadoWord = Word->dadosPalavra;
                dadoWord->coluna = coluna;
                dadoWord->linha = (indice-tamPalavra);
                dadoWord->orientacao = 'V';
            }
        }
    }
    return Word;
}

int main () {
    srand(time(NULL));
	//Pré-Processamento - Gerando Tabuleiro
	int tamanho = 100000;
    int indice = 1;

    char tabuleiro[TAM][TAM];
    ZeraTabuleiro(tabuleiro);

    TArrayDinamico* PalavrasEntrada = ObtemPalavras("entrada.txt",tamanho);         //PALAVRAS DO ARQUIVO INSERIDAS NO ADI
    PalavrasEntrada->ordenar(PalavrasEntrada,1);                                     //ORDENA AS PALAVRAS EM ORDEM ALFABETICA CRESCENTE
    TDadosADI* dadosEntrada = PalavrasEntrada->dadosADI;

    while(indice < dadosEntrada->ocupacao) {                              //INSERINDO PALAVRAS NO TABULEIRO
        TPalavra* palavra = dadosEntrada->vetor[indice];
        TDadosPalavra* dadoPalavra = palavra->dadosPalavra;
        InsereTabuleiro(tabuleiro,Orientacao(),dadoPalavra->palavra);

        indice++;
    }

    printf("Quantidade de palavras: %d\n\n",dadosEntrada->ocupacao);

    CompletaTabuleiro(tabuleiro);  //PREENCHE POSICOES VAZIAS NO TABULEIRO COM LETRAS ALEATORIAS

    indice = 0;

    //Processamento - Busca de palavras no Tabuleiro

    TArrayDinamico* PalavrasCacadas = ObtemPalavras("busca.txt",tamanho);
    TDadosADI* dadosCacada = PalavrasCacadas->dadosADI;

    THash* Encontradas = criarHash(26);
    TArrayDinamico* NaoEncontradas = criarADI(tamanho);

    while(indice < dadosCacada->ocupacao) {
        TPalavra* procurado = dadosCacada->vetor[indice];
        TDadosPalavra* dadoProcurado = procurado->dadosPalavra;

        TPalavra* resultado = BuscaTabuleiro(tabuleiro,dadoProcurado->palavra);
        if(resultado != NULL) {
            Encontradas->inserir(Encontradas,resultado);           //PALAVRAS ENCONTRADAS SÃO INSERIDAS NA HASH
        }else{
            NaoEncontradas->inserir(NaoEncontradas,procurado);     //PALAVRAS NÃO ENCONTRADAS SÃO INSERIDAS EM UM TADI
        }

        indice += 1;
    }

    //RETORNA OS ARQUIVOS DE SAÍDA
    ImprimeTabuleiroTXT(tabuleiro);
    ImprimeEncontradasTXT(Encontradas);
    ImprimeNaoEncontradasTXT(NaoEncontradas);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candidato.h"

TDadosCandidato* criarDadosCandidato(char nome[], char cidade[], char bairro[], int fase, char lingua[]){
    TDadosCandidato* dadoCand = malloc(sizeof(TDadosCandidato));
    if(dadoCand != NULL){
        strcpy(dadoCand->nome,nome);
        strcpy(dadoCand->cidade,cidade);
        strcpy(dadoCand->bairro,bairro);
        dadoCand->fase = fase;
        strcpy(dadoCand->opcaoEstrangeira,lingua);
    }

    return dadoCand;
}

void ImprimeCandArq(TCandidato* cand, FILE* arq){
    TDadosCandidato* dadoCand = cand->dadosCandidato;
    fprintf(arq,"Nome: %s\nCidade: %s\nBairro: %s\nFase: %d fase\nOpcao Estrangeira: %s\nEscola %d\nSala %d\n\n",dadoCand->nome,dadoCand->cidade,dadoCand->bairro,dadoCand->fase,dadoCand->opcaoEstrangeira,dadoCand->escola,dadoCand->sala);
}

void ImprimeTela(TCandidato* cand){
    TDadosCandidato* dadoCand = cand->dadosCandidato;
    printf("Nome: %s\nCidade: %s\nBairro: %s\nFase: %d fase\nOpcao Estrangeira: %s\nEscola %d\nSala %d\n\n",dadoCand->nome,dadoCand->cidade,dadoCand->bairro,dadoCand->fase,dadoCand->opcaoEstrangeira,dadoCand->escola,dadoCand->sala);
}

void AtualizaDados(TCandidato* cand, int escola, int sala){
    TDadosCandidato* dadoCand = cand->dadosCandidato;
    dadoCand->escola = escola;
    dadoCand->sala = sala;
}

TCandidato* criarCandidato(char nome[], char cidade[], char bairro[], int fase, char lingua[]){
    TCandidato* cand = malloc(sizeof(TCandidato));
    if(cand != NULL){
        cand->dadosCandidato = criarDadosCandidato(nome,cidade,bairro,fase,lingua);
        cand->imprimeCandArq = ImprimeCandArq;
        cand->imprimeTela = ImprimeTela;
        cand->atualizaDado = AtualizaDados;
    }

    return cand;
}

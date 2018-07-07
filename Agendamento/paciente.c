#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paciente.h"

//CRIA OS DADOS DE UM ARRAY DINÂMICO COM TAMANHO INICIAL
static TDadosPaciente* criarDadosPaciente(char nome[], char telefone[]){
	TDadosPaciente *aloca = malloc(sizeof(TDadosPaciente));
	if(aloca!= NULL){
		strcpy(aloca->nome,nome);
		strcpy(aloca->telefone,telefone);
	}
	return aloca;
}

static void imprimePaciente(TPaciente* alguem) {
    TDadosPaciente* dadoAlguem = alguem->dadoPaciente;
    printf("\n\nNome: %s\nTelefone: %s\n",dadoAlguem->nome, dadoAlguem->telefone);
}

TPaciente* criarPaciente(char nome[], char telefone[]){
	TPaciente *alguem = malloc(sizeof(TPaciente));
	if(alguem != NULL){
		alguem->dadoPaciente = criarDadosPaciente(nome, telefone);
        alguem->imprimirPaciente = imprimePaciente;
	}

	return alguem;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "adinamico.h"
#include "paciente.h"
#include "rubronegra.h"

TArrayDinamico* criarAgenda(int tamanho) {
	int contador1 = 0;
	int contador2;
	int contador3;
	int contador4;

	TArrayDinamico* agenda = criarADI(tamanho);
	TDadosADI* dadoAgenda = agenda->dadosADI;

	while(contador1 < dadoAgenda->tamanho){
		dadoAgenda->vetor[contador1] = criarADI(12);
		TArrayDinamico* Ano = dadoAgenda->vetor[contador1];
		TDadosADI* dadoAno = Ano->dadosADI;
		contador2 = 0;
		while(contador2 < dadoAno->tamanho){
			dadoAno->vetor[contador2] = criarADI(31);
			TArrayDinamico* mes = dadoAno->vetor[contador2];
			TDadosADI* dadoMes = mes->dadosADI;
			contador3 = 0;
			while(contador3 < dadoMes->tamanho){
				dadoMes->vetor[contador3] = criarADI(23);
				TArrayDinamico* dia = dadoMes->vetor[contador3];
				TDadosADI* dadoDia = dia->dadosADI;
				contador4 = 0;
				while(contador4 < dadoDia->tamanho){
					dadoDia->vetor[contador4] = NULL;
					contador4 = contador4 + 1;
				}
				contador3 = contador3 + 1;
			}
			contador2 = contador2 + 1;
		}

		contador1 = contador1 + 1;
	}

	return agenda;
}

void InserirAgenda(TArrayDinamico* agenda, TPaciente* alguem, int dia, int mes, int hora){
	mes -= 1;
	dia -= 1;

	TDadosADI* dadoAgenda = agenda->dadosADI;

	TArrayDinamico* ano = dadoAgenda->vetor[0];
	TDadosADI* dadoAno = ano->dadosADI;
	TArrayDinamico* mes2 = dadoAno->vetor[mes];
	TDadosADI* dadoMes2 = mes2->dadosADI;
	TArrayDinamico* dia2 = dadoMes2->vetor[dia];

	dia2->inserirposicao(dia2, alguem, hora);

}

void exibirAgenda(TArrayDinamico* agenda){
	int mes, dia;
	int contador = 0;
	int achou = 0;
	printf("Digite a data no formato correto (26/10): ");
	setbuf(stdin,NULL);
	scanf("%d/%d",&dia,&mes);

	mes -= 1;
	dia -= 1;

	TDadosADI* dadoAgenda = agenda->dadosADI;
	TArrayDinamico* ano = dadoAgenda->vetor[0];
	TDadosADI* dadoAno = ano->dadosADI;
	TArrayDinamico* mes2 = dadoAno->vetor[mes];
	TDadosADI* dadoMes2 = mes2->dadosADI;
	TArrayDinamico* dia2 = dadoMes2->vetor[dia];
	TDadosADI* dadoDia2 = dia2->dadosADI;

	while(contador < dadoDia2->tamanho){
		if(dadoDia2->vetor[contador] != NULL){
			achou = 1;
			TPaciente* alguem = dadoDia2->vetor[contador];
			alguem->imprimirPaciente(alguem);
			printf("Horario: %dh\n\n",contador);
		}
		contador = contador + 1;
	}

	if((achou == 0) && (contador == dadoDia2->tamanho)){
		printf("\n\nSem pacientes nesta data!");
	}

}

void novoPaciente(TArrayDinamico* agenda){
	char nome[50];
	char telefone[10];
	int dia;
	int mes;
	int hora;

	printf("\n\nDigite o nome do paciente: ");
	setbuf(stdin,NULL);
	scanf("%s",nome);
	printf("\n\nDigite o telefone: ");
	setbuf(stdin,NULL);
	scanf("%s",telefone);
	printf("\n\nDigite a data no formato correto (26/10): ");
	setbuf(stdin,NULL);
	scanf("%d/%d",&dia,&mes);
	printf("\n\nDigite apenas o valor da hora (formato 24h): ");
	setbuf(stdin,NULL);
	scanf("%d",&hora);
	TPaciente* novo = criarPaciente(nome,telefone);
	InserirAgenda(agenda, novo, dia, mes, hora);
}

void chamadaAgenda(TArrayDinamico* agenda){
	int mes, dia;
	int contador = 0;
	int achou = 0;
	printf("Digite a data no formato correto (26/10): ");
	setbuf(stdin,NULL);
	scanf("%d/%d",&dia,&mes);

	mes -= 1;
	dia -= 1;

	TDadosADI* dadoAgenda = agenda->dadosADI;
	TArrayDinamico* ano = dadoAgenda->vetor[0];
	TDadosADI* dadoAno = ano->dadosADI;
	TArrayDinamico* mes2 = dadoAno->vetor[mes];
	TDadosADI* dadoMes2 = mes2->dadosADI;
	TArrayDinamico* dia2 = dadoMes2->vetor[dia];
	TDadosADI* dadoDia2 = dia2->dadosADI;

	while(contador < dadoDia2->tamanho){
		if(dadoDia2->vetor[contador] != NULL){
			achou = 1;
			TPaciente* alguem = dadoDia2->vetor[contador];
			TDadosPaciente* dadoAlguem = alguem->dadoPaciente;
			alguem->imprimirPaciente(alguem);
			printf("Horario: %dh\n",contador);
			if((rand() % 100)%2 == 0){
				dadoAlguem->presenca = 1;
				printf("Atendido\n\n");
			}else{
				dadoAlguem->presenca = 0;
				printf("Nao antendido\n\n");
			}
		}
		contador = contador + 1;
	}

	if((achou == 0) && (contador == dadoDia2->tamanho)){
		printf("\n\nSem pacientes nesta data!");
	}
}

void imprimeAtendimento(TArrayDinamico* agenda){
	int contador1 = 0;
	int contador2;
	int contador3;
	int contador4;

	FILE* arquivo;
	arquivo = fopen("../saida/atendimento.txt","w");
	TDadosADI* dadoAgenda = agenda->dadosADI;
	TRubroNegra* atendidos = criarRubroNegra();
	TRubroNegra* naoAtendidos = criarRubroNegra();

	while(contador1 < dadoAgenda->tamanho){
		TArrayDinamico* Ano = dadoAgenda->vetor[contador1];
		TDadosADI* dadoAno = Ano->dadosADI;
		contador2 = 0;
		while(contador2 < dadoAno->tamanho){
			TArrayDinamico* mes = dadoAno->vetor[contador2];
			TDadosADI* dadoMes = mes->dadosADI;
			contador3 = 0;
			while(contador3 < dadoMes->tamanho){
				TArrayDinamico* dia = dadoMes->vetor[contador3];
				TDadosADI* dadoDia = dia->dadosADI;
				contador4 = 0;
				while(contador4 < dadoDia->tamanho){
					if(dadoDia->vetor[contador4] != NULL){
						TPaciente* alguem = dadoDia->vetor[contador4];
						TDadosPaciente* dadoAlguem = alguem->dadoPaciente;
						if(dadoAlguem->presenca == 1){
							atendidos->inserir(atendidos,alguem);
						}else {
							naoAtendidos->inserir(naoAtendidos,alguem);
						}
					}
					contador4 = contador4 + 1;
				}
				contador3 = contador3 + 1;
			}
			contador2 = contador2 + 1;
		}

		contador1 = contador1 + 1;
	}

	TDadosRubroNegra* dadoAtendidos = atendidos->dadosRubroNegra;
	TDadosRubroNegra* dadoNaoAtendidos = naoAtendidos->dadosRubroNegra;

	printf("\n\nAtendidos:\n");
	fprintf(arquivo,"\n\nAtendidos:\n");
	atendidos->imprime(dadoAtendidos->Raiz,arquivo);
	printf("\n\nNao Atendidos\n");
	fprintf(arquivo,"\n\nNao Atendidos:\n");
	naoAtendidos->imprime(dadoNaoAtendidos->Raiz,arquivo);

}

int main(){
	int opcao = 99;
	srand(time(NULL));

	TArrayDinamico* Agenda = criarAgenda(5);

	while(opcao != 0){
		printf("\n\nAgendamento de Consultas\n\n");
		printf("Marcar agendamento [1]\n");
		printf("Exibir agenda [2]\n");
		printf("Chamar agenda do dia [3]\n");
		printf("Finalizar dia [4]\n");
		printf("op: ");
		setbuf(stdin,NULL);
		scanf("%d",&opcao);

		switch(opcao){
			case 1:
				novoPaciente(Agenda);
			break;

			case 2:
				exibirAgenda(Agenda);
			break;

			case 3:
				chamadaAgenda(Agenda);
			break;

			case 4:
				imprimeAtendimento(Agenda);
			break;

			case 0:
			break;

			default:
				printf("\n\nOpcao Invalida!");
		}
	}

	return 0;
}

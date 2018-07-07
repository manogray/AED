#ifndef PACIENTE_H_
#define PACIENTE_H_

typedef struct Paciente TPaciente;

//Métodos do Tipo TPaciente
typedef void (*TimprimePaciente)(TPaciente *alguem);

//Dados do Tipo TPaciente
typedef struct dadosPaciente{
	char nome[200];
	char telefone[20];
	int presenca;
} TDadosPaciente;

struct Paciente{
	void *dadoPaciente; //Dados encapsulados
	TimprimePaciente imprimirPaciente;
};

//Funcao construtor do TPaciente
TPaciente* criarPaciente(char nome[], char telefone[]);
#endif /* PACIENTE_H_ */

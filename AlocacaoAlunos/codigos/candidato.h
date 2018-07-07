#ifndef CANDIDATO_H_
#define CANDIDATO_H_

typedef struct Candidato TCandidato;

//Metodos do Tipo Candidato
typedef void (*TImprimeArq)(TCandidato* cand, FILE* arq);
typedef void (*TImprimeTela)(TCandidato* cand);
typedef void (*TAtualiza)(TCandidato* cand, int escola, int sala);

typedef struct dadosCandidato{
	char nome[200];
	char cidade[200];
	char bairro[200];
	int fase;
	char opcaoEstrangeira[100];
	int escola;
	int sala;
}TDadosCandidato;

struct Candidato {
    void* dadosCandidato;
    TImprimeArq imprimeCandArq;
    TImprimeTela imprimeTela;
    TAtualiza atualizaDado;
};

TCandidato* criarCandidato(char nome[],char cidade[],char bairro[], int fase, char lingua[]);
#endif /* CANDIDATO_H_ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "btree.h"
#include "adinamico.h"
#include "candidato.h"

char* retornaLingua(){
    char* resp=(char*)calloc(100,sizeof(char));
    int sort = rand() % 2;
    if(sort == 0){
        strcpy(resp,"Ingles");
    }else {
        strcpy(resp,"Espanhol");
    }

    return resp;
}

char* retornaCidade(){
    char* resp=(char*)calloc(100,sizeof(char));
    int sort = rand() % 6;
    switch(sort){
        case 0:
            strcpy(resp,"MANAUS");
            break;
        case 1:
            strcpy(resp,"BENJAMIN CONSTANT");
            break;
        case 2:
            strcpy(resp,"COARI");
            break;
        case 3:
            strcpy(resp,"ITACOATIARA");
            break;
        case 4:
            strcpy(resp,"HUMAITA");
            break;
        case 5:
            strcpy(resp,"PARINTINS");
            break;
    }

    return resp;
}

char* retornaBairro(char cidade[]){
    char* resp=(char*)calloc(100,sizeof(char));
    int sort = rand() % 5;
    if(strcmp(cidade,"MANAUS") == 0){
        switch(sort){
            case 0:
                strcpy(resp,"CENTRO");
                break;
            case 1:
                strcpy(resp,"PONTA NEGRA");
                break;
            case 2:
                strcpy(resp,"CIDADE NOVA");
                break;
            case 3:
                strcpy(resp,"ALEIXO");
                break;
            case 4:
                strcpy(resp,"CIDADE DE DEUS");
                break;
        }
    }
    if(strcmp(cidade,"PARINTINS") == 0){
        switch(sort){
            case 0:
                strcpy(resp,"CENTRO");
                break;
            case 1:
                strcpy(resp,"CASTANHEIRA");
                break;
            case 2:
                strcpy(resp,"PAULO CORREA");
                break;
            case 3:
                strcpy(resp,"ITAUNA I");
                break;
            case 4:
                strcpy(resp,"FRANCESA");
                break;
        }
    }
    if(strcmp(cidade,"ITACOATIARA") == 0){
        switch(sort){
            case 0:
                strcpy(resp,"CENTRO");
                break;
            case 1:
                strcpy(resp,"VITORIA");
                break;
            case 2:
                strcpy(resp,"PEDREIRAS");
                break;
            case 3:
                strcpy(resp,"IRACI");
                break;
            case 4:
                strcpy(resp,"SAO JORGE");
                break;
        }
    }
    if(strcmp(cidade,"BENJAMIN CONSTANT") == 0){
        switch(sort){
            case 0:
                strcpy(resp,"CENTRO");
                break;
            case 1:
                strcpy(resp,"COIMBRA");
                break;
            case 2:
                strcpy(resp,"COHABAM");
                break;
            case 3:
                strcpy(resp,"BOM JARDIM");
                break;
            case 4:
                strcpy(resp,"UMARIZAL");
                break;
        }
    }
    if(strcmp(cidade,"COARI") == 0){
        switch(sort){
            case 0:
                strcpy(resp,"CENTRO");
                break;
            case 1:
                strcpy(resp,"UNIAO");
                break;
            case 2:
                strcpy(resp,"SANTA HELENA");
                break;
            case 3:
                strcpy(resp,"URUCU");
                break;
            case 4:
                strcpy(resp,"ITAMARATI");
                break;
        }
    }
    if(strcmp(cidade,"HUMAITA") == 0){
        switch(sort){
            case 0:
                strcpy(resp,"CENTRO");
                break;
            case 1:
                strcpy(resp,"NOVA HUMAITA");
                break;
            case 2:
                strcpy(resp,"DIVINO PRANTO");
                break;
            case 3:
                strcpy(resp,"SAO PEDRO");
                break;
            case 4:
                strcpy(resp,"NOVA ESPERANCA");
                break;
        }
    }

    return resp;
}

int retornaFase(){
    int sort = rand() % 3;
    sort = sort + 1;

    return sort;
}

TArrayDinamico* ObtemPalavras(char *diretorio,int tamanho){
	TArrayDinamico* ADI = criarADI(tamanho);
	char nome[200];
	char cidade[200];
	char bairro[200];
	int fase;
	char lingua[100];

	FILE* arquivo = fopen(diretorio,"r");
    if(arquivo != NULL){
        while((fgets(nome,sizeof(nome),arquivo)) != NULL){
            nome[strlen(nome)-1] = '\0';
            strcpy(nome,strupr(nome));
            strcpy(cidade,retornaCidade());
            strcpy(bairro,retornaBairro(cidade));
            fase = retornaFase();
            strcpy(lingua,retornaLingua());
            TCandidato* Cand = criarCandidato(nome,cidade,bairro,fase,lingua);
            ADI->inserir(ADI,Cand);
        }
    }else{
        printf("\n\n Arquivo '%s' Não Encontrado !\n\n",diretorio);
    }
    fclose(arquivo);
	return ADI;
}

TArrayDinamico* criarLocaisDeProva(){
    int contador = 0;
    int contador2;
    int contador3;
    int contador4;

    TArrayDinamico* cidades = criarADI(6);
    TDadosADI* dadoCidades = cidades->dadosADI;
    while(contador < dadoCidades->tamanho){
        dadoCidades->vetor[contador] = criarADI(5);
        TArrayDinamico* bairros = dadoCidades->vetor[contador];
        TDadosADI* dadoBairros = bairros->dadosADI;
        contador = contador + 1;
        contador2 = 0;
        while(contador2 < dadoBairros->tamanho){
            dadoBairros->vetor[contador2] = criarADI(6);
            TArrayDinamico* escolas = dadoBairros->vetor[contador2];
            TDadosADI* dadoEscolas = escolas->dadosADI;
            contador2 = contador2 + 1;
            contador3 = 0;
            while(contador3 < dadoEscolas->tamanho){
                dadoEscolas->vetor[contador3] = criarADI(20);
                TArrayDinamico* salas = dadoEscolas->vetor[contador3];
                TDadosADI* dadoSalas = salas->dadosADI;
                contador3 = contador3 + 1;
                contador4 = 0;
                while(contador4 < dadoSalas->tamanho){
                    dadoSalas->vetor[contador4] = criarADI(30);
                    contador4 = contador4 + 1;
                }
            }
        }
    }

    return cidades;
}

int indiceCidade(char cidade[100]){
    int ind;
    if(strcmp(cidade,"MANAUS") == 0){ind = 0;}
    if(strcmp(cidade,"BENJAMIN CONSTANT") == 0){ind = 1;}
    if(strcmp(cidade,"COARI") == 0){ind = 2;}
    if(strcmp(cidade,"ITACOATIARA") == 0){ind = 3;}
    if(strcmp(cidade,"HUMAITA") == 0){ind = 4;}
    if(strcmp(cidade,"PARINTINS") == 0){ind = 5;}

    return ind;
}

int indiceBairro(char cidade[100], char bairro[100]){
    int ind;
    if(strcmp(cidade,"MANAUS") == 0){
        if(strcmp(bairro,"CENTRO")){ind = 0;}
        if(strcmp(bairro,"PONTA NEGRA")){ind = 1;}
        if(strcmp(bairro,"CIDADE NOVA")){ind = 2;}
        if(strcmp(bairro,"ALEIXO")){ind = 3;}
        if(strcmp(bairro,"CIDADE DE DEUS")){ind = 4;}
    }
    if(strcmp(cidade,"PARINTINS") == 0){
        if(strcmp(bairro,"CENTRO")){ind = 0;}
        if(strcmp(bairro,"CASTANHEIRA")){ind = 1;}
        if(strcmp(bairro,"PAULO CORREA")){ind = 2;}
        if(strcmp(bairro,"ITAUNA I")){ind = 3;}
        if(strcmp(bairro,"FRANCESA")){ind = 4;}
    }
    if(strcmp(cidade,"ITACOATIARA") == 0){
        if(strcmp(bairro,"CENTRO")){ind = 0;}
        if(strcmp(bairro,"VITORIA")){ind = 1;}
        if(strcmp(bairro,"PEDREIRAS")){ind = 2;}
        if(strcmp(bairro,"IRACI")){ind = 3;}
        if(strcmp(bairro,"SAO JORGE")){ind = 4;}
    }
    if(strcmp(cidade,"BENJAMIN CONSTANT") == 0){
        if(strcmp(bairro,"CENTRO")){ind = 0;}
        if(strcmp(bairro,"COIMBRA")){ind = 1;}
        if(strcmp(bairro,"COHABAM")){ind = 2;}
        if(strcmp(bairro,"BOM JARDIM")){ind = 3;}
        if(strcmp(bairro,"UMARIZAL")){ind = 4;}
    }
    if(strcmp(cidade,"COARI") == 0){
        if(strcmp(bairro,"CENTRO")){ind = 0;}
        if(strcmp(bairro,"UNIAO")){ind = 1;}
        if(strcmp(bairro,"SANTA HELENA")){ind = 2;}
        if(strcmp(bairro,"URUCU")){ind = 3;}
        if(strcmp(bairro,"ITAMARATI")){ind = 4;}
    }
    if(strcmp(cidade,"HUMAITA") == 0){
        if(strcmp(bairro,"CENTRO")){ind = 0;}
        if(strcmp(bairro,"NOVA HUMAITA")){ind = 1;}
        if(strcmp(bairro,"DIVINO PRANTO")){ind = 2;}
        if(strcmp(bairro,"SAO PEDRO")){ind = 3;}
        if(strcmp(bairro,"NOVA ESPERANCA")){ind = 4;}
    }

    return ind;
}

int verificaRestricao(TCandidato* cand1, TCandidato* cand2){
    TDadosCandidato* dadoCand1 = cand1->dadosCandidato;
    TDadosCandidato* dadoCand2 = cand2->dadosCandidato;
    int retorno = 0;

    if((strcmp(dadoCand1->opcaoEstrangeira,dadoCand2->opcaoEstrangeira) == 0) && dadoCand1->fase == dadoCand2->fase){
        retorno = 1;
    }

    return retorno;
}

TArrayDinamico* alocaCandidatos(TArrayDinamico* alunos, TArrayDinamico* locais){
    int contador = 0;
    int bairroAtual;
    int escolaAtual;
    int salaAtual;
    int inseriu = 0;

    TDadosADI* dadoAlunos = alunos->dadosADI;
    while(contador < dadoAlunos->ocupacao){
        TCandidato* cand = dadoAlunos->vetor[contador];
        TDadosCandidato* dadoCand = cand->dadosCandidato;
        TDadosADI* dadoLocais = locais->dadosADI;
        TArrayDinamico* bairro = dadoLocais->vetor[indiceCidade(dadoCand->cidade)];
        bairro->atualizarOcupacao(bairro);
        TDadosADI* dadoBairro = bairro->dadosADI;
        bairroAtual = indiceBairro(dadoCand->cidade,dadoCand->bairro);
        TArrayDinamico* escolas = dadoBairro->vetor[bairroAtual];
        TDadosADI* dadoEscolas = escolas->dadosADI;
        while(inseriu == 0){ //ENQUANTO NAO INSERIR UM ALUNO
            escolas->atualizarOcupacao(escolas);
            escolaAtual = rand()%6;
            TArrayDinamico* salas = dadoEscolas->vetor[escolaAtual];
            TDadosADI* dadoSalas = salas->dadosADI;
            salaAtual = rand()%20;
            TArrayDinamico* cadeiras = dadoSalas->vetor[salaAtual];
            TDadosADI* dadoCadeiras = cadeiras->dadosADI;
            if(dadoCadeiras->ocupacao == 0){ //A SALA ESTA VAZIA ?
                cadeiras->inserirposicao(cadeiras,cand,0);
                inseriu = 1;
                cand->atualizaDado(cand,escolaAtual,salaAtual);
                salas->atualizarOcupacao(salas);
            }else{// SE A SALA NAO ESTIVER VAZIA
                TCandidato* determinante = dadoCadeiras->vetor[0];
                if(verificaRestricao(determinante,cand) == 1){//CANDIDATO OBEDECE AS RESTRICOES ?
                    if(dadoCadeiras->ocupacao < dadoCadeiras->tamanho){//SALA TEM ESPACO?
                        cadeiras->inserirposicao(cadeiras,cand,0);
                        inseriu = 1;
                        cand->atualizaDado(cand,escolaAtual,salaAtual);
                        salas->atualizarOcupacao(salas);
                    }
                }
            }
        }
        contador = contador + 1;
        inseriu = 0;
    }

    return alunos;
}

void buscarCandidato(TBtree* tree){
    char pesquisa[200];
    TDadosBtree* dadoTree = tree->dadosBtree;
    while(strcmp(pesquisa,"SAIR") != 0){
        printf("Digite o nome completo do candidato(Digite 'sair' para sair): ");
        setbuf(stdin,NULL);
        scanf("%[^\n]s",pesquisa);
        strcpy(pesquisa,strupr(pesquisa));
        tree->buscarB(dadoTree->raiz,pesquisa);
    }
}

int main() {
    srand(time(NULL));

    //PRE-PROCESSAMENTO DOS ALUNOS
    TArrayDinamico* ListaGeral = ObtemPalavras("../../listageral.txt",100);
    int contador = 0;

    FILE* arquivoSaida = fopen("../../saida.txt","a");
    fprintf(arquivoSaida,"Criando candidatos...\n");

    TArrayDinamico* LocaisDeProva = criarLocaisDeProva();

    fprintf(arquivoSaida,"Alocando candidatos...\n\n");
    TArrayDinamico* ListaGeralAlocada = alocaCandidatos(ListaGeral,LocaisDeProva);
    TDadosADI* dadoListaGeralAlocada = ListaGeralAlocada->dadosADI;
    LocaisDeProva->destruir(LocaisDeProva);

    printf("Criando arquivo de saida...\n\n");
    while(contador < dadoListaGeralAlocada->ocupacao){
        TCandidato* cand = dadoListaGeralAlocada->vetor[contador];
        cand->imprimeCandArq(cand,arquivoSaida);
        contador = contador + 1;
    }
    contador = 0;
    fclose(arquivoSaida);

    TBtree* BDCandidatos = criarBtree(10);

    printf("Inserindo dados em arvore B...\n\n");
    while(contador < dadoListaGeralAlocada->ocupacao){
        TDadosBtree* dadoBD = BDCandidatos->dadosBtree;
        BDCandidatos->inserirB(dadoBD->raiz,dadoListaGeralAlocada->vetor[contador]);

        contador = contador + 1;
    }

    buscarCandidato(BDCandidatos);

    return 0;
}

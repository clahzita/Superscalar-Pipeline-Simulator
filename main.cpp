#include <fstream>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

#define MAX 10
#define MaxPipelines 8
using namespace std;

//Estrutura que guarda os componentes de cada instrução:
// ordem - recebe a ordem em que se encontra a instrução no bloco de instruções
//tipoo - vetor de caracteres que guarda o tipo de operacao Assembly
//receptor - vetor de caracteres do registrados que recebe resultado da operação
//op1 - vetor de caracteres do registrador operando 1
//op2 - vetor de caracteres do registrador operando 2
//depende - mostra um vetor de inteiros que indicam que instruções dependem do receptor da instrução lida
typedef struct tpInstrucao{
	int ordem;
	char tipo[5];
	char receptor[4];
	char op1[4];
	char op2[5];
	int depende[2];
	bool naoExecutando = true;
	int estagio = 0;
} Instrucao;


typedef struct tpEstagios{
	int* BI;
	int* DI;
	int* EX;
	int* MEM;
	int* WB;	
} estagios;

int pegarInstrucao(vector<Instrucao> &instrucoesRestantes, int inst, int pipe);
bool existeInstrucoesASeremExecutadas(vector<Instrucao> &instrucoes);
void liberarInstrucoesExecutadas(vector<Instrucao> &instrucoes);

int main(){

	vector<Instrucao> instrucao;



	//Inicio: Leitura do arquivo txt
	ifstream arquivoInstrucoes ("instrucoes.txt");

	int qtdePipelines;
	int numeroinstrucoes;

	int i=0, j=0;
	int aux;

	if(arquivoInstrucoes.is_open()){

		arquivoInstrucoes >> qtdePipelines;

		if(qtdePipelines > MaxPipelines){
			cout << "Número de Pipelines superior ao máximo suportado (8)." << endl;
			return 0;
		}

		cout << "Número de Pipelines: " << qtdePipelines << endl;

		auto_ptr<Instrucao> inst( new Instrucao);

		//Enquanto nao chega ao final do arquivo, ler e guardar em variaveis
		while(arquivoInstrucoes >> inst->ordem >> inst->tipo >> inst->receptor >> inst->op1 >> 
			  inst->op2 >> inst->depende[0] >> inst->depende[1]){


			instrucao.push_back((*inst));
			

			cout << inst->ordem << " " << inst->tipo << " " << inst->receptor << " " << inst->op1 << " " << inst->op2 << " ";

			cout << inst->depende[0] << "," << inst->depende[1] << endl;
			inst.release();
			inst.reset(new Instrucao);
			
		} 

		numeroinstrucoes = instrucao.size();


		arquivoInstrucoes.close();
	}	
		
	
	else{
		cout << "Não foi possivel ler o arquivo" << endl;
	}
	//Fim: Leitura do arquivo txt

	//Início: Verificação de Dependências

	int numeroDoCiclo = 1;

	while( existeInstrucoesASeremExecutadas(instrucao) ){
		Instrucao aux = instrucao[0];

	//	cout << "1 aux0.estagio: " << aux.estagio << " aux0.naoExecutando" << aux.naoExecutando << endl;

		int estagio[qtdePipelines][5];

		for(int i=0; i<5;i++){
			for(int j=0;j<qtdePipelines;j++){
				estagio[i][j] = pegarInstrucao(instrucao,i,j);
	//			cout << "2 aux0.estagio: " << aux.estagio << " aux0.naoExecutando" << aux.naoExecutando << endl;
			}
		}


		liberarInstrucoesExecutadas(instrucao);
		
		cout << "---------------------------------------------" << endl;
		cout << "Ciclo " << numeroDoCiclo << endl;
		for(int i=0;i<qtdePipelines;i++){
			cout << "Pipeline" << i+1 << "	";		
		}

		cout << "\n";

		for(int i=0;i<5;i++){
			for(int j=0; j<qtdePipelines;j++){
				cout << estagio[i][j] << "		";
			}
			cout << "\n";
		}
		numeroDoCiclo++;
	}

	//Fim: Verificação de Dependências



	//Impressão

	return 0;
}


//Se existir apena uma instrução com estágio menor que 5 retornar verdadeiro, caso contrário retornar falso
bool existeInstrucoesASeremExecutadas(vector<Instrucao> &instrucoes){
	

	for(int i=0; i<instrucoes.size(); i++ ){
		Instrucao* aux = &instrucoes[i];

		if(aux->estagio < 5){
			return true;
		}
		
	}
	return false;
}

//Pegar todas as instruções que estão no estágio naoExecutando para true
void liberarInstrucoesExecutadas(vector<Instrucao> &instrucoes){
	for(int i=0; i<instrucoes.size(); i++ ){
		Instrucao* aux = &instrucoes[i];

		aux->naoExecutando = true;
	}	

}

int pegarInstrucao(vector<Instrucao> &instrucoesRestantes, int estagio, int pipe){
	for(int i=0; i<instrucoesRestantes.size(); i++ ){
		Instrucao *aux = &instrucoesRestantes[i];
		if(aux->naoExecutando && aux->estagio == estagio){
			if(true){ // aqui no futuro voce vai substituir pelo algoritmo que vai calcular dependencias
				aux->naoExecutando = false;
				aux->estagio++;
//				cout << "Estagio: " << estagio << " Pipeline:" << pipe;
//				cout << " Instrucao: " << i<<endl;
//				cout << "2.1 aux0.estagio: " << aux->estagio << " aux0.naoExecutando" << aux->naoExecutando << endl;
				return i+1;
			}
			
		}
	}

	return 0;
}

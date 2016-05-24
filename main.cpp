#include <fstream>
#include <string.h>
#include <locale.h>
#include <iostream>

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
struct tpInstrucao{
	int ordem;
	char tipo[5];
	char receptor[4];
	char op1[4];
	char op2[5];
	int depende[2];
};


struct tpEstagios{
	int* BI;
	int* DI;
	int* EX;
	int* MEM;
	int* WB;	
};



int main(){

	struct tpInstrucao instrucao[MAX];



	//Inicio: Leitura do arquivo txt
	ifstream arquivoInstrucoes ("instrucoes.txt");

	int qtdePipelines;

	int i=0, j=0;
	int aux;

	if(arquivoInstrucoes.is_open()){

		arquivoInstrucoes >> qtdePipelines;

		if(qtdePipelines > MaxPipelines){
			cout << "Número de Pipelines superior ao máximo suportado (8)." << endl;
			return 0;
		}


		//Enquanto nao chega ao final do arquivo, ler e guardar em variaveis
		while(arquivoInstrucoes >> instrucao[i].ordem >> instrucao[i].tipo >> instrucao[i].receptor >> instrucao[i].op1 >> 
			  instrucao[i].op2 >> instrucao[i].depende[0] >> instrucao[i].depende[1]){

			
			cout << instrucao[i].ordem << " " << instrucao[i].tipo << " " << instrucao[i].receptor << " " << instrucao[i].op1 << " " << instrucao[i].op2 << " ";

			cout << instrucao[i].depende[0] << "," << instrucao[i].depende[1] << endl;

			i++;
		} 
		arquivoInstrucoes.close();
	}	
		
	
	else{
		cout << "Não foi possivel ler o arquivo" << endl;
	}
	//Fim: Leitura do arquivo txt

	/*Início: Verificação de Dependências
	if(){
		
	}

	fscanf(*arquivoInstrucoes,%s %s)


	//Fim: Verificação de Dependências*/



	//Impressão

	return 0;
}

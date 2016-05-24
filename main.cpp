#include <fstream>
#include <string.h>
#include <locale.h>
#include <iostream>

#define MAX 10

using namespace std;

//Estrutura que guarda os componentes de cada instrução:
//tipooperacao - vetor de caracteres que guarda o tipo de operacao Assembly
//receptor - vetor de caracteres do registrados que recebe resultado da operação
//op1 - vetor de caracteres do registrador operando 1
//op2 - vetor de caracteres do registrador operando 2
struct tpInstrucao{
	int ordem;
	char tipooperacao[5];
	char receptor[3];
	char op1[3];
	char op2[3];
};




int main(){

	struct tpInstrucao instrucao[MAX] ;


	//Inicio: Leitura do arquivo txt
	ifstream arquivoInstrucoes ("instrucoes.txt");

	int qtdePipelines;

	int i=0;

	if(arquivoInstrucoes.is_open()){

		arquivoInstrucoes >> qtdePipelines;


		//Enquanto nao chega ao final do arquivo, ler e guardar em variaveis
		while(arquivoInstrucoes >> instrucao[i].ordem >> instrucao[i].tipooperacao >> instrucao[i].receptor >> instrucao[i].op1 >> instrucao[i].op2){			

			cout << instrucao[i].ordem << " " << instrucao[i].tipooperacao << " " << instrucao[i].receptor << " " << instrucao[i].op1 << " " << instrucao[i].op2 << " " << endl;
			i++;

		} 
		arquivoInstrucoes.close();
	}	
		
	}else{
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
//
//  main.cpp
//  SuperscalarPipelineSimulator
//
//  Created by Clarissa Alves Soares on 02/06/2016.
//  Copyright (c) 2016 Clarissa Alves Soares. All rights reserved.
//


#include <fstream>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <vector>
#include <memory>
#include <locale.h>
#include "funcoes.h"
#include <cstring>
#include <string>
#include <thread>    // std::this_thread::sleep_for
#include <chrono> 	// std::chrono::seconds


int main(){
	setlocale(LC_ALL,"pt_BR"); 

	//Declaração de variavéis

	vector<Instrucao> instrucao;
	int qtdePipelines;
	int numeroinstrucoes;
	string nomeArquivoStr;



	cout << "==========================* Superscalar Pipeline Simulator *==========================" << endl;

	cout << "Digite a quantidade de Pipelines que deseja simular(1 a 8): ";
	cin >> qtdePipelines;


	if(qtdePipelines > MaxPipelines || qtdePipelines < 1){
			cout << "Número de Pipeline(s) inválido. Digite valores de 1 a 8." << endl;
			return 0;
	}


	cout << "Digite o nome do arquivo com a lista de intruções: ";
	cin >> nomeArquivoStr;
	cout << endl;
	char* nomeArquivo = new char[nomeArquivoStr.length()+1];
	strcpy(nomeArquivo,nomeArquivoStr.c_str());

	string extensao = nomeArquivoStr.substr(nomeArquivoStr.length()-4, nomeArquivoStr.length());

	if( extensao != ".txt"){
		cout << "Extensão do arquivo inválida. Apenas arquivos .txt" << endl;
	}


	//Inicio: Leitura do arquivo txt
	ifstream arquivoInstrucoes ((char*)nomeArquivo);


	if(arquivoInstrucoes.is_open()){

		auto_ptr<Instrucao> inst( new Instrucao);

		//Enquanto nao chega ao final do arquivo, ler e guardar em variaveis
		while(arquivoInstrucoes >> inst->ordem >> inst->tipo >> inst->receptor >> inst->op1 >> 
			  inst->op2 >> inst->depende[0] >> inst->depende[1]){


			instrucao.push_back((*inst));

			inst.release();
			inst.reset(new Instrucao);
			
		} 

		numeroinstrucoes = instrucao.size();

		arquivoInstrucoes.close();
	}		
	else{
		cout << "Não foi possivel ler o arquivo" << endl;
		return 0;
	}
	//Fim: Leitura do arquivo txt

	getchar();
	getchar();
	system("clear");

	//Início: Verificação de Dependências

	int numeroDoCiclo = 1;

	while( existeInstrucoesASeremExecutadas(instrucao) ){

		int estagio[5][qtdePipelines];

		for(int i=0; i<5;i++){
			for(int j=0;j<qtdePipelines;j++){
				estagio[i][j] = pegarInstrucao(instrucao,i,j);
	
			}
		}

		liberarInstrucoesExecutadas(instrucao);
	//Fim: Verificação de Dependências

	imprimeInstrucoesNaoConcluidas(instrucao,numeroinstrucoes);
		
	//Início: Impressão	por Ciclo
		for(int i=1;i<=qtdePipelines;i++){
			cout << "---------------";
		}
		cout << "\n";

		cout << "Ciclo " << numeroDoCiclo << endl;
		numeroDoCiclo++;

		for(int i=1;i<=qtdePipelines;i++){
			cout << "Pipeline " << i << "	";
		}

		cout << "\n";

		for(int i=0; i<qtdePipelines;i++){
			cout << "BI:  " << estagio[0][i] << "		";
		}

		cout << "\n";

		for(int i=0; i<qtdePipelines;i++){
			cout << "DI:  " << estagio[1][i] << "		";
		}

		cout << "\n";

		for(int i=0; i<qtdePipelines;i++){
			cout << "EX:  " << estagio[2][i] << "		";
		}

		cout << "\n";

		for(int i=0; i<qtdePipelines;i++){
			cout << "MEM: " << estagio[3][i] << "		";
		}

		cout << "\n";

		for(int i=0; i<qtdePipelines;i++){
			cout << "WB:  " << estagio[4][i] << "		";
		}

		cout << "\n";

	//Fim: Impressao por Ciclo

		//getchar();
		std::this_thread::sleep_for (std::chrono::seconds(1));
		system("clear");
	}

	return 0;
}

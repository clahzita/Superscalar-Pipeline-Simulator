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
#include "funcoes.h"


int main(){

	//Declaração de variavéis

	vector<Instrucao> instrucao;
	int qtdePipelines;
	int numeroinstrucoes;



	cout << "==========================* Superscalar Pipeline Simulator *==========================" << endl;

	cout << "Digite a quantidade de Pipelines que deseja simular: ";
	cin >> qtdePipelines;
	cout << endl;

	if(qtdePipelines > MaxPipelines || qtdePipelines < 1){
			cout << "Número de Pipeline(s) inválido. Digite valores de 1 a 8." << endl;
			return 0;
	}


	//Inicio: Leitura do arquivo txt
	ifstream arquivoInstrucoes ("inst.txt");


	if(arquivoInstrucoes.is_open()){

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
		return 0;
	}
	//Fim: Leitura do arquivo txt

	getchar();
	getchar();

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

		getchar();
	}

	return 0;
}


bool verificaSeExisteDependencia(vector<Instrucao> &instrucoes, Instrucao* atual){

//	cout << "calculando dependencia" << endl;
	int numeroInstrucaoQueDepende_Op1 = atual->depende[0];
	int numeroInstrucaoQueDepende_Op2 = atual->depende[1];

	Instrucao aux1 = instrucoes[numeroInstrucaoQueDepende_Op1-1];
	Instrucao aux2 = instrucoes[numeroInstrucaoQueDepende_Op2-1];

	//atual->Independencia = true;
	//return true;
	
	//Se a instrução atual que está sendo verificada não depende de outras instruções, retorna true
	if(numeroInstrucaoQueDepende_Op1 == 0 && numeroInstrucaoQueDepende_Op2 == 0){
		atual->Independencia = true;
		return true;
	}
	//Se a instrução atual depende de outra(s) instrução(ões) mas ela(s) já foi(ram) executada(s) e seu(s) estagio(s)
	//for(em) = ou maior que o 4º(MEM),retorna true
	
	//Se a instrução recebe o operando2 de outra instrução, retorne false
	else if(numeroInstrucaoQueDepende_Op1 == 0 && numeroInstrucaoQueDepende_Op2 != 0){
		if(aux2.estagio < 3){
			atual->Independencia = false;
			return false;
		}
		else{
			atual->Independencia = true;
			return true;
		}
	}
		//Se a instrução recebe o operando1 de outra instrução, retorne false
	else if(numeroInstrucaoQueDepende_Op1 != 0 && numeroInstrucaoQueDepende_Op2 == 0){
		if(aux1.estagio < 3){
			atual->Independencia = false;
			return false;
		}
		else{
			atual->Independencia = true;
			return true;
		}
	}
		//Se a instrução recebe o operando1 e operando2 de outras instruções, retorne false
	else if(numeroInstrucaoQueDepende_Op1 != 0 && numeroInstrucaoQueDepende_Op2 != 0){
		if(aux1.estagio < 3 || aux2.estagio <= 3){
			atual->Independencia = false;
			return false;
		}
		else{
			atual->Independencia = true;
			return true;		
		}
	}
	
}
/*
bool verificaSeExisteDependencia(vector<Instrucao> &instrucoes, Instrucao* atual){
	int depende1 =atual->depende[0];
	int depende2 = atual->depende[1];
	bool dependencia1Executando = false;
	bool dependencia2Executando = false;
	Instrucao aux;

	if(depende1>0){
		aux = instrucoes[depende1-1];
		dependencia1Executando = aux.estagio <4;
	}


	if(depende2>0){
		aux = instrucoes[depende2-1];
		dependencia2Executando = aux.estagio <4;
	}

	bool naoDeveRodar = (depende2 > 0 && dependencia2Executando ) || 
		(depende1 > 0 && dependencia1Executando );

	atual->Independencia = !naoDeveRodar;
	return !naoDeveRodar;
}
*/


int pegarInstrucao(vector<Instrucao> &instrucoesRestantes, int estagio, int pipe){

	for(int i=0; i<instrucoesRestantes.size(); i++ ){
		
		Instrucao *aux = &instrucoesRestantes[i]; //cria ponteiro para instrução do vetor na posição i

		bool verificador = verificaSeExisteDependencia(instrucoesRestantes,aux);

		//naoExecutando é uma flag pra que a mesma instrução não seja executada mais de uma vez por ciclo
		//aux->estagio == estagio - verifica em que estagio está instrução para adioná-la na linha/estagio da matriz corretamente
		if(aux->naoExecutando && aux->estagio == estagio && aux->Independencia){
			
			aux->naoExecutando = false;
			aux->estagio++;
			return i+1;
		}
		//cout << "instrucao " << i+1 << " nao rodara" << endl;
		
	}

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

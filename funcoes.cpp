//
//  funcoes.cpp
//  SuperscalarPipelineSimulatorFunctions
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

//Função verifica se a instrução depende de outra e se a instrução a qual depende já está no estágio MEM
// @param - vetor de todas instruções 
// @param - instrução atual que vai verificar se depende de outra
// return - true se não depende, false se depende

bool verificaSeExisteDependencia(vector<Instrucao> &instrucoes, Instrucao* atual){

//	cout << "calculando dependencia" << endl;
	int numeroInstrucaoQueDepende_Op1 = atual->depende[0];
	int numeroInstrucaoQueDepende_Op2 = atual->depende[1];

	Instrucao aux1 = instrucoes[numeroInstrucaoQueDepende_Op1-1];
	Instrucao aux2 = instrucoes[numeroInstrucaoQueDepende_Op2-1];
	
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
		if(aux1.estagio < 3 || aux2.estagio < 3){
			atual->Independencia = false;
			return false;
		}
		else{
			atual->Independencia = true;
			return true;		
		}
	}
	
}
//Função que retorna o número de instrução a ser colocada no estagio e pipeline a qual se está avaliando
// @param - vetor de todas instruções 
// @param - estagio que está sendo verificado
// @param - pipeline que está sendo verificada
// return - retorna o inteiro a posição da matriz, colocando a instrução corretamente na matriz em cada ciclo
//
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

//Função que verifica se todas as instruções já passaram por todos os estágios
// @param - vetor de todas instruções 
// return - true se houver instrução a ser executada, false se todas já foram executadas
//
//Se existir apena uma instrução com estágio menor que 5 retornar verdadeiro, caso contrário retornar falso
//
bool existeInstrucoesASeremExecutadas(vector<Instrucao> &instrucoes){
	

	for(int i=0; i<instrucoes.size(); i++ ){
		Instrucao* aux = &instrucoes[i];

		if(aux->estagio < 5){
			return true;
		}
		
	}
	return false;
}

//Função que garante que a mesma instrução nao vai executar mais de uma vez pro ciclo
// @param - vetor de todas instruções 
// return - true se houver instrução a ser executada, false se todas já foram executadas
//
// Depois de alimentar a matriz, pega todas as instruções que estão no estágio naoExecutando false e passa para true
// para que no próximo ciclo todas sejam checadas novamente.
void liberarInstrucoesExecutadas(vector<Instrucao> &instrucoes){
	
	for(int i=0; i<instrucoes.size(); i++ ){
		Instrucao* aux = &instrucoes[i];

		aux->naoExecutando = true;
	}

}

//Função que imprime as instruções que ainda estão em execução
// @param - vetor de todas instruções 
// @param - numero de instruções
// Imprime as instruções que estão até o último estagio, senão imprime linha em branco
//
void imprimeInstrucoesNaoConcluidas(vector<Instrucao> &instrucao, int tamanho){

	cout << "====* Lista de Instruções a executar *====" << endl;
	for(int i = 0; i < tamanho; i++){
		Instrucao* aux = &instrucao[i];

		if(aux->estagio < 5){
			cout << aux->ordem << " " << aux->tipo << " " << aux->receptor << " " << aux->op1 << " " << aux->op2 << " ";
			cout << aux->depende[0] << "," << aux->depende[1] << endl;	
		}
		else{
			cout << endl;
		}
	}
}
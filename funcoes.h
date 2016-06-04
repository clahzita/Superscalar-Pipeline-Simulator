//
//  funcoes.h
//  Instructions
//
//  Created by Clarissa Alves Soares on 02/06/2016.
//  Copyright (c) 2016 Clarissa Alves Soares. All rights reserved.
//

#ifndef _SIMULADOR_PROCESSADOR_SUPERESCALAR_
#define _SIMULADOR_PROCESSADOR_SUPERESCALAR_

#define MaxPipelines 8
using namespace std;

//Estrutura que guarda os componentes de cada instrução:
//
// ordem - recebe a ordem em que se encontra a instrução no bloco de instruções
// tipo - vetor de caracteres que guarda o tipo de operacao Assembly
// receptor - vetor de caracteres que armazena o registrador que recebe resultado da operação
// op1 - vetor de caracteres do registrador operando 1
// op2 - vetor de caracteres do registrador operando 2
// depende - mostra um vetor de inteiros que indicam que instruções dependem do receptor da instrução lida
// naoExecutando - booleano que identifica se a instrução foi executado ou não no ciclo
// Independencia - booleano que identifica a dependência a outra instrução
// estagio - Indica em que estagio está a instrução 
//
typedef struct tpInstrucao{
	int ordem;
	char tipo[5];
	char receptor[4];
	char op1[4];
	char op2[5];
	int depende[2];
	bool naoExecutando = true;
	bool Independencia;
	int estagio = 0;
} Instrucao;


bool existeInstrucoesASeremExecutadas(vector<Instrucao> &instrucoes);
void liberarInstrucoesExecutadas(vector<Instrucao> &instrucoes);
bool verificaSeExisteDependencia(vector<Instrucao> &instrucoes, Instrucao* atual);
int pegarInstrucao(vector<Instrucao> &instrucoesRestantes, int inst, int pipe);



#endif
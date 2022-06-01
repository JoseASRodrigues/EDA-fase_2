#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//!Criação da estrutura da lista ligada
typedef struct obj
{
	int estado;
	int process;
	int operacoes;
	int maquina;
	int tempo;
	struct obj* seguinte;
}Jobs;
//!Lista ligada para extração dos processos do ficheiro
typedef struct pr
{
	int linhaMaquinas;//!Linha onde se encontra o processo e maquinas
	int linhaTempo;//!Linha onde se encontra os tempos
	int proc;//!Numero do processo
	struct pr* seguinte;
}Prs;
//!Lista ligada dos endereços dos processos
typedef struct proc
{
	struct Jobs* job;
	int operacoes;
	int prs;
	struct proc* seguinte;
}Processo;
//!Lista ligada das maquinas
typedef struct maq
{
	int tempo;
	int maquina;
	struct maq* seguinte;
}Maquinas;
//! Lista ligada do escalonamento
typedef struct esc
{
	struct EscalProcOpe* eps;
	int maquina;
	struct esc* seguinte;
}Escalonamento;
//! Lista ligada tempos processo operação
typedef struct eps
{
	int processo;
	int operacao;
	struct eps* seguinte;
}EscalProcOpe;



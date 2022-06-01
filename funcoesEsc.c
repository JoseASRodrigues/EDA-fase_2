#define _CRT_SECURE_NO_WARNINGS
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "estrutura.h"
#include "calculos.h"
#include "escalonamento.h"

//! Ddetermina o numero de máquinas de todo o processo
int maquinas(Processo* inicio) {
	Processo* procura = inicio;
	Jobs* aux = NULL;
	int encontrou = 0, conta = 0;
	while (procura != NULL) {
		aux = procura->job;
		while (aux != NULL) {
			if ((conta + 1) == aux->maquina) {
				conta++;
				encontrou = 1;
				break;
			}
			aux = aux->seguinte;
		}
		if (encontrou == 0) procura = procura->seguinte;
		if (encontrou == 1)procura = inicio;
		encontrou = 0;
	}
	return conta;
}

//! Cria na lista registo de maquinas no inicio
Maquinas* inserirInicioMaq(Maquinas* inicio, int Maquina, int Tempo)
{
	Maquinas* novo = (Maquinas*)malloc(sizeof(Maquinas));
	if (novo != NULL)
	{
		novo->maquina = Maquina;
		novo->tempo = Tempo;
		novo->seguinte = inicio;
		return(novo);
	}
	else return(inicio);
}
//! Cria na lista registo de maquinas no inicio
Maquinas* inserirFimMaq(Maquinas* inicio, int Maquina, int Tempo)
{
	Maquinas* aux = inicio, * novo = (Maquinas*)malloc(sizeof(Maquinas));
	if (novo != NULL)
	{
		if (aux == NULL) return(inserirInicioMaq(aux, Maquina, Tempo));
		else {
			while (aux->seguinte != NULL)
				aux = aux->seguinte;
			novo->maquina = Maquina;
			novo->tempo = Tempo;
			novo->seguinte = NULL;
			aux->seguinte = novo;
			return(inicio);
		}
	}
	else return(inicio);
}

//! Cria lista de escalonamento no inicio
Escalonamento* inserirInicioEsca(Escalonamento* inicio, EscalProcOpe* inicioOpe, int Maquina)
{
	Escalonamento* novo = (Escalonamento*)malloc(sizeof(Escalonamento));
	if (novo != NULL)
	{
		novo->eps = inicioOpe;
		novo->maquina = Maquina;
		novo->seguinte = inicio;
		return(novo);
	}
	else return(inicio);
}

//! Cria lista de escalonamento no fim
Escalonamento* inserirFimEsca(Escalonamento* inicio, EscalProcOpe* inicioOpe, int Maquina)
{
	Escalonamento* aux = inicio, * novo = (Escalonamento*)malloc(sizeof(Escalonamento));
	if (novo != NULL)
	{
		if (aux == NULL) return(inserirInicioEsca(aux, inicioOpe, Maquina));
		else {
			while (aux->seguinte != NULL)
				aux = aux->seguinte;
			novo->eps = inicioOpe;
			novo->maquina = Maquina;
			novo->seguinte = NULL;
			aux->seguinte = novo;
			return(inicio);
		}
	}
	else return(inicio);
}
//! Cria lista de registo no inicio, de processos e operações relativas a uma máquina
EscalProcOpe* inserirInicioProcOpe(EscalProcOpe* inicio, int Processo, int Operacao)
{
	EscalProcOpe* novo = (EscalProcOpe*)malloc(sizeof(EscalProcOpe));
	if (novo != NULL)
	{
		novo->processo = Processo;
		novo->operacao = Operacao;
		novo->seguinte = inicio;
		return(novo);
	}
	else return(inicio);
}
//! Cria lista de registo no fim, de processos e operações relativas a uma máquina
EscalProcOpe* inserirFimProcOpe(EscalProcOpe* inicio, int Processo, int Operacao)
{
	EscalProcOpe* aux = inicio, * novo = (EscalProcOpe*)malloc(sizeof(EscalProcOpe));
	if (novo != NULL)
	{
		if (aux == NULL) return(inserirInicioProcOpe(aux, Processo, Operacao));
		else {
			while (aux->seguinte != NULL)
				aux = aux->seguinte;
			novo->processo = Processo;
			novo->operacao = Operacao;
			novo->seguinte = NULL;
			aux->seguinte = novo;
			return(inicio);
		}
	}
	else return(inicio);
}

//! Verifica se a máquina está em utilização
int verificaMaquina(Maquinas* inicio, int maquina) {
	while (inicio != NULL)
	{

		if ((inicio->maquina == maquina) && (inicio->tempo > 0)) return 1;
		inicio = inicio->seguinte;

	}
	return 0;
}
//! Volta a colocar a maquina disponivel
void descontaMaquina(Maquinas* inicio) {
	while (inicio != NULL)
	{
		//inicio->tempo = inicio->tempo--;
		//if (inicio->tempo < 0) inicio->tempo = 0;
		printf("\nMaquina %d Tempo %d", inicio->maquina, inicio->tempo);
		inicio = inicio->seguinte;
	}
}
//! Verifica se Job e operação já existe no lista do escalonamento
int verificaEscalonamento(Escalonamento* inicio, int Processo, int Operacao) {
	EscalProcOpe* inicioEsc = NULL;
	while (inicio != NULL) {
		inicioEsc = inicio->eps;
		printf("\n Maquina %d  %p", inicio->maquina, inicio->eps);
		while (inicioEsc != NULL) {
			if ((inicioEsc->processo == Processo) && (inicioEsc->operacao == Operacao)) return 1;
			inicioEsc = inicioEsc->seguinte;
		}
		inicio = inicio->seguinte;
	}
	return 0;
}




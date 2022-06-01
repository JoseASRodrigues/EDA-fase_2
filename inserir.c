#define _CRT_SECURE_NO_WARNINGS
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "estrutura.h"
#include "calculos.h"
//!Inserir novo registo no inicio da lista com dados 
Jobs* inserirInicio(Jobs* inicio, int Estado, int Processo, int Operacao, int Maquina, int Tempo)
{
	Jobs* novo = (Jobs*)malloc(sizeof(Jobs));
	if (novo != NULL)
	{
		novo->estado = Estado;
		novo->process = Processo;
		novo->operacoes = Operacao;
		novo->maquina = Maquina;
		novo->tempo = Tempo;
		novo->seguinte = inicio;
		return(novo);
	}
	else return(inicio);
}

//!Inserir um registo no fim da lista ou no inicio se estiver vazia 
Jobs* inserirFim(Jobs* inicio, int Estado, int Processo, int Operacao, int Maquina, int Tempo)
{
	Jobs* aux = inicio, * novo = (Jobs*)malloc(sizeof(Jobs));
	if (novo != NULL)
	{
		if (aux == NULL) return(inserirInicio(aux, Estado, Processo, Operacao, Maquina, Tempo));
		else {
			while (aux->seguinte != NULL)
				aux = aux->seguinte;
			novo->estado = Estado;
			novo->process = Processo;
			novo->operacoes = Operacao;
			novo->maquina = Maquina;
			novo->tempo = Tempo;
			novo->seguinte = NULL;
			aux->seguinte = novo;
			return(inicio);
		}
	}
	else return(inicio);
}

Prs* inserirInicioPrs(Prs* inicio, int linha, int Proc)
{
	Prs* novo = (Prs*)malloc(sizeof(Prs));
	if (novo != NULL)
	{
		novo->linhaMaquinas = linha;
		novo->linhaTempo = linha + 1;
		novo->proc = Proc;
		novo->seguinte = inicio;
		return(novo);
	}
	else return(inicio);
}

Prs* inserirFimPrs(Prs* inicio, int linha, int proc) {
	Prs* aux = inicio, * pr = (Prs*)malloc(sizeof(Prs));
	if (pr != NULL)
	{
		if (aux == NULL) return(inserirInicioPrs(aux, linha, proc));
		else {
			while (aux->seguinte != NULL)
				aux = aux->seguinte;
			pr->linhaMaquinas = linha;
			pr->linhaTempo = linha + 1;
			pr->proc = proc;
			pr->seguinte = NULL;
			aux->seguinte = pr;
			return(inicio);
		}
	}
	else return(inicio);
}
//!Inserir no inicio da lista dos processos (Jobs)
Processo* inserirInicioProcesso(Processo* inicio, Jobs* lista, int operacoes, int prs)
{
	Processo* novo = (Processo*)malloc(sizeof(Processo));
	if (novo != NULL)
	{
		novo->job = lista;
		novo->operacoes = operacoes;
		novo->prs = prs;
		novo->seguinte = inicio;

		return(novo);
	}

	else return(inicio);
}


//!Inserir no fim da lista dos processos (Jobs)
Processo* inserirFimProcesso(Processo* inicio, Jobs* lista, int operacoes, int prs) {
	Processo* aux = inicio, * processo = (Processo*)malloc(sizeof(Processo));
	if (processo != NULL)
	{
		if (aux == NULL) return(inserirInicioProcesso(aux, lista, operacoes, prs));
		else {
			while (aux->seguinte != NULL)
				aux = aux->seguinte;
			processo->job = lista;
			processo->operacoes = operacoes;
			processo->prs = prs;
			processo->seguinte = NULL;
			aux->seguinte = processo;

			return(inicio);
		}
	}
	else return(inicio);
}

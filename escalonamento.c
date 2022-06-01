#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "estrutura.h"
#include "calculos.h"
#include "escalonamento.h"

//! Calculo do escalonamento
void escalonamento(Processo* inicio) {
	Processo* aux = inicio;
	Maquinas* inicioMaq = NULL;
	Escalonamento* inicioEsca = NULL;
	EscalProcOpe* lista = NULL;
	Jobs* inicioJobs = NULL;
	int quantidade = 0, numeroMaq = 0, tempo = 0, operacoes = 0, verificaoperacoes = 0, contajob = 0, conta = 0;
	int maquina = 0, temposfinal = 0, proc = 0, contaTempo = 0, opera = 0;
	//! Determina a quantidades de maquinas existente no MasterPlan
	quantidade = maquinas(inicio);
	//! prenche lista das maquinas com tempo=0 ->Maquinas disponiveis
	for (int i = 0; i < quantidade; i++) inicioMaq = inserirFimMaq(inicioMaq, (i + 1), tempo);
	Maquinas* auxMaq = NULL;
	auxMaq = inicioMaq;
	while (inicioMaq != NULL) {
		inicioEsca = inserirFimEsca(inicioEsca, lista, inicioMaq->maquina);
		inicioMaq = inicioMaq->seguinte;
	}
	inicioMaq = auxMaq;
	//! Determina o numero máximo de operações
	conta = 0;
	while (aux != NULL) {
		if (conta == 0) {
			opera = aux->operacoes;
		}
		else {
			if (opera < aux->operacoes) opera = aux->operacoes;
		}
		conta++;
		aux = aux->seguinte;
	}

	procuraMenor(inicio, inicioMaq, inicioEsca, lista, opera);
}

//! Procura o menor tempo de maquina para utilizar
void procuraMenor(Processo* inicio, Maquinas* inicioMaq, Escalonamento* inicioEsca, EscalProcOpe* lista, int Operacoes) {
	Processo* aux = inicio;
	Jobs* inicioJobs = NULL;
	Maquinas* auxMaq = inicioMaq;
	int quantidade = 0, numeroMaq = 0, tempo = 0, opera = 0, verificaoperacoes = 0, contajob = 0, conta = 0;
	int maquina = 0, temposfinal, proc = 0, encontrou = 0, verifica = 0;
	temposfinal = 0;
	opera = 1;
	while (opera <= Operacoes) {
		for (int i = 1; i <= opera; i++) {
			while (aux != NULL) {
				inicioJobs = aux->job;
				encontrou = 0;
				while (inicioJobs != NULL) {
					contajob = aux->prs;
					if (inicioJobs->operacoes == opera) {
						printf("\nverifica %d", verificaMaquina(inicioMaq, inicioJobs->maquina));

						if (verificaMaquina(inicioMaq, inicioJobs->maquina) != 1) {

							if (conta == 0) {
								verificaoperacoes = inicioJobs->tempo;
								maquina = inicioJobs->maquina;
								proc = contajob;
								encontrou = 1;
								temposfinal = inicioJobs->tempo;
								conta++;
							}
							if ((conta > 0) && (verificaoperacoes > inicioJobs->tempo)) {
								verificaoperacoes = inicioJobs->tempo;
								maquina = inicioJobs->maquina;
								proc = contajob;
								encontrou = 1;
								temposfinal = inicioJobs->tempo;
							}
						}

					}

					inicioJobs = inicioJobs->seguinte;
				}
				aux = aux->seguinte;
			}
			aux = inicio;
			auxMaq = inicioMaq;
			while (auxMaq != NULL) {
				if (auxMaq->maquina = maquina) {
					auxMaq->maquina = maquina; auxMaq->tempo = verificaoperacoes;
				}
				auxMaq = auxMaq->seguinte;
			}
			printf("\nmaquina %d tempo %d processo %d", maquina, verificaoperacoes, proc);


		}
		opera++;
	}




	getchar(); getchar();
	return 0;
}



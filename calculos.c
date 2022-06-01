#define _CRT_SECURE_NO_WARNINGS
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "calculos.h"

//!Calculo do processo tempos minimos tempos máximos e médias
void Calculo(Processo* inicioPro, int info) {
	Processo* inicial = inicioPro;
	if (inicioPro == NULL) {
		textcolor(RED);
		printf("\n         Lista vazia"); getchar();
		textcolor(WHITE);
		return;
	}
	Jobs* lista = NULL;
	int soma = 1, operacao = 1, maquina = 0, menor = 0, maior = 0, tempo = 0, a = 0, antes = 0, aux = 0, maquina1 = 0, aux1 = 0;
	int totalMaquinas = 1, calculo = 0;
	float somaMaior = 0, somaMenor = 0;
	listar(inicioPro);
	printf("Qual o job que deseja calcular (0 Aborta) Job->"); scanf("%d", &calculo);
	if (calculo == 0) return;
	while (inicial != NULL)
	{
		if (calculo == (inicial->prs)) {
			lista = inicial->job;
			break;
		}
		inicial = inicial->seguinte;
		if (inicial == NULL) {
			textcolor(RED);
			printf("   Não foi encontrado o job-> %d  Enter continua", calculo); getchar();
			textcolor(WHITE);
			return inicioPro;
		}
	}
	if (lista != NULL) soma = lista->operacoes;
	while (lista != NULL) {
		if (lista->operacoes == soma) {
			aux = lista->operacoes;
			if (a == 0) {
				maior = lista->tempo;
				maquina = lista->maquina;
				menor = lista->tempo;
				maquina1 = lista->maquina;
				a++;
			}
			else if (lista->tempo > maior) {
				maior = lista->tempo;
				maquina = lista->maquina;
				aux = lista->operacoes;
			}
			else if (lista->tempo < menor) {
				menor = lista->tempo;
				maquina1 = lista->maquina;
				aux = lista->operacoes;
			}
			aux1 = aux;
			aux = lista->operacoes;
		}
		lista = lista->seguinte;
		if (lista != NULL) {
			if (aux != lista->operacoes) {
				soma = lista->operacoes;
				a = 0;
				textcolor(YELLOW);
				if (info == 1) {
					estadoPoe(inicial->job, aux1, maquina1, 1);
				}
				if (info == 2) {
					estadoPoe(inicial->job, aux1, maquina, 2);
				}

			}
		}
	}
	if (info == 1) {
		somaMenor = somaMenor + menor;
		estadoPoe(inicial->job, aux1, maquina1, 1);
		textcolor(GREEN);
		somas(inicial->job, 1, info, calculo);
		textcolor(WHITE);
	}
	if (info == 2) {
		estadoPoe(inicial->job, aux1, maquina, 2);
		textcolor(BLUE);
		somas(inicial->job, 2, info, calculo);
		textcolor(WHITE);
	}
	if (info == 3) {
		textcolor(BLUE);
		somas(inicial->job, 3, info, calculo);
		textcolor(WHITE);
	}
	getchar();
}
//!Coloca o estado da máquina em função da operação se for maio ou menor
void estadoPoe(Jobs* inicio, int aux1, int maquina, int estado) {
	Jobs* aux = inicio;
	while (aux != NULL)
	{
		if ((aux->operacoes == aux1) && (aux->maquina == maquina)) {
			if (estado == 1) aux->estado = 1;
			if (estado == 2) aux->estado = 2;
		}
		aux = aux->seguinte;
	}
}
//!Calculo de quantidade de máquinas e tempos e médias e listagem
void somas(Jobs* inicio, int estado, int info, int calculo) {
	Jobs* aux = inicio;
	if (inicio != NULL) {
		textcolor(WHITE);
		listarJob(inicio, calculo);
		float total1 = 0, total2 = 0, tempos = 0, tempos1 = 0;
		printf("\n\nMáquinas utilizadas\n");
		while (inicio != NULL) {
			if ((estado == inicio->estado) || (estado == 3)) {
				if ((inicio->estado == 1) || (inicio->estado == 3)) {
					total1++;
					tempos = tempos + inicio->tempo;
					textcolor(GREEN);
					printf("\nOperação %d Maquina %d Tempo %d ", inicio->operacoes, inicio->maquina, inicio->tempo);
					textcolor(WHITE);
				}
				if ((inicio->estado == 2) || (inicio->estado == 3)) {
					total2++;
					tempos1 = tempos1 + inicio->tempo;
					textcolor(BLUE);
					printf("\nOperação %d Maquina %d Tempo %d ", inicio->operacoes, inicio->maquina, inicio->tempo);
					textcolor(WHITE);
				}
			}
			inicio = inicio->seguinte;
		}
		inicio = aux;
		textcolor(YELLOW);
		if ((estado == 1) || (estado == 3)) printf("\nTotal de máquinas utilizadas->%.0f  Menor tempo total %.0f", total1, tempos);
		if ((estado == 2) || (estado == 3)) printf("\nTotal de máquinas utilizadas->%.0f  Maior tempo total %.0f\n", total2, tempos1);
		if (estado == 3) {
			textcolor(LIGHTRED);
			printf("\nMédia menor tempo %.2f", tempos / total1);
			printf("\nMédia maior tempo %.2f", tempos1 / total2);
			textcolor(WHITE);
		}
		textcolor(WHITE);
		printf("\n\n");
		while (aux != NULL) {
			if ((aux->estado) == info) {
				printf("((%d)[%d])-->", aux->maquina, aux->tempo);
			}
			aux = aux->seguinte;
		}
		if (info == 1) printf("  %.0f", tempos);
		if (info == 2) printf("  %.0f", tempos1);
		printf("\n\n");
		aux = inicio;
		//! Limpa todos os estados da lista
		while (aux != NULL) {
			if (aux->estado > 0) aux->estado = 0;
			aux = aux->seguinte;
		}
	}
	else {
		textcolor(RED);
		printf("\n\n\n          lista vazia");
		textcolor(WHITE);
	}
}

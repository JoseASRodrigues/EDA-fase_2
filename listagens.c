#define _CRT_SECURE_NO_WARNINGS
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "estrutura.h"
#include "calculos.h"

//! Função de listagem todos jobs
int listar(Processo* inicio)
{
	int a = 1;
	Jobs* aux = NULL;
	printf("                     Listagem geral\n\n");
	while (inicio != NULL) {
		aux = inicio->job;
		textcolor(BLUE);
		if (inicio->prs != NULL) printf("\nJob %d Operações %d\n\n", inicio->prs, inicio->operacoes);
		textcolor(WHITE);
		while ((aux != NULL) && (inicio->prs != NULL)) {
			printf("Operação %d Maquina (%d) [%d] Tempo  Numero de registo %d\n", aux->operacoes, aux->maquina, aux->tempo, a);	//getchar();
			aux = aux->seguinte;
			a++;
		}
		inicio = inicio->seguinte;
		a = 1;
	}
	textcolor(GREEN);
	printf("\n\n             Fim da listagem, Enter para continuar\n\n");
	textcolor(WHITE);
	return 0;
}
//! Listar um job e calculos
int listarJob(Jobs* inicio, int calculo)
{
	int a = 0;
	Jobs* aux = inicio;
	printf("             Listagem do job-> %d\n\n", calculo);
	while (aux != NULL)
	{
		a++;
		if (aux->estado == 1) {
			textcolor(GREEN);
			printf("Job %d operacao -> %d  Maquina ->(%d) Tempo ->[%d]  Registo %d \n", aux->process, aux->operacoes, aux->maquina, aux->tempo, a);
			textcolor(WHITE);
		}
		if (aux->estado == 2) {
			textcolor(BLUE);
			printf("Job %d operacao -> %d  Maquina ->(%d) Tempo ->[%d]  Registo %d \n", aux->process, aux->operacoes, aux->maquina, aux->tempo, a);
			textcolor(WHITE);
		}
		if (aux->estado == 0) {
			textcolor(WHITE);
			printf("Job %d operacao -> %d  Maquina ->(%d) Tempo ->[%d]  Registo %d \n", aux->process, aux->operacoes, aux->maquina, aux->tempo, a);
		}
		aux = aux->seguinte;
	}
	return a;
}
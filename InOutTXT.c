#define _CRT_SECURE_NO_WARNINGS
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#pragma warning(disable : 4996)//! Disable o erro por causa da função itoa()

//!função ler do ficheiro e coloca os dados em várias listas ligadas simples
Processo* ler(char ficheiro[]) {
	Processo* processo = NULL;
	Jobs* lista = NULL; //! Lista ligada simples vazia
	Prs* pr = NULL;
	Prs* inicio = NULL;
	system("cls");
	int valor = 0, b = 0, c = 0, d = 1, estado = 0, tempo = 0, posicao = 1, contaLinhas = 1;
	char linha[100], * t, list[10], auxiliar[10];
	int operacoes;
	const char* maquinas = "(,)";
	const char* tempos = "[,]";
	//!Abre ficheiro para leitura 
	fp = fopen(ficheiro, "r");
	if (fp == NULL) {
		gotoxy(30, 12);
		textcolor(LIGHTRED);
		printf("Não foi possivel abrir o ficheiro!!!\n");//!Verificar se o ficheiro foi aberto com sucesso
		textcolor(WHITE);
		strcpy(ficheiro, "dados.txt");//!repor nome do ficheiro por defeito 
		return processo;
	}
	else {
		//!Faz varrimento ao ficheiro txt e guarda numa lista ligada a posição das maquinas e dos tempos dos jobs
		while ((fgets(linha, 100, fp)) != NULL) { //!Lê do ficheiro uma linha completa enquanto não encontrar o fim do ficheiro
			t = strtok(linha, "Pr ");//!Lê a ocurrencia Pr na linha
			valor = atoi(t);
			if (valor != 0) pr = inserirFimPrs(pr, contaLinhas, valor);
			contaLinhas++;//!numero da linha do ficheiro txt
		}
		inicio = pr;
		rewind(fp);//!Coloca o ficheiro no inicio
		contaLinhas = 1;

		while (pr != NULL) {
			for (int a = 0; a < pr->linhaMaquinas; a++) fgets(linha, 100, fp);
			itoa(pr->proc, list, 10);//!Converte numero do job em string
			strcpy(auxiliar, "Pr");//!Coloca na variavel auxiliar  "Pr" 
			strcat(auxiliar, list);//!Adiciona a auxiliar o caracter da converção do job
			Jobs* auxiliar = NULL;//!Inicia a varial auxiliar

			operacoes = 0;
			t = strtok(linha, maquinas);//!Lê a promeira ocurrencia na linha
			while (t != NULL) {
				valor = atoi(t);
				if (valor == 0) operacoes++;
				if (valor != 0) {
					auxiliar = inserirFim(auxiliar, estado, d, operacoes, valor, tempo);
					b++;
				}
				t = strtok(NULL, maquinas);
			}
			d++;
			processo = inserirFimProcesso(processo, auxiliar, operacoes - 1, pr->proc);

			rewind(fp);//!Coloca o ficheiro no inicio
			for (int a = 0; a < pr->linhaTempo; a++) fgets(linha, 100, fp);
			rewind(fp);//!Coloca o ficheiro no inicio
			pr = pr->seguinte;
		}
		b = 0;
		Processo* temporario = NULL;//!Inicia a varial auxiliar
		temporario = processo;
		pr = inicio;
		Jobs* endereco = NULL;
		while (temporario != NULL) {
			while (pr != NULL) {
				rewind(fp);//!Coloca o ficheiro no inicio
				for (int a = 0; a < pr->linhaTempo; a++) fgets(linha, 100, fp);
				// printf("linha %s", linha);
				t = strtok(linha, tempos);//!Lê a promeira ocurrencia na linha
				endereco = temporario->job;
				while (t != NULL) {
					valor = atoi(t);
					if (valor == 0) operacoes++;
					if (valor != 0) {
						tempo = valor;
						b++;
						if (endereco != NULL) endereco->tempo = valor;
						if (endereco != NULL) endereco = endereco->seguinte;
					}
					t = strtok(NULL, tempos);
				}
				temporario = temporario->seguinte;
				pr = pr->seguinte;
			}
		}
		free(temporario);
	}
	fclose(fp);
	return (processo);
}


//!função escrever no ficheiro 
void escrever(Processo* inicio, char ficheiro[])
{
	system("cls");
	Processo* maior = inicio;
	int contador = 0, min = 1, a = 1, max = 0;
	int atual = 0, anterior = 0, oper = 0, saida = 0, tem = 0;
	//!Calcula o maior numero de operações
	while (maior != NULL) {
		if (contador == 0) {
			max = maior->operacoes;
		}
		if ((maior->operacoes) > max) max = maior->operacoes;
		maior = maior->seguinte;
		contador++;
	}
	maior = inicio;//!Volta a colocar a lista de processos no inicio
	if (maior != NULL) {//!Verifica se lista está vazia para não gravar ficheiro 
	//!Abre ficheiro para escrita  
		fp = fopen(ficheiro, "w");
		printf("Process Plan");
		printf("						Operation\n");
		fprintf(fp, "Process Plan");
		fprintf(fp, "						Operation\n");
		printf("\t");
		for (int i = 1; i <= max; i++)printf("\t\t 0%d", i);
		fprintf(fp, "\t");
		for (int i = 1; i <= max; i++)fprintf(fp, "\t\t 0%d", i);
		Jobs* endereco = NULL;
		endereco = maior->job;
		while (maior != NULL) {
			if (maior->prs != 0) {
				oper = maior->operacoes;

				printf("\nPr%d", maior->prs);
				fprintf(fp, "\nPr%d", maior->prs);

				contador = 1;
				printf("\t");
				fprintf(fp, "\t");
				for (int i = 0; i < maior->operacoes; i++) {
					min = 0;
					endereco = maior->job;
					while (endereco != NULL) {
						if (endereco->operacoes == contador) min++;
						endereco = endereco->seguinte;
					}
					if (tem > 3) {
						printf("\t(");
					}
					else {
						printf("\t\t(");
					}
					if (tem > 2) {

						fprintf(fp, "\t(");
					}
					else {

						fprintf(fp, "\t\t(");
					}
					tem = min;
					endereco = maior->job;
					anterior = 1;
					while (endereco != NULL) {
						if (endereco->operacoes == contador) {
							printf("%d", endereco->maquina);
							fprintf(fp, "%d", endereco->maquina);
							if (anterior < min) printf(",");
							if (anterior < min) fprintf(fp, ",");
							anterior++;
						}
						endereco = endereco->seguinte;
					}
					printf(")");
					fprintf(fp, ")");
					endereco = maior->job;
					contador++;
				}
				tem = 0;
				contador = 1;
				endereco = maior->job;
				printf("\n\t");
				fprintf(fp, "\n\t");
				for (int i = 0; i < maior->operacoes; i++) {
					min = 0;
					while (endereco != NULL) {
						if (endereco->operacoes == contador) min++;
						endereco = endereco->seguinte;
					}
					if (tem > 3) {
						printf("\t[");
					}
					else {
						printf("\t\t[");
					}
					if (tem > 2) {
						fprintf(fp, "\t[");
					}
					else {
						fprintf(fp, "\t\t[");
					}
					tem = min;
					endereco = maior->job;
					anterior = 1;
					while (endereco != NULL) {
						if (endereco->operacoes == contador) {
							printf("%d", endereco->tempo);
							fprintf(fp, "%d", endereco->tempo);
							if (anterior < min) printf(",");
							if (anterior < min) fprintf(fp, ",");
							anterior++;
						}
						endereco = endereco->seguinte;
					}
					printf("]");
					fprintf(fp, "]");
					//maior = maior->seguinte;
					endereco = maior->job;
					contador++;
				}
			}
			tem = 0;
			maior = maior->seguinte;
		}
	}
	textcolor(GREEN);
	printf("\n\n        Dados guardados no ficheiro %s\n\n", ficheiro);
	textcolor(WHITE);
	printf("\n\n             Enter para continuar");
	fclose(fp);
}

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "utils.h"
#include "funcoes.h"
#include "estrutura.h"
#include "calculos.h"
#include "escalonamento.h"
void main() {
	setlocale(LC_ALL, "portuguese");
	setlocale(LC_NUMERIC, "us");
	textcolor(WHITE);
	//!Defenir variaveis 
	int opcao = 0, inicio = 0, valor = 0, opcao_1 = 0, info = 0;
	char ficheiro[50] = "dados.txt", opcao_2 = 0;
	char ficheiroGrava[50] = "saida.txt";
	Processo* processos = NULL;
	while (opcao != 10) {

		//!Menu e submenu
		system("cls");
		printf("-----------Flexible Job Shop Problem (FJSSP)-----------\n\n");
		printf("Menu:\n");
		printf("1 - leitura de ficheiro de texto com representação de um job \n");
		printf("2 - Gravação de ficheiro de texto com representação de um job \n");
		printf("3 - Inserção e alteração de uma operação num job-> "); textcolor(YELLOW); printf("(SubMenu)\n"); textcolor(WHITE);
		printf("4 - Calculo do tempo minimo e listagem de um job\n");
		printf("5 - Calculo do tempo Maximo e listagem de um job\n");
		printf("6 - Inserção de um novo job\n");
		printf("7 - Remoção de um job\n");
		printf("8 - Escalonamento\n");
		printf("9 - Listagem de todos os jobs\n");
		printf("10 - sair\n");
		scanf("%d", &opcao);
		switch (opcao) {
		case 1://!leitura de ficheiro de texto com representação de um job
			system("cls");
			while (getchar() != '\n') {}
			if (processos != NULL) {
				textcolor(RED);
				printf("Deseja continuar ?, já existe dados na lista \nSe continuar vai perder todos os dados existentes \n");
				textcolor(MAGENTA);
				printf("Não (N) outra opção continua ->");
				textcolor(WHITE);
				while (toupper(getchar()) == 'N')
				{
					opcao = 0;
					break;
				}
			}
			if (opcao != 0) {
				printf("Nome do ficheiro:");
				textcolor(YELLOW);
				printf(": %s\n", ficheiro);
				textcolor(WHITE);
				printf("Deseja abrir outro ficheiro ? tecla (S) \n");
				while (toupper(getchar()) == 'S')
				{
					printf("Introduza o nome do ficheiro: ");
					scanf("%s", &ficheiro);
				}
				processos = ler(ficheiro);

				textcolor(GREEN);
				if (processos != NULL) printf("               Ficheiro lido com sucesso");//!Verifica se lista não está vazia
				textcolor(WHITE);
				printf("\n\n               Tecla enter para continua");
			}
			break;
		case 2://!Gravação de ficheiro de texto com representação de um job
			system("cls");

			//!printf("Nome do ficheiro a gravar: %s \n", ficheiroGrava);
			printf("Nome do ficheiro:");
			textcolor(YELLOW);
			printf(": %s\n", ficheiroGrava);
			textcolor(WHITE);
			printf("Se o nome for igual a um existente será apagado \n");
			printf("Deseja gravar outro ficheiro ? tecla (S) \n");
			getchar();
			while (toupper(getchar()) == 'S')
			{
				printf("Introduza o nome do ficheiro: ");
				scanf("%s", &ficheiroGrava);
			}
			escrever(processos, ficheiroGrava);/*Escreve num ficheiro o job guardado na memória*/
			break;
		case 3://!Inserção de uma nova operação
			system("cls");
			while (opcao == 3) {
				system("cls");
				textcolor(YELLOW);
				printf("   Submenu:\n\n");
				textcolor(WHITE);
				printf("1-Remover uma operação de um job\n2-Inserir uma operação num job\n3-Remoção de uma determinada operação de um job\n4-Altera uma das operações associadas a um job\n5-Voltar ao menu\n");
				scanf("%d", &opcao_1);
				if (opcao_1 != 0) {
					if (opcao_1 == 1) {//! Remover uma operação de um job
						processos = removerOperacao(processos);
					}
					if (opcao_1 == 2) {//! Inserir uma operação num job
						processos = NovaOperacao(processos);
						//correcao(processos);
					}
					if (opcao_1 == 3) {//! Remove uma das operações associadas a um job
						processos = remover(processos);
						//ordenaLista(processos);
					}
					if (opcao_1 == 4) {//! Altera uma das operações associadas a um job
						processos = altera(processos);
					}
					if (opcao_1 == 5) {//!Voltar ao menu
						opcao = 0;
					}
				}
				else {
					opcao_1 = 0;//!Volta a por a 0 opcao_1
					fflush(stdin);
				}
			}
			break;
		case 4://!Calculo e listagem dos tempos minimos
			system("cls");
			info = 1;//!informa os valores minimos
			Calculo(processos, info);
			break;
		case 5://!Calculo e listagem dos tempos maximos
			system("cls");
			info = 2;//!!informa os valores máximos
			Calculo(processos, info);
			break;
		case 6://!Inserção de um novo job;
			processos = inserioNovoJob(processos);
			break;
		case 7://!Remoção de um job;
			system("cls");
			if (processos != NULL) {
				processos = remocaoJob(processos);
			}
			else {
				textcolor(RED);
				printf("\n                lista vazia\n\n"); getchar();
				textcolor(WHITE);
			}
			break;
		case 8://! Escalonamento
			system("cls");
			if (processos != NULL) {
				escalonamento(processos);
			}
			else {
				textcolor(RED); printf("\n\n\n          Linhas de processos vazia"); textcolor(WHITE); getchar();
			}
			break;
		case 9://!listagem de todos os jobs
			system("cls");
			if (processos != NULL) {
				listar(processos);
				getchar();
			}
			else {
				textcolor(RED);
				printf("\n                lista vazia\n\n"); getchar();
				textcolor(WHITE);
			}
			break;

		case 10://!Limpa memória e sai do programa
			if (processos != NULL) free(processos);
			system("cls");
			break;
		default:
			opcao = 0;
			break;
		}
		getchar();
	}
}


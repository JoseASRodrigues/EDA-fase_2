#define _CRT_SECURE_NO_WARNINGS
#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "estrutura.h"
#include "calculos.h"

//! Novo registo no fim, sendo a lista vazia grava no inicio 
Processo* NovaOperacao(Processo* inicio) {
	Processo* lista = inicio;
	Processo* inicial = inicio;
	int numero = 0, job = 1, operacoes = 0, maquina = 0, tempo = 0, estado = 0, verifica = 0;
	int Qmaquinas = 0, sim = 0;
	listar(lista);
	printf("\nQual o job onde inserir as operações ->");
	scanf("%d", &job);
	if (job == 0) return inicio;
	while (inicial != NULL)
	{
		if (job == (inicial->prs)) {
			lista = inicial->job;
			break;
		}
		if (inicial == NULL) {
			textcolor(RED);
			printf("\n   Não foi encontrado o job-> %d  Enter continua", job); getchar();
			textcolor(WHITE);
			return inicio;
		}
		inicial = inicial->seguinte;
	}
	system("cls");
	listarJob(lista, job);
	printf("\nOperação a inserir-> ");
	scanf("%d", &operacoes);
	printf("Todos as operações existentes a partir de %d vão ter numeração seguinte", operacoes);
	if (operacoes == 0) return inicial;
	printf("\nQuantas máquinas para a operação %d (0 sai)->", operacoes);
	scanf("%d", &Qmaquinas);
	if (Qmaquinas == 0) return inicio;
	Jobs* listajob = NULL;
	listajob = inicial->job;
	//! Renomeia operações seguintes
	for (int i = inicial->operacoes; i >= operacoes; i--) {
		while (listajob != NULL) {
			if (listajob->operacoes == i) {
				listajob->operacoes = listajob->operacoes + 1;
			}
			listajob = listajob->seguinte;
		}
		listajob = inicial->job;//! Repôe lista de operações no inicio
	}
	for (int m = 0; m < Qmaquinas; m++) {
		verifica = 1;
		while (verifica == 1) {
			printf("\nMaquina->");
			while (maquina == 0)	scanf("%d", &maquina);

			verifica = verificaOperacao(listajob, operacoes, maquina);
			if (verifica == 1) {
				textcolor(RED);
				printf("\nmaquina Já existente para o job"); getchar();
				textcolor(WHITE);
				maquina = 0;
			}
			else {
				verifica = 0;
			}
		}
		printf("\nTempo->");
		while (tempo == 0)	scanf("%d", &tempo);
		listajob = inserirFim(listajob, 0, job, operacoes, maquina, tempo);
		maquina = 0;
		tempo = 0;
	}
	ordenaListaCrescente(listajob);
	listajob = inicial->job;//! Repôe lista de operações no inicio
	inicial->operacoes = inicial->operacoes + 1;
	return inicio;
}

//!Altera os valores de um registo menos os dados que sao controlados pelo programa 
Processo* altera(Processo* inicio)
{
	int opcao = 0, NumRegistos = 0, registo = 0, operacao = 0, maquina = 0, tempo = 0, resultado = 1, calculo = 0;
	Processo* inicial = inicio;
	Jobs* lista = NULL;
	if (inicial == NULL) {
		textcolor(RED);
		printf("\n         Lista vazia"); getchar();
		textcolor(WHITE);
		return;
	}
	listar(inicial);
	printf("Qual o job que deseja alterar (0 Aborta) Job->"); scanf("%d", &calculo);
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
			return inicio;
		}
	}
	Jobs* aux = lista;
	if (aux == NULL) {
		system("cls");
		textcolor(RED);
		printf("\n                                          Lista vazia");
		textcolor(WHITE);
		printf("\n                                     Tecla ENTER continua");
		getchar();
		getchar();
		return NULL;
	}
	else {
		system("cls");
		NumRegistos = listarJob(lista, calculo);
		printf("\n\nOnde quer alterar, escolha -> 1 ate %d ", NumRegistos);
		scanf("%d", &opcao);
		aux = lista;
		if (opcao > 0 && opcao <= NumRegistos) {
			for (int i = 1; i < opcao; i++) {
				aux = aux->seguinte;
			}
			textcolor(GREEN);
			printf("\nRegisto->%d Operação->%d Máquina->%d,Tempo->%d\n", opcao, aux->operacoes, aux->maquina, aux->tempo);
			textcolor(WHITE);
			printf("Operação->");
			scanf("%d", &operacao);
			if (operacao > inicial->operacoes) {
				operacao = inicial->operacoes + 1;
				printf("\nOpereção tem que ser sequencial, a sua operação será %d\n", operacao);

			}
			printf("Maquina->");
			while (maquina == 0) scanf("%d", &maquina);
			while (resultado == 1) {
				resultado = verificaOperacao(aux, operacao, maquina);//!Verifica se na operação já existe a maquina 
				if (resultado == 1) {
					textcolor(BLUE);
					printf("\nMáquina (%d) existente para operação-> %d Escolha outra máquina\n", maquina, operacao);
					textcolor(WHITE);
					printf("Operação->");
					scanf("%d", &operacao);
					printf("Maquina->");
					while (maquina == 0) scanf("%d", &maquina);
				}
			}
			printf("Tempo->");

			while (tempo == 0) scanf("%d", &tempo);

			printf("Deseja gravar os dados ? (S) ENTER não grava ");
			while (getchar() != '\n') {}
			if (toupper(getchar()) == 'S') {
				//!Insere na lista os dados 
				aux->operacoes = operacao;
				aux->maquina = maquina;
				aux->tempo = tempo;
				ordenaLista(inicial->job);
				if (operacao > inicial->operacoes) inicial->operacoes = operacao;
				printf("Operacoes %d maquina %d tempo %d ", operacao, maquina, tempo);
				textcolor(GREEN);
				printf("\n                 Os dados foram gravados na lista");
				textcolor(WHITE);
				getchar();
			}
			else {
				textcolor(RED);
				printf("                Os dados não foram gravados na lista");
				textcolor(WHITE);
			}
			getchar();
		}
		else {
			printf("Registo inválido");
			getchar();
			getchar();
		}
		return inicio;
	}
	return inicio;
}
//!Remove um registo da lista 
Processo* remover(Processo* inicio) {
	int numero = 0, operacao = 0, maquina = 0, opcao = 0, registo = 0, estado = 0, contador = 1, calculo;
	system("cls");

	Processo* inicial = inicio;
	Jobs* lista = NULL;
	if (inicial == NULL) {
		textcolor(RED);
		printf("\n         Lista vazia"); getchar();
		textcolor(WHITE);
		return;
	}
	listar(inicial);
	printf("Qual o job em que deseja remover (0 Aborta) Job->"); scanf("%d", &calculo);
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
			return inicio;
		}
	}
	Jobs* aux = lista;//
	if (lista != NULL) {
		system("cls");
		numero = listarJob(lista, calculo);
		getchar();//!Lista na consola e retorna quantos registos tem a lista 
		printf("\n\n\nDeseja remover um registo, ou uma máquina referente a uma operação ?  (1) Registo (2) Máquina->");
		scanf("%d", &opcao);
		if ((opcao < 1) || (opcao > 2)) {
			textcolor(RED);
			printf("\nOpeçao %d inválida", opcao); getchar(); getchar();
			textcolor(WHITE);
			return inicio;
		}
		if (opcao == 1) {
			registo = opcao;
			printf("\nQual o registo a remover %d até %d ? ", registo, numero);
			scanf("%d", &registo);
			textcolor(RED);
			if ((registo < 1) || (registo > numero))	printf("\n\n              Registo %d inválido !!", registo); getchar();
			textcolor(WHITE);
			lista = RemoveRegisto(inicio, registo);
			inicio->job = lista;
			textcolor(GREEN);
			if ((registo > 0) && (registo <= numero))	printf("\n\n              Remoção efetuada do registo %d !!", registo); getchar();
			textcolor(WHITE);
		}
		if (opcao == 2) {
			printf("\nQual a Operação ? ");
			scanf("%d", &operacao);
			printf("\nQual maquina ? ");
			scanf("%d", &maquina);
			Jobs* aux = lista;
			while (aux != NULL) {
				//!verifica se encontra
				if ((aux->operacoes == operacao) && (aux->maquina == maquina)) {
					printf("contador %d", contador);
					lista = RemoveRegisto(lista, contador);
					inicio->job = lista;
					textcolor(GREEN);
					printf("\n\n              Remoção efetuada na operação %d maquina %d !!", operacao, maquina); getchar(); getchar();
					textcolor(WHITE);
					free(aux);
				}
				aux = aux->seguinte;
				contador++;
			}
			textcolor(RED);
			printf("\n\n             Operação %d e Maquina %d não encontrada !!", operacao, maquina); getchar(); getchar();
			textcolor(WHITE);
			free(aux);
			return inicio;
		}
	}
	else
	{
		textcolor(RED);
		printf("\n\n           Lista vazia !!  carregue uma lista ou pode criar uma"); getchar(); getchar();
		textcolor(WHITE);

	}
	return(inicio);
}

Jobs* RemoveRegisto(Jobs* inicio, int registo)
{
	if (registo == 0) return inicio;
	Jobs* aux, * antes;
	int contador = 1;
	if (inicio == NULL)
	{
		return 0;  //! Lista vazia !!!
	}
	else
	{   //! Caso a lista nao esteja vazia
		aux = inicio;
		antes = inicio;
		while (aux != NULL)
		{
			if (contador == registo)
			{
				if (aux == inicio) //! Remove primeiro registo da lista 
				{
					antes = aux->seguinte;
					free(aux);
					inicio = antes;
					return antes; //! removeu !!
				}
				else  //! Remover meio da lista
				{
					antes->seguinte = aux->seguinte;  //! Refaz o encadeamento
					free(aux);                //! Liberta a memoria de aux
					return antes;
				}
			}
			else  //! continua procurando no prox. nodo
			{
				antes = aux;
				aux = aux->seguinte;
				contador++;
			}
		}
		return inicio;
	}
}

//!ordena lista jobs crscente
Jobs* ordenaLista(Jobs* inicio) {
	Jobs* i, * j, * aux;
	aux = (Jobs*)malloc(sizeof(Jobs));
	i = inicio;
	while (i != NULL) {
		j = i->seguinte;
		while (j != NULL) {
			if (i->operacoes > j->operacoes) {
				*aux = *i; //! copia valor de i em aux.
				*i = *j; //! copia valor de j em i.
				i->seguinte = aux->seguinte; //! altera ponterio do próximo de i para que continue a ser o mesmo que era antes da copia
				aux->seguinte = j->seguinte; //! copia o valor do ponteiro do proximo j
				*j = *aux; //! copia valor de aux em j.
				j->seguinte = aux->seguinte; //! altera ponteiro do próximo de i para que ele continue a ser o mesmo que era antes da copia
			}
			j = j->seguinte;
		}
		i = i->seguinte;
	}
	return inicio;
}

//!Verifica se a máquina ja existe para a mesma operação
int verificaOperacao(Jobs* inicio, int operacao, int maquina) {
	int resultado = 0;
	while (inicio != NULL)
	{
		if (inicio != NULL) {
			if ((inicio->operacoes == operacao) && (inicio->maquina == maquina)) {
				resultado = 1;
				break;
			}
		}
		inicio = inicio->seguinte;
	}
	return resultado;
}


//!ordena lista crescente
Jobs* ordenaListaCrescente(Jobs* inicio)
{
	Jobs* i, * j, * aux;
	aux = (Jobs*)malloc(sizeof(Jobs));
	i = inicio;
	while (i != NULL) {
		j = i->seguinte;
		while (j != NULL) {
			if (i->operacoes > j->operacoes) {
				*aux = *i; //! copia valor de i em aux.
				*i = *j; //! copia valor de j em i.
				i->seguinte = aux->seguinte; //! altera ponterio do próximo de i para que continue a ser o mesmo que era antes da copia
				aux->seguinte = j->seguinte; //! copia o valor do ponteiro do proximo j
				*j = *aux; //! copia valor de aux em j.
				j->seguinte = aux->seguinte; //! altera ponteiro do próximo de i para que ele continue a ser o mesmo que era antes da copia
			}
			j = j->seguinte;
		}
		i = i->seguinte;
	}
	free(aux);
	return inicio;
}
//! Remoção de um Job
Processo* remocaoJob(Processo* inicio) {
	int valor = 0;
	Processo* aux = inicio;
	system("cls");
	listar(inicio);
	printf("Qual o job que deseja apagar (0 sai sem apagar) -> ");
	scanf("%d", &valor);
	if (valor == 0) return inicio;
	while (aux != NULL) {
		if (aux->prs == valor) break;
		aux = aux->seguinte;
	}
	Jobs* aux1 = aux->job;
	Jobs* segue = aux->job;
	aux->job = NULL;
	aux->prs = NULL;
	aux->operacoes = 0;
	//! Apagar todos os enderecos do Job selecionado
	while (aux1 != NULL) {
		segue = aux1;
		aux1 = aux1->seguinte;
		free(segue);
	}
	free(aux1);//! Apaga endereco inicial da lista do job
	free(aux->job);//! Apaga endereco inicial do job da lista dos processos
	return inicio;
}
//! Inserir um novo job
Processo* inserioNovoJob(Processo* inicio) {
	Processo* aux = inicio;
	Jobs* lista = NULL;
	int numero = 0, existencia = 1, operacoes = 0, maquina = 0, tempo = 0, estado = 0, verifica = 0;
	int Qmaquinas = 0;
	printf("         Criação de um novo Job\n\n");
	printf("Numero do job a criar, (0 aborta criação do job)->");
	scanf("%d", &numero);
	if (numero == 0)return inicio;

	while (existencia != 0) {
		existencia = verificaExistenciaJob(inicio, numero);//! Verifica existencia do job
		if (existencia == 1) {
			textcolor(RED);
			printf("Numero do job existente, escolha outro (0 aborta criação do job)->");
			textcolor(WHITE);
			scanf("%d", &numero);
			if (numero == 0)  return inicio;
		}
	}
	printf("\nQuantas operações necessita para o job %d ? (0 Aborta) ", numero);
	scanf("%d", &operacoes);
	if (operacoes == 0)  return inicio;
	for (int i = 0; i < operacoes; i++) {
		printf("Operação->%d", i + 1);
		maquina = NULL;
		printf("\nQuantas máquinas para o job %d->", i + 1);
		scanf("%d", &Qmaquinas);
		//! Numero de máquinas para cada job
		for (int n = 0; n < Qmaquinas; n++) {
			//! Não avança enquanto o maquina for 0
			do {
				printf(" Máquina nº->"); scanf("%d", &maquina);
				verifica = verificaOperacao(lista, i + 1, maquina);//! Verifica se já existe maquina para o job
				if (verifica == 1) {
					textcolor(RED);
					printf("\nMaquina já existente para o job->%d Operação->%d Escolha outra máquina\n", numero, i + 1); getchar();
					textcolor(WHITE);
					maquina = 0;
				}
			} while (maquina == 0);
			printf("\nTempo máquina %d ->", maquina); scanf("%d", &tempo);
			lista = inserirFim(lista, estado, numero, i + 1, maquina, tempo);
			if ((i == 0) && (n == 0)) inicio = inserirFimProcesso(inicio, lista, operacoes, numero);
		}
	}


	return inicio;
}
//! Verifica se um job já existe
int verificaExistenciaJob(Processo* inicio, int numero) {
	Processo* aux = inicio;
	while (aux != NULL) {
		if (aux->prs == numero) {
			return 1;
		}
		aux = aux->seguinte;
	}
	return 0;
}

//!Remove uma operação num job
Processo* removerOperacao(Processo* inicio)
{
	int calculo = 0, numero = 0, opcao = 0, conta = 1, encontrou = 0;
	system("cls");
	Processo* inicial = inicio;
	Jobs* lista = NULL;
	Jobs* antes = NULL;
	Jobs* depois = NULL;
	if (inicial == NULL) {
		textcolor(RED);
		printf("\n         Lista vazia"); getchar();
		textcolor(WHITE);
		return;
	}
	listar(inicio);
	printf("Qual o job em que deseja remover a operação(0 Aborta) Job->"); scanf("%d", &calculo);
	if (calculo == 0) return inicial;
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
			return inicio;
		}
	}
	system("cls");
	numero = listarJob(lista, calculo);
	getchar();//! Lista na consola e retorna quantos registos tem a lista 
	printf("\n\nQual a operação do jo->%d que deseja remover -> ", calculo);
	scanf("%d", &opcao);
	lista = inicial->job;
	antes = lista;
	while (lista != NULL) {
		lista = inicial->job;
		conta = 1;
		while (lista != NULL) {
			if (lista->operacoes == opcao) {
				encontrou = 1;
				Remove(inicial->job, inicio, conta);
				lista = inicial->job;
				break;
			}
			conta++;
			lista = lista->seguinte;
		}
	}
	lista = inicial->job;
	//! Atualizar Operações
	while (lista != NULL) {
		for (int i = opcao; i <= inicial->operacoes; i++)
			if ((i + 1) == lista->operacoes) lista->operacoes = lista->operacoes - 1;
		lista = lista->seguinte;
	}
	inicial->operacoes = inicial->operacoes - 1;
	if (inicial->operacoes == 0) inicial->job = NULL;
	textcolor(GREEN);
	if (opcao != 0) {
		printf("Operação %d removida com sucesso e corrigido a sequencia das seguintes ", opcao); getchar(); getchar();
	}
	else {
		textcolor(RED);
		printf("Operação %d não existe ", opcao); getchar(); getchar();
	}
	textcolor(WHITE);
	return inicio;
}

//! Remove registos de operações
Jobs* Remove(Jobs* inicio, Processo* job, int registo)
{
	Jobs* aux, * antes;
	int contador = 1;
	if (inicio == NULL)
	{
		return 0;  //! Lista vazia !!!
	}
	else
	{   //! Caso a lista nao esteja vazia
		aux = inicio;
		antes = inicio;
		while (aux != NULL)
		{
			if (contador == registo)
			{
				if (aux == inicio) //! Remove primeiro registo da lista 
				{
					Jobs* tmp = aux->seguinte;
					antes = aux->seguinte;
					free(aux);
					inicio = antes;
					//return antes; //! removeu !!

					while (inicio != NULL) {
						if (registo = job->prs) job->job = tmp;
						return antes;
						job = job->seguinte;
					}
				}
				else  //! Remover meio da lista
				{
					if (inicio != NULL) {
						antes->seguinte = aux->seguinte;  //! Refaz o encadeamento
						free(aux);                //! Liberta a memoria de aux
						return antes;
					}
					else {
						return inicio;
					}
				}
			}
			else  //! continua procurando no prox. nodo
			{
				antes = aux;
				aux = aux->seguinte;
				contador++;
			}
		}
		return inicio;
	}
}

//! Ordena maquinas por operação

void ordena(Processo* processo) {
	Jobs* iniciojob = NULL;
	while (processo != NULL) {
		iniciojob = processo->job;
		processo = processo->seguinte;
	}

}


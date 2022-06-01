#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

FILE* fp;//!Definição do ficheiro
//!*Definição das funções e procedimentos
Jobs* inserirInicio(Jobs* inicio, int Estado, int Processo, int Operacao, int Maquina, int Tempo);
Jobs* inserirFim(Jobs* inicio, int Estado, int Processo, int Operacao, int Maquina, int Tempo);
Jobs* Remove(Jobs* inicio, Processo* processo, int registo);
Jobs* RemoveRegisto(Jobs* inicio, int registo);
Jobs* ordenaLista(Jobs* inicio);
Jobs* ordenaListaCrescente(Jobs* inicio);
Processo* removerOperacao(Processo* inicio);
Processo* NovaOperacao(Processo* inicio);
Processo* ler(char ficheiro[]);
Processo* altera(Processo* inicio);
Processo* remover(Processo* inicio);
Processo* inserirFimProcesso(Processo* processo, Jobs* lista, int operacoes, int prs);
Processo* inserirInicioProcesso(Processo* processo, Jobs* lista, int operacoes, int prs);
Processo* remocaoJob(Processo* processo);
Processo* inserioNovoJob(Processo* processo);
int verificaOperacao(Jobs* inicio, int operacao, int maquina);
int listar(Processo* inicio);
int listarJob(Jobs* inicio, int calculo);
int verificaExistenciaJob(Processo* processo, int numero);
void ordena(Processo* processo);
void escrever(Processo* inicio, char ficheiro[]);
//! Lista para guardar dados de leitura do ficheiro TXT
Prs* inserirFimPrs(Prs* prs, int linha, int proc);
Prs* inserirInicioPrs(Prs* prs, int linha, int proc);


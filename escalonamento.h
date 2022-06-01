#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

//! Cria na lista registo de maquinas no inicio
Maquinas* inserirInicioMaq(Maquinas* inicio, int Maquina, int Tempo);
//! Cria na lista registo de maquinas no fim
Maquinas* inserirFimMaq(Maquinas* inicio, int Maquina, int Tempo);
//! Cria lista de escalonamento no inicio
Escalonamento* inserirInicioEsca(Escalonamento* inicio, EscalProcOpe* lista, int Maquina);
//! Cria lista de escalonamento no fim
Escalonamento* inserirFimEsca(Escalonamento* inicio, EscalProcOpe* lista, int Maquina);
//! Cria lista de registo no inicio, de processos e operações relativas a uma máquina
EscalProcOpe* inserirInicioProcOpe(EscalProcOpe* inicio, int Processo, int Operacao);
//! Cria lista de registo no fim, de processos e operações relativas a uma máquina
EscalProcOpe* inserirFimProcOpe(EscalProcOpe* inicio, int Processo, int Operacao);
//! Verifica se Job e operação já existe no lista do escalonamento
int verificaEscalonamento(Escalonamento* inicio, int Processo, int Operacao);
//! Determina o numero de máquinas
int maquinas(Processo* inicio);
//! Verifica se a maquina está em utilização
int verificaMaquina(Maquinas* inicio, int maquina);
//! Volta a colocar a maquina disponivel
void descontaMaquina(Maquinas* inicio);
//! Procura o menor tempo de maquina para utilizar
void procuraMenor(Processo* inicio, Maquinas* inicioMaq, Escalonamento* inicioEsca, EscalProcOpe* lista, int Operacoes);
//! Calculo do escalonamento
void escalonamento(Processo* inicio);



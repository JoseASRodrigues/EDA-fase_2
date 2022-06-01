#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculos.h"

void Calculo(Processo* inicio, int control);
void somas(Jobs* inicio, int estado, int info, int calculo);
void estadoPoe(Jobs* inicio, int aux1, int maquina, int estado);
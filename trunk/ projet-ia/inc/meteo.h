
#ifndef METEO_H
#define METEO_H

//Include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../inc/constantes.h"
#include "../inc/structures.h"




//Prototypes
float SimulationTemp(float temp_prec,float temp_min, float temp_max);
float SimulationTemp2(ST_SimuMeteo Meteo_Precedente,ST_DonneeMeteo Normales_Mensuelles);
void SimulationConditionsMeteo(ST_DonneeMeteo Normales_Mensuelles, PTR_ST_SimuMeteo Meteo_Jour);

#endif
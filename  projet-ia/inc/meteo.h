
#ifndef METEO_H
#define METEO_H

//Include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "../inc/constantes.h"
#include "../inc/structures.h"





//Prototypes
float SimulationTemp(ST_JOUR *Jour_prec,ST_DonneeMeteo Normales_Mensuelles);
void SimulationConditionsMeteo(ST_DonneeMeteo Normales_Mensuelles, PTR_ST_SimuMeteo Meteo_Jour);
void SimulationHeuresEnsoleillement(ST_DonneeMeteo NormalesMensuelles, PTR_ST_SimuMeteo Meteo_Jour);
void Calc_puiss_soleil(PTR_ST_SimuMeteo Meteo_Jour);
void Simu_Jour(PTR_ST_SimuMeteo Meteo_Jour, ST_DonneeMeteo NormalesMensuelles,ST_JOUR *Jour_prec);
float my_rand(void);

#endif
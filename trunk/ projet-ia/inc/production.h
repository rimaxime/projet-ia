#ifndef PRODUCTION_H
#define PRODUCTION_H

//Include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "meteo.h"
#include "constantes.h"
#include "structures.h"


//Prototypes
void Calc_puiss_soleil(PRT_ST_SimuMeteo Meteo_Jour, STR_DEPARTEMENT Dept);
float Rendement_geo(ST_DonneGeo Donnees);
void Rendement_panneaux(ST_PANNEAUX Panneaux);
float Rendement_thermique(ST_SimuMeteo Jour);
float Prod_jour(PTR_SimuMeteo Jour,ST_DonneGeo Donnees,ST_PANNEAUX Panneaux);

#endif
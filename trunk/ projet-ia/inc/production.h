#ifndef PRODUCTION_H
#define PRODUCTION_H

//Include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
//#include "meteo.h"
#include "constantes.h"
#include "structures.h"

#include "../inc/meteo.h"

//Prototypes
float Rendement_geo(ST_DonneGeo Donnees);
void Rendement_panneaux(PTR_ST_PANNEAUX Panneaux);
float Rendement_thermique(ST_SimuMeteo Jour);

float Prod_jour(PTR_ST_SimuMeteo Jour,ST_DonneGeo Donnees,PTR_ST_PANNEAUX Panneaux);

#endif
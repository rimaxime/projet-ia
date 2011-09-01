#ifndef CONSOMATION_H
#define CONSOMATION_H

//Include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "constantes.h"
#include "structures.h"


//Prototypes
float consommation_equipements(ST_EQUIPEMENTS Equipement);
float consommation_equipements_piece(ST_PIECES Piece);
float consommation_equipements_habitation(ST_HABITATIONS Habitations);
float volume_piece(ST_PIECES Piece);
float volume_habitation(ST_HABITATIONS Habitation);
float consommation_chauffage(ST_JOUR Jour, ST_HABITATIONS Habitation);
float consommation_globale(ST_JOUR Jour, ST_HABITATIONS Habitation);

#endif
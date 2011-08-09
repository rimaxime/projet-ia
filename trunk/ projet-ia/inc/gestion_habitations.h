/**
  * \file gestion_habitations.h
  * \brief Crée les maisons et les différentes pièces associées
  * \author MRI
  * \date 08/08/2011
  */



#ifndef GESTION_HABITATIONS_H
#define GESTION_HABITATIONS_H



//Include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "../inc/constantes.h"
#include "../inc/structures.h"


ST_HABITATIONS* CreationHabitation(int nombre_pieces, float inclinaison_toit, int Isolation,int Exposition);

ST_PIECES* CreationPiece(char* nom_piece, int type_piece, float Largeur, float Longueur, float coordX1, float coordY1,float coordX2, float coordY2);

ST_PIECES* InsererTrierPiece(ST_PIECES *Nouvelle, ST_PIECES *Tete);

ST_EQUIPEMENTS* CreationEquipement(int indice, char *nom_equipement, float consommation_equipement, float nombre_heures_utilisation_journalier,
				  float Largeur, float Longueur, float coordX1,float coordX2, float coordY1, float coordY2);

ST_EQUIPEMENTS* InsererTrierEquipements(ST_EQUIPEMENTS *Nouveau, ST_EQUIPEMENTS *Tete);

ST_PANNEAUX* CreationPanneaux(int indice, int type, float Largeur, float Longueur, float inclinaison_panneau, int Exposition);

ST_PANNEAUX* InsererTrierPanneaux(ST_PANNEAUX *Nouveau, ST_PANNEAUX *Tete);

void Detruire_Habitation(ST_HABITATIONS *Habitation);

void Detruire_Pieces(ST_PIECES *Tete);

void Detruire_Equipements(ST_EQUIPEMENTS *Tete);

void Detruire_Panneaux(ST_PANNEAUX *Tete);

#endif
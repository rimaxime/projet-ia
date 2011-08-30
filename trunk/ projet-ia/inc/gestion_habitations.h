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

/**
 * \name   Creation Habitation
 * \brief  Crée une nouvelle habitation à l'aide des paramètres de la fonction
 * \param  int nombre_pieces, Isolation, Exposition
 * \param  float inclinaison_toit
 * \return ST_HABITATIONS*, La nouvelle habitation 
 */
ST_HABITATIONS* CreationHabitation(int nombre_pieces, float inclinaison_toit, char* Isolation,int Exposition, char* Departement);

/**
 * \name   Modifier Habitation
 * \brief  Modifie une habitation à l'aide des paramètres de la fonction
 * \param  int nombre_pieces, Isolation, Exposition
 * \param  float inclinaison_toit
 * \return ST_HABITATIONS*, L'habitation 
 */
ST_HABITATIONS* ModifierHabitation(ST_HABITATIONS* Habitation,int nombre_pieces, float inclinaison_toit, char Isolation[CMAX],int Exposition, char Departement[CMAX]);

/**
 * \name   Creation des Pieces
 * \brief  Crée une nouvelle pièce dans la liste de pièces avec les paramètres de la fonction
 * \param  int type_piece
 * \param  float Largeur, Longueur, qui sont la taille de la pièce; coordX1, coordX2, coordY1, coordY2, qui sont les coordonnées des coins hauts 
 * et bas de la pièce dans l'IHM
 * \param  char* nom_piece
 * \return ST_PIECES*, La nouvelle pièce completée 
 */
ST_PIECES* CreationPiece(char* nom_piece, int type_piece, float Largeur, float Longueur, float coordX1, float coordY1,float coordX2, float coordY2);

ST_PIECES* Trouver_Piece(ST_PIECES * Tete, char nom_piece[CMAX]);

/**
 * \name   Modification des Pieces
 * \brief  Modifier une piéce
 * \param  int type_piece
 * \param  float Largeur, Longueur, qui sont la taille de la pièce; coordX1, coordX2, coordY1, coordY2, qui sont les coordonnées des coins hauts 
 * et bas de la pièce dans l'IHM
 * \return ST_PIECES*, La pièce completée 
 */
ST_PIECES* ModifierPiece(ST_PIECES* Piece, int type_piece, float Largeur, float Longueur);

/**
 * \name   Insertion Triée des Pièces
 * \brief  Insère la Pièce au bon emplacement dans la liste de pièces, triée par ordre alphabétique en fonction du nom de la pièce. Fonction Récursive
 * \param  Structure ST_PIECES* qui sont la Tete de cette liste ainsi que la pièce à insérer
 * \return ST_PIECES* Retour de la nouvelle tete de la liste
 */
ST_PIECES* InsererTrierPiece(ST_PIECES *Nouvelle, ST_PIECES *Tete);

/**
 * \name   Création d'un équipement
 * \brief  Crée un nouvel équipement dans une pièce donnée et l'ajoute à la liste associée
 * \param  int indice représentant l'nième équipement de la pièce
 * \param  char* nom_equipement représentant le nom de l'équipement, ne peut être nul
 * \param  float consommation_equipement représentant la consommation de l'appareil, nombre_heures_utilisation_journalier le nombre d'heure moyen de 
 * 		 l'utilisation de l'appareil. Largeur, Longueur représentant la taille de l'appareil. coordX/Y-1/2 représentant les coordonnées de
 * 		 l'appareil dans l'IHM
 * \return ST_EQUIPEMENTS* Retour de l'équipement une fois completé
 */
ST_EQUIPEMENTS* CreationEquipement(int indice, char *nom_equipement, float consommation_equipement, float nombre_heures_utilisation_journalier,
				  float Largeur, float Longueur, float coordX1,float coordX2, float coordY1, float coordY2);


ST_EQUIPEMENTS* ModifierEquipement(ST_EQUIPEMENTS* Equipement, float consommation_equipement, float nombre_heures_utilisation_journalier,
				  float Largeur, float Longueur, float coordX1,float coordX2, float coordY1, float coordY2);				  
				  
/**
 * \name   Insertion Triée des Equipements
 * \brief  Insère la Pièce au bon emplacement dans la liste des équipements, triée par ordre alphabétique en fonction du nom de l'équipement. Fonction Récursive
 * \param  Structure ST_EQUIPEMENTS* qui sont la Tete de cette liste ainsi que l'équipement à insérer
 * \return ST_EQUIPEMENTS* Retour de la nouvelle tete de la liste
 */
ST_EQUIPEMENTS* InsererTrierEquipements(ST_EQUIPEMENTS *Nouveau, ST_EQUIPEMENTS *Tete);


/**
 * \name   Création d'un panneau solaire
 * \brief  Crée un nouveau panneau solaire 
 * \param  int indice représentant l'nième panneau de la maison, type qui spécifie le type de panneaux, Exposition qui donne selon un chiffre 
 * 		de 1 à 8 l'exposition du panneau solaire
 * \param  float Largeur, Longueur représente la taille du panneau solaire, inclinaison_panneau qui est l'inclinaison du panneau
 * \return ST_EQUIPEMENTS* Retour de l'équipement une fois completé
 */
ST_PANNEAUX* CreationPanneaux(int indice, int type, float Largeur, float Longueur, float inclinaison_panneau, int Exposition);


ST_PANNEAUX* ModifierPanneaux(ST_PANNEAUX *Panneau, int type, float Largeur, float Longueur, float inclinaison_panneau, int Exposition);

/**
 * \name   Insertion Triée des Panneaux
 * \brief  Insère le panneau au bon endroit dans une liste triée  par l'indice de celui ci. Fonction récursive
 * \param  Structure ST_PANNEAUX* qui sont la Tete de cette liste ainsi que le panneau à insérer
 * \return ST_PANNEAUX* Retour de la nouvelle tete de la liste
 */
//ST_PANNEAUX* InsererTrierPanneaux(ST_PANNEAUX *Nouveau, ST_PANNEAUX *Tete);

ST_PIECES* Supprimer_Piece(ST_PIECES *Tete, char nom_piece[CMAX]);

ST_EQUIPEMENTS* Supprimer_Equipement(ST_EQUIPEMENTS *Tete, char nom_equipement[CMAX])

void Detruire_Habitation(ST_HABITATIONS *Habitation);

void Detruire_Pieces(ST_PIECES *Tete);

void Detruire_Equipements(ST_EQUIPEMENTS *Tete);

void Detruire_Panneaux(ST_PANNEAUX *Tete);

#endif
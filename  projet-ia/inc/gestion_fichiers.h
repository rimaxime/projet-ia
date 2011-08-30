/**
  * \file gestion_fichiers.h
  * \brief Récupére les données des bases de données pour les
  * les mettre dans des tableaux / listes
  * \author MRI
  * \date 11/07/2011
  */


#ifndef GESTION_FICHIERS_H
#define GESTION_FICHIERS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/constantes.h"
#include "../inc/structures.h"

/**
 * \fn     STR_DEPARTEMENT * RecupererInfosDepartement(STR_DEPARTEMENT * tableau_departements, int* size_tab)
 * \name   Récupérer les Infos sur les Départements
 * \brief  Permet de récupérer toutes les infos sur les département depuis le fichier associé
 * \param  Structure STR_DEPARTEMENT* tableau_departements qui est le tableau dans lequel sera archivé les données du fichier
 * \param  int *size_tab représentant la taille du tableau (nombre de départements)
 * \return STR_DEPARTEMENT* Retour du tableau completé
 */

STR_DEPARTEMENT * RecupererInfosDepartement(STR_DEPARTEMENT * tableau_departements, int* size_tab);


#endif
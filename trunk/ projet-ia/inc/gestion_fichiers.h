/**
  * \file gestion_fichiers.h
  * \brief Récupére les données des bases de données pour les
  * les mettre dans des tableaux / listes
  * \author MRI
  * \date 11/07/2011
  */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/constantes.h"
#include "../inc/structures.h"

/**
	* \fn int RecupererInfosDepartement(STR_DEPARTEMENT * tableau_departements)
  * \brief Cette fonction va balayer le fichier de départements afin de récupérer les normales météo mensuelles de 
  * ses départements.
  * \param tableau_departements Tableau des départements
	* \return 0 si pas d'erreur -1 sinon
  */

STR_DEPARTEMENT * RecupererInfosDepartement(STR_DEPARTEMENT * tableau_departements, int* size_tab);
#ifndef LISTE_EVENEMENT_H
#define LISTE_EVENEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../inc/structures.h"
#include "../inc/constantes.h"


#include "../inc/consomation.h"
#include "../inc/meteo.h"
#include "../inc/production.h"


//Prototypes
ST_JOUR* creer_jour(ST_Date Date, ST_HABITATIONS Habitation, ST_DonneGeo Donnee_geo,STR_DEPARTEMENT departements, ST_JOUR *Jour_precedent);

STR_DEPARTEMENT* parseur_departement(STR_DEPARTEMENT* Tableau_departement, char *nom_departement);

ST_DonneGeo* parseur_donnees_geo(ST_DonneGeo *Tableau_Geo, int inclinaison, int exposition);

ST_JOUR* creer_liste_jours(ST_Date Date_Debut,ST_Date Date_Fin, ST_HABITATIONS Habitation, ST_DonneGeo Donnee_geo,STR_DEPARTEMENT departements, ST_JOUR *Jour_precedent);

#endif
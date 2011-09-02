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

void supprimer_jour(ST_Date Date_sup, PTR_ST_JOUR *tete);

void supprimer_liste_jour(ST_Date Date_Debut,ST_Date Date_Fin , PTR_ST_JOUR *tete);

int comparer_date(ST_Date Date1, ST_Date Date2); //if Date1 > Date2 = 1; Date1=Date2 =0 ; Date1 < Date2 = -1

ST_JOUR* retrouver_jour(ST_Date Date_rech, ST_JOUR *tete);

#endif
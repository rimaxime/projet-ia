//Includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../inc/constantes.h"
#include "../inc/structures.h"
#include "../inc/production.h"
#include "../inc/consomation.h"
#include "../inc/meteo.h"
#include "../inc/liste_evenement.h"
#include "../inc/gestion_fichiers.h"

//prototytpes
void test_creer_evenement();

int main(void)
{
  test_creer_evenement();
  return 0;
}

void test_creer_evenement()
{
  ST_EQUIPEMENTS Equip1;
  ST_EQUIPEMENTS Equip2;
  ST_EQUIPEMENTS Equip3;
  ST_EQUIPEMENTS Equip4;
  ST_EQUIPEMENTS Equip5;
  ST_EQUIPEMENTS Equip6;
  Equip1.consommation_equipement=230;
  Equip1.nombre_heures_utilisation_journalier=6;
  Equip1.suiv=&Equip2;
  Equip2.consommation_equipement=60;
  Equip2.nombre_heures_utilisation_journalier=2;
  Equip2.suiv=&Equip3;
  Equip3.consommation_equipement=130;
  Equip3.nombre_heures_utilisation_journalier=0.3;
  Equip3.suiv=&Equip4;
  Equip4.consommation_equipement=3000;
  Equip4.nombre_heures_utilisation_journalier=2;
  Equip4.suiv=&Equip5;
  Equip5.consommation_equipement=10;
  Equip5.nombre_heures_utilisation_journalier=10;
  Equip5.suiv=&Equip6;
  Equip6.consommation_equipement=100;
  Equip6.nombre_heures_utilisation_journalier=24;
  Equip6.suiv=NULL;

  
  ST_PIECES Piece1;
  ST_PIECES Piece2;
  ST_PIECES Piece3;
  ST_PIECES Piece4;
  Piece1.Largeur=2;
  Piece2.Largeur=2;
  Piece3.Largeur=2;
  Piece4.Largeur=2;
  Piece1.Longueur=5;
  Piece2.Longueur=5;
  Piece3.Longueur=5;
  Piece4.Longueur=5;
  Piece1.LC_Equipements=&Equip1;
  Piece2.LC_Equipements=&Equip2;
  Piece3.LC_Equipements=&Equip3;
  Piece4.LC_Equipements=NULL;
  Piece1.suiv=&Piece2;
  Piece2.suiv=&Piece3;
  Piece3.suiv=&Piece4;
  Piece4.suiv=NULL;
  
  ST_PANNEAUX Panneaux;
  Panneaux.type = 1;
  Panneaux.Largeur = 10;
  Panneaux.Longueur = 5;
  Panneaux.MPPT = 0;
  Panneaux.auto_rotation = 0;
  
  ST_HABITATIONS Habitations;
  Habitations.nombre_pieces=4;
  Habitations.LC_Pieces=&Piece1;
  Habitations.Isolation=1;
  Habitations.climatisation=1;
  Habitations.chauffage_electricite=70;
  Habitations.inclinaison_toit = 30;
  Habitations.Exposition = 30;
  Habitations.LC_Panneaux = &Panneaux;
  strcpy(Habitations.Departement,"Aude");
  ST_Date Date;
  Date.Jour = 12;
  Date.Mois = 8;
  Date.Annee = 2011;  
  
  int taille_tableau;
  STR_DEPARTEMENT *tableau_dept = NULL;
  tableau_dept=RecupererInfosDepartement(tableau_dept,&taille_tableau);
  
  ST_DonneGeo *Donnee_geo = NULL;
  Donnee_geo = RecupererInfosGeographique(Donnee_geo);
  
  STR_DEPARTEMENT *Notre_departements = NULL;
  Notre_departements = parseur_departement(tableau_dept, Habitations.Departement);
  
  ST_DonneGeo *Nos_Donnees_geo = NULL;
  Nos_Donnees_geo = parseur_donnees_geo(Donnee_geo,Habitations.inclinaison_toit,Habitations.Exposition);
  
  ST_JOUR prec;
  prec.date.Jour = 11;
  prec.date.Mois = 8;
  prec.date.Annee = 2011;
  prec.temperature = 22;
  
  ST_JOUR *test = NULL;
  
  test = creer_jour(Date,Habitations,*Nos_Donnees_geo,*Notre_departements,&prec);
  printf("%d/%d/%d :\n\tTemperature :  %f \n\tCondition : %d\n\tProduction : %f\n\t Consommation : %f\n",test->date.Jour,test->date.Mois,
                                                                                                       test->date.Annee,test->temperature,
                                                                                                       test->condition, test->production,
	                                                                                               test->consommation);
  
  
}
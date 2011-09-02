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
void test_creer_liste_evenement();
void test_comp_date();
void test_supprimer_jour();
void test_supprimer_liste_jour();
void test_retrouver_jour();
void test_enregistrer_rapport();


int main(void)
{
  //test_creer_evenement();
  //test_creer_liste_evenement();
  //test_comp_date();
  //test_supprimer_jour();
  //test_supprimer_liste_jour();
  //test_retrouver_jour();
  test_enregistrer_rapport();
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

void test_creer_liste_evenement()
{
  ST_Date Date_Debut;
  Date_Debut.Jour = 1;
  Date_Debut.Mois = 1;
  Date_Debut.Annee = 2010;
  
  ST_Date Date_Fin;
  Date_Fin.Jour = 1;
  Date_Fin.Mois = 1;
  Date_Fin.Annee = 2020;
  
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
  
  
  STR_DEPARTEMENT *tableau_dept = NULL;
  int taille_tableau;
  tableau_dept=RecupererInfosDepartement(tableau_dept,&taille_tableau);
  

  
  STR_DEPARTEMENT *Notre_departements = NULL;
  Notre_departements = parseur_departement(tableau_dept, Habitations.Departement);
  
  ST_DonneGeo *Donnee_geo = NULL;
  Donnee_geo = RecupererInfosGeographique(Donnee_geo);
  
  ST_DonneGeo *Nos_Donnees_geo = NULL;
  Nos_Donnees_geo = parseur_donnees_geo(Donnee_geo,Habitations.inclinaison_toit,Habitations.Exposition);
  
  ST_JOUR *Jour_precedent = NULL;
  
  ST_JOUR* liste = NULL;
  liste = creer_liste_jours(Date_Debut,Date_Fin,Habitations,*Nos_Donnees_geo,*Notre_departements,Jour_precedent);
  
  while(liste != NULL)
  {
    printf("\nDate : %d / %d / %d",liste->date.Jour,liste->date.Mois,liste->date.Annee);
    printf("\n\tTemperature:  %f",liste->temperature);
    printf("\n\tCondition:    %d",liste->condition);
    printf("\n\tProduction:   %f",liste->production);
    printf("\n\tConsommation: %f",liste->consommation);
    printf("\n\tGain:         %f",liste->gain); 
    printf("\n\tCout:         %f\n",liste->cout);
    liste=liste->suiv;
  }
  
}

void test_comp_date()
{
  ST_Date Date1;
  Date1.Jour = 1;
  Date1.Mois = 1;
  Date1.Annee = 2010;
  
  ST_Date Date2;
  Date2.Jour = 1;
  Date2.Mois = 1;
  Date2.Annee = 2020;
  
  printf("Resultat inf : %d\n",comparer_date(Date1,Date2));
  
  Date1.Jour = 14;
  Date1.Mois = 3;
  Date1.Annee = 2010;
  Date2.Jour = 14;
  Date2.Mois = 3;
  Date2.Annee = 2010; 
  printf("Resultat egual : %d\n",comparer_date(Date1,Date2));
  
  Date1.Jour = 18;
  Date1.Mois = 5;
  Date1.Annee = 2011;
  Date2.Jour = 15;
  Date2.Mois = 4;
  Date2.Annee = 2011; 
  printf("Resultat sup : %d\n",comparer_date(Date1,Date2));
}

void test_supprimer_jour()
{
  ST_Date Date_Debut;
  Date_Debut.Jour = 2;
  Date_Debut.Mois = 11;
  Date_Debut.Annee = 2010;
  
  ST_Date Date_Fin;
  Date_Fin.Jour = 6;
  Date_Fin.Mois = 11;
  Date_Fin.Annee = 2010;
  
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
  
  
  STR_DEPARTEMENT *tableau_dept = NULL;
  int taille_tableau;
  tableau_dept=RecupererInfosDepartement(tableau_dept,&taille_tableau);
  

  
  STR_DEPARTEMENT *Notre_departements = NULL;
  Notre_departements = parseur_departement(tableau_dept, Habitations.Departement);
  
  ST_DonneGeo *Donnee_geo = NULL;
  Donnee_geo = RecupererInfosGeographique(Donnee_geo);
  
  ST_DonneGeo *Nos_Donnees_geo = NULL;
  Nos_Donnees_geo = parseur_donnees_geo(Donnee_geo,Habitations.inclinaison_toit,Habitations.Exposition);
  
  ST_JOUR *Jour_precedent = NULL;
  
  printf("avant liste\n");
  PTR_ST_JOUR liste = NULL;
  liste = creer_liste_jours(Date_Debut,Date_Fin,Habitations,*Nos_Donnees_geo,*Notre_departements,Jour_precedent);
  printf("après liste\n");
  
  ST_Date Date_sup;
  Date_sup.Jour = 2;
  Date_sup.Mois = 11;
  Date_sup.Annee = 2010;
  printf("Pré-entre supprimer1\n");
  supprimer_jour(Date_sup,&liste);
  printf("Sorti supprimer 1\n");
  
  ST_Date Date_sup2;
  Date_sup2.Jour = 6;
  Date_sup2.Mois = 11;
  Date_sup2.Annee = 2010;
  supprimer_jour(Date_sup2,&liste);
  
  while(liste != NULL)
  {
    printf("\nDate : %d / %d / %d",(liste->date.Jour),(liste->date.Mois),(liste->date.Annee));
    printf("\n\tTemperature:  %f",(liste->temperature));
    printf("\n\tCondition:    %d",(liste->condition));
    printf("\n\tProduction:   %f",(liste->production));
    printf("\n\tConsommation: %f",(liste->consommation));
    printf("\n\tGain:         %f",(liste->gain)); 
    printf("\n\tCout:         %f\n",(liste->cout));
    liste=(liste->suiv);
  }
}

void test_supprimer_liste_jour()
{
  ST_Date Date_Debut;
  Date_Debut.Jour = 1;
  Date_Debut.Mois = 11;
  Date_Debut.Annee = 2010;
  
  ST_Date Date_Fin;
  Date_Fin.Jour = 10;
  Date_Fin.Mois = 11;
  Date_Fin.Annee = 2010;
  
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
  
  
  STR_DEPARTEMENT *tableau_dept = NULL;
  int taille_tableau;
  tableau_dept=RecupererInfosDepartement(tableau_dept,&taille_tableau);
  

  
  STR_DEPARTEMENT *Notre_departements = NULL;
  Notre_departements = parseur_departement(tableau_dept, Habitations.Departement);
  
  ST_DonneGeo *Donnee_geo = NULL;
  Donnee_geo = RecupererInfosGeographique(Donnee_geo);
  
  ST_DonneGeo *Nos_Donnees_geo = NULL;
  Nos_Donnees_geo = parseur_donnees_geo(Donnee_geo,Habitations.inclinaison_toit,Habitations.Exposition);
  
  ST_JOUR *Jour_precedent = NULL;
  

  PTR_ST_JOUR liste = NULL;
  liste = creer_liste_jours(Date_Debut,Date_Fin,Habitations,*Nos_Donnees_geo,*Notre_departements,Jour_precedent);
 
  ST_Date Date_Debut_sup;
  Date_Debut_sup.Jour = 5;
  Date_Debut_sup.Mois = 11;
  Date_Debut_sup.Annee = 2010;
  
  ST_Date Date_Fin_sup;
  Date_Fin_sup.Jour = 10;
  Date_Fin_sup.Mois = 11;
  Date_Fin_sup.Annee = 2010;
  
  printf("Debut suppr\n");
  supprimer_liste_jour(Date_Debut_sup,Date_Fin_sup,&liste);
  printf("Fin suppr\n");
  
  while(liste != NULL)
  {
    printf("\nDate : %d / %d / %d",(liste->date.Jour),(liste->date.Mois),(liste->date.Annee));
    printf("\n\tTemperature:  %f",(liste->temperature));
    printf("\n\tCondition:    %d",(liste->condition));
    printf("\n\tProduction:   %f",(liste->production));
    printf("\n\tConsommation: %f",(liste->consommation));
    printf("\n\tGain:         %f",(liste->gain)); 
    printf("\n\tCout:         %f\n",(liste->cout));
    liste=(liste->suiv);
  }
}

void test_retrouver_jour()
{
  ST_Date Date_Debut;
  Date_Debut.Jour = 1;
  Date_Debut.Mois = 2;
  Date_Debut.Annee = 2010;
  
  ST_Date Date_Fin;
  Date_Fin.Jour = 25;
  Date_Fin.Mois = 11;
  Date_Fin.Annee = 2010;
  
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
  
  
  STR_DEPARTEMENT *tableau_dept = NULL;
  int taille_tableau;
  tableau_dept=RecupererInfosDepartement(tableau_dept,&taille_tableau);
  

  
  STR_DEPARTEMENT *Notre_departements = NULL;
  Notre_departements = parseur_departement(tableau_dept, Habitations.Departement);
  
  ST_DonneGeo *Donnee_geo = NULL;
  Donnee_geo = RecupererInfosGeographique(Donnee_geo);
  
  ST_DonneGeo *Nos_Donnees_geo = NULL;
  Nos_Donnees_geo = parseur_donnees_geo(Donnee_geo,Habitations.inclinaison_toit,Habitations.Exposition);
  
  ST_JOUR *Jour_precedent = NULL;
  

  PTR_ST_JOUR liste = NULL;
  liste = creer_liste_jours(Date_Debut,Date_Fin,Habitations,*Nos_Donnees_geo,*Notre_departements,Jour_precedent);
 
  ST_Date Date_rech;
  Date_rech.Jour = 1;
  Date_rech.Mois = 1;
  Date_rech.Annee = 2010;
  
  ST_JOUR *RECH = NULL;  
  RECH = retrouver_jour(Date_rech, liste);

    printf("\nDate : %d / %d / %d",(RECH->date.Jour),(RECH->date.Mois),(RECH->date.Annee));
    printf("\n\tTemperature:  %f",(RECH->temperature));
    printf("\n\tCondition:    %d",(RECH->condition));
    printf("\n\tProduction:   %f",(RECH->production));
    printf("\n\tConsommation: %f",(RECH->consommation));
    printf("\n\tGain:         %f",(RECH->gain)); 
    printf("\n\tCout:         %f\n",(RECH->cout));
    liste=(liste->suiv);
}

void test_enregistrer_rapport()
{
  ST_Date Date_Debut;
  Date_Debut.Jour = 1;
  Date_Debut.Mois = 1;
  Date_Debut.Annee = 2010;
  
  ST_Date Date_Fin;
  Date_Fin.Jour = 25;
  Date_Fin.Mois = 11;
  Date_Fin.Annee = 2010;
  
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
  
  
  STR_DEPARTEMENT *tableau_dept = NULL;
  int taille_tableau;
  tableau_dept=RecupererInfosDepartement(tableau_dept,&taille_tableau);
  
  STR_DEPARTEMENT *Notre_departements = NULL;
  Notre_departements = parseur_departement(tableau_dept, Habitations.Departement);
  
  ST_DonneGeo *Donnee_geo = NULL;
  Donnee_geo = RecupererInfosGeographique(Donnee_geo);
  
  ST_DonneGeo *Nos_Donnees_geo = NULL;
  Nos_Donnees_geo = parseur_donnees_geo(Donnee_geo,Habitations.inclinaison_toit,Habitations.Exposition);
  
  ST_JOUR *Jour_precedent = NULL;
  
  PTR_ST_JOUR liste = NULL;
  liste = creer_liste_jours(Date_Debut,Date_Fin,Habitations,*Nos_Donnees_geo,*Notre_departements,Jour_precedent);
 
  Exporter_Evenement_Fichier(liste,"essai");
}  
  
//Includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../inc/constantes.h"
#include "../inc/structures.h"
#include "../inc/production.h"
#include "../inc/meteo.h"
#include "../inc.consomation.h"

//Prototypes
void test_consomation_habitation(ST_HABITATIONS Habitations)

float consommation_chauffage(ST_JOUR Jour, ST_HABITATIONS Habitation);
float consommation_climatisation(ST_JOUR Jour, ST_HABITATIONS Habitation);
void consommation_globale(PTR_ST_JOUR Jour, ST_HABITATIONS Habitation);
*/

//Main
int main(void)
{

  ST_EQUIPEMENTS Equip1;
  ST_EQUIPEMENTS Equip2;
  ST_EQUIPEMENTS Equip3;
  ST_EQUIPEMENTS Equip4;
  ST_EQUIPEMENTS Equip5;
  ST_EQUIPEMENTS Equip6;
  Equip1.consommation_equipement=230;
  Equip1.nombre_heures_utilisation_journalier=6;
  Equipe1.suiv=&Equip2;
  Equip2.consommation_equipement=60;
  Equip2.nombre_heures_utilisation_journalier=2;
  Equipe2.suiv=&Equip3;
  Equip3.consommation_equipement=130;
  Equip3.nombre_heures_utilisation_journalier=0.3;
  Equipe3.suiv=&Equip4;
  Equip4.consommation_equipement=3000;
  Equip4.nombre_heures_utilisation_journalier=2;
  Equipe4.suiv=&Equip5;
  Equip5.consommation_equipement=10;
  Equip5.nombre_heures_utilisation_journalier=10;
  Equipe5.suiv=&Equip6;
  Equip6.consommation_equipement=100;
  Equip6.nombre_heures_utilisation_journalier=24;
  Equip6.suiv=NULL;

  
  ST_PIECES Piece1;
  ST_PIECES Piece2;
  ST_PIECES Piece3;
  ST_PIECES Piece4;
  Piece1.Largeur=4;
  Piece2.Largeur=5;
  Piece3.Largeur=2;
  Piece4.Largeur=8;
  Piece1.Longueur=4;
  Piece2.Longueur=5;
  Piece3.Longueur=2;
  Piece4.Longueur=8;
  Piece1.LC_Equipements=&Equip1;
  Piece2.LC_Equipements=&Equipe;
  Piece3.LC_Equipements=&Equip2;
  Piece4.LC_Equipements=NULL;
  Piece1.suiv=&Piece2;
  Piece2.suiv=&Piece3;
  Piece3.suiv=&Piece4;
  Piece4.suiv=NULL;
  
  
  ST_HABITATIONS Habitations;
  Habitations.nombre_pieces=4;
  Habitations.LC_Pieces=&Piece1;
  Habitations.Isolation=1;
  Habitations.Climatisation=1;
  Habitations.Pourcentage_elec=0.7;
  
  consommation_equipements_habitatiion(Habitation);
 
  return 0;
}


typedef struct Habitations
{
	int nombre_pieces;
	ST_PIECES* LC_Pieces;
	ST_PANNEAUX* LC_Panneaux;
	float inclinaison_toit;
	int Isolation[CMAX]; 
	int Exposition; :
	int climatisation;
	int pourcentage_elec;e
	char Departement[CMAX];
	int chauffage_bois;
	int chauffage_gaz;
	int chauffage_electricite;
void test_consomation_habitation(ST_HABITATIONS Habitations)
{
  float conso_hab;
  int n;
  FILE *conso_habitation;
	conso_habitation= fopen("Test_conso_habitation.csv","w+");
  fprintf(conso_habitation,"Test de consommation habitation\n");
  for(n=0;n<100;n++)
  {
    conso_hab=test_consomation_habitation(Habitations);
    printf("%d ; %2.2f",n,conso_hab);
  }
  fclose(conso_habitation);
}
  consommation_equipements_habitation(Habitations); 
  
}
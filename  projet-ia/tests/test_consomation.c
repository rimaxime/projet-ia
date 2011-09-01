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


//Prototypes
void test_consomation_habitation(ST_HABITATIONS Habitations);
void test_consommation_chauffage(ST_HABITATIONS Habitations);




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
  
  
  ST_HABITATIONS Habitations;
  Habitations.nombre_pieces=4;
  Habitations.LC_Pieces=&Piece1;
  Habitations.Isolation=1;
  Habitations.climatisation=1;
  Habitations.chauffage_electricite=70;
  
  test_consomation_habitation(Habitations);
  test_consommation_chauffage(Habitations);
 
  return 0;
}


void test_consomation_habitation(ST_HABITATIONS Habitations)
{
  float conso_hab;
  int n;
  FILE *conso_habitation;
	conso_habitation= fopen("Test_conso_habitation.csv","w+");
  fprintf(conso_habitation,"Test de consommation habitation\n");
  for(n=0;n<100;n++)
  {
    conso_hab=consommation_equipements_habitation(Habitations);
    printf("%d ; %2.2f\n",n,conso_hab);
    fprintf(conso_habitation,"%d ; %2.2f\n",n,conso_hab);
  }
  fclose(conso_habitation);
  printf("ok\n");
}

void test_consommation_chauffage(ST_HABITATIONS Habitations)
{
  float conso_chauff;
  ST_JOUR Jour;
  Jour.temperature = -10;
  
  FILE *conso_chauffage = NULL;
  conso_chauffage= fopen("test_conso_chauffage.csv","w+");
  if(conso_chauffage == NULL)
  {
    printf("erreur fichier\n");
    exit(-1);
  }
  fprintf(conso_chauffage,"Test de consommation chauffage\nTemperature Jour ; Conso chauffage\n");
  while(Jour.temperature<40)
  {
    printf("Entree test consommation chauffage\n");
    conso_chauff=consommation_chauffage(Jour,Habitations);
    printf("%2.2f ; %2.2f\n",Jour.temperature,conso_chauff);
    fprintf(conso_chauffage,"%2.2f ; %2.2f\n",Jour.temperature,conso_chauff);
    Jour.temperature=Jour.temperature+10;
    printf("Temperature : %f\n",Jour.temperature);
  }
  fclose(conso_chauffage);
}
/**
  * \file test_fichiers.c
  * \brief test les fonctions d'agrégation de fichiers
  * \author MRI
  * \date 11/07/2011
  */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/constantes.h"
#include "../inc/structures.h"
#include "../inc/gestion_fichiers.h"

void test_fichiers();
void test_equipements();
void test_geo();

int main()
{
  test_fichiers();
  test_geo();
  test_equipements();
  
  return 0;
}


void test_fichiers()
{
  STR_DEPARTEMENT* tableau_departements = NULL;
  int size_tab=0;
  tableau_departements = RecupererInfosDepartement(tableau_departements,&size_tab);
	printf("Ok\n");
  printf("%s : %s \n",tableau_departements[0].nom_departement,tableau_departements[1].Tableau_Mois[10].nom_mois);
}

void test_equipements()
{
  ST_EQUIPEMENTS *tableau_equipements = NULL;
  tableau_equipements = RecupererInfosEquipements(tableau_equipements);
  printf("%s\n",tableau_equipements[3].nom_equipement);
  printf("%s\n",tableau_equipements[3].suiv->nom_equipement);
  printf("%s\n",tableau_equipements[3].suiv->suiv->nom_equipement);
}

void test_geo()
{
  ST_DonneGeo *tableau_geo = NULL;
  tableau_geo = RecupererInfosGeographique(tableau_geo);
  printf("%d\n",tableau_geo[0].inclinaison);
  printf("%d\n",tableau_geo[3].suiv->suiv->suiv->suiv->orientation);
  printf("%d\n",tableau_geo[8].suiv->suiv->orientation);
  printf("%f\n",tableau_geo[3].suiv->suiv->suiv->suiv->rendement);
}

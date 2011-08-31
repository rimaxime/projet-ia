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


int main()
{
  test_fichiers();
  test_equipements();
  return 0;
}


void test_fichiers()
{
  STR_DEPARTEMENT* tableau_departements = NULL;
  int size_tab=0;
  tableau_departements = RecupererInfosDepartement(tableau_departements,&size_tab);
	printf("Ok\n");
  printf("%s : %s \n",tableau_departements[1].nom_departement,tableau_departements[1].Tableau_Mois[11].nom_mois);
}

void test_equipements()
{
  ST_EQUIPEMENTS tableau_equipements[7] = NULL;
  tableau_equipements = RecupererInfosEquipements(tableau_equipements);
  printf("%s\n",tableau_equipements[1].nom_equipement);

}

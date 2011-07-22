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

int main()
{
  test_fichiers();
  
}


void test_fichiers()
{
  STR_DEPARTEMENT* tableau_departements = NULL;
  int size_tab=0;
  RecupererInfosDepartement(tableau_departements,&size_tab);
  
}

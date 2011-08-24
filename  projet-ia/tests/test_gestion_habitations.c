//Includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../inc/constantes.h"
#include "../inc/structures.h"
#include "../inc/gestion_habitations.h"
#include "../tests/test.h"


void test_creation_habitation();
void test_creation_piece();
void test_inserertrier_piece();

void test_creation_equipement();
void test_inserertrier_equipement();

void test_creation_panneaux();
void test_inserertrier_panneaux();

int main()
{
   test_creation_habitation();
   test_creation_piece();
   test_inserertrier_piece();
   
   
   test_creation_equipement();
   test_inserertrier_equipement();
   
   test_creation_panneaux();
   //test_inserertrier_panneaux();
   return 0;
}

void test_creation_habitation()
{
  TEST_TITLE("test_creation_habitation");
  ST_HABITATIONS *Nouveau;
  Nouveau = CreationHabitation(4,20,6,5,"3");
  TEST(Nouveau->Exposition == 5);
  TEST(Nouveau->inclinaison_toit == 20);
}


void test_creation_piece()
{
  ST_PIECES *Nouvelle = NULL;
  Nouvelle =CreationPiece("Chambre",1, 3,4, 12,15,18,25);
  TEST_TITLE("test_creation_piece");
  TEST(Nouvelle->coordX1 == 12);
  TEST(Nouvelle->type_piece == 1);
  TEST(strcasecmp(Nouvelle->nom_piece,"Chambre") == 0);
}


void test_inserertrier_piece()
{
  TEST_TITLE("test_inserertrier_piece");
  ST_PIECES *Tete = NULL;
  ST_PIECES *Nouvelle = NULL;
  Nouvelle = CreationPiece("Chambre",1, 3,4, 12,15,18,25);
  Tete = InsererTrierPiece(Nouvelle,NULL);
  TEST(strcasecmp(Tete->nom_piece,"Chambre") == 0);
  ST_PIECES *Nouvelle2 = NULL;
  Nouvelle2 = CreationPiece("Buanderie",2, 3,4, 12,15,18,25);
  Tete = InsererTrierPiece(Nouvelle2,Tete);
  TEST(strcasecmp(Tete->nom_piece,"Buanderie") == 0);
  TEST(strcasecmp(Tete->suiv->nom_piece,"Chambre") == 0);
  ST_PIECES *Nouvelle3 = NULL;
  Nouvelle3 = CreationPiece("Salon",3, 3,4, 12,15,18,25);
  Tete = InsererTrierPiece(Nouvelle3,Tete);
  TEST(strcasecmp(Tete->nom_piece,"Buanderie") == 0);
  TEST(strcasecmp(Tete->suiv->nom_piece,"Chambre") == 0);
  TEST(strcasecmp(Tete->suiv->suiv->nom_piece,"Salon") == 0);
  ST_PIECES *Nouvelle4 = NULL;
  Nouvelle4 = CreationPiece("Chambre",3, 3,4, 12,15,18,25);
  Tete = InsererTrierPiece(Nouvelle4,Tete);
   TEST(strcasecmp(Tete->nom_piece,"Buanderie") == 0);
  TEST(strcasecmp(Tete->suiv->nom_piece,"Chambre") == 0);
  TEST(strcasecmp(Tete->suiv->suiv->nom_piece,"Chambre") == 0);
  TEST(strcasecmp(Tete->suiv->suiv->suiv->nom_piece,"Salon") == 0);
}

void test_creation_equipement()
{
  ST_EQUIPEMENTS *Nouveau = NULL;
  Nouveau = CreationEquipement(1, "Television", 1200, 4.5, 0.9, 1.5, 12,18, 15, 20);
  TEST_TITLE("test_creation_equipement");
  TEST(Nouveau->coordX1 == 12);
  TEST(Nouveau->indice == 1);
  TEST(strcasecmp(Nouveau->nom_equipement,"Television") == 0);
}

void test_inserertrier_equipement()
{
  ST_EQUIPEMENTS *Nouveau = NULL;
  ST_EQUIPEMENTS *Tete = NULL;
  Nouveau = CreationEquipement(1, "Television", 1200, 4.5, 0.9, 1.5, 12,18, 15, 20);
  TEST_TITLE("test_inserertrier_equipement");
  Tete = InsererTrierEquipements(Nouveau,NULL);
  TEST(strcasecmp(Tete->nom_equipement,"Television") == 0);
  ST_EQUIPEMENTS *Nouveau2 = NULL;
  Nouveau2 = CreationEquipement(3,"Buanderie",1500,2, 3,4, 12,15,18,25);
  Tete = InsererTrierEquipements(Nouveau2,Tete);
  TEST(strcasecmp(Tete->nom_equipement,"Buanderie") == 0);
  TEST(strcasecmp(Tete->suiv->nom_equipement,"Television") == 0);
  ST_EQUIPEMENTS *Nouveau3 = NULL;
  Nouveau3 = CreationEquipement(4,"Salon",1400,3, 3,4, 12,15,18,25);
  Tete = InsererTrierEquipements(Nouveau3,Tete);
  TEST(strcasecmp(Tete->nom_equipement,"Buanderie") == 0);
  TEST(strcasecmp(Tete->suiv->suiv->nom_equipement,"Television") == 0);
  TEST(strcasecmp(Tete->suiv->nom_equipement,"Salon") == 0);
  ST_EQUIPEMENTS *Nouveau4 = NULL;
  Nouveau4 = CreationEquipement(5,"Television",1200,3, 3,4, 12,15,18,25);
  Tete = InsererTrierEquipements(Nouveau4,Tete);
   TEST(strcasecmp(Tete->nom_equipement,"Buanderie") == 0);
  TEST(strcasecmp(Tete->suiv->nom_equipement,"Salon") == 0);
  TEST(strcasecmp(Tete->suiv->suiv->nom_equipement,"Television") == 0);
  TEST(strcasecmp(Tete->suiv->suiv->suiv->nom_equipement,"Television") == 0);
}


void test_creation_panneaux()
{
  ST_PANNEAUX *Nouveau = NULL;
  Nouveau = CreationPanneaux(1, 2,3,4,5,6);
  TEST_TITLE("test_creation_panneaux");
  TEST(Nouveau->type == 2);
  TEST(Nouveau->indice == 1);
}


/*void test_inserertrier_panneaux()
{
   ST_PANNEAUX *Nouveau = NULL;
  Nouveau = CreationPanneaux(1, 2,3,4,5,6);
  TEST_TITLE("test_inserertrier_panneaux");
  ST_PANNEAUX *Nouveau2 = NULL;
  Nouveau2 = CreationPanneaux( 3,4,5,6,7,8);
  ST_PANNEAUX *Nouveau3 = NULL;
  Nouveau3 = CreationPanneaux( 2,3,4,5,6,7);
  ST_PANNEAUX *Nouveau4 = NULL;
  Nouveau4 = CreationPanneaux( 2,3,4,5,6,7);
  ST_PANNEAUX *Tete = NULL;
  Tete = InsererTrierPanneaux(Nouveau,Tete);
  TEST(Tete->indice == 1);
  Tete = InsererTrierPanneaux(Nouveau2,Tete);
  TEST(Tete->indice == 1);
  TEST(Tete->suiv->indice == 3);
  Tete = InsererTrierPanneaux(Nouveau3,Tete);
  TEST(Tete->indice == 1);
  TEST(Tete->suiv->indice == 2);
  Tete = InsererTrierPanneaux(Nouveau4,Tete);
  TEST(Tete->indice == 1);
  TEST(Tete->suiv->indice == 2);
  TEST(Tete->suiv->suiv->indice == 2);
  TEST(Tete->suiv->suiv->suiv->indice == 3);
}*/
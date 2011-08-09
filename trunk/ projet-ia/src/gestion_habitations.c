/**
  * \file gestion_habitations.c
  * \brief Crée les maisons et les différentes pièces associées
  * \author MRI
  * \date 08/08/2011
  */

#include "../inc/gestion_habitations.h"

ST_HABITATIONS CreationHabitation(ST_HABITATIONS Nouveau,int nombre_pieces, float inclinaison_toit, int Isolation,int Exposition)
{
  Nouveau.nombre_pieces = nombre_pieces;
  Nouveau.inclinaison_toit = inclinaison_toit;
  Nouveau.Isolation = Isolation;
  Nouveau.Exposition = Exposition;
  Nouveau.LC_Pieces = NULL;
  Nouveau.LC_Panneaux = NULL;  
  return Nouveau;
}


ST_PIECES* CreationPiece(char* nom_piece, int type_piece, float Largeur, float Longueur, float coordX1, float coordY1,float coordX2, float coordY2)
{
  ST_PIECES *Nouvelle = NULL;
  Nouvelle = (ST_PIECES *) malloc (sizeof(ST_PIECES));
  if(Nouvelle==NULL)						
  {
    fprintf(stdout,"CreationPiece : Erreur d'alloc mémoire \n");
    exit(-1);
  }
  strcpy(Nouvelle->nom_piece,nom_piece);
  Nouvelle->type_piece = type_piece;
  Nouvelle->Largeur = Largeur;
  Nouvelle->Longueur = Longueur;
  Nouvelle->coordX1 = coordX1;
  Nouvelle->coordY1= coordY1;
  Nouvelle->coordX2 = coordX2;
  Nouvelle->coordY2= coordY2;
  Nouvelle->LC_Equipements = NULL;
  Nouvelle->suiv = NULL;
  return Nouvelle;
}


ST_PIECES* InsererTrierPiece(ST_PIECES *Nouvelle, ST_PIECES *Tete)
{
  if(Tete == NULL || strcasecmp(Nouvelle->nom_piece,Tete->nom_piece) <= 0)
  {
    Nouvelle->suiv = Tete;
    return Nouvelle;
  }
  else
  {
    Tete->suiv = InsererTrierPiece(Nouvelle,Tete->suiv);
   
    return Tete;
  }
}


ST_EQUIPEMENTS* CreationEquipement(int indice, char *nom_equipement, float consommation_equipement, float nombre_heures_utilisation_journalier,
				  float Largeur, float Longueur, float coordX1,float coordX2, float coordY1, float coordY2)
{
  ST_EQUIPEMENTS *Nouveau = NULL;
  Nouveau = (ST_EQUIPEMENTS *) malloc (sizeof(ST_EQUIPEMENTS));
  if(Nouveau==NULL)						
  {
    fprintf(stdout,"CreationEquipement : Erreur d'alloc mémoire \n");
    exit(-1);
  }

  Nouveau->indice = indice;
  strcpy(Nouveau->nom_equipement,nom_equipement);
  Nouveau->consommation_equipement = consommation_equipement;
  Nouveau->nombre_heures_utilisation_journalier = nombre_heures_utilisation_journalier;
  Nouveau-> Largeur = Largeur;
  Nouveau-> Longueur = Longueur;
  Nouveau->coordX1 = coordX1;
  Nouveau->coordY1 = coordY1;
  Nouveau->coordX2 = coordX2;
  Nouveau->coordY2 = coordY2; 
  Nouveau -> suiv = NULL;
  
  return Nouveau;
}


ST_EQUIPEMENTS* InsererTrierEquipements(ST_EQUIPEMENTS *Nouveau, ST_EQUIPEMENTS *Tete)
{
  if(Tete == NULL || strcasecmp(Nouveau->nom_equipement,Tete->nom_equipement) <= 0)
  {
    Nouveau->suiv = Tete;
    return Nouveau;
  }
  else
  {
    Tete->suiv = InsererTrierEquipements(Nouveau,Tete->suiv);
   
    return Tete;
  }
}


ST_PANNEAUX* CreationPanneaux(int indice, int type, float Largeur, float Longueur, float inclinaison_panneau, int Exposition)
{
  ST_PANNEAUX *Nouveau = NULL;
  Nouveau = (ST_PANNEAUX *) malloc (sizeof(ST_PANNEAUX));
  if(Nouveau==NULL)						
  {
    fprintf(stdout,"CreationPanneaux : Erreur d'alloc mémoire \n");
    exit(-1);
  }

  Nouveau->indice = indice;
  Nouveau->type = type;
  Nouveau->Largeur = Largeur;
  Nouveau->Longueur = Longueur;
  Nouveau->inclinaison_panneau = inclinaison_panneau;
  Nouveau->Exposition = Exposition;
  Nouveau->suiv = NULL;
  return Nouveau; 
}

ST_PANNEAUX* InsererTrierPanneaux(ST_PANNEAUX *Nouveau, ST_PANNEAUX *Tete)
{
  if(Tete == NULL || Nouveau->indice <= Tete->indice)
  {
    Nouveau->suiv = Tete;
    return Nouveau;
  }
  else
  {
    Tete->suiv = InsererTrierPanneaux(Nouveau,Tete->suiv);
   
    return Tete;
  }
}

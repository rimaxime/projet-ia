/**
  * \file consommation.c
  * \brief Fichier contenant les fonctions utiles pour le calcul de la consommation electrique du foyer
  * \author Benoit Eche
  * \date 31/08/11
  */

#include "../inc/consomation.h"

//Fonctions
float consommation_equipements(ST_EQUIPEMENTS Equipement)
{
  float conso = 0;
  if(Equipement.suiv==NULL)
    conso = Equipement.consommation_equipement*Equipement.nombre_heures_utilisation_journalier;
  else
  {
    conso =  consommation_equipements(*Equipement.suiv);
    conso += (Equipement.consommation_equipement*Equipement.nombre_heures_utilisation_journalier);
  }
  return conso; 
}

float consommation_equipements_piece(ST_PIECES Piece)
{
  if(Piece.LC_Equipements == NULL)
    return 0;
  else
    return consommation_equipements(*Piece.LC_Equipements);  
}

float consommation_equipements_habitation(ST_HABITATIONS Habitations)
{
  float conso_equ=0;
  ST_PIECES *Piece = Habitations.LC_Pieces;
  if(Habitations.LC_Pieces == NULL)
    return 0;
  else
    while(Piece != NULL)
    {
      conso_equ += consommation_equipements_piece(*Piece);
      Piece = Piece->suiv;      
    }
    return conso_equ;
}

float volume_piece(ST_PIECES Piece)
{
  float volume = -1;
  
  volume = (Piece.Largeur*Piece.Longueur*HABITATIONS_HAUTEUR);
  return volume; 
}

float volume_habitation(ST_HABITATIONS Habitation)
{
  float volume = 0;
  ST_PIECES *Piece = NULL;
  Piece = Habitation.LC_Pieces;
  if(Piece== NULL)
    return 0;
  else
  {
    while(Piece != NULL)
    {
      volume+=volume_piece(*Piece);
      Piece=Piece->suiv;
    }
  }
  return volume;
}


float consommation_chauffage(ST_JOUR Jour, ST_HABITATIONS Habitation)
{
  float conso_chauff;
  float volume;
  volume = volume_habitation(Habitation);
  switch(Habitation.Isolation)
  {
    case 0 :
      conso_chauff=volume*(TEMPERATURE_INTERIEURE - Jour.temperature)*COEFF_ISOLATION_BONNE*24;
      break;
    case 1 :
      conso_chauff=volume*(TEMPERATURE_INTERIEURE - Jour.temperature)*COEFF_ISOLATION_NORMALE*24;
      break;
    case 2 :
      conso_chauff=volume*(TEMPERATURE_INTERIEURE - Jour.temperature)*COEFF_ISOLATION_FAIBLE*24;
      break;
    case 3 :
      conso_chauff=volume*(TEMPERATURE_INTERIEURE - Jour.temperature)*C0EFF_ISOLATION_NULLE*24;
      break;
    default:
      conso_chauff = -1;
      break;  
  }  
  if(Jour.temperature < TEMPERATURE_INTERIEURE)
    return (conso_chauff*Habitation.chauffage_electricite/100);
  else if(Habitation.climatisation == 0)
    return conso_chauff*COEFF_CONSO_CLIM*-1;
  else
    return 0;
}


float consommation_globale(ST_JOUR Jour, ST_HABITATIONS Habitation)
{
  float conso_globale;
  conso_globale = consommation_equipements_habitation(Habitation) + consommation_chauffage(Jour,Habitation);
  return conso_globale;
}

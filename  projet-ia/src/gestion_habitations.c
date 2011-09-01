/**
  * \file gestion_habitations.c
  * \brief Crée les maisons et les différentes pièces associées
  * \author MRI
  * \date 08/08/2011
  */

#include "../inc/gestion_habitations.h"


/**
 * \name   Creation Habitation
 * \brief  Crée une nouvelle habitation à l'aide des paramètres de la fonction
 * \param  int nombre_pieces, Isolation, Exposition
 * \param  float inclinaison_toit
 * \return ST_HABITATIONS*, La nouvelle habitation 
 */
ST_HABITATIONS* CreationHabitation(int nombre_pieces, float inclinaison_toit, int Isolation,int Exposition, char Departement[CMAX])
{
  ST_HABITATIONS *Nouveau = NULL;
  
  Nouveau = (ST_HABITATIONS *) malloc (sizeof(ST_HABITATIONS));
  if(Nouveau==NULL)						
  {
    fprintf(stdout,"CreationHabitation : Erreur d'alloc mémoire \n");
    exit(-1);
  }
  Nouveau->nombre_pieces = nombre_pieces;
  
  Nouveau->inclinaison_toit = inclinaison_toit;
  Nouveau->Isolation = Isolation;
  Nouveau->Exposition = Exposition;
  Nouveau->LC_Pieces = NULL;
  Nouveau->LC_Panneaux = NULL;  
  strcpy(Nouveau->Departement,Departement);
  Nouveau->chauffage_gaz = 0;
  Nouveau->chauffage_electricite = 0;
  Nouveau->chauffage_bois = 0;
  Nouveau->climatisation = 2;
  return Nouveau;
}


/**
 * \name   Modifier Habitation
 * \brief  Modifie une habitation à l'aide des paramètres de la fonction
 * \param  int nombre_pieces, Isolation, Exposition
 * \param  float inclinaison_toit
 * \return ST_HABITATIONS*, L'habitation 
 */
ST_HABITATIONS* ModifierHabitation(ST_HABITATIONS* Habitation,int nombre_pieces, float inclinaison_toit, int Isolation,int Exposition, char Departement[CMAX])
{
  Habitation->nombre_pieces = nombre_pieces;
  Habitation->inclinaison_toit = inclinaison_toit;
  Habitation->Isolation = Isolation;
  Habitation->Exposition = Exposition;
  strcpy(Habitation->Departement,Departement);
  return Habitation;
}


/**
 * \name   Creation des Pieces
 * \brief  Crée une nouvelle pièce dans la liste de pièces avec les paramètres de la fonction
 * \param  int type_piece
 * \param  float Largeur, Longueur, qui sont la taille de la pièce; coordX1, coordX2, coordY1, coordY2, qui sont les coordonnées des coins hauts 
 * et bas de la pièce dans l'IHM
 * \param  char* nom_piece
 * \return ST_PIECES*, La nouvelle pièce complétée
 */
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

ST_PIECES* Trouver_Piece(ST_PIECES * Tete, char nom_piece[CMAX])
{
  if(Tete == NULL || strcasecmp(Tete->nom_piece, nom_piece) == 0)
	return Tete;
  else
    return(Trouver_Piece(Tete->suiv, nom_piece));
}


/**
 * \name   Modification des Pieces
 * \brief  Modifier une piéce
 * \param  int type_piece
 * \param  float Largeur, Longueur, qui sont la taille de la pièce; coordX1, coordX2, coordY1, coordY2, qui sont les coordonnées des coins hauts 
 * et bas de la pièce dans l'IHM
 * \return ST_PIECES*, La pièce completée 
 */
ST_PIECES* ModifierPiece(ST_PIECES* Piece, int type_piece, float Largeur, float Longueur)
{
  Piece->type_piece = type_piece;
  Piece->Largeur = Largeur;
  Piece->Longueur = Longueur;
  return Piece;
}

/**
 * \name   Insertion Triée des Piècés
 * \brief  Insère la Pièce au bon emplacement dans la liste de pièces, triée par ordre alphabétique en fonction du nom de la pièce. Fonction Récursive
 * \param  Structure ST_PIECES* qui sont la Tete de cette liste ainsi que la pièce à insérer
 * \return ST_PIECES* Retour de la nouvelle tete de la liste
 */
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

/**
 * \name   Création d'un équipement
 * \brief  Crée un nouvel équipement dans une pièce donnée et l'ajoute à la liste associée
 * \param  int indice représentant l'nième équipement de la pièce
 * \param  char* nom_equipement représentant le nom de l'équipement, ne peut être nul
 * \param  float consommation_equipement représentant la consommation de l'appareil, nombre_heures_utilisation_journalier le nombre d'heure moyen de 
 * 		 l'utilisation de l'appareil. Largeur, Longueur représentant la taille de l'appareil. coordX/Y-1/2 représentant les coordonnées de
 * 		 l'appareil dans l'IHM
 * \return ST_EQUIPEMENTS* Retour de l'équipement une fois completé
 */
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

ST_EQUIPEMENTS* ModifierEquipement(ST_EQUIPEMENTS* Equipement, float consommation_equipement, float nombre_heures_utilisation_journalier,
				  float Largeur, float Longueur, float coordX1,float coordX2, float coordY1, float coordY2)
{
  Equipement->consommation_equipement = consommation_equipement;
  Equipement->nombre_heures_utilisation_journalier = nombre_heures_utilisation_journalier;
  Equipement-> Largeur = Largeur;
  Equipement-> Longueur = Longueur;
  Equipement->coordX1 = coordX1;
  Equipement->coordY1 = coordY1;
  Equipement->coordX2 = coordX2;
  Equipement->coordY2 = coordY2; 
  
  return Equipement;
}

/**
 * \name   Insertion Triée des Equipements
 * \brief  Insère la Pièce au bon emplacement dans la liste des équipements, triée par ordre alphabétique en fonction du nom de l'équipement. Fonction Récursive
 * \param  Structure ST_EQUIPEMENTS* qui sont la Tete de cette liste ainsi que l'équipement à insérer
 * \return ST_EQUIPEMENTS* Retour de la nouvelle tete de la liste
 */
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

/**
 * \name   Création d'un panneau solaire
 * \brief  Crée un nouveau panneau solaire 
 * \param  int indice représentant l'nième panneau de la maison, type qui spécifie le type de panneaux, Exposition qui donne selon un chiffre 
 * 		de 1 à 8 l'exposition du panneau solaire
 * \param  float Largeur, Longueur représente la taille du panneau solaire, inclinaison_panneau qui est l'inclinaison du panneau
 * \return ST_EQUIPEMENTS* Retour de l'équipement une fois completé
 */
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
  //Nouveau->suiv = NULL;
  return Nouveau; 
}


ST_PANNEAUX* ModifierPanneaux(ST_PANNEAUX *Panneau, int type, float Largeur, float Longueur, float inclinaison_panneau, int Exposition)
{
  Panneau->type = type;
  Panneau->Largeur = Largeur;
  Panneau->Longueur = Longueur;
  Panneau->inclinaison_panneau = inclinaison_panneau;
  Panneau->Exposition = Exposition;
  return Panneau;
}

//Obsolete
/**
 * \name   Insertion Triée des Panneaux
 * \brief  Insère le panneau au bon endroit dans une liste triée  par l'indice de celui ci. Fonction récursive
 * \param  Structure ST_PANNEAUX* qui sont la Tete de cette liste ainsi que le panneau à insérer
 * \return ST_PANNEAUX* Retour de la nouvelle tete de la liste
 */
/*ST_PANNEAUX* InsererTrierPanneaux(ST_PANNEAUX *Nouveau, ST_PANNEAUX *Tete)
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
}*/


ST_PIECES* Supprimer_Piece(ST_PIECES *Tete, char nom_piece[CMAX])
{
	if(Tete == NULL)
		return(NULL);
	else if(strcasecmp(Tete->nom_piece,nom_piece) == 0)
	{
		ST_PIECES *test = NULL;
		test = Tete->suiv;
		free(Tete);
		return(test);
	}
	else
		Tete->suiv = Supprimer_Piece(Tete->suiv, nom_piece);
	return Tete;
}

ST_EQUIPEMENTS* Supprimer_Equipement(ST_EQUIPEMENTS *Tete, char nom_equipement[CMAX])
{
	if(Tete == NULL)
		return(Tete);
	else if(strcasecmp(Tete->nom_equipement,nom_equipement) == 0)
	{
		ST_EQUIPEMENTS *test = NULL;
		test = Tete->suiv;
		free(Tete);
		return(test);
	}
	else
		Tete->suiv = Supprimer_Equipement(Tete->suiv, nom_equipement);
	return Tete;
}



void Detruire_Habitation(ST_HABITATIONS* Tete)
{
  if (Tete != NULL)
  {
    Detruire_Panneaux(Tete->LC_Panneaux);
    free(Tete);
  }
}

void Detruire_Pieces(ST_PIECES *Tete)
{
  if (Tete != NULL)
  {
     Detruire_Equipements(Tete->LC_Equipements);
     Detruire_Pieces(Tete->suiv);
     free(Tete);
  }
}

void Detruire_Equipements(ST_EQUIPEMENTS *Tete)
{
  if(Tete != NULL)
  {
    Detruire_Equipements(Tete->suiv);
    free(Tete);
  }
}

void Detruire_Panneaux(ST_PANNEAUX *Tete)
{
  if(Tete != NULL)
  {
    //Detruire_Panneaux(Tete->suiv);
    free(Tete);
  }
}


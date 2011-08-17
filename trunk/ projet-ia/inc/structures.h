/**
  * \file structures.h
  * \brief Contient l'ensemble des structures du programme 
  * utilisés tout au long du programme
  * \author MRI BEC
  * \date 11/07/2011
  */

#ifndef STRUCTURES_H
#define STRUCTURES_H

//Structures
typedef struct Date
{
  int Jour;
  int Mois;
  int Annee;  
}ST_Date;

typedef struct SimuMeteo //Valeurs simulées
{
  ST_Date date; //date de la simulation
  float temp; //Température du jour simulé
  float h_soleil; //Heure d'ensoleilement du jour simulé
  float puiss_soleil; //Puissance du soleil durant la journée
  float precipitation; //Nombre de mm de pluie durant la journée
  int condition; //0=Ensoleillé, 1=Couvert, 2=Pluie, 3=Grèle, 4=Neige
}ST_SimuMeteo;

typedef ST_SimuMeteo* PTR_ST_SimuMeteo;



typedef struct DonneeMeteo //Valeurs normales
{
  int num_mois; 
  char nom_mois[CMAX];
  float temp_min; //Température minimale lors de ce mois
  float temp_max; //Température maximale lors de ce mois
  float mm_pluie; //Nombre de mm de pluie normal au cours de ce mois
  int jr_pluie; //Nombre de jours de pluie normal au cours de ce mois
  int nb_soleil; //Nombre d'heure de d'ensoleillement au cours de ce mois
}ST_DonneeMeteo;



typedef struct Departements
{
  int num_departement;
  char nom_departement[CMAX];
  char nom_region[CMAX];
  int zone_climatique;
  ST_DonneeMeteo Tableau_Mois[12];  
}STR_DEPARTEMENT;



typedef struct Panneaux
{
  int indice;
  int type;
  float Largeur;
  float Longueur;
  float inclinaison_panneau;
  int Exposition;
  int surface;
  struct Panneaux *suiv;
}ST_PANNEAUX;


typedef struct Equipements
{
  int indice;
  char nom_equipement[CMAX];
  float consommation_equipement;
  float nombre_heures_utilisation_journalier;
  float Largeur;
  float Longueur;
  float coordX1;
  float coordY1;
  float coordX2;
  float coordY2; 
  struct Equipements  * suiv;
  //TBC
}ST_EQUIPEMENTS;



typedef struct Pieces
{
 char nom_piece[CMAX];
 int type_piece; //Le type correspond a un entier représentant une pièce d'un certain type
 //1 Chambre/Bureau
 //2 Salon-Salle à manger
 //3 Cuisine
 //4 Salle de Bain
 //5 Toilettes
 //6 Buanderie
 //TBC
 float Largeur;
 float Longueur;
 float coordX1;
 float coordY1;
 float coordX2;
 float coordY2;
 ST_EQUIPEMENTS *LC_Equipements;
 struct Pieces *suiv;
}ST_PIECES;
  


typedef struct Habitations
{
	int nombre_pieces;
	ST_PIECES* LC_Pieces;
	ST_PANNEAUX* LC_Panneaux;
	float inclinaison_toit;
	int Isolation; //le type d'isolation correspond à un chiffre (à lister ci-dessous)
	int Exposition; //l'exposition correspond à un entier :
	//1 Sud
	//2 Sud Ouest
	//3 Ouest
	//4 Nord Ouest
	//5 Nord
	//6 Nord Est
	//7 Est
	//8 Sud Est
}ST_HABITATIONS;  
  
#endif
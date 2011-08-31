/**
  * \file gestion_fichiers.c
  * \brief Récupére les données des bases de données pour les
  * les mettre dans des tableaux / listes
  * \author MRI
  * \date 11/07/2011
  */

#include "../inc/gestion_fichiers.h"


/**
 * \fn     STR_DEPARTEMENT * RecupererInfosDepartement(STR_DEPARTEMENT * tableau_departements, int* size_tab)
 * \name   Récupérer les Infos sur les Départements
 * \brief  Permet de récupérer toutes les infos sur les département depuis le fichier associé
 * \param  Structure STR_DEPARTEMENT* tableau_departements qui est le tableau dans lequel sera archivé les données du fichier
 * \param  int *size_tab représentant la taille du tableau (nombre de départements)
 * \return STR_DEPARTEMENT* Retour du tableau completé
 */
STR_DEPARTEMENT * RecupererInfosDepartement(STR_DEPARTEMENT *tableau_departements, int *size_tab)
{  
	char *st_token=NULL;
	char chaine[CMAX];
	int i=0,j=0,k=0;
	int compte_mois = 12;
	int size_chaine=0;
	memset(chaine,0,sizeof(chaine));
	FILE* fp;
	fp = fopen("../ressource/Projet_Meteo_CSV.csv","r");
	if(fp==NULL)
	{
	  fprintf(stderr,"Erreur d'ouverture fichier\n");
	  exit(-1);
	}
	while(fgets(chaine,CMAX,fp)!=NULL)
	{
		size_chaine=strlen(chaine)-1; 
		st_token=strtok(chaine,";"); 
		size_chaine-=(strlen(st_token)+1); 
		k=0;
		j=0;

		if(size_chaine>0)
		{
		  if(compte_mois>=12)
		  {
			tableau_departements=(STR_DEPARTEMENT *)realloc(tableau_departements,(i+1)*sizeof(STR_DEPARTEMENT));	//Il faut que st_recover=NULL -->realloc=malloc a la difference que l'on peut deplace dans une zone mémoire de taille suffisante si la premiere ne l'est pas et fait un free de la première zone.
//	Exemple si le malloc M prend 2 case mémoire et qu'il nous en faut 3 et que l'espace contigu le première malloc est occupé xx on réallou R plus loin ou la place est suffisante MMxx0O0-->00xxRRR
				if(tableau_departements==NULL)						
				{
					fprintf(stdout,"RecupérerInfoFichier : Erreur d'alloc mémoire \n");
					exit(-1);
				}
				
				memset(tableau_departements+i,0,sizeof(STR_DEPARTEMENT));
				compte_mois=0;
		  }
		}
		else
			i--;
		
		while(st_token!=NULL && size_chaine>=0)
		{
			switch(j)
			{			
				case 0:
					if(compte_mois==1)
					 strcpy(tableau_departements[i].num_departement,(st_token));
					break;
				case 1:
					if(compte_mois==1)
					  strcpy(tableau_departements[i].nom_departement,st_token);
					break;
				case 2:
					if(compte_mois==1)
					 strcpy(tableau_departements[i].nom_region,st_token);
					break;
				case 3:
					if(compte_mois==1)
					  tableau_departements[i].zone_climatique=atoi(st_token);
					break;
				case 4:
					tableau_departements[i].Tableau_Mois[compte_mois].num_mois = atoi(st_token);
					 break;
				case 5:
					strcpy(tableau_departements[i].Tableau_Mois[compte_mois].nom_mois ,st_token);
					break;
				case 6:
					tableau_departements[i].Tableau_Mois[compte_mois].temp_min = atof(st_token);
					break;
				case 7:
					tableau_departements[i].Tableau_Mois[compte_mois].temp_max = atof(st_token);
					break;
				case 8:
					tableau_departements[i].Tableau_Mois[compte_mois].mm_pluie = atoi(st_token);
					break;
				case 9:
					tableau_departements[i].Tableau_Mois[compte_mois].jr_pluie = atoi(st_token);
					break;
				case 10:
					tableau_departements[i].Tableau_Mois[compte_mois].nb_soleil = atoi(st_token);
					break;
				default:
					break;
			}
			st_token=strtok(NULL,";");
			size_chaine-=(strlen(st_token)+1);
			j++;
			
		}
		memset(chaine,0,sizeof(chaine));
		compte_mois++;
		if(compte_mois == 12)
			i++;
	}
	*size_tab=i;
	return tableau_departements;
}

ST_EQUIPEMENTS * RecupererInfosEquipements(ST_EQUIPEMENTS *tableau_equipements)
{
    char *st_token=NULL;
	char chaine[CMAX];
	int i=0,j=0,k=0;
	int size_chaine=0;
	memset(chaine,0,sizeof(chaine));
	FILE* fp;
	float consommation;
	float temps;
	char nom_equipement[CMAX];
	ST_EQUIPEMENTS* nouveau = NULL;
	ST_EQUIPEMENTS* suivant = NULL;
	fp = fopen("../ressource/Equipements.csv","r");
	if(fp==NULL)
	{
	  fprintf(stderr,"Erreur d'ouverture fichier\n");
	  exit(-1);
	}
	while(k<7)
	{
	  tableau_equipements=(ST_EQUIPEMENTS *)realloc(tableau_equipements,(i+1)*sizeof(ST_EQUIPEMENTS));	//Il faut que st_recover=NULL -->realloc=malloc a la difference que l'on peut deplace dans une zone mémoire de taille suffisante si la premiere ne l'est pas et fait un free de la première zone.
//	Exemple si le malloc M prend 2 case mémoire et qu'il nous en faut 3 et que l'espace contigu le première malloc est occupé xx on réallou R plus loin ou la place est suffisante MMxx0O0-->00xxRRR
	  if(tableau_equipements==NULL)						
	  {
		fprintf(stdout,"RecupérerInfoFichier : Erreur d'alloc mémoire \n");
		exit(-1);
	  }
				
	  memset(tableau_equipements+i,0,sizeof(ST_EQUIPEMENTS));
	}
	while(fgets(chaine,CMAX,fp)!=NULL)
	{
		size_chaine=strlen(chaine)-1; 
		st_token=strtok(chaine,";"); 
		size_chaine-=(strlen(st_token)+1); 
		j=0;

		if(size_chaine<0)
			i--;
		
		while(st_token!=NULL && size_chaine>=0)
		{
			switch(j)
			{			
				case 0:
					strcpy(nom_equipement,st_token);
					break;
				case 1:
					consommation = atof(st_token);
					break;
				case 2:
					temps = atof(st_token);
					break;
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
						nouveau = (ST_EQUIPEMENTS*) malloc (sizeof(ST_EQUIPEMENTS));
						suivant = &(tableau_equipements[atoi(st_token)]);
						tableau_equipements[atoi(st_token)]= *nouveau;
						tableau_equipements[atoi(st_token)].suiv = suivant;
						tableau_equipements[atoi(st_token)].consommation_equipement = consommation;
						tableau_equipements[atoi(st_token)].nombre_heures_utilisation_journalier = temps;
						tableau_equipements[atoi(st_token)].Largeur = 0;
						tableau_equipements[atoi(st_token)].Longueur = 0;
						tableau_equipements[atoi(st_token)].coordX1 = 0;
						tableau_equipements[atoi(st_token)].coordY1 = 0;
						tableau_equipements[atoi(st_token)].coordX2 = 0;
						tableau_equipements[atoi(st_token)].coordY2 = 0;
					break;	
				default:
					break;
			}
			st_token=strtok(NULL,";");
			size_chaine-=(strlen(st_token)+1);
			j++;
			
		}
		memset(chaine,0,sizeof(chaine));
		i++;
	}
	return tableau_equipements;
}
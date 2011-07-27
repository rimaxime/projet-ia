/**
  * \file gestion_fichiers.c
  * \brief Récupére les données des bases de données pour les
  * les mettre dans des tableaux / listes
  * \author MRI
  * \date 11/07/2011
  */

#include "../inc/gestion_fichiers.h"

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
	  exit(1);
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
					 tableau_departements[i].num_departement=atoi(st_token);
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
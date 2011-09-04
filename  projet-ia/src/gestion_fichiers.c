/**
  * \file gestion_fichiers.c
  * \brief Récupére les données des bases de données pour les
  * les mettre dans des tableaux / listes
  * \author MRI & BEC
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
					if(compte_mois==0)
					 strcpy(tableau_departements[i].num_departement,(st_token));
					break;
				case 1:
					if(compte_mois==0)
					  strcpy(tableau_departements[i].nom_departement,st_token);
					break;
				case 2:
					if(compte_mois==0)
					 strcpy(tableau_departements[i].nom_region,st_token);
					break;
				case 3:
					if(compte_mois==0)
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
	fclose(fp);
	
	
	return tableau_departements;
}

ST_EQUIPEMENTS * RecupererInfosEquipements(ST_EQUIPEMENTS *tableau_equipements)
{
    char *st_token=NULL;
	char chaine[CMAX];
	int i=0,j=0,k=0;
	int size_chaine=0;
	memset(chaine,0,sizeof(chaine));
	FILE* ft;
	float consommation=0;
	float temps=0;
	int id;
	char nom_equipement[CMAX];
	ST_EQUIPEMENTS* nouveau = NULL;
	ft = fopen("../ressource/Equipements.csv","r");
	if(ft==NULL)
	{
	  fprintf(stderr,"Erreur d'ouverture fichier\n");
	  exit(-1);
	}
	while(k<7)
	{
	  tableau_equipements=(ST_EQUIPEMENTS *)realloc(tableau_equipements,(k+1)*sizeof(ST_EQUIPEMENTS));	//Il faut que st_recover=NULL -->realloc=malloc a la difference que l'on peut deplace dans une zone mémoire de taille suffisante si la premiere ne l'est pas et fait un free de la première zone.
//	Exemple si le malloc M prend 2 case mémoire et qu'il nous en faut 3 et que l'espace contigu le première malloc est occupé xx on réallou R plus loin ou la place est suffisante MMxx0O0-->00xxRRR
	  if(tableau_equipements==NULL)						
	  {
		fprintf(stdout,"RecupérerInfoFichier : Erreur d'alloc mémoire \n");
		exit(-1);
	  }
	  
	  memset(tableau_equipements+k,0,sizeof(ST_EQUIPEMENTS));
	  tableau_equipements[k].suiv = NULL;
	  k++;
	}
	while(fgets(chaine,CMAX,ft)!=NULL)
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
						if(strcasecmp(st_token,"Chambre") == 0)
						  id = 1;
						else if (strcasecmp(st_token,"Salon") == 0)
						  id = 2;
						else if (strcasecmp(st_token,"Cuisine") == 0)
						  id = 3;
						else if (strcasecmp(st_token,"Salle de bain") == 0)
						  id = 4;
						else if (strcasecmp(st_token,"Toilettes") == 0)
						  id = 5;
						else if (strcasecmp(st_token,"Buanderie") == 0)
						  id = 6;
						else 
						  id = 1;
						nouveau = (ST_EQUIPEMENTS*) malloc (sizeof(ST_EQUIPEMENTS));
						strcpy(nouveau->nom_equipement,nom_equipement);
						nouveau->consommation_equipement = consommation;
						nouveau->nombre_heures_utilisation_journalier = temps;
						nouveau->Largeur = 0;
						nouveau->Longueur = 0;
						nouveau->coordX1 = 0;
						nouveau->coordY1 = 0;
						nouveau->coordX2 = 0;
						nouveau->coordY2 = 0;
						nouveau->suiv = NULL;
						ST_EQUIPEMENTS *test = NULL;
						test = &(tableau_equipements[id]);
						ST_EQUIPEMENTS *precedent = test;
						while(test != NULL)
						{
						  precedent = test;
						  test = test->suiv;
						}
						precedent->suiv = nouveau;
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
	free(ft);
	return tableau_equipements;
}


ST_DonneGeo* RecupererInfosGeographique(ST_DonneGeo *tableau_geo)
{
	char *st_token=NULL;
	char chaine[CMAX];
	int i=0,j=0,k=0;
	int compte_degres = 10;
	int size_chaine=0;
	int inclinaison=0;
	int exposition=0;
	float rendement=0;
	memset(chaine,0,sizeof(chaine));
	FILE* fp;
	fp = fopen("../ressource/Projet_Rendement_Geo.csv","r");
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
		  if(compte_degres>=10)
		  {
			tableau_geo=(ST_DonneGeo *)realloc(tableau_geo,(i+1)*sizeof(ST_DonneGeo));	//Il faut que st_recover=NULL -->realloc=malloc a la difference que l'on peut deplace dans une zone mémoire de taille suffisante si la premiere ne l'est pas et fait un free de la première zone.
//	Exemple si le malloc M prend 2 case mémoire et qu'il nous en faut 3 et que l'espace contigu le première malloc est occupé xx on réallou R plus loin ou la place est suffisante MMxx0O0-->00xxRRR
				if(tableau_geo==NULL)						
				{
					fprintf(stdout,"RecupérerInfoFichier : Erreur d'alloc mémoire \n");
					exit(-1);
				}
				
				memset(tableau_geo+i,0,sizeof(ST_DonneGeo));
				compte_degres=0;
		  }
		}
		else
			i--;
		
		while(st_token!=NULL && size_chaine>=0)
		{
			switch(j)
			{			
				case 0:
					inclinaison = atoi(st_token);
					break;
				case 1:
					exposition = atoi(st_token);
					break;
				case 2:
					rendement = atof(st_token);
					if(compte_degres == 0)
					{
					  tableau_geo[i].inclinaison = inclinaison;
					  tableau_geo[i].orientation = exposition;
					  tableau_geo[i].rendement = rendement;
					  tableau_geo[i].suiv = NULL;
					}
					else
					{
					 ST_DonneGeo* Nouveau = NULL;
					 Nouveau = (ST_DonneGeo*) malloc (sizeof(ST_DonneGeo));
					 Nouveau->inclinaison = inclinaison;
					 Nouveau->orientation = exposition;
					 Nouveau->rendement = rendement;
					 Nouveau->suiv = NULL;
					 
					 ST_DonneGeo *test = NULL;
					 test = &(tableau_geo[i]);
					 ST_DonneGeo* precedent = test;
					 while(test != NULL)
					 {
					   precedent = test;
				           test = test->suiv;
					 }
					 precedent->suiv = Nouveau;
					}
					break;
				default:
					break;
			}
			st_token=strtok(NULL,";");
			size_chaine-=(strlen(st_token)+1);
			j++;
			
		}
		memset(chaine,0,sizeof(chaine));
		compte_degres++;
		if(compte_degres == 10)
			i++;
	}
	fclose(fp);
	return tableau_geo;
}
  
void Exporter_Evenement_Fichier(ST_JOUR *Tete,char Nom_fichier[CMAX])
{
  ST_JOUR *courant= Tete;
  float somme_prod,somme_gain,somme_conso,somme_cout;
  somme_prod=0;
  somme_gain=0;
  somme_conso=0;
  somme_cout=0;
  float temp_moy,temp_min,temp_max,somme_temp,i;
  temp_moy=Tete->temperature;
  temp_min=Tete->temperature;
  temp_max=Tete->temperature;
  somme_temp=0;
  i=0;
  ST_Date Date_min;
  Date_min.Jour=0;
  Date_min.Mois=0;
  Date_min.Annee=0;
  ST_Date Date_max;
  Date_max.Jour=0;
  Date_max.Mois=0;
  Date_max.Annee=0;
 
  FILE *report_evenement;
	report_evenement=fopen(Nom_fichier,"w"); //Voir comment passer le nom en parametres
  if(report_evenement == NULL)
  {
    printf("\nErreur d'ouverture fichier \n");
    exit(-1);
  }
  if(Tete == NULL)
    printf("\nLa file d'evenement est vide\n");
  //Calcul des statistiques 
  while(courant !=NULL)
  {
    i++;
    somme_prod += courant->production;
    somme_gain += courant->gain;
    somme_conso += courant->consommation;
    somme_cout += courant->cout;
    somme_temp += courant->temperature; 
    temp_moy=somme_temp/i;
    if(courant->temperature < temp_min)
    {
      temp_min = courant->temperature;
      Date_min.Jour = courant->date.Jour;
      Date_min.Mois = courant->date.Mois;
      Date_min.Annee = courant->date.Annee;
    }
    if(courant->temperature > temp_max)
    {
      temp_max = courant->temperature;
      Date_max.Jour = courant->date.Jour;
      Date_max.Mois = courant->date.Mois;
      Date_max.Annee = courant->date.Annee;
    }   
    courant=courant->suiv;
  }
  
  fprintf(report_evenement,"___SOLARIS Report\n\n");
  fprintf(report_evenement,"File_Name : %s\n\n",Nom_fichier);
  fprintf(report_evenement,"\nTotal : \n");  
  fprintf(report_evenement,"\tEnergie Produite  = %2.2f KWh soit %2.2f €\n",somme_prod/1000,somme_gain);  
  fprintf(report_evenement,"\tEnergie Consommée = %2.2f KWh soit %2.2f €\n\n",somme_conso/1000,somme_cout);  
  fprintf(report_evenement,"Statistiques :\n");
  fprintf(report_evenement,"\tTemperature Moy : %2.2f°C\n",temp_moy);
  fprintf(report_evenement,"\tTemperature Min : %2.2f°C le %d/%d/%d\n",temp_min,Date_min.Jour,Date_min.Mois,Date_min.Annee);
  fprintf(report_evenement,"\tTemperature Max : %2.2f°C le %d/%d/%d\n\n",temp_max,Date_max.Jour,Date_max.Mois,Date_max.Annee);
  fprintf(report_evenement,"\nDetails :\n");
  
  while(Tete != NULL)
  {
    fprintf(report_evenement,"\nDate : %d / %d / %d",Tete->date.Jour,Tete->date.Mois,Tete->date.Annee);
    fprintf(report_evenement,"\n\tTemperature:  %f",Tete->temperature);
    fprintf(report_evenement,"\n\tCondition:    %d",Tete->condition);
    fprintf(report_evenement,"\n\tProduction:   %f",Tete->production);
    fprintf(report_evenement,"\n\tConsommation: %f",Tete->consommation);
    fprintf(report_evenement,"\n\tGain:         %f",Tete->gain); 
    fprintf(report_evenement,"\n\tCout:         %f\n",Tete->cout);
    Tete=Tete->suiv;
  }
  fprintf(report_evenement,"\n\n__________________________________");  
  fprintf(report_evenement,"\n Solaris 2011 © All right reserved");
    
  fclose(report_evenement);  
}
  
void save_simu(ST_HABITATIONS *Habitation,ST_PARAMETRES_SIMULATION *Param_Simu, ST_JOUR *tete,char *nom_fichier)
{
  ST_PIECES *piece = NULL;
  ST_EQUIPEMENTS *equipement = NULL;
  ST_PANNEAUX *panneau = NULL;
  ST_JOUR *liste = NULL;
  FILE *simu = NULL;
simu=fopen(nom_fichier,"w");
  if(simu == NULL)
  {
    printf("\nErreur d'ouverture fichier \n");
    exit(-1);
  }
  
  if(Habitation == NULL)
  {
    printf("\nSauvegarde impossible : Pas d'habitation definie\n");
    exit(-1);    
  }
  
  fprintf(simu,"h|%d|%f|%d|%s|%d|%d|%s|%s|%s|%d|%d|%d|\n",Habitation->nombre_pieces,Habitation->inclinaison_toit,
 Habitation->Isolation,Habitation->Isolation_ihm,Habitation->Exposition,Habitation->climatisation,
 Habitation->climatisation_ihm,Habitation->Departement,Habitation->Departement_ihm,Habitation->chauffage_bois,
 Habitation->chauffage_gaz,Habitation->chauffage_electricite);
  piece = Habitation->LC_Pieces;
  while(piece != NULL)
  {
    fprintf(simu,"p|%s|%d|%s|%f|%f|%f|%f|%f|%f|\n",piece->nom_piece,piece->type_piece,piece->type_piece_ihm,piece->Largeur,
      piece->Longueur,piece->coordX1,piece->coordY1,piece->coordX2,piece->coordY2);
    equipement = piece->LC_Equipements;
    while(equipement != NULL)
    {
      fprintf(simu,"e|%d|%s|%f|%f|%f|%f|%f|%f|%f|%f|\n",equipement->indice,equipement->nom_equipement,equipement->consommation_equipement,
     equipement->nombre_heures_utilisation_journalier,equipement->Largeur,equipement->Longueur,equipement->coordX1,
     equipement->coordY1,equipement->coordX2,equipement->coordY2);
      equipement = equipement->suiv;    
    }
    piece = piece->suiv;
  }
  
  panneau = Habitation->LC_Panneaux;
  if(panneau != NULL);
    fprintf(simu,"n|%d|%d|%s|%f|%f|%f|%d|%d|%f|%d|%s|%d|%s|\n",panneau->indice,panneau->type,panneau->type_ihm,panneau->Largeur,
      panneau->Longueur,panneau->inclinaison_panneau,panneau->Exposition,panneau->surface,panneau->rendement,panneau->MPPT,
      panneau->MPPT_ihm,panneau->auto_rotation,panneau->auto_rotation_ihm);
  
  if(Param_Simu != NULL)
    fprintf(simu,"s|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|\n",Param_Simu->date_initiale.Jour,Param_Simu->date_initiale.Mois,
   Param_Simu->date_initiale.Annee,Param_Simu->date_finale.Jour,Param_Simu->date_finale.Mois,Param_Simu->date_finale.Annee,
   Param_Simu->date_courante.Jour,Param_Simu->date_courante.Mois,Param_Simu->date_courante.Annee,Param_Simu->vitesse,
   Param_Simu->modification_habitation,Param_Simu->modification_date);
  
  if(tete != NULL)
    liste = tete;
  while(liste != NULL)
  {
    fprintf(simu,"j|%d|%d|%d|%f|%d|%f|%f|%f|%f|\n",liste->date.Jour,liste->date.Mois,liste->date.Annee,liste->temperature,
      liste->condition,liste->production,liste->consommation,liste->gain,liste->cout);
    liste = liste->suiv;
  }
   fclose(simu);
}



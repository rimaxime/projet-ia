/**
  * \file liste_evenement.c
  * \brief Fichier contenant les fonctions utiles à la gestion de la file d'evenement
  * \author Benoit Eche
  * \date 01/09/11
  */

#include "../inc/liste_evenement.h"

ST_JOUR *creer_jour(ST_Date Date, ST_HABITATIONS Habitation, ST_DonneGeo Donnee_geo,STR_DEPARTEMENT departements, ST_JOUR *Jour_precedent)
{
  int mois;
  mois=Date.Mois -1;
  float conso, prod;
  conso = 0;
  prod = 0;
  ST_SimuMeteo Meteo_Jour;
  ST_JOUR *Nouveau = NULL;
  Nouveau = (ST_JOUR *) malloc (sizeof(ST_JOUR));
  if(Nouveau == NULL)
  {
    fprintf(stdout,"Creer_jour : Erreur d'allocation memoire");
    exit(-1);
  }
  Nouveau->suiv = NULL;

  Simu_Jour(&Meteo_Jour, departements.Tableau_Mois[mois],Jour_precedent);
  Nouveau->temperature = Meteo_Jour.temp;
  conso = consommation_globale(*Nouveau,Habitation);
  prod = Prod_jour(&Meteo_Jour,Donnee_geo,(Habitation.LC_Panneaux));
  
  Nouveau->date=Date;
 
  Nouveau->condition = Meteo_Jour.condition;
  Nouveau->production = prod;
  Nouveau->consommation = conso;
  Nouveau->gain = prod*PRIX_ACHAT;
  Nouveau->cout = conso*PRIX_VENTE;
  
  return Nouveau;
}

/*
--ST_JOUR :
  ST_Date date;	
  float temperature;
  int condition; 
  float production; 
  float consommation;
  float gain; 
  float cout; 
  struct jour *suiv; 

--SimuMeteo //Valeurs simulées
  ST_Date date; //date de la simulation
  float temp; //Température du jour simulé
  float h_soleil; //Heure d'ensoleilement du jour simulé
  float puiss_soleil; //Puissance du soleil durant la journée
  float precipitation; //Nombre de mm de pluie durant la journée
  int condition; //0=Ensoleillé, 1=Couvert, 2=Pluie, 3=Grèle, 4=Neige

*/

STR_DEPARTEMENT* parseur_departement(STR_DEPARTEMENT* Tableau_departement, char *nom_departement)
{
 int i=0;
 while(&(Tableau_departement[i]) != NULL && strcasecmp(Tableau_departement[i].nom_departement , nom_departement) != 0)
 {
   i++;
 }
 return(&(Tableau_departement[i]));
}

ST_DonneGeo* parseur_donnees_geo(ST_DonneGeo *Tableau_Geo, int inclinaison, int exposition)
{
 int i = 0;
 ST_DonneGeo * test = NULL;
 while(Tableau_Geo[i].inclinaison < inclinaison)
 {
  i++;
 }
 if(Tableau_Geo[i].inclinaison == inclinaison)
 {
   
   test = &(Tableau_Geo[i]);
   while(test != NULL && test->orientation <exposition)
   {
     test = test->suiv;
   }
 }
 return test;
}

ST_JOUR* creer_liste_jours(ST_Date Date_Debut,ST_Date Date_Fin, ST_HABITATIONS Habitation, ST_DonneGeo Donnee_geo,STR_DEPARTEMENT departements, ST_JOUR *Jour_precedent)
{
 ST_JOUR* Nouveau = NULL;
 ST_JOUR* Liste = NULL;
 ST_JOUR* tete_liste = Jour_precedent;
 while((Date_Debut.Annee < Date_Fin.Annee) ||
       (Date_Debut.Annee == Date_Fin.Annee && Date_Debut.Mois < Date_Fin.Mois) ||
       (Date_Debut.Annee == Date_Fin.Annee && Date_Debut.Mois == Date_Fin.Mois && Date_Debut.Jour <= Date_Fin.Jour))
 {
   Nouveau = creer_jour(Date_Debut,Habitation,Donnee_geo,departements,Jour_precedent);
   if(Jour_precedent == NULL)
   {
    Jour_precedent = (ST_JOUR*) malloc (sizeof(ST_JOUR)); //Added
    Jour_precedent = Nouveau; //Added
    tete_liste = Nouveau;
    Liste = tete_liste;
   }
   else if(tete_liste->suiv == NULL)
   {
     tete_liste->suiv = Nouveau;
     Liste = Nouveau;
   }
   else
   {
     Liste->suiv = Nouveau;
     Liste = Nouveau;
   }
   
   if(Date_Debut.Mois == 12 && Date_Debut.Jour ==31)
   {
     Date_Debut.Mois = 1;
     Date_Debut.Jour =1;
     Date_Debut.Annee = Date_Debut.Annee + 1;
   }
   else if(Date_Debut.Mois % 2 != 1 && Date_Debut.Jour == 31)
   {
    Date_Debut.Mois = Date_Debut.Mois + 1;
    Date_Debut.Jour = 1;
   }
   else if((Date_Debut.Mois == 2 && Date_Debut.Jour == 28) ||(Date_Debut.Mois % 2 == 1 && Date_Debut.Jour == 30))
   {
     Date_Debut.Mois = Date_Debut.Mois + 1;
     Date_Debut.Jour = 1;
   }
   else
     Date_Debut.Jour = Date_Debut.Jour + 1;
  
   
}
 return(tete_liste);
}

void supprimer_jour(ST_Date Date_sup, PTR_ST_JOUR *tete)
{
  ST_JOUR *prec = NULL;
  ST_JOUR *courant = *tete;
  
  if(*tete == NULL)
    printf("\nSuppression impossible : La liste est vide\n");
  
  while(courant != NULL)
  {
    if(comparer_date(courant->date,Date_sup)==0)
    {
      if(courant == *tete)
	*tete=courant->suiv;
      else
	prec->suiv=courant->suiv;
      free(courant);
      courant=NULL;
    }
    else
    {
      prec=courant;
      courant=courant->suiv;
    }
  }
}

void supprimer_liste_jour(ST_Date Date_Debut,ST_Date Date_Fin , PTR_ST_JOUR *tete)
{
 ST_JOUR *prec = NULL;
 ST_JOUR *courant = *tete;
 ST_JOUR *suiv = courant->suiv;
 
 if(*tete == NULL)
   printf("\nSuppression impossible : La liste est vite\n");
 else
 {
   while(courant!=NULL)
   {
      if(comparer_date(courant->date,Date_Debut)==0)
      {
	if(courant == *tete)
	{
	  while(courant!=NULL && comparer_date(courant->date,Date_Fin) != 1)
	  {
	    suiv=courant->suiv;
	    free(courant);
	    courant=suiv;
	  }
	  *tete=suiv;
	}
	else
	{
	  while(courant!=NULL && comparer_date(courant->date,Date_Fin) !=1)
	  {
	    suiv=courant->suiv;
	    free(courant);
	    courant=suiv;
	  }
	  prec->suiv=suiv;
	}
      }
      else
      {
	prec=courant;
	courant=courant->suiv;
      }
   }
  }
}


int comparer_date(ST_Date Date1, ST_Date Date2) //if Date1 > Date2 = 1; Date1=Date2 =0 ; Date1 < Date2 = -1
{
  if(Date1.Annee > Date2.Annee)
    return 1;
  else if(Date1.Annee == Date2.Annee && Date1.Mois > Date2.Mois)
    return 1;
  else if(Date1.Annee == Date2.Annee && Date1.Mois == Date2.Mois && Date1.Jour > Date2.Jour)
    return 1;
  else if(Date1.Annee == Date2.Annee && Date1.Mois == Date2.Mois && Date1.Jour == Date2.Jour)
    return 0;
  else
    return -1; 
}

ST_JOUR* retrouver_jour(ST_Date Date_rech, ST_JOUR *tete)
{
  ST_JOUR *courant=tete;
  if(tete==NULL)
    printf("\nRecherche impossible : La liste est vide\n");
    
  while(courant != NULL)
  {
    if(comparer_date(Date_rech,courant->date)==0)
      return courant;
    else
      courant=courant->suiv;  
  }
  return tete;
}
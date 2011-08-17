/**
  * \file meteo.c
  * \brief Fichier générant les simulations climatique du logiciel
  * \author Benoit Eche
  * \version 0.1
  * \date 10/07/11
  */



#include "../inc/meteo.h"

//Fonctions

/**
 * \name   Simulation Temp
 * \brief  Calcule la météo du jour en fonction de la témpérature précedente et des normales
 * \param  Structure Simulation météo jour précédent, structures des normales mensuelles
 * \return Météo du jour 
 */
float SimulationTemp(ST_SimuMeteo Meteo_Precedente,ST_DonneeMeteo Normales_Mensuelles)
{
  //Créations des variables locales
  float nombre_aleatoire,r,temp;
  r=100;
  //Création d'un nombre aléatoire
  nombre_aleatoire=my_rand();
  //Calcul de la temérature journalière
  temp = (Normales_Mensuelles.temp_min + ((Normales_Mensuelles.temp_max-Normales_Mensuelles.temp_min)*nombre_aleatoire)) * 0.6 
	  + Meteo_Precedente.temp * 0.4;
  if(temp>(Normales_Mensuelles.temp_max))
    temp=Normales_Mensuelles.temp_max;
  else if(temp<Normales_Mensuelles.temp_min)
    temp=Normales_Mensuelles.temp_min;
  return temp;   
}

/**
 * \name   SimulationConditionsMeteo
 * \brief  Calcule les conditions météo du jour (soleil,pluie,neige,grele)
 * \param  Structure Simulation météo jour précédent, structures des normales mensuelles
 * \return none
 */
void SimulationConditionsMeteo(ST_DonneeMeteo Normales_Mensuelles, PTR_ST_SimuMeteo Meteo_Jour)
{
  //Création des variables locales
  float probabilite_precipitation,nombre_aleatoire,r;
  r=100;
  
  //Calcul de la probabilité de pluie de la journée
  if(Meteo_Jour->date.Mois%2==0)
  {
    if(Meteo_Jour->date.Mois==2)
      probabilite_precipitation=(float)Normales_Mensuelles.jr_pluie/28;
    else
      probabilite_precipitation=(float)Normales_Mensuelles.jr_pluie/30;
  }
  else
    probabilite_precipitation=(float)Normales_Mensuelles.jr_pluie/31;
  //Génération de nombres aléatoires
  nombre_aleatoire=my_rand();

  //Calcul de la condition météo
  if(nombre_aleatoire<probabilite_precipitation)
  {
    if(Meteo_Jour->temp>=-1 && Meteo_Jour->temp <= 1)
      Meteo_Jour->condition=4;
    else if(nombre_aleatoire<0.1*probabilite_precipitation)
      Meteo_Jour->condition=3;
    else
      Meteo_Jour->condition=2;
  }
  else if(nombre_aleatoire<1.4*probabilite_precipitation)
    Meteo_Jour->condition=1;
  else
    Meteo_Jour->condition=0;
}

/**
 * \name   SimulationHeureEnsoleillement
 * \brief  Calcule le nombre d'heures d'ensoleillement de la journée
 * \param  Structure Simulation météo du jour, structures des normales mensuelles
 * \return none
 */
void SimulationHeuresEnsoleillement(ST_DonneeMeteo NormalesMensuelles, PTR_ST_SimuMeteo Meteo_Jour)
{
  //Création des variables locales
  float nombre_aleatoire;
  float nb_hnormales;
  float r;
  r=100;
  
  //Calcul du nombre d'heure d'ensoleillement par jour de non pluie
    if(Meteo_Jour->date.Mois%2==0)
  {
    if(Meteo_Jour->date.Mois==2)
      nb_hnormales=(float)NormalesMensuelles.nb_soleil/28;
    else
      nb_hnormales=(float)NormalesMensuelles.nb_soleil/30;
  }
  else
    nb_hnormales=(float)NormalesMensuelles.nb_soleil/31;
  
  //Génération de nombres aléatoires
  nombre_aleatoire=my_rand();
  
  //Calcul du nombre d'heure d'ensoleillement
  if(Meteo_Jour->condition==0)
  {
    Meteo_Jour->h_soleil = nombre_aleatoire*2*nb_hnormales;
    //printf("0-%2.2f-%2.2f\n",nombre_aleatoire,Meteo_Jour->h_soleil);
  }
  if(Meteo_Jour->condition==1)
  {
    Meteo_Jour->h_soleil = nombre_aleatoire*1.2*nb_hnormales;
    //printf("1-%2.2f-%2.2f\n",nombre_aleatoire,Meteo_Jour->h_soleil);
  }
  if(Meteo_Jour->condition==4)
    Meteo_Jour->h_soleil = 1*nombre_aleatoire*nb_hnormales;
  else
     Meteo_Jour->h_soleil = 0.8*nombre_aleatoire*nb_hnormales;    
}


float my_rand(void)
{
  static int tab[TMAX];
  static int premier = 0;
  int index;
  int rn;
  float r;
  r=100;
  
  if(premier == 0)
  {
    int i;
    srand(time(NULL));
    for(i=0;i<TMAX;i++)
      tab[i] = rand();
    premier = 1;    
  }
  index = (int)(rand() / RAND_MAX * (TMAX-1));
  rn = tab[index];
  tab[index]= rand();
  r=((rn%100)/r);
  return(r);
}

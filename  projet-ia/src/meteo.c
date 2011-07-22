/**
  * \file meteo.c
  * \brief Fichier générant les simulations climatique du logiciel
  * \author Benoit Eche
  * \version 0.1
  * \date 10/07/11
  */



#include "../inc/meteo.h"

//Fonctions

float SimulationTemp(float temp_prec,float temp_min, float temp_max)
{
	float i,n,r,temp;
	r=100;
 	srand(rand());
	i=((rand()%100)/r);
	printf("i : %f\n",i);
	n=((rand()%100)/r);
	if(temp_prec<temp_min)
	{
		temp = temp_prec + 0.2*i*temp_prec;
	}
	else if(temp_prec>temp_max)
	{
		temp= temp_prec - 0.2*n*temp_prec;
	}
	else
	{
		temp= temp_prec + 0.2*i*temp_prec - 0.2*n*temp_prec;
	}

  return temp;   
}



float SimulationTemp2(ST_SimuMeteo Meteo_Precedente,ST_DonneeMeteo Normales_Mensuelles)
{
  float nb_aleatoire,n,r,temp;
  r=100;
  srand(rand());
  nb_aleatoire=((rand()%100)/r);
  temp = (Normales_Mensuelles.temp_min + ((Normales_Mensuelles.temp_max-Normales_Mensuelles.temp_min)*nb_aleatoire)) * 0.6 
	  + Meteo_Precedente.temp * 0.4;
  if(temp>(Normales_Mensuelles.temp_max))
    temp=Normales_Mensuelles.temp_max;
  else if(temp<Normales_Mensuelles.temp_min)
    temp=Normales_Mensuelles.temp_min;
  return temp;   
}

void SimulationConditionsMeteo(ST_DonneeMeteo Normales_Mensuelles, PTR_ST_SimuMeteo Meteo_Jour)
{
  float probabilite_precipitation,nombre_aleatoire,r;
  r=100;
  if(Meteo_Jour->date.Mois%2==0)
  {
    if(Meteo_Jour->date.Mois==2)
      probabilite_precipitation=(float)Normales_Mensuelles.jr_pluie/28;
    else
      probabilite_precipitation=(float)Normales_Mensuelles.jr_pluie/30;
  }
  else
    probabilite_precipitation=(float)Normales_Mensuelles.jr_pluie/31;
  
  srand(rand());
  nombre_aleatoire=((rand()%100)/r);
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




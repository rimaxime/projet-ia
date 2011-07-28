//Include
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../inc/constantes.h"
#include "../inc/structures.h"
#include "../inc/meteo.h"

void simulation_temperature();
void simulation_condition();
void simulation_hsoleil();

//Main
int main(void)
{	
	//simulation_temperature();
	//simulation_condition();
	simulation_hsoleil();
	return 0;
}


void simulation_temperature()
{
  int n,t;
  ST_DonneeMeteo Normales;
  ST_SimuMeteo Prec;
	float prec;	
	FILE *Simu;
	Simu= fopen("Simu_temperature.csv","w+");
	printf("Entrer temp_prec,temp_min,temp_max\n");
	n=scanf("%f,%f,%f",&(Prec.temp),&(Normales.temp_min),&(Normales.temp_max));
	printf("Entrer le nombre de test a faire : ");
	n=scanf("%d",&t);
	for(n=0;n<t;n++)
	{
	  prec=SimulationTemp(Prec,Normales);
	  fprintf(Simu,"%d;%2.2f\n",n,prec);
	}
}

void simulation_condition()
{
  int i;
  ST_DonneeMeteo Normales;
  ST_SimuMeteo Jour;
  FILE *Simu;
	Simu= fopen("Simu_condition.csv","w+");
  Jour.date.Mois=1;
  Jour.temp=0;
  Normales.jr_pluie=12;
  for(i=0;i<100;i++)
  {
    SimulationConditionsMeteo(Normales, &Jour);
    fprintf(Simu,"%d ; %d\nt",i,Jour.condition);
  }
}

void simulation_hsoleil()
{
  int i;
  ST_DonneeMeteo Normales;
  ST_SimuMeteo Jour;
  FILE *Simu;
  Simu = fopen("Simu_hsoleil.csv","w+");
  Jour.date.Mois=2;
  Normales.nb_soleil=155;
  fprintf(Simu,"Test;Condition;Nb d'heure de soleil\n");
  for(i=0;i<100;i++)
  {
    for(Jour.condition=0;Jour.condition<4;Jour.condition++)
    {
      SimulationHeuresEnsoleillement(Normales,&Jour);
      fprintf(stdout,"%d;%d;%2.2f\n",i,Jour.condition,Jour.h_soleil);
    } 
  }  
}

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

//Main
int main(void)
{	
	//simulation_temperature();
	simulation_condition();
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
	  prec=SimulationTemp2(Prec,Normales);
	  fprintf(Simu,"%d;%2.2f\n",n,prec);
	}
}

void simulation_condition()
{
  int n,i;
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

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../inc/constantes.h"
#include "../inc/structures.h"
#include "../inc/meteo.h"

//Prototypes
void simulation_temperature();
void simulation_condition();
void simulation_hsoleil();
void simulation_myrand();

//Main
int main(void)
{	
	simulation_temperature();
	//simulation_condition();
	//simulation_hsoleil();
	//simulation_myrand();
	return 0;
}


void simulation_temperature()
{
  int n,t;
  ST_DonneeMeteo Normales;
  ST_JOUR Prec;
	float prec;	
	FILE *Simu;
	Simu = fopen("Simu_temperature_complete.csv","w+");
	//printf("Entrer temp_prec,temp_min,temp_max\n");
	//n=scanf("%f,%f,%f",&(Prec.temp),&(Normales.temp_min),&(Normales.temp_max));
	//printf("Entrer le nombre de test a faire : ");
	//n=scanf("%d",&t);
	t=40;
	Prec.temperature=-15;
	Normales.temp_min=13;
	Normales.temp_max=24;
	fprintf(Simu,"INFERIEUR\nTemp_prec;Temp_min; Temp_max;\n%2.2f;%2.2f;%2.2f\n",Prec.temperature,Normales.temp_min,Normales.temp_max);
	
	for(n=0;n<t;n++)
	{
	  prec=SimulationTemp(NULL,Normales);
	  fprintf(Simu,"%d;%2.2f\n",n,prec);
	  Prec.temperature=prec;
	}
	/*t=40;
	Prec.temperature=17;
	Normales.temp_min=10;
	Normales.temp_max=28;
	fprintf(Simu,"NORMAL\nTemp_prec;Temp_min;Temp_max;\n%2.2f;%2.2f;%2.2f\n",Prec.temperature,Normales.temp_min,Normales.temp_max);
	for(n=0;n<t;n++)
	{
	  prec=SimulationTemp(&Prec,Normales);
	  fprintf(Simu,"%d;%2.2f\n",n,prec);
	  Prec.temperature=prec;
	}
	t=40;
	Prec.temperature=45;
	Normales.temp_min=5;
	Normales.temp_max=14;
	fprintf(Simu,"SUPERIEUR\nTemp_prec;Temp_min; Temp_max;\n%2.2f;%2.2f;%2.2f\n",Prec.temperature,Normales.temp_min,Normales.temp_max);
	for(n=0;n<t;n++)
	{
	  prec=SimulationTemp(&Prec,Normales);
	  fprintf(Simu,"%d;%2.2f\n",n,prec);
	  Prec.temperature=prec;
	}
	ST_JOUR *Prec2 = NULL;
	prec = SimulationTemp(Prec2,Normales);
	printf("%f : prec\n",prec);
	*/
	fclose(Simu);
	printf("** SUCCES **\n");  
}

void simulation_condition()
{
  int i;
  ST_DonneeMeteo Normales;
  ST_SimuMeteo Jour;
  FILE *Simu;
	Simu= fopen("Simu_condition.csv","w+");
  Jour.date.Mois=1;
  Jour.temp=15;
  Normales.jr_pluie=12;
  for(i=0;i<100;i++)
  {
    SimulationConditionsMeteo(Normales, &Jour);
    fprintf(Simu,"%d ; %d\n",i,Jour.condition);
  }
  fclose(Simu);
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
  for(i=0;i<30;i++)
  {
    for(Jour.condition=0;Jour.condition<5;Jour.condition++)
    {
      SimulationHeuresEnsoleillement(Normales,&Jour);
      fprintf(Simu,"%d;%d;%2.2f\n",i,Jour.condition,Jour.h_soleil);
    }
  }
  fclose(Simu);
}

void simulation_myrand()
{
  float i,r;
  r=100;
  int n;
  for(n=0;n<200;n++)
  {
    i=my_rand();
    printf("%f \n",i);
  }
}
//Includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../inc/constantes.h"
#include "../inc/structures.h"
#include "../inc/production.h"
#include "../inc/meteo.h"

//Prototypes
void test_rendement_geo();
void test_calc_puiss_soleil();
void test_rendement_panneaux();
void test_rendement_thermique();
void test_prod_jour();

//Main

int main(void)
{
  printf("\nDebut test_production");
  test_rendement_geo();
  printf("\nTest_rendement_geo : OK");
  test_calc_puiss_soleil();
  printf("\nTest_calc_puiss_soleil : OK");
  test_rendement_panneaux();
  printf("\nTest_rendement_panneaux : OK");
  test_rendement_thermique();
  printf("\nTest_rendement_thermique : OK");
  test_prod_jour();
  printf("\nTest_prod_jour : OK");
  printf("\nSUCCESS\n\n");
  return 0;
}
void test_rendement_geo()
{
  ST_DonneGeo Geo;
  Geo.orientation = 0;
  Geo.inclinaison = 0;
  Geo.rendement = 0;
  FILE *rend_geo;
	rend_geo= fopen("Test_rendement_geo.csv","w+");
  fprintf(rend_geo,"Inclinaison ; Orientation ; Rendement\n");
  
  while(Geo.inclinaison < 100)
  {
    Geo.orientation = 0;
    while(Geo.orientation< 100)
    { 
      Geo.rendement = 0;
      Geo.rendement = Rendement_geo(Geo);
      fprintf(rend_geo,"%d ; %d ; %2.2f\n",Geo.inclinaison,Geo.orientation,Geo.rendement);
      Geo.orientation=Geo.orientation + 10;
    }
    Geo.inclinaison=Geo.inclinaison+10;    
  }
  fclose(rend_geo);
}

void test_calc_puiss_soleil()
{  
  FILE *puiss_sol;
    puiss_sol= fopen("Test_puiss_soleil.csv","w+");
  
  int i;
  ST_SimuMeteo Meteo_Jour;
  fprintf(puiss_sol,"Condition ; Puissance soleil\n");
  for(Meteo_Jour.condition=0;Meteo_Jour.condition<5;Meteo_Jour.condition++)
  {
    for(i=0;i<15;i++)
    {
      Calc_puiss_soleil(&Meteo_Jour);
      fprintf(puiss_sol,"%d ; %2.2f\n",Meteo_Jour.condition,Meteo_Jour.puiss_soleil);
    }
  }
  fclose(puiss_sol);  
}

void test_rendement_panneaux()
{
  FILE *rend_panneaux;
    rend_panneaux= fopen("Test_rendement_panneaux.csv","w+");
  ST_PANNEAUX Panneaux;
  Panneaux.rendement = -1;
  fprintf(rend_panneaux,"Type ; MPPT ; Auto_rot ; Rendement \n");
  for(Panneaux.type=0;Panneaux.type<6;Panneaux.type++)
  {
    for(Panneaux.MPPT=0;Panneaux.MPPT<3;Panneaux.MPPT++)
    {
      for(Panneaux.auto_rotation=0; Panneaux.auto_rotation<3; Panneaux.auto_rotation++)
      {
	Rendement_panneaux(&Panneaux);
	fprintf(rend_panneaux," %d ; %d ; % d ; %2.2f \n", Panneaux.type, Panneaux.MPPT, Panneaux.auto_rotation, Panneaux.rendement);
      }
    }
  }
  fclose(rend_panneaux);
  
}
void test_rendement_thermique()
{
  FILE *rend_th;
    rend_th= fopen("Test_rendement_therm.csv","w+");
  ST_SimuMeteo Jour;
  fprintf(rend_th,"Temp ; Rendement\n");
  for(Jour.temp =-10; Jour.temp < 100; Jour.temp++)
  {
    fprintf(rend_th," %2.2f ; %2.2f \n",Jour.temp,Rendement_thermique(Jour));
  }
  fclose(rend_th);
  
}

void test_prod_jour()
{
  FILE *prod;
    prod= fopen("Test_rendement_geo.csv","w+");
  fprintf(prod,"Test en cour de realisation");
  fclose(prod);
  
}
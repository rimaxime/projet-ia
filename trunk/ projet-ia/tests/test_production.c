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
void test_rendement_geo()

//Main
void test_rendement_geo()
{
  int i;
  ST_DonneGeo Geo;
  Geo.orientation = 0;
  Geo.inclinaison = 0;
  FILE *test;
	test= fopen("Test_rendement_geo.csv","w+");
  fprinf(test,"Inclinaison ; Orientation ; Rendement");
  
  while(Geo.inclinaison <100)
  {
    while(Geo.orientation<100)
    {     
      fprintf(test,"%d ; %d\n ; %2.2f",Geo.inclinaison,Geo.orientation,Rendement_geo(Geo));
      Geo.orientation=Geo.orientation+10;
    }
    Geo.inclinaison=Geo.inclinaison+10;    
  }
  fclose(Simu);
}
/**
  * \file production.c
  * \brief Fichier contenant les fonctions utiles pour le calcul de la production photovoltaique
  * \author Benoit Eche
  * \date 28/08/11
  */

#include "../inc/production.h"

//Fonctions

/**
 * \name Calc_puiss_soleil
 * \brief  Calcul de la puissance solaire journalière
 * \param PTR_ST_SimuMeteo Meteo_jour,struct Departements Dept
 * \return none
 */

void Calc_puiss_soleil(PRT_ST_SimuMeteo Meteo_Jour, STR_DEPARTEMENT Dept)
{
  if(Meteo_Jour.condition == 0)
    Meteo_Jour.puiss_soleil = PUISSANCE_SOLEIL + 0.2*myrand()*PUISSANCE_SOLEIL;
  else if(Meteo_Jour.condition == 4)
    Meteo_Jour.puiss_soleil = PUISSANCE_SOLEIL + 0.1*myrand()*PUISSANCE_SOLEIL;
  else(Meteo_Jour.condition == 1)
    Meteo_Jour.puiss_soleil = PUISSANCE_SOLEIL + 0.2*2*(myrand()-0.5)*PUISSANCE_SOLEIL;
}

/**
 * \name   
 * \brief  
 * \param  
 * \return  
 */

/**
 * \name   
 * \brief  
 * \param  
 * \return  
 */

/**
 * \name   
 * \brief  
 * \param  
 * \return  
 */

/**
 * \name   
 * \brief  
 * \param  
 * \return  
 */

/**
 * \name   myrand
 * \brief  Genere un nombre aleatoire floatant entre 0 et 1.
 * \param  none
 * \return Nombre aleatoire
 */
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
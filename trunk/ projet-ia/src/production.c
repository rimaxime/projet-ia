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
 * \param PTR_ST_SimuMeteo Meteo_jour
 * \return none
 */

void Calc_puiss_soleil(PTR_ST_SimuMeteo Meteo_Jour) //voir si on prend en compte l'indice climatique du departement
{
  if(Meteo_Jour->condition == 0)
    Meteo_Jour->puiss_soleil = PUISSANCE_SOLEIL + 0.2*my_rand()*PUISSANCE_SOLEIL;
  else if(Meteo_Jour->condition == 4)
    Meteo_Jour->puiss_soleil = PUISSANCE_SOLEIL + 0.1*my_rand()*PUISSANCE_SOLEIL;
  else if(Meteo_Jour->condition == 1)
    Meteo_Jour->puiss_soleil = PUISSANCE_SOLEIL + 0.2*2*(my_rand()-0.5)*PUISSANCE_SOLEIL;
  else
    Meteo_Jour->puiss_soleil = PUISSANCE_SOLEIL + 0.03*2*(my_rand()-0.5)*PUISSANCE_SOLEIL;
}

/**
 * \name   Rendement_geo
 * \brief  Renvoi le rendement geographique
 * \param  ST_DonneGeo Donnees;
 * \return  Rendement_geo
 */
float Rendement_geo(ST_DonneGeo Donnees)
{
  float incl_rad, orient_rad;
  
  if(Donnees.rendement != 0)
    return Donnees.rendement;
  else
  {
    incl_rad = ((Donnees.inclinaison*2*M_PI)/360);
    orient_rad = ((Donnees.orientation*2*M_PI)/360);
    return sin(incl_rad)*cos(orient_rad);   
  }
}


/**
 * \name Rendement_panneaux
 * \brief  Calcul du rendement du panneaux
 * \param  ST_Panneaux Panneaux
 * \return  none
 */

void Rendement_panneaux(PTR_ST_PANNEAUX Panneaux)
{
  switch(Panneaux->type)
  {  
    case 0 :
      if(Panneaux->MPPT == 0 || Panneaux->auto_rotation == 0)
    {
      if(Panneaux->MPPT == 0)
      {
	if(Panneaux->auto_rotation ==0)
	  Panneaux->rendement = (MONOCRISTALLIN_REND*2) + 0.15;
	else
	  Panneaux->rendement = MONOCRISTALLIN_REND + 0.15;
      }
      else if(Panneaux->auto_rotation == 0)
	Panneaux->rendement = MONOCRISTALLIN_REND*2;
    }
    else
      Panneaux->rendement = MONOCRISTALLIN_REND;
  break;
  
    case 1 :
      if(Panneaux->MPPT == 0 || Panneaux->auto_rotation == 0)
      {
	if(Panneaux->MPPT == 0)
	{
	  if(Panneaux->auto_rotation ==0)
	    Panneaux->rendement = (POLYCRISTALLIN_REND*2) + 0.15;
	  else
	    Panneaux->rendement = POLYCRISTALLIN_REND + 0.15;
	}
	else if(Panneaux->auto_rotation == 0)
	  Panneaux->rendement = POLYCRISTALLIN_REND*2;
      }
      else
	Panneaux->rendement = POLYCRISTALLIN_REND;
      break;
      
    case 2 :
      if(Panneaux->MPPT == 0 || Panneaux->auto_rotation == 0)
      {
	if(Panneaux->MPPT == 0)
	{
	  if(Panneaux->auto_rotation ==0)
	    Panneaux->rendement = (AMORPHE_REND*2) + 0.15;
	  else
	    Panneaux->rendement = AMORPHE_REND + 0.15;
	}
	else if(Panneaux->auto_rotation == 0)
	  Panneaux->rendement = AMORPHE_REND*2;
      }
      else
	Panneaux->rendement = AMORPHE_REND;
    break;
    
    default:
      Panneaux->rendement = 0;
      break; 
  }
}

/**
 * \name   Rendement_thermique
 * \brief  Calcul le rendement du à la temperature exterieure
 * \param  ST_SimuMeteo Jour
 * \return  rendement_thermique
 */
float Rendement_thermique(ST_SimuMeteo Jour)
{
  float rend_th;
  if(Jour.temp == TEMP_REF)
    rend_th = 1;
  else if(Jour.temp > TEMP_REF)
    rend_th = 1 - REND_TH*(Jour.temp - TEMP_REF);
  else
    rend_th = 1 + REND_TH*(TEMP_REF - Jour.temp); 

  if(rend_th > 2)
    rend_th = 1.5;
  else if(rend_th < 0.5)
    rend_th = 0.5;
  return rend_th;
}

/**
 * \name   Production_jour
 * \brief  Calcul de la production d'electricite journaliere
 * \param  ST_SimuMeteo Jour,
 * \return  Prod_jour
 */

float Prod_jour(PTR_ST_SimuMeteo Jour,ST_DonneGeo Donnees,ST_PANNEAUX Panneaux)
{
  float production;
  production = Jour->puiss_soleil*Rendement_geo(Donnees)*Panneaux.rendement*Rendement_thermique(*Jour);
  return production;
}



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
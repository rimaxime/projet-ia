/**
  * \file constantes.h
  * \brief Contient l'ensemble des constantes du programme 
  * utilisés tout au long du code
  * \author MRI BEC
  * \date 11/07/2011
  */

/**
  * \brief Macro-programmation de gestion des erreurs
  */

#ifndef CONSTANTES_H
#define CONSTANTES_H

#define ERREUR_FICHIER_NON_EXISTANT \
  fprintf(stderr, " Le fichier demandé n'existe pas - %s (%d)\r\n", __FILE__, __LINE__);

#define ERREUR_FICHIER \
  fprintf(stderr, " Erreur de lecture de fichier - %s (%d)\r\n", __FILE__, __LINE__);

#define ERREUR_MEMOIRE \
  fprintf(stderr, " Erreur d'allocation mémoire - %s (%d)\r\n", __FILE__, __LINE__);





/**
  * \brief Constantes sur les tailles maximales des chaines de caractéres & tableaux
  */
#define CMAX 200
#define TMAX 100


/**
  * \brief Constantes contenant les chemins/noms des différents fichiers
  */


/**
  * \brief Constantes meteo
  */

#define PUISSANCE_SOLEIL 1000 //La puissance solaire moyenne est de 1000W/m²

/**
  * \brief Constantes panneaux
  */

#define MONOCRISTALLIN_REND 0.16
#define POLYCRISTALLIN_REND 0.13
#define AMORPHE_REND 0.1
#define TEMP_REF 25
#define REND_TH 0.03
#define PRIX_ACHAT 0.00042
#define PRIX_VENTE 0.00012

/**
  * \brief Constantes chauffage
  */

#define TEMPERATURE_INTERIEURE 20
#define COEFF_ISOLATION_BONNE 0.8
#define COEFF_ISOLATION_NORMALE 1
#define COEFF_ISOLATION_FAIBLE 1.2
#define C0EFF_ISOLATION_NULLE 1.4

#define COEFF_CONSO_CLIM 0.3


/**
  * \brief Constantes habitations
  */

#define HABITATIONS_HAUTEUR 2.5

#endif
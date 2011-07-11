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

#define ERREUR_FICHIER_NON_EXISTANT \
  fprintf(stderr, " Le fichier demandé n'existe pas - %s (%d)\r\n", __FILE__, __LINE__);

#define ERREUR_FICHIER \
  fprintf(stderr, " Erreur de lecture de fichier - %s (%d)\r\n", __FILE__, __LINE__);

#define ERREUR_MEMOIRE \
  fprintf(stderr, " Erreur d'allocation mémoire - %s (%d)\r\n", __FILE__, __LINE__);






/**
  * \brief Constantes sur les tailles maximales des chaines de caractéres & tableaux
  */



/**
  * \brief Constantes contenant les chemins/noms des différents fichiers
  */



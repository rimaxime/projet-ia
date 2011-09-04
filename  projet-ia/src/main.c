
#include <gtk/gtk.h>
#include <stdio.h>
#include "../inc/structures.h"

#include "../inc/gestion_habitations.h"
#include "../inc/gestion_fichiers.h"
#include "../inc/liste_evenement.h"
#include "../inc/ihm_general.h"



int main()
{
  Data data;
  
 
  STR_DEPARTEMENT* tableau_departements = NULL;
  int size_tab=0;
  
  
  
  
  GtkBuilder *builder =NULL;
  builder = creationbuilder();
  
 
  data = chargement_fenetres(builder);
  data.tableau_departements = NULL;
  data.tableau_departements = RecupererInfosDepartement(tableau_departements,&size_tab);
  data = champs_habitation(builder,data,size_tab,data.tableau_departements);
  data = champs_pieces(builder, data);
  data = champ_panneaux(builder,data);
  data = champ_simulation(builder,data);
  data = champ_chauffage(builder,data);
  data = champ_equipements(builder,data);
  data = champ_calendrier(builder,data);
  data.Tableau_Equipements = NULL;
  data.Tableau_Equipements = RecupererInfosEquipements(data.Tableau_Equipements);
  data.Tableau_Geo = NULL;
  data.Tableau_Geo = RecupererInfosGeographique(data.Tableau_Geo);
  Initialisation_parametres_simulation();
  
  
  connexion_signaux(builder,data);
  /* Destroy builder */
  g_object_unref( G_OBJECT( builder ) );
  
  /* Show main window and start main loop */
  gtk_widget_show( data.window );
  gtk_main();
 return 0;
  
}
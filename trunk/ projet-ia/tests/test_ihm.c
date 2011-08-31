


#include <gtk/gtk.h>
#include <stdio.h>
#include "../inc/structures.h"

#include "../inc/gestion_habitations.h"
#include "../inc/gestion_fichiers.h"

#include "../inc/ihm_general.h"


int main()
{
  
  STR_DEPARTEMENT* tableau_departements = NULL;
  int size_tab=0;
  tableau_departements = RecupererInfosDepartement(tableau_departements,&size_tab);
  
  
  
  GtkBuilder *builder =NULL;
  builder = creationbuilder();
  Data data;
  
  
  
  
  data = chargement_fenetres(builder);
  data = champs_habitation(builder,data,size_tab,tableau_departements);
  data = champs_pieces(builder, data);
  data = champ_panneaux(builder,data);
  data = champ_chauffage(builder,data);
  if(! GTK_COMBO_BOX(data.Isolation))
    printf("champ non fonctionnel\n");
  else
    printf("combo box ok\n");
  connexion_signaux(builder,data);
  /* Destroy builder */
  g_object_unref( G_OBJECT( builder ) );
  
  /* Show main window and start main loop */
  gtk_widget_show( data.window );
  gtk_main();
 return 0;
  
}
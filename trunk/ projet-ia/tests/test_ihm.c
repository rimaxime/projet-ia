


#include <gtk/gtk.h>
#include <stdio.h>
#include "../inc/ihm_general.h"



int main()
{
  GtkBuilder *builder =NULL;
  builder = creationbuilder();
  Data data = chargement_fenetres(builder);
  /* Destroy builder */
  g_object_unref( G_OBJECT( builder ) );
  /* Show main window and start main loop */
  gtk_widget_show( data.window );
  gtk_main();
 return 0;
  
}
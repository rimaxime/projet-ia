/*
 * Compile me with:
 *  gcc -o dialog1 dialog1.c $(pkg-config --cflags --libs gtk+-2.0 gmodule-export-2.0 cairo) -Wl,--export-dynamic 
 * 
 * 
 *   gcc -Wall -g -o dialog1 dialog1.c `pkg-config --cflags --libs gtk+-2.0` -export-dynamic -Wl,--export-dynamic

 */
 
#include <gtk/gtk.h>
#include <cairo.h> 
 

typedef struct _Data Data;
struct _Data
{
    GtkWidget *quit;
    GtkWidget *about;
    GtkWidget *selection_fichier;
};
 

typedef struct _Save Save;
struct _Save
{
    GtkWidget *sauvegarde;
    GtkWidget *entry;
};
G_MODULE_EXPORT gboolean
cb_delete_event( GtkWidget *window,
                 GdkEvent  *event,
                 Data      *data )
{
    gint response = 1;
 
    /* Run dialog */
    response = gtk_dialog_run( GTK_DIALOG( data->quit ) );
    gtk_widget_hide( data->quit );
 
    return( 1 != response );
}
 
G_MODULE_EXPORT void
cb_show_about( GtkButton *button,
               Data      *data )
{
    /* Run dialog */
    gtk_dialog_run( GTK_DIALOG( data->about ) );
    gtk_widget_hide( data->about );
}

static void destroy (GtkWidget *window, gpointer data) 
{
  gtk_main_quit();
}
 
 
void play_clicked_cb (gpointer user_data)
{
  gtk_label_set_text(GTK_LABEL(user_data),"play_clicked");
}
 
static gboolean gestion_browser(GtkWidget *sauvegarde,Save *save)
{
  char *filename;
  filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (sauvegarde));
  if(filename != NULL)
    gtk_entry_set_text(GTK_ENTRY(save->entry),filename);
  return TRUE;
}  

void  on_ouvrir_activate (GtkWidget * user_data)
{ 
  gtk_widget_show(user_data);
}

static gboolean on_selection_fichier_activate(GtkWidget *sauvegarde, Save *save)
{
  fprintf(stdout,"%s\n\n",gtk_entry_get_text(GTK_ENTRY(save->entry)));
  gtk_widget_hide(save->sauvegarde);

  return TRUE;
}

void on_valider_parametres_maison_clicked(GtkWidget *combobox,GtkWidget *habitation)
{
  fprintf(stdout,"%s\n\n",gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox)));
  gtk_widget_hide(gtk_widget_get_parent(gtk_widget_get_parent(habitation)));
  gtk_main_quit();
}
static gboolean on_annuler_fichier_clicked(GtkWidget *annuler, Save *save)
{
  gtk_widget_hide(save->sauvegarde);
  return TRUE;
}


int main( int argc,char **argv )
{
    GtkBuilder *builder;
    GtkWidget  *window;
    Data        data;
    GtkWidget *quit;
    GtkWidget *label;
    gtk_init( NULL,NULL );
    GtkWidget *play;
    /* Create builder and load interface */
    builder = gtk_builder_new();
    gtk_builder_add_from_file( builder, "../ressource/ihm.glade", NULL );
 
    /* Obtain widgets that we need */
    window = GTK_WIDGET( gtk_builder_get_object( builder, "fenetre" ) );
    /* Connect callbacks */
    
    
   
    
    //IHM Ouverture fichier
    GtkWidget *sauvegarde = NULL;
    sauvegarde = GTK_WIDGET( gtk_builder_get_object( builder, "ouvrir_sauvegarde" ) );
    GtkWidget *entry = NULL;
    entry = GTK_WIDGET( gtk_builder_get_object(builder,"entry1"));
    Save save;
    save.sauvegarde = sauvegarde;
    save.entry = entry;
    GtkWidget *ouvrir = NULL;
    //ouvrir = GTK_WIDGET(gtk_builder_get_object(builder,"ouvrir"));
    //g_signal_connect(G_OBJECT(ouvrir), "activate", G_CALLBACK(ouvrir_clicked_cb), &save);
    
    g_signal_connect(G_OBJECT(sauvegarde),"selection_changed",G_CALLBACK(gestion_browser), &save);
    GtkWidget *selection_fichier = NULL;
    selection_fichier = GTK_WIDGET(gtk_builder_get_object(builder,"selection_fichier"));    
    g_signal_connect(G_OBJECT(selection_fichier),"clicked",G_CALLBACK(on_selection_fichier_activate),&save);
    GtkWidget *annuler_ouverture = NULL;
    annuler_ouverture = GTK_WIDGET(gtk_builder_get_object(builder,"annuler_fichier"));
    g_signal_connect(G_OBJECT(annuler_ouverture),"clicked",G_CALLBACK(on_annuler_fichier_clicked),&save);
    
    //parametres_habitations
    GtkWidget *Param_habitation = NULL;
    Param_habitation = GTK_WIDGET(gtk_builder_get_object(builder, "parametres_habitation"));
    gtk_builder_connect_signals( builder, NULL );
    gtk_builder_connect_signals( builder, &save );
    //drawing area
    GtkWidget *AreaMaison;
    AreaMaison = GTK_WIDGET(gtk_builder_get_object(builder, "dessin_maison"));
    
    /*GtkWidget *frame = NULL;
    frame = gtk_frame_new (NULL);
    gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);
     gtk_container_add (GTK_CONTAINER (frame), AreaMaison);*/
    cairo_t *cr;
    cr = gdk_cairo_create (AreaMaison->window);
    //cairo_clip(cr);
    //cairo_rectangle(cr, 20, 20, 120, 80);
    
    
    /* Destroy builder */
    g_object_unref( G_OBJECT( builder ) );
    /* Show main window and start main loop */
    gtk_widget_show( Param_habitation );
    gtk_main();
 
    return( 0 );
}

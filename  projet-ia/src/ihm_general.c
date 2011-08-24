


#include "../inc/ihm_general.h"

ST_HABITATIONS* Habitation = NULL;
ST_HABITATIONS* Habitation_travail = NULL;

GtkBuilder * creationbuilder()
{
  GtkBuilder *builder;
  gtk_init( NULL,NULL );
  /* Create builder and load interface */
  builder = gtk_builder_new();
  gtk_builder_add_from_file( builder, "../ressource/ihm.glade", NULL );
  return builder;  
}


Data chargement_fenetres(GtkBuilder *builder)
{
  Data data;
  data.window = GTK_WIDGET( gtk_builder_get_object( builder, "fenetre" ) );
  data.sauvegarde = GTK_WIDGET(gtk_builder_get_object(builder, "ouvrir_sauvegarde"));
  data.habitation = GTK_WIDGET(gtk_builder_get_object(builder,"parametres_habitation"));
  gtk_builder_connect_signals(builder, NULL);
  return data;
}


void  on_ouvrir_activate (GtkWidget * user_data)
{ 
  gtk_widget_show(user_data);
}

void on_selection_fichier_activate(GtkWidget *entry)
{
  //Habitation = charger_sauvegarde(gtk_entry_get_text(GTK_ENTRY(entry))); A developeer
  gtk_widget_hide(gtk_widget_get_parent(gtk_widget_get_parent(entry)));;
}

void on_annuler_fichier_clicked(GtkWidget *widget)
{
  gtk_widget_hide(widget);
}

void on_annuler_parametres_maison_clicked(GtkWidget *widget)
{
  Habitation_travail = Habitation;
  gtk_widget_hide(widget);
}

void on_valider_parametres_maison_clicked(GtkWidget *widget)
{
  Habitation = Habitation_travail;
  gtk_widget_hide(widget);
}

void on_parametres_maison_clicked(GtkWidget *widget)
{
  gtk_widget_show(widget);
}





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
  data.piece = GTK_WIDGET(gtk_builder_get_object(builder,"creation_piece"));
  return data;
}

Data champs_habitation(GtkBuilder *builder, Data data, int size_tab, STR_DEPARTEMENT Tableau[])
{
  data.Departement_habitation = GTK_WIDGET( gtk_builder_get_object( builder, "departement" ) );
  int i = 0;
  GtkTreeIter iter;
  GtkListStore *store;
  store = gtk_list_store_new(1,G_TYPE_STRING);
  for(i=0;i<size_tab;i++)
  {
    gtk_list_store_prepend(store,&iter);
    gtk_list_store_set(store, &iter,0, Tableau[i].nom_departement, -1);
  }
  gtk_combo_box_set_model(GTK_COMBO_BOX(data.Departement_habitation),GTK_TREE_MODEL(store));
  data.Inclinaison_habitation = GTK_WIDGET( gtk_builder_get_object( builder,"inclinaison_toit"));
  data.Exposition_habitation = GTK_WIDGET( gtk_builder_get_object( builder, "exposition_sud" ) );
  data.Isolation = GTK_WIDGET( gtk_builder_get_object( builder, "Isolation" ) );
  
  return data;
}

Data champs_pieces(GtkBuilder *builder, Data data)
{
  data.NomPiece = GTK_WIDGET(gtk_builder_get_object(builder,"nom_piece"));
  data.TypePiece = GTK_WIDGET(gtk_builder_get_object(builder,"type_piece"));
  data.LargeurPiece = GTK_WIDGET(gtk_builder_get_object(builder,"largeur_piece"));
  data.LongueurPiece = GTK_WIDGET(gtk_builder_get_object(builder,"longueur_piece"));
  return data;
}



void connexion_signaux(GtkBuilder *builder, Data data)
{
  gtk_builder_connect_signals(builder, &data);
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
  gtk_widget_hide(widget);
}

void on_valider_parametres_maison_clicked(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter,iter2;
  gchar *string_isol = NULL;
  gchar *string_dept = NULL;
  GtkTreeModel *model;
  GtkTreeModel *model2;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->Isolation),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->Isolation));
    gtk_tree_model_get(model, &iter, 0, &string_isol, -1);  }  
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->Departement_habitation),&iter2)){
    model2 = gtk_combo_box_get_model(GTK_COMBO_BOX(data->Departement_habitation));
    gtk_tree_model_get(model2, &iter2, 0, &string_dept, -1);}

  
  
  GtkAdjustment *adjust;
  gdouble inclinaison = 0;
  gdouble exposition = 0;
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->Inclinaison_habitation)); 
  inclinaison = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->Exposition_habitation)); 
  exposition = gtk_adjustment_get_value(adjust);

  
  
  if(Habitation == NULL)
  {
     
     Habitation = CreationHabitation(0,
				     inclinaison,
				     string_isol,
				     exposition,
				     string_dept);
  }   
  else
    Habitation = CreationHabitation(Habitation->nombre_pieces,
				    inclinaison,
				    string_isol,
				    exposition,
				    string_dept);
  gtk_widget_hide(data->habitation);
}

void on_parametres_maison_clicked(GtkWidget *widget, Data *data)
{
  gtk_widget_show(widget);
}


void on_creer_piece_clicked(GtkWidget *Widget, Data *data)
{
  gtk_entry_set_text(GTK_ENTRY(data->NomPiece),"");
  GtkAdjustment *adjust;
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->LargeurPiece)); 
  gtk_adjustment_set_value(adjust,0);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->LongueurPiece)); 
  gtk_adjustment_set_value(adjust,0);
  gtk_widget_show(data->piece);
 
  
}

void on_annuler_piece_clicked(GtkWidget *widget,Data *data)
{
 gtk_widget_hide(data->piece); 
  
}


void on_valider_piece_clicked(GtkWidget *widget,Data *data)
{
  GtkAdjustment *adjust;
  gdouble largeur = 0;
  gdouble longueur = 0;
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->LargeurPiece)); 
  largeur = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->LongueurPiece)); 
  longueur = gtk_adjustment_get_value(adjust);
  gchar* Nom_piece = NULL;
  Nom_piece = gtk_entry_get_text(GTK_ENTRY(data->NomPiece));
  
  
  GtkTreeIter iter;
  gchar *string_type = NULL;
  int extraction;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->TypePiece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->TypePiece));
    gtk_tree_model_get(model, &iter, 0, &string_type, -1);  }
  extraction = atoi(strtok(string_type," "));
  
  ST_PIECES * Nouvelle = NULL;
  Nouvelle = CreationPiece(Nom_piece,extraction,largeur,longueur,0,0,0,0);
  Habitation->LC_Pieces = InsererTrierPiece(Nouvelle, NULL);
 //ne fonctionne pas ! 
  gtk_widget_hide(data->piece);
 
  
}
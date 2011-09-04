/*Signaux crees : 
 * on_stop_clicked
 * on_accelerer_clicked
 * on_ralentir_clicked
 * on_exporter_donnees_clicked
 * on_exporter_graphique_clicked
 * on_exporter_maison_clicked
 * on_courbe1_configure_event
 * on_courbe1_expose_event
 * on_courbe2_configure_event
 * on_courbe2_expose_event
 * */

#include "../inc/ihm_general.h"

static ST_HABITATIONS* Habitation = NULL;
ST_PARAMETRES_SIMULATION Parametres_simulation;
static ST_JOUR * tete = NULL;

static cairo_surface_t *surface_habitation = NULL;
static cairo_surface_t *surface_courbe1 = NULL;
//test pause
int test_pause = 0;

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
  data.modificationpiece = GTK_WIDGET(gtk_builder_get_object(builder,"modification_piece"));
  data.supprimerpiece = GTK_WIDGET(gtk_builder_get_object(builder,"suppression_piece"));
  data.panneausolaires = GTK_WIDGET(gtk_builder_get_object(builder,"parametres_panneaux_solaires"));
  data.chauffage = GTK_WIDGET(gtk_builder_get_object(builder,"parametres_chauffag"));
  data.equipements = GTK_WIDGET(gtk_builder_get_object(builder,"parametres_equipements"));
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
  data.popup_habitation = GTK_WIDGET( gtk_builder_get_object( builder, "popup_habitation" ) );
  
  
  //test a supprimer
  data.DA_Habitation = GTK_WIDGET( gtk_builder_get_object( builder, "dessin_maison" ) );
  
  gtk_widget_set_sensitive(data.DA_Habitation,FALSE);
  data.Jour = NULL;
  
  return data;
}

Data champs_pieces(GtkBuilder *builder, Data data)
{
  data.NomPiece = GTK_WIDGET(gtk_builder_get_object(builder,"nom_piece"));
  data.TypePiece = GTK_WIDGET(gtk_builder_get_object(builder,"type_piece"));
  data.LargeurPiece = GTK_WIDGET(gtk_builder_get_object(builder,"largeur_piece"));
  data.LongueurPiece = GTK_WIDGET(gtk_builder_get_object(builder,"longueur_piece"));
  
 
  
  data.ModificationNomPiece = GTK_WIDGET(gtk_builder_get_object(builder,"modification_nom_piece"));
  data.ModificationTypePiece = GTK_WIDGET(gtk_builder_get_object(builder,"modification_type_piece"));
  data.ModificationLargeurPiece = GTK_WIDGET(gtk_builder_get_object(builder,"modification_largeur_piece"));
  data.ModificationLongueurPiece = GTK_WIDGET(gtk_builder_get_object(builder,"modification_longueur_piece"));
  
  
  data.SuppressionNomPiece = GTK_WIDGET(gtk_builder_get_object(builder,"suppression_nom_piece"));
  
  return data;
}


Data champ_panneaux(GtkBuilder *builder, Data data)
{
 data.type_panneau = GTK_WIDGET(gtk_builder_get_object(builder,"type_panneaux"));
 data.mppt = GTK_WIDGET(gtk_builder_get_object(builder,"mppt"));
 data.autorotation = GTK_WIDGET(gtk_builder_get_object(builder,"autorotation"));
 data.largeur_panneau = GTK_WIDGET(gtk_builder_get_object(builder,"largeur_panneau"));
 data.longueur_panneau = GTK_WIDGET(gtk_builder_get_object(builder,"longueur_panneau"));
 data.inclinaison_panneau = GTK_WIDGET(gtk_builder_get_object(builder,"inclinaison_panneau"));
 return data;
 
}

Data champ_chauffage(GtkBuilder *builder, Data data)
{
  data.bois = GTK_WIDGET(gtk_builder_get_object(builder,"chauffage_bois"));
  data.electricite = GTK_WIDGET(gtk_builder_get_object(builder,"chauffage_electricite"));
  data.gaz = GTK_WIDGET(gtk_builder_get_object(builder,"chauffage_gaz"));
  data.climatisation = GTK_WIDGET(gtk_builder_get_object(builder,"climatisation"));
  data.popup_chauffage = GTK_WIDGET(gtk_builder_get_object(builder,"popup_chauffage"));
  return data;
}

Data champ_equipements(GtkBuilder *builder, Data data)
{
  data.Tableau_Equipements = NULL;
  data.liste_equipements_possible = GTK_WIDGET(gtk_builder_get_object(builder,"arbre_equipement_possible"));
  data.liste_equipements_piece = GTK_WIDGET(gtk_builder_get_object(builder,"arbre_equipement_piece"));
  data.equipements_piece = GTK_WIDGET(gtk_builder_get_object(builder,"equipement_piece"));
  
    
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;


  col = gtk_tree_view_column_new();
  gtk_tree_view_column_set_title(col, "Idents");
  gtk_tree_view_append_column(GTK_TREE_VIEW(data.liste_equipements_possible), col);

  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  gtk_tree_view_column_add_attribute(col, renderer, 
      "text", 0);

  col = gtk_tree_view_column_new();
  gtk_tree_view_column_set_title(col, "Idents");
  gtk_tree_view_append_column(GTK_TREE_VIEW(data.liste_equipements_piece), col);

  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  gtk_tree_view_column_add_attribute(col, renderer, 
      "text", 0);
  
  //data.selection_equipement_possible = gtk_tree_view_get_selection(GTK_TREE_VIEW(data.liste_equipements_possible));
  //data.selection_equipement_piece = gtk_tree_view_get_selection(GTK_TREE_VIEW(data.liste_equipements_piece));
  

  
  return data;
}

Data champ_calendrier(GtkBuilder *builder, Data data)
{
 data.label_date_debut = GTK_WIDGET(gtk_builder_get_object(builder,"date_debut"));
 data.label_date_fin = GTK_WIDGET(gtk_builder_get_object(builder,"date_fin"));
 data.calendrier_debut = GTK_WIDGET(gtk_builder_get_object(builder,"calendar1"));
 data.calendrier_fin = GTK_WIDGET(gtk_builder_get_object(builder,"calendar2"));
 return data;
  
}

Data champ_simulation(GtkBuilder *builder, Data data)
{
  data.label_jour = GTK_WIDGET( gtk_builder_get_object( builder, "jour" ) );
  data.image_meteo = GTK_WIDGET( gtk_builder_get_object( builder, "meteo" ) );
  data.da_conso = GTK_WIDGET( gtk_builder_get_object( builder, "courbe1" ) );
  data.da_prod = GTK_WIDGET( gtk_builder_get_object( builder, "courbe2" ) );
  data.generer_rapport = GTK_WIDGET( gtk_builder_get_object( builder, "exporter_donnees" ) );
  data.entry_sauvegarde = GTK_WIDGET( gtk_builder_get_object( builder, "entry1" ) );
  return data;
}

void Initialisation_parametres_simulation()
{
  Parametres_simulation.date_initiale.Jour = 0;
  Parametres_simulation.date_initiale.Mois = 0;
  Parametres_simulation.date_initiale.Annee = 0;
  Parametres_simulation.date_finale.Jour = 0;
  Parametres_simulation.date_finale.Mois = 0;
  Parametres_simulation.date_finale.Annee = 0;
  Parametres_simulation.date_courante.Jour = 0;
  Parametres_simulation.date_courante.Mois = 0;
  Parametres_simulation.date_courante.Annee = 0;
  Parametres_simulation.vitesse = 3;
  Parametres_simulation.modification_habitation = 0;
  Parametres_simulation.modification_date = 0;
  
}

void connexion_signaux(GtkBuilder *builder, Data data)
{
  gtk_builder_connect_signals(builder, &data);
}



void  on_ouvrir_activate (GtkWidget * user_data)
{ 
  gtk_widget_show(user_data);
}


/**
 * @TODO Récupération du chemin, récupération du nom de fichier, strcat( ,".sol"), lancement de la sauvegarde
 * */
void on_selection_fichier_clicked(GtkWidget *widget,Data *data)
{
  gchar * string_path = NULL;
  //Habitation = charger_sauvegarde(gtk_entry_get_text(GTK_ENTRY(entry))); A developeer
  string_path = gtk_file_chooser_get_current_folder_uri(GTK_FILE_CHOOSER(data->sauvegarde));
  gchar* nom_fichier = NULL;
  nom_fichier = gtk_entry_get_text(GTK_ENTRY(data->entry_sauvegarde));
  strcat(string_path,nom_fichier);
  strcat(string_path,".sol");
  save_simu(Habitation, &(Parametres_simulation), tete,string_path);
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
  gchar *string_ihm_dpt = NULL;
  gchar *string_ihm_isolation = NULL;
  int extraction=0;
  GtkTreeModel *model;
  GtkTreeModel *model2;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->Isolation),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->Isolation));
    gtk_tree_model_get(model, &iter, 0, &string_isol, -1);  
    extraction = atoi(strtok(string_isol," "));
    string_ihm_isolation = gtk_tree_model_get_string_from_iter(model,&iter);} 
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->Departement_habitation),&iter2)){
    model2 = gtk_combo_box_get_model(GTK_COMBO_BOX(data->Departement_habitation));
    gtk_tree_model_get(model2, &iter2, 0, &string_dept, -1);
    string_ihm_dpt = gtk_tree_model_get_string_from_iter(model2,&iter2);
  }

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
				     (extraction-1),
				     exposition,
				     string_dept,
				     string_ihm_dpt,
				     string_ihm_isolation
				    );
  }   
  else
    Habitation = ModifierHabitation(Habitation,
				    Habitation->nombre_pieces,
				    inclinaison,
				    (extraction-1),
				    exposition,
				    string_dept,
				    string_ihm_dpt,
				    string_ihm_isolation
 				  );
    if(Parametres_simulation.date_courante.Jour != 0)
    {
     Parametres_simulation.modification_habitation = 1;  
    }
  gtk_widget_hide(data->habitation);
}

void on_parametres_maison_clicked(GtkWidget *widget, Data *data)
{
  gtk_widget_show(data->habitation);
 if(Habitation != NULL)
  {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GtkAdjustment *adjust;
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->Departement_habitation));
    if(gtk_tree_model_get_iter_from_string(model,&iter,Habitation->Departement_ihm))
      gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->Departement_habitation),&iter);
    adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->Inclinaison_habitation)); 
    gtk_adjustment_set_value(adjust,Habitation->inclinaison_toit);
   
    adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->Exposition_habitation)); 
    gtk_adjustment_set_value(adjust,Habitation->Exposition);
    
    
  }
}


void on_creer_piece_clicked(GtkWidget *Widget, Data *data)
{
  
  if(Habitation != NULL)
  {
    gtk_entry_set_text(GTK_ENTRY(data->NomPiece),"");
    GtkAdjustment *adjust;
    adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->LargeurPiece)); 
    gtk_adjustment_set_value(adjust,0);
    adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->LongueurPiece)); 
    gtk_adjustment_set_value(adjust,0);
	GtkTreeModel *model;
	GtkTreeIter iter;
	model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->TypePiece));
	if(gtk_tree_model_get_iter_first(model,&iter))
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->TypePiece),&iter);
    gtk_widget_show(data->piece);
  }
    else
      gtk_widget_show(data->popup_habitation);
  
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
  gchar* string_type_ihm = NULL;
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
    gtk_tree_model_get(model, &iter, 0, &string_type, -1);
    string_type_ihm = gtk_tree_model_get_string_from_iter(model,&iter);
  }
  extraction = atoi(strtok(string_type," "));
  ST_PIECES * Nouvelle = NULL;
  Nouvelle = CreationPiece(Nom_piece,extraction,largeur,longueur,0,0,0,0,string_type_ihm);
  Habitation->LC_Pieces = InsererTrierPiece(Nouvelle, Habitation->LC_Pieces);
  Habitation->nombre_pieces = Habitation->nombre_pieces + 1;
  if(Parametres_simulation.date_courante.Jour != 0)
    {
     Parametres_simulation.modification_habitation = 1;  
    }
  gtk_widget_hide(data->piece);
  gtk_widget_set_sensitive(data->DA_Habitation,TRUE);
 
}

void on_modifier_piece_clicked(GtkWidget *widget, Data *data)
{
  if(Habitation != NULL && Habitation->LC_Pieces != NULL)
  {
    GtkTreeIter iter;
    GtkListStore *store;
    ST_PIECES* test_piece = NULL;
    test_piece = Habitation->LC_Pieces;
    store = gtk_list_store_new(1,G_TYPE_STRING);
    while(test_piece != NULL)
    {
      gtk_list_store_prepend(store,&iter);
      gtk_list_store_set(store, &iter,0, test_piece->nom_piece, -1);
      test_piece = test_piece->suiv;
    }
    gtk_combo_box_set_model(GTK_COMBO_BOX(data->ModificationNomPiece),GTK_TREE_MODEL(store));
    GtkAdjustment *adjust;
    adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->ModificationLargeurPiece)); 
    gtk_adjustment_set_value(adjust,0);
    adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->ModificationLongueurPiece)); 
    gtk_adjustment_set_value(adjust,0);
	GtkTreeModel *model;
	model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->ModificationTypePiece));
	if(gtk_tree_model_get_iter_first(model,&iter))
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter);
    gtk_widget_set_sensitive(data->ModificationTypePiece,FALSE);
    gtk_widget_set_sensitive(data->ModificationLargeurPiece,FALSE);
    gtk_widget_set_sensitive(data->ModificationLongueurPiece,FALSE);
  
    gtk_widget_show(data->modificationpiece);
  }
  else
    gtk_widget_show(data->popup_habitation);
}

void on_valider_modification_piece_clicked(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_nom_piece = NULL;
  gchar *string_type = NULL;
  gchar *string_type_ihm = NULL;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->ModificationNomPiece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->ModificationNomPiece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  
  int extraction;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->ModificationTypePiece));
    gtk_tree_model_get(model, &iter, 0, &string_type, -1);
    string_type_ihm = gtk_tree_model_get_string_from_iter(model,&iter);
  }
  extraction = atoi(strtok(string_type," "));

  GtkAdjustment *adjust;
  gdouble largeur = 0;
  gdouble longueur = 0;
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->ModificationLargeurPiece)); 
  largeur = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->ModificationLongueurPiece)); 
  longueur = gtk_adjustment_get_value(adjust);
  
  ST_PIECES * Piece = NULL;
  Piece = Trouver_Piece(Habitation->LC_Pieces, string_nom_piece);
  if(Piece == NULL)
  {
	fprintf(stderr,"Erreur de travail sur la liste de pièces");
	exit(-1);
  }
  else
    Piece = ModifierPiece(Piece,extraction,largeur,longueur,string_type_ihm);
  if(Parametres_simulation.date_courante.Jour != 0)
    {
     Parametres_simulation.modification_habitation = 1;  
    }
  gtk_widget_hide(data->modificationpiece);

}


void on_valider_suppression_piece_clicked(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_nom_piece = NULL;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->SuppressionNomPiece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->SuppressionNomPiece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  ST_PIECES * Piece = NULL;
  Piece = Trouver_Piece(Habitation->LC_Pieces, string_nom_piece);
  if(Piece == NULL)
  {
	fprintf(stderr,"Erreur de travail sur la liste de pièces");
	exit(-1);
  }
  else
  {
	Detruire_Equipements(Piece->LC_Equipements);
        Habitation->LC_Pieces = Supprimer_Piece(Habitation->LC_Pieces, string_nom_piece);
	gtk_widget_hide(data->supprimerpiece);
  }
}

void on_supprimer_piece_clicked(GtkWidget *widget, Data *data)
{
  if(Habitation != NULL && Habitation->LC_Pieces != NULL)
  {
   GtkTreeIter iter;
	GtkListStore *store;
	ST_PIECES* test_piece = NULL;
	test_piece = Habitation->LC_Pieces;
	store = gtk_list_store_new(1,G_TYPE_STRING);
	while(test_piece != NULL)
	{
      gtk_list_store_prepend(store,&iter);
      gtk_list_store_set(store, &iter,0, test_piece->nom_piece, -1);
	test_piece = test_piece->suiv;
	}
	gtk_combo_box_set_model(GTK_COMBO_BOX(data->SuppressionNomPiece),GTK_TREE_MODEL(store));

	gtk_widget_show(data->supprimerpiece);
  }	
  else
    gtk_widget_show(data->popup_habitation);
}


void on_modification_nom_piece_changed(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_nom_piece = NULL;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->ModificationNomPiece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->ModificationNomPiece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  if(strcasecmp(string_nom_piece,"") != 0)
  {
    ST_PIECES * Piece = NULL;
    Piece = Trouver_Piece(Habitation->LC_Pieces, string_nom_piece);
    if(Piece == NULL)
    {
	  fprintf(stderr,"Erreur de travail sur la liste de pièces");
	  exit(-1);
    }
    else
    {
	  GtkAdjustment *adjust;
	  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->ModificationLargeurPiece)); 
	  gtk_adjustment_set_value(adjust,Piece->Largeur);
	  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->ModificationLongueurPiece)); 
	  gtk_adjustment_set_value(adjust,Piece->Longueur);
	  
	
    
      model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->ModificationTypePiece));
      if(gtk_tree_model_get_iter_from_string(model,&iter,Piece->type_piece_ihm))
        gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter);
	  
	  
	  gtk_widget_set_sensitive(data->ModificationTypePiece,TRUE);
	  gtk_widget_set_sensitive(data->ModificationLargeurPiece,TRUE);
	  gtk_widget_set_sensitive(data->ModificationLongueurPiece,TRUE);
    }
  } 
  else
  {
    gtk_widget_set_sensitive(data->ModificationTypePiece,FALSE);
	gtk_widget_set_sensitive(data->ModificationLargeurPiece,FALSE);
	gtk_widget_set_sensitive(data->ModificationLongueurPiece,FALSE);
  }
}


void on_creer_panneau_clicked(GtkWidget *widget, Data *data)
{
  if(Habitation != NULL)
  {
   gtk_widget_show(data->panneausolaires); 
   if(Habitation->LC_Panneaux != NULL)
   {
	 GtkTreeIter iter;
     GtkTreeModel *model;
	 model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->mppt));
	 if(gtk_tree_model_get_iter_from_string(model,&iter,Habitation->LC_Panneaux->MPPT_ihm))
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->mppt),&iter);
	
	 model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->autorotation));
	 if(gtk_tree_model_get_iter_from_string(model,&iter,Habitation->LC_Panneaux->auto_rotation_ihm))
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->autorotation),&iter);
	 model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->type_panneau));
	 if(gtk_tree_model_get_iter_from_string(model,&iter,Habitation->LC_Panneaux->type_ihm))
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->type_panneau),&iter);
	 
	 GtkAdjustment *adjust;
	 adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->largeur_panneau)); 
	 gtk_adjustment_set_value(adjust,Habitation->LC_Panneaux->Largeur);
	 adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->longueur_panneau)); 
	 gtk_adjustment_set_value(adjust,Habitation->LC_Panneaux->Longueur);
   }
  }  

}



void on_valider_panneau_clicked(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_type = NULL;
  gchar *string_mppt = NULL;
  gchar *string_autorotation = NULL;
  gchar *string_mppt_ihm = NULL;
  gchar *string_type_ihm = NULL;
  gchar *string_autorotation_ihm = NULL;
  GtkTreeModel *model;
  int mppt =1,autorotation = 1;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->mppt),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->mppt));
    gtk_tree_model_get(model, &iter, 0, &string_mppt, -1);
    string_mppt_ihm = gtk_tree_model_get_string_from_iter(model,&iter);
    
  }
  if(strcasecmp(string_mppt,"Oui") == 0)
    mppt = 0;
  else
    mppt = 1;
    
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->autorotation),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->autorotation));
    gtk_tree_model_get(model, &iter, 0, &string_autorotation, -1);  
    string_autorotation_ihm = gtk_tree_model_get_string_from_iter(model,&iter); 
  }
  if(strcasecmp(string_autorotation,"Oui") == 0)
    autorotation = 0;
  else
    autorotation = 1;  
    
  int extraction_type;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->type_panneau),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->type_panneau));
    gtk_tree_model_get(model, &iter, 0, &string_type, -1); 
    string_type_ihm = gtk_tree_model_get_string_from_iter(model,&iter);
  }
  extraction_type = atoi(strtok(string_type," "));

  GtkAdjustment *adjust;
  gdouble largeur = 0;
  gdouble longueur = 0;
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->largeur_panneau)); 
  largeur = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->longueur_panneau)); 
  longueur = gtk_adjustment_get_value(adjust);

  
  if(Habitation->LC_Panneaux == NULL)
  {
    Habitation->LC_Panneaux = CreationPanneaux(1, extraction_type, largeur,longueur, Habitation->inclinaison_toit,Habitation->Exposition,string_type_ihm,
					       string_autorotation_ihm,string_mppt_ihm);
    
  }
  else
    Habitation->LC_Panneaux = ModifierPanneaux( Habitation->LC_Panneaux, extraction_type, largeur,longueur, Habitation->inclinaison_toit,Habitation->Exposition,string_type_ihm,
					       string_autorotation_ihm,string_mppt_ihm);
   
  if(Parametres_simulation.date_courante.Jour != 0)
    {
     Parametres_simulation.modification_habitation = 1;  
    }
  gtk_widget_hide(data->panneausolaires);    
  
}


void on_parametres_chauffage_clicked(GtkWidget *widget, Data *data)
{
  if(Habitation != NULL)
  {
    gtk_widget_show(data->chauffage);  
	if(Habitation->chauffage_bois != 0 || Habitation->chauffage_gaz != 0 || Habitation->chauffage_electricite != 0)
	{
	 GtkAdjustment *adjust;
	 GtkTreeModel *model;
	 GtkTreeIter iter;
	 adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->bois)); 
	 gtk_adjustment_set_value(adjust,Habitation->chauffage_bois);
	 gtk_adjustment_set_upper(adjust,100 - Habitation->chauffage_gaz - Habitation->chauffage_electricite);
	 adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->gaz)); 
	 gtk_adjustment_set_value(adjust,Habitation->chauffage_gaz);
	 gtk_adjustment_set_upper(adjust,100 - Habitation->chauffage_bois - Habitation->chauffage_electricite);
	 adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->electricite)); 
	 gtk_adjustment_set_value(adjust,Habitation->chauffage_electricite);
	 gtk_adjustment_set_upper(adjust,100 - Habitation->chauffage_bois - Habitation->chauffage_gaz);
	 model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->climatisation));
	 if(gtk_tree_model_get_iter_from_string(model,&iter,Habitation->climatisation_ihm))
            gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->climatisation),&iter);
	 
	}
  }  
}

void on_chauffage_bois_value_changed(GtkWidget *widget, Data *data)
{
  GtkAdjustment *adjust_bois;
  GtkAdjustment *adjust_gaz;
  GtkAdjustment *adjust_electricite;
  adjust_gaz = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->gaz)); 
  adjust_bois = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->bois)); 
  adjust_electricite = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->electricite)); 
  gtk_adjustment_set_upper(adjust_bois,100 - gtk_adjustment_get_value(adjust_gaz) - gtk_adjustment_get_value(adjust_electricite)); 
  gtk_adjustment_set_upper(adjust_gaz,100 - gtk_adjustment_get_value(adjust_bois) - gtk_adjustment_get_value(adjust_electricite));
  gtk_adjustment_set_upper(adjust_electricite,100 - gtk_adjustment_get_value(adjust_bois) - gtk_adjustment_get_value(adjust_gaz));
}

void on_chauffage_gaz_value_changed(GtkWidget *widget, Data *data)
{
  GtkAdjustment *adjust_bois;
  GtkAdjustment *adjust_gaz;
  GtkAdjustment *adjust_electricite;
  adjust_gaz = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->gaz)); 
  adjust_bois = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->bois)); 
  adjust_electricite = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->electricite)); 
  gtk_adjustment_set_upper(adjust_bois,100 - gtk_adjustment_get_value(adjust_gaz) - gtk_adjustment_get_value(adjust_electricite)); 
  gtk_adjustment_set_upper(adjust_gaz,100 - gtk_adjustment_get_value(adjust_bois) - gtk_adjustment_get_value(adjust_electricite));
  gtk_adjustment_set_upper(adjust_electricite,100 - gtk_adjustment_get_value(adjust_bois) - gtk_adjustment_get_value(adjust_gaz));
}

void on_chauffage_electricite_value_changed(GtkWidget *widget, Data *data)
{
  GtkAdjustment *adjust_bois;
  GtkAdjustment *adjust_gaz;
  GtkAdjustment *adjust_electricite;
  adjust_gaz = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->gaz)); 
  adjust_bois = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->bois)); 
  adjust_electricite = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->electricite)); 
  gtk_adjustment_set_upper(adjust_bois,100 - gtk_adjustment_get_value(adjust_gaz) - gtk_adjustment_get_value(adjust_electricite)); 
  gtk_adjustment_set_upper(adjust_gaz,100 - gtk_adjustment_get_value(adjust_bois) - gtk_adjustment_get_value(adjust_electricite));
  gtk_adjustment_set_upper(adjust_electricite,100 - gtk_adjustment_get_value(adjust_bois) - gtk_adjustment_get_value(adjust_gaz));
}

void on_valider_chauffage_clicked(GtkWidget *widget, Data *data)
{
  GtkAdjustment *adjust;
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->bois)); 
  Habitation->chauffage_bois = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->gaz)); 
  Habitation->chauffage_gaz = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->electricite)); 
  Habitation->chauffage_electricite = gtk_adjustment_get_value(adjust);
  
  GtkTreeIter iter;
  gchar *string_climatisation = NULL;
  gchar *string_climatisation_ihm = NULL;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->climatisation),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->climatisation));
    gtk_tree_model_get(model, &iter, 0, &string_climatisation, -1); 
    string_climatisation_ihm = gtk_tree_model_get_string_from_iter(model,&iter); 
  }
  if(strcasecmp(string_climatisation,"Oui") == 0)
    Habitation->climatisation = 0;
  else
    Habitation->climatisation = 1; 
  strcpy(Habitation ->climatisation_ihm,string_climatisation_ihm);	
  if((Habitation->chauffage_bois + Habitation->chauffage_gaz + Habitation->chauffage_electricite) < 100)
	gtk_widget_show(data->popup_chauffage);
  else
    gtk_widget_hide(data->chauffage);  

  if(Parametres_simulation.date_courante.Jour != 0)
    {
     Parametres_simulation.modification_habitation = 1;  
    }
}


void on_gestion_equipements_clicked(GtkWidget *widget, Data *data)
{
  if(Habitation != NULL && Habitation->LC_Pieces != NULL)
  {
    GtkTreeIter iter;
    GtkListStore *store;
    ST_PIECES* test_piece = NULL;
    test_piece = Habitation->LC_Pieces;
    store = gtk_list_store_new(1,G_TYPE_STRING);
    while(test_piece != NULL)
    {
      gtk_list_store_prepend(store,&iter);
      gtk_list_store_set(store, &iter,0, test_piece->nom_piece, -1);
      test_piece = test_piece->suiv;
    }
    gtk_combo_box_set_model(GTK_COMBO_BOX(data->equipements_piece),GTK_TREE_MODEL(store));
	gtk_tree_view_set_model(GTK_TREE_VIEW(data->liste_equipements_possible),NULL);
	gtk_tree_view_set_model(GTK_TREE_VIEW(data->liste_equipements_piece),NULL);
	gtk_widget_show(data->equipements);
  }
  else
    printf("Popup a créer pour quand il n'y a pas de pièce créée");
	//creer popup
}

void on_equipement_piece_changed(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_nom_piece = NULL;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->equipements_piece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->equipements_piece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  if(strcasecmp(string_nom_piece,"") != 0)
  {
    ST_PIECES * Piece = NULL;
    Piece = Trouver_Piece(Habitation->LC_Pieces, string_nom_piece);
    if(Piece == NULL)
    {
	  fprintf(stderr,"Erreur de travail sur la liste de pièces");
	  exit(-1);
    }
    else
    {
	  GtkTreeIter iter_equipements;
	  GtkListStore *store;

	  

	  
	  /*store = gtk_list_store_new(1,G_TYPE_STRING);
	  while(Piece->LC_Equipements != NULL)
	  {
	    gtk_list_store_prepend(store,&iter_equipements);
	    gtk_list_store_set(store, &iter_equipements,0, Piece->LC_Equipements->nom_equipement, -1);
	    Piece->LC_Equipements = Piece->LC_Equipements->suiv;
	  }
	  gtk_tree_view_set_model(GTK_TREE_VIEW(data->liste_equipements_piece),GTK_TREE_MODEL(store));
	  
	  store = gtk_list_store_new(1,G_TYPE_STRING);*/
	  
	  
	  ST_EQUIPEMENTS *Test = NULL;
	  
	  Test = Piece->LC_Equipements;
	  GtkTreeIter iter_equipements_piece;
	  
	  GtkTreeStore *treestore;

	  treestore = gtk_tree_store_new(1,
                  G_TYPE_STRING);
	  
	  while(Test != NULL)
	  {
	     gtk_tree_store_append(treestore, &iter_equipements_piece, NULL);
	     gtk_tree_store_set(treestore, &iter_equipements_piece,
                     0,Test->nom_equipement ,-1);
            Test = Test->suiv;
	  }
	  model = GTK_TREE_MODEL(treestore);
	  gtk_tree_view_set_model(GTK_TREE_VIEW(data->liste_equipements_piece), model);

	  
	  data->selection_equipement_piece = gtk_tree_view_get_selection(GTK_TREE_VIEW(data->liste_equipements_piece));
	  
	  
	  
	  Test = &(data->Tableau_Equipements[Piece->type_piece]);
	  GtkTreeIter iter_equipements_possibles;
	  

	  treestore = gtk_tree_store_new(1,
                  G_TYPE_STRING);
	  
	  while(Test != NULL)
	  {
	     if(strcasecmp(Test->nom_equipement,"") != 0)
	     {
	       gtk_tree_store_append(treestore, &iter_equipements_possibles, NULL);
	       gtk_tree_store_set(treestore, &iter_equipements_possibles,
                     0,Test->nom_equipement ,-1);
	     }
            Test = Test->suiv;
	  }
	  model = GTK_TREE_MODEL(treestore);
	  gtk_tree_view_set_model(GTK_TREE_VIEW(data->liste_equipements_possible), model);

	  
	  data->selection_equipement_possible = gtk_tree_view_get_selection(GTK_TREE_VIEW(data->liste_equipements_possible));
	  
	}
  }
}


void on_ajouter_equipement_clicked(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_nom_piece = NULL;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->equipements_piece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->equipements_piece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  if(strcasecmp(string_nom_piece,"") != 0)
  {
    ST_PIECES * Piece = NULL;
    Piece = Trouver_Piece(Habitation->LC_Pieces, string_nom_piece);
    if(Piece == NULL)
    {
	  fprintf(stderr,"Erreur de travail sur la liste de pièces");
	  exit(-1);
    }
    else
    {
	  GtkTreeIter iter;
      gchar *value=NULL;
      if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data->selection_equipement_possible), &model, &iter)) 
	  {
		gtk_tree_model_get(model, &iter, 0, &value,  -1);
	        GtkTreeStore *treestore;

	        treestore = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(data->liste_equipements_piece)));
		 gtk_tree_store_append(treestore, &iter, NULL);
	          gtk_tree_store_set(treestore, &iter,
                     0,value ,-1);
		
	  }	  
	}
  }
}

void on_supprimer_equipement_clicked(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_nom_piece = NULL;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->equipements_piece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->equipements_piece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  if(strcasecmp(string_nom_piece,"") != 0)
  {
    ST_PIECES * Piece = NULL;
    Piece = Trouver_Piece(Habitation->LC_Pieces, string_nom_piece);
    if(Piece == NULL)
    {
	  fprintf(stderr,"Erreur de travail sur la liste de pièces");
	  exit(-1);
    }
    else
    {
	  GtkTreeIter iter;
      
      if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data->selection_equipement_piece), &model, &iter)) 
	  {
		
		 GtkTreeStore *treestore;
	        treestore = GTK_TREE_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(data->liste_equipements_piece)));
		gtk_tree_store_remove(treestore, &iter);
	  }	  
	}
  }
}

void on_valider_equipement_clicked(GtkWidget *widget, Data *data)
{
  
  GtkTreeModel *model;
  GtkTreeIter iter;
  gchar *value = NULL;
  gchar *string_nom_piece = NULL;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->equipements_piece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->equipements_piece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  if(strcasecmp(string_nom_piece,"") != 0)
  {
    ST_PIECES * Piece = NULL;
    Piece = Trouver_Piece(Habitation->LC_Pieces, string_nom_piece);
    if(Piece == NULL)
    {
	  fprintf(stderr,"Erreur de travail sur la liste de pièces");
	  exit(-1);
    }
    else
    {
	  ST_EQUIPEMENTS *Test = NULL;
	  Detruire_Equipements(Piece->LC_Equipements);
	  Piece->LC_Equipements = NULL;
	  int trouve = 0;
      //if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data->selection_equipement_piece), &model, &iter)) 
	  {
	        model = gtk_tree_view_get_model(GTK_TREE_VIEW(data->liste_equipements_piece));
		//gtk_tree_model_get(model, &iter, 0, &value,  -1);
		if(gtk_tree_model_get_iter_first(model,&iter))
		{
		  do
		  {
		    Test = &(data->Tableau_Equipements[Piece->type_piece]);
		    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);
		       while(Test != NULL && trouve == 0)
			{
			  if(strcasecmp(string_nom_piece,Test->nom_equipement) == 0)
			  {
			        trouve = 1;
				ST_EQUIPEMENTS*nouveau = NULL;
				nouveau = CreationEquipement(Test->indice, Test->nom_equipement,Test->consommation_equipement, Test->nombre_heures_utilisation_journalier,
				  Test->Largeur,Test->Longueur, Test->coordX1,Test->coordX2, Test->coordY1, Test->coordY2);
				Piece->LC_Equipements = InsererTrierEquipements(nouveau, Piece->LC_Equipements);
			  }
			  Test = Test->suiv;
			}  
		    trouve = 0;
		  }while(gtk_tree_model_iter_next(model,&iter));
		
		}
	  }
	}
  }
  if(Parametres_simulation.date_courante.Jour != 0)
    {
     Parametres_simulation.modification_habitation = 1;  
    }
  gtk_widget_hide(data->equipements);
}


void on_calendar1_day_selected_double_click(GtkWidget *widget, Data *data)
{
  char str[CMAX];
  guint day, month,year;
  if(Parametres_simulation.date_initiale.Jour != 0)
  {
    Parametres_simulation.modification_date = 1;
  }
  gtk_calendar_get_date(GTK_CALENDAR(data->calendrier_debut),&year,&month,&day);
  sprintf(str,"Date debut : %d/%d/%d",day,month+1,year);
  gtk_label_set_text(GTK_LABEL(data->label_date_debut),str);
  Parametres_simulation.date_initiale.Jour = (int)day;
  Parametres_simulation.date_initiale.Mois = (int)month+1;
  Parametres_simulation.date_initiale.Annee = (int)year;
  
}

void on_calendar2_day_selected_double_click(GtkWidget *widget, Data *data)
{
  char str[CMAX];
  guint day, month,year;
  if(Parametres_simulation.date_finale.Jour != 0 && Parametres_simulation.modification_date == 0)
  {
    Parametres_simulation.modification_date = 2;
  }
  gtk_calendar_get_date(GTK_CALENDAR(data->calendrier_fin),&year,&month,&day);
  sprintf(str,"Date fin : %d/%d/%d",day,month+1,year);
  gtk_label_set_text(GTK_LABEL(data->label_date_fin),str);
  Parametres_simulation.date_finale.Jour = (int)day;
  Parametres_simulation.date_finale.Mois = (int)month+1;
  Parametres_simulation.date_finale.Annee = (int)year;
  
}

void on_play_clicked(GtkWidget *widget, Data *data)
{
 
 //test_stop = 0;
 test_pause =0;
 char str[CMAX];
   GTimer *time;
   gulong micro;
 if(Habitation == NULL || Habitation->LC_Pieces == NULL || Habitation->LC_Panneaux == NULL)
 {
   printf("L'habitation doit etre concu avant la simulation. Ainsi que les dates de simulation selectionnee.\n");
   return;
 }
 if(Parametres_simulation.date_courante.Jour == 0)
 {
   
   
   if(Parametres_simulation.date_initiale.Jour != 0 && Parametres_simulation.date_finale.Jour != 0)
   {
    if(Habitation != NULL && Habitation->LC_Pieces != NULL && Habitation->LC_Panneaux != NULL)
    {
      STR_DEPARTEMENT *departement_actuel = NULL;
      departement_actuel = parseur_departement(data->tableau_departements,Habitation->Departement);
      ST_DonneGeo *Donnee_geo = NULL;
      Donnee_geo = parseur_donnees_geo(data->Tableau_Geo,Habitation->inclinaison_toit,Habitation->Exposition);
      data->Jour = creer_liste_jours(Parametres_simulation.date_initiale,Parametres_simulation.date_finale,*Habitation,*Donnee_geo ,*departement_actuel, NULL);
      Parametres_simulation.date_courante = Parametres_simulation.date_initiale;
    }
   }
 } 
 else if(Parametres_simulation.modification_habitation == 1)
    {
      STR_DEPARTEMENT *departement_actuel = NULL;
      departement_actuel = parseur_departement(data->tableau_departements,Habitation->Departement);
      ST_DonneGeo *Donnee_geo = NULL;
      Donnee_geo = parseur_donnees_geo(data->Tableau_Geo,Habitation->inclinaison_toit,Habitation->Exposition);
      supprimer_liste_jour(Parametres_simulation.date_courante, Parametres_simulation.date_finale, &(data->Jour));
      data->Jour = creer_liste_jours(Parametres_simulation.date_courante,Parametres_simulation.date_finale,*Habitation,*Donnee_geo ,*departement_actuel, NULL);
      Parametres_simulation.modification_habitation = 0;
    }  
  else if(Parametres_simulation.modification_date == 2)
  {
     STR_DEPARTEMENT *departement_actuel = NULL;
      departement_actuel = parseur_departement(data->tableau_departements,Habitation->Departement);
      ST_DonneGeo *Donnee_geo = NULL;
      Donnee_geo = parseur_donnees_geo(data->Tableau_Geo,Habitation->inclinaison_toit,Habitation->Exposition);
      supprimer_liste_jour(Parametres_simulation.date_courante, Parametres_simulation.date_finale, &(data->Jour));
      data->Jour = creer_liste_jours(Parametres_simulation.date_courante,Parametres_simulation.date_finale,*Habitation,*Donnee_geo ,*departement_actuel, NULL);
      Parametres_simulation.modification_date = 0;
  
  }
  else if(Parametres_simulation.modification_date == 1)
  {
      STR_DEPARTEMENT *departement_actuel = NULL;
      departement_actuel = parseur_departement(data->tableau_departements,Habitation->Departement);
      ST_DonneGeo *Donnee_geo = NULL;
      Donnee_geo = parseur_donnees_geo(data->Tableau_Geo,Habitation->inclinaison_toit,Habitation->Exposition);
      supprimer_liste_jour(Parametres_simulation.date_courante, Parametres_simulation.date_finale, &(data->Jour));
      data->Jour = creer_liste_jours(Parametres_simulation.date_initiale,Parametres_simulation.date_finale,*Habitation,*Donnee_geo ,*departement_actuel, NULL);
      Parametres_simulation.date_courante = Parametres_simulation.date_initiale;
      Parametres_simulation.modification_date = 0;
  }
  time = g_timer_new();
      g_timer_start(time);
      if(tete == NULL)
	tete = data->Jour;
      while(comparaison_date(Parametres_simulation.date_courante,Parametres_simulation.date_finale) <= 0 && test_pause == 0)
       {
	 if(g_timer_elapsed(time,&micro) >= Parametres_simulation.vitesse )
	 {
	 g_timer_start(time);
         
	 sprintf(str,"%d/%d/%d\nTemperature moyenne : %f\nConsommation : %2.2f W\nProduction : %2.2f W",data->Jour->date.Jour,data->Jour->date.Mois,
											      data->Jour->date.Annee,data->Jour->temperature,
											      data->Jour->consommation,data->Jour->production);
	 printf("%d/%d/%d\nTemperature moyenne : %f\nConsommation : %f W\nProduction : %f W\n",data->Jour->date.Jour,data->Jour->date.Mois,
											      data->Jour->date.Annee,data->Jour->temperature,
											      data->Jour->consommation,data->Jour->production);
	 gtk_label_set_text(GTK_LABEL(data->label_jour),str);
	   
	 switch(data->Jour->condition)
	 {
	   case 0:
	     gtk_image_set_from_file(GTK_IMAGE(data->image_meteo),"../ressource/icone_meteo/sunny.png");
	     break;
	     
	   case 1:
	     gtk_image_set_from_file(GTK_IMAGE(data->image_meteo),"../ressource/icone_meteo/partly-cloudy-day-icon350.png");
	     break;
	     
	   case 2:
	     gtk_image_set_from_file(GTK_IMAGE(data->image_meteo),"../ressource/icone_meteo/rain-icon.png");
	     break;
	   
	   case 3:
	     gtk_image_set_from_file(GTK_IMAGE(data->image_meteo),"../ressource/icone_meteo/thunder-icon.png");
	     break;
	     
	   case 4:
	     gtk_image_set_from_file(GTK_IMAGE(data->image_meteo),"../ressource/icone_meteo/snow-icon.png");
	     break; 
	 }
	     
	 //gtk_main_iteration();
  if(Parametres_simulation.date_courante.Mois == 12 && Parametres_simulation.date_courante.Jour ==31)
	{
     Parametres_simulation.date_courante.Mois = 1;
     Parametres_simulation.date_courante.Jour =1;
     Parametres_simulation.date_courante.Annee = Parametres_simulation.date_courante.Annee + 1;
	}
  else if(Parametres_simulation.date_courante.Mois % 2 != 1 && Parametres_simulation.date_courante.Jour == 31)
   {
    Parametres_simulation.date_courante.Mois = Parametres_simulation.date_courante.Mois + 1;
    Parametres_simulation.date_courante.Jour = 1;
   }
   else if((Parametres_simulation.date_courante.Mois == 2 && Parametres_simulation.date_courante.Jour == 28) ||(Parametres_simulation.date_courante.Mois % 2 == 1 && Parametres_simulation.date_courante.Jour == 30))
   {
     Parametres_simulation.date_courante.Mois = Parametres_simulation.date_courante.Mois + 1;
     Parametres_simulation.date_courante.Jour = 1;
   }
   else
     Parametres_simulation.date_courante.Jour = Parametres_simulation.date_courante.Jour + 1;
   
      data->Jour = data->Jour->suiv;
      
       }
       (gtk_main_iteration());
      }
     
    
   
 }

void on_pause_clicked(GtkWidget *widget, Data *data)
{
 test_pause = 1;
}


void on_accelerer_clicked()
{
  if(Parametres_simulation.vitesse >1)
    Parametres_simulation.vitesse = Parametres_simulation.vitesse - 1;
}

void on_ralentir_clicked()
{
  if(Parametres_simulation.vitesse <5)
    Parametres_simulation.vitesse = Parametres_simulation.vitesse + 1;
}

void on_stop_clicked()
{
  Parametres_simulation.date_courante.Jour = 0;
  Parametres_simulation.date_courante.Mois = 0;
  Parametres_simulation.date_courante.Annee = 0;
  test_pause = 1;
}

void on_courbe1_configure_event(GtkWidget *widget, GdkEventConfigure *event)
{
    cairo_t *cr = NULL;
    
  if(surface_courbe1)
  {
    cairo_surface_destroy(surface_courbe1);
  }
  surface_courbe1 = gdk_window_create_similar_surface(widget->window, 
					      CAIRO_CONTENT_COLOR,
					      widget->allocation.width,
					      widget->allocation.height);
  cr = cairo_create(surface_courbe1);
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);
   cairo_set_source_rgb(cr,0,0,0);
   cairo_set_line_width (cr, 0.5);
  cairo_move_to(cr,20, 20);
  cairo_line_to(cr, 100, 20);
 
  
  cairo_destroy(cr);
  
     GdkRectangle update;
  memset(&update,0,sizeof(GdkRectangle));  
    
    update.x = 20 ;
    update.y = 20 ;
    update.width = 200;
    update.height = 0.5;  
    cr =cairo_create(surface_courbe1);
    cairo_set_source_rgb(cr,0,0,0);  
    gdk_cairo_rectangle(cr, &update );
    
    
     //cairo_rectangle(cr,event->x,event->y,10,10);  
    cairo_fill(cr);
    cairo_destroy(cr);
    gdk_window_invalidate_rect(widget->window,
			       &update,
			       FALSE);
  
  
}

void on_courbe1_expose_event(GtkWidget *da,GdkEventExpose *event)
{
  //a manager ! 
 cairo_t *cr = NULL;
 cr = gdk_cairo_create(da->window);
 cairo_set_source_surface(cr,surface_courbe1,0,0);
 gdk_cairo_rectangle(cr, &event->area);
 cairo_fill(cr);
 cairo_destroy(cr);
 

}

  

void on_dessin_maison_configure_event(GtkWidget *widget, GdkEventConfigure *event)
{
  cairo_t *cr = NULL;
  
  if(surface_habitation)
  {
    cairo_surface_destroy(surface_habitation);
  }
  surface_habitation = gdk_window_create_similar_surface(widget->window, 
					      CAIRO_CONTENT_COLOR,
					      widget->allocation.width,
					      widget->allocation.height);
  cr = cairo_create(surface_habitation);
  cairo_set_source_rgb(cr,1,1,1);
  cairo_paint(cr);
  cairo_destroy(cr);
}


void on_dessin_maison_expose_event(GtkWidget *da,GdkEventExpose *event)
{
  //a manager ! 
 cairo_t *cr = NULL;
 cr = gdk_cairo_create(da->window);
 cairo_set_source_surface(cr,surface_habitation,0,0);
 gdk_cairo_rectangle(cr, &event->area);
 cairo_fill(cr);
 cairo_destroy(cr);
}

void on_dessin_maison_button_press_event(GtkWidget *da,GdkEventButton *event,Data *data)
{

  if(event->button == 1)
  {
      GdkRectangle update;
  memset(&update,0,sizeof(GdkRectangle));  
  cairo_t *cr = NULL;
   
   
    update.x = event->x ;
    update.y = event->y ;
    update.width = 200;
    update.height = 300;  
    cr =cairo_create(surface_habitation);
    cairo_set_source_rgb(cr,0,0,0);  
    gdk_cairo_rectangle(cr, &update );
    
    
     //cairo_rectangle(cr,event->x,event->y,10,10);  
    cairo_fill(cr);
    cairo_destroy(cr);
    gdk_window_invalidate_rect(da->window,
			       &update,
			       FALSE);
    gtk_widget_set_sensitive(data->DA_Habitation,FALSE);
  }
}

void on_dessin_maison_motion_notify_event(GtkWidget *da,GdkEventMotion *event)
{
 int x,y;
  GdkRectangle update;
 GdkModifierType state = 0;
 gdk_window_get_pointer(event->window,&x,&y,&state);
  if(state && GDK_BUTTON1_MASK)
  {
   printf("entrée2\n");
  cairo_t *cr = NULL;
  cr = gdk_cairo_create(da->window);
   update.x = 0;
  update.y = 0;
  update.width = 600;
  update.height = 600;
gdk_cairo_rectangle(cr, &update);
 cairo_clip(cr);
 cairo_set_source_rgb(cr,0.45777,0,0.45777);
 cairo_rectangle(cr,event->x,event->y,10,10);
 cairo_fill(cr);
 cairo_destroy(cr);
    
    
  }
  
}


int comparaison_date(ST_Date date1,ST_Date date2)
{
  if(date1.Annee < date2.Annee || (date1.Annee == date2.Annee && date1.Mois < date2.Mois) || (date1.Annee == date2.Annee && date1.Mois == date2.Mois
                                                                                              && date1.Jour < date2.Jour))
    return -1;
  else if(date1.Annee == date2.Annee && date1.Mois == date2.Mois && date1.Jour == date2.Jour)
    return 0;
  else 
    return 1;
}

void on_exporter_donnees_clicked(GtkWidget *widget, Data *data)
{
  Exporter_Evenement_Fichier(tete,"../ressource/rapport_donnees.txt");
}

void on_menu_rapport_activate(GtkWidget *widget, Data *data)
{
  Exporter_Evenement_Fichier(data->Jour,"../ressource/rapport_donnees.txt");
}


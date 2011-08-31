


#include "../inc/ihm_general.h"

ST_HABITATIONS* Habitation = NULL;


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
  
  data.selection_equipement_possible = gtk_tree_view_get_selection(GTK_TREE_VIEW(data.liste_equipements_possible));
  data.selection_equipement_piece = gtk_tree_view_get_selection(GTK_TREE_VIEW(data.liste_equipements_piece));
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
    Habitation = ModifierHabitation(Habitation,
					Habitation->nombre_pieces,
				    inclinaison,
				    string_isol,
				    exposition,
				    string_dept);
  gtk_widget_hide(data->habitation);
}

void on_parametres_maison_clicked(GtkWidget *widget, Data *data)
{
  gtk_widget_show(widget);
  if(Habitation != NULL)
  {
	GtkTreeIter iter;
    GtkTreeModel *model;
	model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->Departement_habitation));
	if(gtk_tree_model_get_iter_from_string(model,&iter,Habitation->Departement)
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->Departement_habitation),&iter);
	
	model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->Isolation));
	if(gtk_tree_model_get_iter_from_string(model,&iter,Habitation->Isolation)
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->Isolation),&iter);
	
	adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->Inclinaison_habitation)); 
    gtk_adjustment_set_value(adjust,Habitation->inclinaison_toit);
	
	adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->Exposition_habitation)); 
    gtk_adjustment_set_value(adjust,Habitation->Exposition).
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
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->TypePiece),iter);
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
  Habitation->LC_Pieces = InsererTrierPiece(Nouvelle, Habitation->LC_Pieces);
  Habitation->nombre_pieces = Habitation->nombre_pieces + 1;
  gtk_widget_hide(data->piece);
 
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
	GtkTreeIter iter;
	model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->ModificationTypePiece));
	if(gtk_tree_model_get_iter_first(model,&iter))
		gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),iter);
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
  gchar *string_type;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->ModificationNomPiece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->ModificationNomPiece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  
  int extraction;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->ModificationTypePiece));
    gtk_tree_model_get(model, &iter, 0, &string_type, -1);  }
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
	fprintf(stderr,"Erreur de travail sur la liste de pi�ces");
	exit(-1);
  }
  else
    Piece = ModifierPiece(Piece,extraction,largeur,longueur);
	
  gtk_widget_hide(data->modificationpiece);

}


void on_valider_suppression_piece_clicked(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_nom_piece = NULL;
  gchar *string_type;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->SuppressionNomPiece),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->SuppressionNomPiece));
    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);  }
  ST_PIECES * Piece = NULL;
  Piece = Trouver_Piece(Habitation->LC_Pieces, string_nom_piece);
  if(Piece == NULL)
  {
	fprintf(stderr,"Erreur de travail sur la liste de pi�ces");
	exit(-1);
  }
  else
  {
	Detruire_Equipements(Piece->LC_Equipements);
        Supprimer_Piece(Habitation->LC_Pieces, string_nom_piece);
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
  gchar *string_type;
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
	  fprintf(stderr,"Erreur de travail sur la liste de pi�ces");
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
	  switch(Piece->type_piece)
	  {
		case 1:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"1 Chambre")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter);
				break;
		case 2:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"2 Salon/Salle � manger")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter);
				break;
				
		case 3:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"3 Cuisine")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter);
				break;
		
		case 4:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"4 Salle de bain")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter);
				break;
		
		case 5:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"5 Toilettes")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter);
				break;
				
		case 6:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"6 Buanderie")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->ModificationTypePiece),&iter);
				break;
	  }
	  
	  
	  
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
	 switch(Habitation->LC_Panneaux->MPPT)
	 {
		case 1:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"Oui")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->mppt),&iter);
				break;
		
		case 2:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"Non")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->mppt),&iter);
				break;
     }
	 model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->autorotation));
	 switch(Habitation->LC_Panneaux->auto_rotation)
	 {
		case 1:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"Oui")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->autorotation),&iter);
				break;
		
		case 2:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"Non")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->autorotation),&iter);
				break;
     }
	 model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->type_panneau));
	 switch(Habitation->LC_Panneaux->type)
	 {
		case 1:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"1 Monocristallins")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->type),&iter);
				break;
		
		case 2:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"2 Polycristallins")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->type),&iter);
				break;
		
		case 3:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"3 Amorphes")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->type),&iter);
				break;				
     }
	 GtkAdjustment *adjust;
	 adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->largeur_panneau)); 
	 gtk_adjustment_set_value(adjust,Habitation->LC_Panneaux->Largeur);
	 adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->longueur_panneau)); 
	 gtk_adjustment_set_value(adjust,Habitation->LC_Panneaux->Longueur);
	 adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->inclinaison_panneau)); 
	 gtk_adjustment_set_value(adjust,Habitation->LC_Panneaux->inclinaison_panneau);
   }
  }  

}



void on_valider_panneau_clicked(GtkWidget *widget, Data *data)
{
  GtkTreeIter iter;
  gchar *string_type = NULL;
  gchar *string_mppt = NULL;
  gchar *string_autorotation = NULL;
  GtkTreeModel *model;
  int mppt =1,autorotation = 1;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->mppt),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->mppt));
    gtk_tree_model_get(model, &iter, 0, &string_mppt, -1);  }
  if(strcasecmp(string_mppt,"Oui") == 0)
    mppt = 1;
  else
    mppt = 2;
    
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->autorotation),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->autorotation));
    gtk_tree_model_get(model, &iter, 0, &string_autorotation, -1);  }
  if(strcasecmp(string_autorotation,"Oui") == 0)
    autorotation = 1;
  else
    autorotation = 2;  
    
  int extraction_type;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->type_panneau),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->type_panneau));
    gtk_tree_model_get(model, &iter, 0, &string_type, -1);  }
  extraction_type = atoi(strtok(string_type," "));

  GtkAdjustment *adjust;
  gdouble largeur = 0;
  gdouble longueur = 0;
  gdouble inclinaison = 0;
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->largeur_panneau)); 
  largeur = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->longueur_panneau)); 
  longueur = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->inclinaison_panneau)); 
  inclinaison = gtk_adjustment_get_value(adjust);
  
  if(Habitation->LC_Panneaux == NULL)
  {
    Habitation->LC_Panneaux = CreationPanneaux(1, extraction_type, largeur,longueur, inclinaison,Habitation->Exposition);
    
  }
  else
    Habitation->LC_Panneaux = ModifierPanneaux( Habitation->LC_Panneaux, extraction_type, largeur,longueur, inclinaison,Habitation->Exposition);
   
  
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
	 switch(Habitation->climatisation)
	 {
		case 1:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"Oui")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->climatisation),&iter);
				break;
		
		case 2:
				if(gtk_tree_model_get_iter_from_string(model,&iter,"Non")
					gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->climatisation),&iter);
				break;
     }
	 
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
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->bois)); 
  Habitation->chauffage_bois = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->gaz)); 
  Habitation->chauffage_gaz = gtk_adjustment_get_value(adjust);
  adjust = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(data->electricite)); 
  Habitation->chauffage_electricite = gtk_adjustment_get_value(adjust);
  
  GtkTreeIter iter;
  gchar *string_climatisation = NULL;
  GtkTreeModel *model;
  if(gtk_combo_box_get_active_iter(GTK_COMBO_BOX(data->climatisation),&iter)){
    model = gtk_combo_box_get_model(GTK_COMBO_BOX(data->climatisation));
    gtk_tree_model_get(model, &iter, 0, &string_climatisation, -1);  }
  if(strcasecmp(string_autorotation,"Oui") == 0)
    Habitation->climatisation = 1;
  else
    Habitation->climatisation = 2; 
	
  if((Habitation->chauffage_bois + Habitation->chauffage_gaz + Habitation->chauffage_electricite) < 100)
	gtk_widget_show(data->popup_chauffage);
  else
    gtk_widget_hide(data->chauffage);  
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
	gtk_combo_box_set_model(GTK_COMBO_BOX(data->liste_equipements_possible),NULL);
	gtk_combo_box_set_model(GTK_COMBO_BOX(data->liste_equipements_piece),NULL);
	gtk_widget_show(data->equipements);
  }
  else
    printf("Popup a cr�er pour quand il n'y a pas de pi�ce cr��e");
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
	  fprintf(stderr,"Erreur de travail sur la liste de pi�ces");
	  exit(-1);
    }
    else
    {
	  GtkTreeIter iter_equipements;
      GtkListStore *store;
	  store = gtk_list_store_new(1,G_TYPE_STRING);
	  while(Piece->LC_Equipements != NULL)
	  {
	    gtk_list_store_prepend(store,&iter_equipements);
        gtk_list_store_set(store, &iter_equipements,0, Piece->LC_Equipements->nom_equipement, -1);
        Piece->LC_Equipements = Piece->LC_Equipements->suiv;
	  }
	  gtk_tree_view_set_model(GTK_TREE_VIEW(data->liste_equipements_piece),store);
	  GtkTreeIter iter_equipements_possibles;
	  store = gtk_list_store_new(1,G_TYPE_STRING);
	  ST_EQUIPEMENTS *Test = NULL;
	  Test = data->Tableau_Equipements[Piece->type_piece];
	  while(Test != NULL)
	  {
		gtk_list_store_prepend(store,&iter_equipements_possibles);
        gtk_list_store_set(store, &iter_equipements_possibles,0, Test->nom_equipement, -1);
        Test = Test->suiv;
	  }
	  gtk_tree_view_set_model(GTK_TREE_VIEW(data->liste_equipements_possible),store);
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
	  fprintf(stderr,"Erreur de travail sur la liste de pi�ces");
	  exit(-1);
    }
    else
    {
	  GtkTreeIter iter;
      gchar *value=NULL;
      if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data->selection_equipement_possible), &model, &iter)) 
	  {
		gtk_tree_model_get(model, &iter, 0, &value,  -1);
		GtkListStore *store;
		store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(data->liste_equipements_piece)));
		gtk_list_store_append(store, &iter);
		gtk_list_store_set(store, &iter, 0, value, -1);
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
	  fprintf(stderr,"Erreur de travail sur la liste de pi�ces");
	  exit(-1);
    }
    else
    {
	  GtkTreeIter iter;
      gchar *value=NULL;
      if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data->selection_equipement_piece), &model, &iter)) 
	  {
		
		GtkListStore *store;
		store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(data->liste_equipements_piece)));
		gtk_list_store_remove(store, &iter);
	  }	  
	}
}

void on_valider_equipement_clicked(GtkWidget *widget, Data *data)
{
  
  GtkTreeModel *model;
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
	  fprintf(stderr,"Erreur de travail sur la liste de pi�ces");
	  exit(-1);
    }
    else
    {
	  ST_EQUIPEMENTS *Test = NULL;
	  Test = data->Tableau_Equipements[Piece->type_piece];
	  Detruire_Equipements(Piece->LC_Equipements);
	  int trouve = 0;
      if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(data->selection_equipement_possible), &model, &iter)) 
	  {
		gtk_tree_model_get(model, &iter, 0, &value,  -1);
		if(gtk_tree_model_get_iter_first(model,&iter))
		{
		  do
		  {
		    gtk_tree_model_get(model, &iter, 0, &string_nom_piece, -1);
		    while(Test != NULL && trouve = 0)
			{
			  if(strcasecmp(string_nom_piece,Test->nom_equipement) == 0)
			  {
			    trouve = 1;
				Piece->LC_Equipements = InsererTrierEquipements(Test->nom_equipement, Piece->LC_Equipements);
			  }
			}  
		  }while(gtk_tree_model_iter_next(model,&iter));
		
		}
	  }
	}
  }
  gtk_widget_hide(data->equipements);
}

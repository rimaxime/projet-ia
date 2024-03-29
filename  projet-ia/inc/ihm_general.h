

#ifndef IHM_GENERAL_H
#define IHM_GENERAL_H
#include <gtk/gtk.h>
#include "../inc/structures.h"
#include "../inc/gestion_habitations.h"
#include "../inc/liste_evenement.h"
#include "../inc/gestion_fichiers.h"
#define PATH_IHM "../ressources/ihm.glade"

typedef struct _Data Data;
struct _Data
{
	//fenetres
    GtkWidget *window;
    GtkWidget *sauvegarde;
    GtkWidget *habitation;
    GtkWidget *piece;
    GtkWidget *popup_habitation;
    GtkWidget *modificationpiece;
    GtkWidget *supprimerpiece;
    GtkWidget *panneausolaires;
    GtkWidget *chauffage;
	GtkWidget *equipements;
	
    //champs habitation
    GtkWidget *Departement_habitation;
    GtkWidget *Inclinaison_habitation;
    GtkWidget *Exposition_habitation;
    GtkWidget *Isolation;
    STR_DEPARTEMENT* tableau_departements;
    
    //champs piece
    GtkWidget *NomPiece;
    GtkWidget *TypePiece;
    GtkWidget *LargeurPiece;
    GtkWidget *LongueurPiece;
    
	//champs Modification Piece
    GtkWidget *ModificationNomPiece;
    GtkWidget *ModificationTypePiece;
    GtkWidget *ModificationLargeurPiece;
    GtkWidget *ModificationLongueurPiece;
	
    //champs Suppression Piece
    GtkWidget *SuppressionNomPiece;

    
    //Champs Panneaux solaires

    GtkWidget *type_panneau;
    GtkWidget *mppt;
    GtkWidget *autorotation;
    GtkWidget *largeur_panneau;
    GtkWidget *longueur_panneau;
    GtkWidget *inclinaison_panneau;
    
    
    //champs chauffage
    GtkWidget *bois;
    GtkWidget *gaz;
    GtkWidget *electricite;
    GtkWidget *climatisation;
    GtkWidget *popup_chauffage;
	
	//Gestion des équipements
	ST_EQUIPEMENTS *Tableau_Equipements;
	GtkWidget *liste_equipements_possible;
	GtkWidget *liste_equipements_piece;
	GtkWidget *equipements_piece;
	GtkTreeSelection *selection_equipement_possible;
	GtkTreeSelection *selection_equipement_piece;
	
	
  //champ calendrier
  GtkWidget *label_date_debut;
  GtkWidget *label_date_fin;
  GtkWidget *calendrier_debut;
  GtkWidget *calendrier_fin;
  

  //tests image
  GtkWidget *image_meteo;
  
  //Da habitation
  GtkWidget *DA_Habitation;
  
  //Gestion de la file : 
  
  ST_JOUR* Jour;
  ST_DonneGeo *Tableau_Geo;
  
  GtkWidget *label_jour;
  GtkWidget *da_conso;
  GtkWidget *da_prod;
  
  GtkWidget *entry_sauvegarde;
  GtkWidget *generer_rapport;
};




GtkBuilder * creationbuilder();

Data chargement_fenetres(GtkBuilder *builder);

void Initialisation_parametres_simulation();

void on_ouvrir_activate (GtkWidget * user_data);

void on_annuler_fichier_clicked(GtkWidget *widget);

void on_selection_fichier_activate(GtkWidget *widget,Data *data);

void on_annuler_fichier_clicked(GtkWidget *widget);

void on_annuler_parametres_maison_clicked(GtkWidget *widget);

void on_valider_parametres_maison_clicked(GtkWidget *widget, Data *data);

void on_parametres_maison_clicked(GtkWidget *widget, Data *data);

Data champs_habitation(GtkBuilder *builder, Data data, int size_tab, STR_DEPARTEMENT Tableau[]);

void connexion_signaux(GtkBuilder *builder, Data data);

void on_Isolation_changed(GtkWidget *combo, Data *data);

Data champs_pieces(GtkBuilder *builder, Data data);

void on_creer_piece_clicked(GtkWidget *Widget, Data *data);

void on_annuler_piece_clicked(GtkWidget *widget,Data *data);

void on_valider_piece_clicked(GtkWidget *widget,Data *data);

void on_modifier_piece_clicked(GtkWidget *widget, Data *data);

void on_valider_modification_piece_clicked(GtkWidget *widget, Data *data);

void on_supprimer_piece_clicked(GtkWidget *widget, Data *data);

void on_modification_nom_piece_changed(GtkWidget *widget, Data *data);

Data champ_panneaux(GtkBuilder *builder, Data data);

void on_creer_panneau_clicked(GtkWidget *widget, Data *data);

void on_valider_panneau_clicked(GtkWidget *widget, Data *data);

void on_parametres_chauffage_clicked(GtkWidget *widget, Data *data);

void on_chauffage_bois_value_changed(GtkWidget *widget, Data *data);

void on_chauffage_gaz_value_changed(GtkWidget *widget, Data *data);

void on_chauffage_electricite_value_changed(GtkWidget *widget, Data *data);

void on_valider_chauffage_clicked(GtkWidget *widget, Data *data);

Data champ_chauffage(GtkBuilder *builder, Data data);


Data champ_equipements(GtkBuilder *builder, Data data);

void on_gestion_equipements_clicked(GtkWidget *widget, Data *data);

void on_equipement_piece_changed(GtkWidget *widget, Data *data);

void on_ajouter_equipement_clicked(GtkWidget *widget, Data *data);

void on_supprimer_equipement_clicked(GtkWidget *widget, Data *data);

Data champ_calendrier(GtkBuilder *builder, Data data);

void on_calendar1_day_selected_double_click(GtkWidget *widget, Data *data);

Data champ_simulation(GtkBuilder *builder, Data data);

int comparaison_date(ST_Date date1,ST_Date date2);

void affichage_jour(Data *data);

#endif
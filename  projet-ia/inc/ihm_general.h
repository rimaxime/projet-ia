

#ifndef IHM_GENERAL_H
#define IHM_GENERAL_H

#include <gtk/gtk.h>
#include "../inc/structures.h"
#include "../inc/gestion_habitations.h"


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
	
    //champs habitation
    GtkWidget *Departement_habitation;
    GtkWidget *Inclinaison_habitation;
    GtkWidget *Exposition_habitation;
    GtkWidget *Isolation;
    
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
    
    
    
};




GtkBuilder * creationbuilder();

Data chargement_fenetres(GtkBuilder *builder);


void on_ouvrir_activate (GtkWidget * user_data);

void on_annuler_fichier_clicked(GtkWidget *widget);

void on_selection_fichier_activate(GtkWidget *entry);

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
#endif
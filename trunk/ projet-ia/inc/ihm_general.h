

#ifndef IHM_GENERAL_H
#define IHM_GENERAL_H

#include <gtk/gtk.h>
#include "../inc/structures.h"

#define PATH_IHM "../ressources/ihm.glade"

typedef struct _Data Data;
struct _Data
{
    GtkWidget *window;
    GtkWidget *sauvegarde;
    GtkWidget *habitation;
};




GtkBuilder * creationbuilder();

Data chargement_fenetres(GtkBuilder *builder);


void on_ouvrir_activate (GtkWidget * user_data);

void on_annuler_fichier_clicked(GtkWidget *widget);

void on_selection_fichier_activate(GtkWidget *entry);

void on_annuler_fichier_clicked(GtkWidget *widget);

void on_annuler_parametres_maison_clicked(GtkWidget *widget);

void on_valider_parametres_maison_clicked(GtkWidget *widget);

void on_parametres_maison_clicked(GtkWidget *widget);




#endif
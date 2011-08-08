/**
  * \file gestion_habitations.c
  * \brief Crée les maisons et les différentes pièces associées
  * \author MRI
  * \date 08/08/2011
  */



ST_HABITATIONS CreationHabitation(ST_HABITATIONS Nouveau,int nombre_pieces, float inclinaison_toit, int Isolation,int Exposition)
{
  Nouveau->nombre_pieces = nombre_pieces;
  Nouveau->inclinaison_toit = inclinaison_toit;
  Nouveau->Isolation = Isolation;
  Nouveau->Exposition = Exposition;
  Nouveau->LC_Pieces = NULL;
  Nouveau->LC_Panneaux = NULL;  
  return Nouveau;
}


ST_PIECES CreationPiece(ST_PIECES Nouvelle, char* nom_piece, int type_piece, float Largeur, float Longueur, float coordX, float coordY)
{
  strcpy(Nouvelle->nom_piece,nom_piece);
  Nouvelle->type_piece = type_piece;
  Nouvelle->Largeur = Largeur;
  Nouvelle->Longueur = Longueur;
  Nouvelle->coordX = coordX;
  Nouvelle->coordY= coordY;
  Nouvelle->LC_Equipements = NULL;
  Nouvelle->suiv = NULL;
}


ST_PIECES InsererTrierPiece(ST_PIECES Nouvelle, ST_PIECES *Tete)
{
  if(Tete == NULL || strcasecmp(Nouvelle.nom_piece,Tete->nom_piece) <= 0)
  {
    Nouvelle->suiv = Tete;
    return Nouvelle;
  }
  else
  {
    Tete->suiv = InsererTrierPiece(Nouvelle,Tete->suiv);
    return Tete;
  }
}




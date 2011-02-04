#ifndef H_ARBRE
#define H_ARBRE

#include "define.h"
#include "graphique.h"

class arbre{

public :
      
//Constructeur et destructeur        
arbre(int x,int y);
~arbre();

//Affichage de l'arbre
void show(SDL_Surface *);

string sourceData;

//composant de l'arbre
graphique *tronc;
graphique *feuille;
graphique *sol;       
};

#endif

#ifndef H_FONT
#define H_FONT

#include "graphique.h"

class font{

public :
        graphique *gp;
        
        string sourceData;

        SDL_Rect clip[4];
        SDL_Rect pelouse;
        
        int largeur_image;
        int hauteur_image;
        int largeur;
        int hauteur;
        
       //Constructeur, Destructeur
       font(int,int);
       ~font();
       
       //Affichage du font
       void show(SDL_Surface *);
};

#endif

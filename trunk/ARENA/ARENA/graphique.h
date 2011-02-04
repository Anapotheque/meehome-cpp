#ifndef H_GRAPHIQUE
#define H_GRAPHIQUE

#include "define.h"

class graphique{

public :

//Constructeur et destructeur
graphique(int, int, string);
~graphique();

//Positionnement
SDL_Rect position;

//Gestion de l'affichage
SDL_Surface *area;

//Src de mon image
string src;
    
//Initialisation de l'objet
bool init();

//Chargement d'une image
SDL_Surface *load_image(string);
       
//Affichage de l'objet dans la fenetre
bool show(SDL_Surface *);   
bool show(SDL_Surface *,SDL_Rect);   
bool show(SDL_Surface *,SDL_Rect,SDL_Rect); 

//Deplacement de l'objet
bool move(int,int);
      
};

#endif

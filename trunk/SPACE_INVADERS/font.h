#ifndef H_FONT
#define H_FONT

#include "define.h"

class font{

private:
        //Positionnement
        SDL_Rect position;

        //Gestion de l'affichage
        SDL_Surface *area;
public :
       //Constructeur, Destructeur
       font();
       ~font();  

       //Initialisation de l'ennemy
       bool init();
       
       //Affichage de l'objet dans la fenetre
       bool show(SDL_Surface *screen);
};

#endif

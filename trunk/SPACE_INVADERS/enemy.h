#ifndef H_ENEMY
#define H_ENEMY

#include "define.h"

class enemy{

private:
        //Variable de mouvement et niveau
        int mvt_avant   ;
        int mvt_arriere ;
        int mvt         ;
        int vitesse     ;
        
        //Positionnement
        SDL_Rect position;

        //Gestion de l'affichage
        SDL_Surface *area;
public :
       //Constructeur, Destructeur
       enemy();
       ~enemy();
       
       //Mouvements latérals
       bool move();     

       //Initialisation de l'ennemy
       bool init();
       bool init(int x, int y);
       
       //Affichage de l'objet dans la fenetre
       bool show(SDL_Surface *screen);
       
       //Destruction de l'ennemy
       bool destroy();
       
       //recuperation coordonnées
       SDL_Rect get_position();
};

#endif

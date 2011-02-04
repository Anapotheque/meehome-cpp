#ifndef H_MISSILE
#define H_MISSILE

#include "define.h"

class missile{

private:
        //Positionnement
        SDL_Rect position;

        //Vitesse et acceleration
        int vitesse;
        int acceleration;

        //Gestion de l'affichage
        SDL_Surface *area;
public :
       //Constructeur, Destructeur
       missile();
       ~missile();
       
       //Mouvement du missile sur le char (mono missile)
       void move(SDL_Rect position);
       //Mouvement du missile sur le char (poly missile)
       void move(int x);
       //Mouvement du missile apres mise à feu 
       void move(); 

       //Initialisation de l'ennemy
       bool init();
       bool init(int x, int y);
       
       //Affichage de l'objet dans la fenetre
       bool show(SDL_Surface *screen);
       
       //Test la reussite du lancé de missile
       bool sucess(SDL_Rect positionEnnemy);
       bool lancer(SDL_Rect positionTank);
       bool finCourse();
       
       //recuperation coordonnées
       SDL_Rect get_position();
};

#endif

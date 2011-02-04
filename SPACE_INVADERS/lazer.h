#ifndef H_LAZER
#define H_LAZER

#include "define.h"

class lazer{

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
       lazer();
       ~lazer();
       
       //Mouvement du missile sur le char (mono missile)
       void move(SDL_Rect position);
       //Mouvement du missile sur le char (poly missile)
       void move(int x);
       //Mouvement du missile apres mise � feu 
       void move(); 

       //Initialisation de l'ennemy
       bool init();
       bool init(int x, int y);
       
       //Affichage de l'objet dans la fenetre
       bool show(SDL_Surface *screen);
       
       //Test la reussite du lanc� de missile
       bool sucess(SDL_Rect positionEnnemy);
       bool lancer(SDL_Rect positionTank);
       bool finCourse();
       
       //recuperation coordonn�es
       SDL_Rect get_position();
};

#endif

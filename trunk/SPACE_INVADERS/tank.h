#ifndef H_TANK
#define H_TANK

#include "define.h"
#include "missile.h"

class tank{

private:        
        //Positionnement
        SDL_Rect position;

        //Gestion de l'affichage
        SDL_Surface *area;
public :
       //Constructeur, Destructeur
       tank();
       ~tank();
       
       //ETAT TANK
       int missileFire;
       int mouvementG;
       int mouvementD;
       
       //Variable de tire switch
       int switchMissile;
       
       //Etat du tank
       void refresh();
       
       //Deux missiles equipe le tank
       missile missileD,missileG;
       
       //Sens de deplacement du tank et vitesse 
       int droite,gauche,stop,feu,vitesse;
       
       //Mouvements latérals   
       void mouvementGauche();
       void mouvementDroite();
       
       //Tire des missiles
       void fire();
       
       //Initialisation de l'ennemy
       bool init();
       bool init(int x, int y);
       
       //Capture des evenements
       void captureEvent(int);
       
       //Affichage de l'objet dans la fenetre
       bool show(SDL_Surface *screen);
       
       //recuperation coordonnées
       SDL_Rect get_position();
};

#endif

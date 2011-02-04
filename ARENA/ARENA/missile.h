#ifndef H_MISSILE
#define H_MISSILE

#include "define.h"

class missile{

public: 
       
int LIMIT_MAX_X;
int LIMIT_MAX_Y;  
       
//Angle de rotation
double angle;

//Acceleration
int Vx,Vy,Vr,Vitesse,Tire,Lost;

//Positionnement
SDL_Rect position;
//Gestion de l'affichage
SDL_Surface *area;

//Constructeur, destructeur
missile();
~missile();

//Initialisation de l'objet
void init(SDL_Rect);

//Affichage de l'objet dans la fenetre
void show(SDL_Surface *); 
     
//Repositionnement de l'objet
void refresh(SDL_Surface *,SDL_Rect);    

};

#endif

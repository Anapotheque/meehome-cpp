#ifndef H_ENNEMY
#define H_ENNEMY

#include "define.h"
#include "listMissile.h"
#include "missile.h"

class ennemy{

public:
       
listMissile listM;  
      
int LIMIT_MAX_X;
int LIMIT_MAX_Y;       
       
//Angle de rotation
double angle;

//Acceleration
int Vx,Vy,Vr,Vitesse,Tire,cadence;

//Positionnement
SDL_Rect position;
//Gestion de l'affichage
SDL_Surface *area;

//Constructeur, destructeur
ennemy();
~ennemy();

//Initialisation de l'objet
void init();

//Affichage de l'objet dans la fenetre
void show(SDL_Surface *); 
     
//Repositionnement de l'objet
void refresh(SDL_Surface *);    

//Mise à feu des missiles
void feu();

};

#endif

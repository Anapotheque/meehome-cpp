#ifndef H_POINT
#define H_POINT

#include "define.h"
#include "listMissile.h"
#include "missile.h"
#include "graphique.h"

class point : public graphique{

public:
 

//Constructeur, destructeur
point(int,int,char *);
~point(); 
       
listMissile listM;  
      
int LIMIT_MAX_X;
int LIMIT_MAX_Y;       

//Acceleration
int Vx,Vy,Vr,Vitesse,Tire;

//Positionnement
SDL_Rect position,positionR;
//Gestion de l'affichage
SDL_Surface *area;

//Initialisation de l'objet
void initialisation();  
     
//Repositionnement de l'objet
void refresh(SDL_Surface *);    

//Mise à feu des missile
void feu();
};

#endif

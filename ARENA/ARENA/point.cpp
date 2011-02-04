#include "point.h"

using namespace std;

//******************************************************************************
//******************************************************************************

point::point(int x, int y, char *src):graphique(x,y,src){
}

point::~point(){
}

void point::initialisation(){  
    
    //Creation de la liste de missile vide
    listM.suivant = NULL;
    
    //Initialisation des mouvements de rotations
    Vx = 0;
    Vy = 0; 
    Vr = 0; 
    Vitesse = 5;
    Tire = 0;   

    //Positionnement de l'objet sur l'ecran    
    position.x = WIDTH / 2 - area -> w / 2;
    position.y = HEIGHT / 2 - area -> h / 2;
    
    //Definition des limites du cadre
    LIMIT_MAX_X = WIDTH  - area->w - 10;
    LIMIT_MAX_Y = HEIGHT - area->h - 10;
}

//Ajout de missile à ma liste de missile
void point::feu(){
     missile *mis = new missile;
     mis->init(position);
     mis->Tire = 1;
     listM.ajoutMissile(mis);
}

//Repositionnement de l'objet
void point::refresh(SDL_Surface *screen){

     //Limite de bordure
     if( position.x < LIMIT_MIN_X )         position.x += 5;
     if( position.x > LIMIT_MAX_X )         position.x -= 5;
     if( position.y < LIMIT_MIN_Y )         position.y += 5;
     if( position.y > LIMIT_MAX_Y )         position.y -= 5;

     //Si on a appuyé sur le clavier alors on gere les mouvements
     position.x += Vx * Vitesse;
     position.y += Vy * Vitesse;
     
     show(screen);
     
     //positionR.x = position.x + area -> w / 2 + 5;
     //positionR.y = position.y + area -> h / 2 + 5;
     
     listMissile *ptr = listM.suivant;
     
     while(ptr!= NULL){       
        ptr->obj->refresh(screen,position);
        ptr = ptr->suivant;    
     }     
}

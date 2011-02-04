#include "ennemy.h"

using namespace std;

//******************************************************************************
//******************************************************************************

ennemy::ennemy(){
    //Initialisation des surfaces
    area = NULL;
}

ennemy::~ennemy(){
    //On libére la surface
    SDL_FreeSurface(area);
}

void ennemy::init(){  
    
    //Creation de la liste de missile vide
    listM.suivant = NULL;
     
    //Initialisation des mouvements de rotations
    angle = 0; 
    Vx = 5;
    Vy = 1; 
    Vr = 0; 
    Vitesse = 1;
    Tire = 0; 
    cadence = 0;  
          
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("ennemy.bmp");
    
    //Gestion de la transparence de l'image
    SDL_SetColorKey(area, SDL_SRCCOLORKEY, SDL_MapRGB(area->format, 255, 255, 255));
    
    //Transparence globale de l'objet
    SDL_SetAlpha(area, SDL_SRCALPHA, 255);
    
    //Positionnement de l'objet sur l'ecran    
    position.x = WIDTH / 2 - area -> w / 2;
    position.y = 10;
    
    //positionR.x = position.x + area -> w / 2 + 5;
    //positionR.y = position.y + area -> h / 2 + 5;
    
    //Definition des limites du cadre
    LIMIT_MAX_X = WIDTH  - area->w - 10;
    LIMIT_MAX_Y = HEIGHT  - area->h - 10;
}

void ennemy::show(SDL_Surface *screen){
    //Ajout de l'image à ma surface
    SDL_BlitSurface(area,NULL,screen,&position);	               
}

//Ajout de missile à ma liste de missile
void ennemy::feu(){
     missile *mis = new missile;
     mis->init(position);
     mis->Tire = -1;
     listM.ajoutMissile(mis);
}

//Repositionnement de l'objet
void ennemy::refresh(SDL_Surface *screen){

     //Limite de bordure
     if( position.x < LIMIT_MIN_X )         Vitesse = 1;
     if( position.x > LIMIT_MAX_X )         Vitesse = -1;

     //On arrete l'objet si il atteint les limites basses de la fenetre
     if( position.y < LIMIT_MAX_Y ){
         position.x += Vx * Vitesse;
         position.y += Vy;
         if(cadence == 10){
            feu();
            cadence = 0;
         }
         cadence++;
     }
     else{
          init();
     }

     show(screen);
     
     listMissile *ptr = listM.suivant;
     while(ptr!= NULL){       
        ptr->obj->refresh(screen,position);
        ptr = ptr->suivant;    
     }     
}

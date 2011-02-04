#include "missile.h"

using namespace std;

//******************************************************************************
//******************************************************************************

missile::missile(){
    //Initialisation des surfaces
    area = NULL;
}

missile::~missile(){
    //On libére la surface
    SDL_FreeSurface(area);
}

void missile::init(SDL_Rect pos){  
     
    //Initialisation des mouvements de rotations
    angle = 0; 
    Vx = 0;
    Vy = 1; 
    Vr = 0; 
    Vitesse = 10;
    Tire = 0;  
    Lost = 0; 
          
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("point.bmp");
    
    //Gestion de la transparence de l'image
    SDL_SetColorKey(area, SDL_SRCCOLORKEY, SDL_MapRGB(area->format, 255, 255, 255));
    
    //Transparence globale de l'objet
    SDL_SetAlpha(area, SDL_SRCALPHA, 255);
    
    //Positionnement de l'objet sur l'ecran    
    position.x = pos.x;
    position.y = pos.y;
    
    //Definition des limites du cadre
    LIMIT_MAX_X = WIDTH  - area->w - 10;
    LIMIT_MAX_Y = HEIGHT - area->h - 10;
}

void missile::show(SDL_Surface *screen){
    //Ajout de l'image à ma surface
    SDL_BlitSurface(area,NULL,screen,&position);	               
}

//******************************************************************************
//******************************************************************************

//Repositionnement de l'objet
void missile::refresh(SDL_Surface *screen,SDL_Rect pos){
     //Si on a appuyé sur le clavier alors on gere les mouvements
     if(Tire){         
     //Limite de bordure
     if( position.y < LIMIT_MIN_Y ){         
     position.y += 5;
     Lost = 1;
     }
     
     position.y -= Vy * Vitesse * Tire;
     }
     else{
     position.x = pos.x +8;
     position.y = pos.y +8;     
     }
     
     //Affichage de mon objet
     show(screen);
}

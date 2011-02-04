#include "font.h"

font::font(){
    //Initialisation des surfaces
    area = NULL;
}

font::~font(){
    //On libére la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
}

bool font::init(){       
    //Vérification de l'allocation de la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
    
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("font.bmp");
   
    //Positionnement de l'objet sur l'ecran
    position.x = 0;
    position.y = 0;
    
    //On retourne vrai si pas de pb
    return true;
}

bool font::show(SDL_Surface *screen){
    //Ajout de l'image à ma surface
    SDL_BlitSurface(area,NULL,screen,&position);	               
}

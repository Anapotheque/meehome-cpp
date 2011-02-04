#include "font.h"

font::font(){
    //Initialisation des surfaces
    area = NULL;
}

font::~font(){
    //On lib�re la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
}

bool font::init(){       
    //V�rification de l'allocation de la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
    
    //On charge l'image dans la surface associ�e
    area = SDL_LoadBMP("font.bmp");
   
    //Positionnement de l'objet sur l'ecran
    position.x = 0;
    position.y = 0;
    
    //On retourne vrai si pas de pb
    return true;
}

bool font::show(SDL_Surface *screen){
    //Ajout de l'image � ma surface
    SDL_BlitSurface(area,NULL,screen,&position);	               
}

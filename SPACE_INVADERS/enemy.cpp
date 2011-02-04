#include "enemy.h"

enemy::enemy(){
    //Initialisation des surfaces
    area = NULL;
}

enemy::~enemy(){
    //On libére la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
}

bool enemy::init(){
    // Initialisation des mouvements 
    mvt_avant     = 1;
    mvt_arriere   = -1;
    mvt           = mvt_avant;
    vitesse       = 1;
    
            
    //Vérification de l'allocation de la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
    
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("boss.bmp");
   
    //Gestion de la transparence de l'image
    SDL_SetColorKey(area, SDL_SRCCOLORKEY, SDL_MapRGB(area->format, 255, 255, 255));
    
    //Transparence globale de l'objet
    SDL_SetAlpha(area, SDL_SRCALPHA, 255);
   
    //Positionnement de l'objet sur l'ecran
    position.x = 10;
    position.y = 10;
    
    //On retourne vrai si pas de pb
    return true;
}

bool enemy::init(int x, int y){   
    // Initialisation des mouvements 
    mvt_avant     = 1;
    mvt_arriere   = -1;
    mvt           = mvt_avant;
    vitesse       = 5; 
         
    //Vérification de l'allocation de la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
    
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("boss.bmp");
   
    //Gestion de la transparence de l'image
    SDL_SetColorKey(area, SDL_SRCCOLORKEY, SDL_MapRGB(area->format, 255, 255, 255));
    
    //Transparence globale de l'objet
    SDL_SetAlpha(area, SDL_SRCALPHA, 255);
   
    //Positionnement de l'objet sur l'ecran
    position.x = x;
    position.y = y;
    
    //On retourne vrai si pas de pb
    return true;
}

bool enemy::show(SDL_Surface *screen){
    //Ajout de l'ennemy à ma surface
    SDL_BlitSurface(area,NULL,screen,&position);	               
}

SDL_Rect enemy::get_position(){
    return position;
}

bool enemy::destroy(){
}

bool enemy::move(){      
//Detection des bords de fenetre
if(position.x == WIDTH-30       && mvt == mvt_avant)     mvt = mvt_arriere;
if(position.x == 0              && mvt == mvt_arriere)   mvt = mvt_avant;

//Gestion du mouvement
position.x = position.x + mvt * vitesse; 
}

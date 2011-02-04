#include "missile.h"

using std::cout;


//Constructeur du missile
missile::missile(){
    //Initialisation des surfaces
    area = NULL;
    cout << "Missile aloué" << endl;
}

//Destructeur du missile
missile::~missile(){
    //On libére la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
    cout << "Missile detruit" << endl;
}

//Initialisation du missile
bool missile::init(){ 
     
    cout << "TEST\n";  
     
    //Initialisation de la vitesse et de l'acceleration
    vitesse = 1;
    acceleration = 1; 
           
    //Vérification de l'allocation de la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
    
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("missile.bmp");
   
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

//Initialisation du missile
bool missile::init(int x, int y){ 
     
    //Initialisation de la vitesse et de l'acceleration
    vitesse = 1;
    acceleration = 1;  
           
    //Vérification de l'allocation de la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
    
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("missile.bmp");
   
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

//Affiche le missile dans la fenetre principale
bool missile::show(SDL_Surface *screen){
    //Ajout de l'image à ma surface
    SDL_BlitSurface(area,NULL,screen,&position);	               
}

//Retourne la position courante du missile
SDL_Rect missile::get_position(){
    return position;
}

//Mouvement du missile sur le char (mono missile)
void missile::move(SDL_Rect positionAsuivre){  
    position.x = positionAsuivre.x;
    position.y = positionAsuivre.y;   
}

//Mouvement du missile sur le char (poly missile)
void missile::move(int x){  
    position.x = x; 
}

//Mouvement du missile apres mise à feu
void missile::move(){  
    position.y = position.y - (vitesse * acceleration);
    while(acceleration < 10) acceleration++;  
}

bool missile::sucess(SDL_Rect positionEnnemy){
    if(position.x >= positionEnnemy.x - 10 && 
       position.x <= positionEnnemy.x + 10 &&
       position.y == positionEnnemy.y ) return true;
    else false;    
}

bool missile::lancer(SDL_Rect positionTank){
    if(position.y != positionTank.y) return true;
    else                             return false;  
}

bool missile::finCourse(){
    if(position.y >= 0 && position.y <= 50 ) return true;
    else                                     return false;     
}

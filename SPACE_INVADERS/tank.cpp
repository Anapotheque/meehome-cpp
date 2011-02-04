#include "tank.h"

tank::tank(){
    //Initialisation des surfaces
    area = NULL;
}

tank::~tank(){
    //On libére la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
}

bool tank::init(){ 
    missileFire = 0;
    switchMissile = 0; 
     
    //Initialisation des missiles du tank 
    missileD.init(position.x-10,position.y);
    missileG.init(position.x+10,position.y); 
     
    //initialisation de variable de mouvement
    droite = 2;
    stop = 0;
    gauche = 1;
    feu = 3;
    vitesse = 10; 
      
    missileFire     = 0;
    mouvementG = 0;
    mouvementD = 0;  
           
    //Vérification de l'allocation de la surface
    if(area!=NULL)   SDL_FreeSurface(area), area = NULL;
    
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("tank.bmp");
   
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

bool tank::init(int x, int y){   
    
    missileFire     = 0;
    mouvementG      = 0;
    mouvementD      = 0; 
    switchMissile   = 0;
    stop            = 0;
    gauche          = 1;
    droite          = 2; 
    feu             = 3;
    vitesse         = 10;
   
    //Initialisation des missiles du tank 
    missileD.init(x+10,y);
    missileG.init(x-10,y);
    
    //On charge l'image dans la surface associée
    area = SDL_LoadBMP("tank.bmp");
   
    //Gestion de la transparence de l'image
    SDL_SetColorKey(area, SDL_SRCCOLORKEY, SDL_MapRGB(area->format, 255, 255, 255));
    
    //Transparence globale de l'objet
    SDL_SetAlpha(area, SDL_SRCALPHA, 255);
   
    //Positionnement de l'objet sur l'ecran
    position.x = x;
    position.y = y;

    return true;
}

//Ajout de l'image à ma surface
bool tank::show(SDL_Surface *screen){
    SDL_BlitSurface(area,NULL,screen,&position);	               
}

// Retourne la position courante du mon tank
SDL_Rect tank::get_position(){
    return position;
}

//0n fait evoluer le tank à gauche
void tank::mouvementGauche(){
     position.x = position.x - vitesse;  
}
//0n fait evoluer le tank à droite
void tank::mouvementDroite(){
     position.x = position.x + vitesse;  
} 

//Tire des missiles
void tank::fire(){
     if((missileFire == droite || missileD.lancer(position)) && !missileD.finCourse())
                    missileD.move();
     if((missileFire == gauche || missileG.lancer(position)) && !missileG.finCourse())
                    missileG.move();
}

//Etat du tank
void tank::refresh(){
    if(mouvementG){
                  mouvementGauche(); 
                  if(missileFire == gauche || missileFire == stop  && !missileD.lancer(position)){
                  missileD.move(position.x+10); 
                  }
                  if(missileFire == stop && !missileG.lancer(position)){
                  missileG.move(position.x-10);
                  }
    }
    if(mouvementD){
                  mouvementDroite();
                  if(missileFire == gauche || missileFire == stop && !missileD.lancer(position))
                          missileD.move(position.x+10); 
                  if(missileFire == stop && !missileG.lancer(position))
                          missileG.move(position.x-10);
    } 
    if(missileFire || missileD.lancer(position) || missileG.lancer(position)) fire(); 
       
    if(missileD.finCourse()){
    missileD = *new missile;
    missileD.init(position.x+10,position.y);
    missileFire = stop;
    }
    
    if(missileG.finCourse()){
    missileG = *new missile;
    missileG.init(position.x-10,position.y);
    missileFire = stop;
    }       
}

void tank::captureEvent(int mouvementCapture){
        if(mouvementCapture == feu){    
                            if(missileFire == stop)  missileFire = gauche;
                            if(missileFire == gauche)missileFire = droite ;
        }
        if(mouvementCapture == droite) mouvementD = 1;   
        if(mouvementCapture == gauche) mouvementG = 1;
        if(mouvementCapture == stop){
                            mouvementD = 0;
                            mouvementG = 0;
        } 
}




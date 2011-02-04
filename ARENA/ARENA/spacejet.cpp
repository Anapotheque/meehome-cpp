#include "spacejet.h"

//Lecture du fichier de configuration
string getFile1(string file,int iteration){
    string s;
    int i = 0;
    ifstream inputfile(file.c_str());
    while(i<iteration){
        inputfile >> s;
        i++;
    }
    return s;
}

//Constructeur
spacejet::spacejet(int x, int y){
    //Mon fichier de configuration
    sourceData = "DATA/spaceJet.txt";  
    
    //Instanciation de l'objet                
    sj = new graphique(x,y,getFile1(sourceData,2));
    sj->init();
    
    //Initialisation position et vitesse
    Vx = 0;
    Vy = 0;
    Vitesse = 1;
    
    //Configuration de l'image
    largeur_image = 380;
    hauteur_image = 75;
    largeur = largeur_image / 14;
    hauteur = hauteur_image / 2;
    
    //Configuration des changement de position
    switchingGraph = 0;
    latence = 0;
    latenceMax = 8;
    
    //Affectations des differentes positions
    int i;
    for(i = 0; i < 14; i++){
        clip[i].x = largeur*i;
        clip[i].y = 0;
        clip[i].w = largeur;
        clip[i].h = hauteur;
    }
    for(i = 0; i < 14; i++){
        clip[i+14].x = largeur*i;
        clip[i+14].y = hauteur;
        clip[i+14].w = largeur;
        clip[i+14].h = hauteur;
    }  
}

//Destruction
spacejet::~spacejet(){
    delete sj;
}

//Gestion des mouvement
void spacejet::translation(){
          
    sj->position.x += Vx * Vitesse * latence;
    sj->position.y += Vy * Vitesse * latence;
    
    //Gestion des mouvement
    mvt();
          
    if( sj->position.x < LIMIT_MIN_X ) sj->position.x += Vitesse;
    if( sj->position.x + sj->area->w/14 > LIMIT_MAX_X ) sj->position.x -= Vitesse;
    if( sj->position.y < LIMIT_MIN_Y ) sj->position.y += Vitesse;
    if( sj->position.y + sj->area->h/2 > LIMIT_MAX_Y ) sj->position.y -= Vitesse;      
}

//Gestion des mouvement
void spacejet::mvt(){
    //descend
    if(Vy > 0 && Vx == 0){
        if(switchingGraph == 6) switchingGraph = 0;  
        if(latence < latenceMax) latence++; 
        switchingGraph++;
    }
    //monte
    if(Vy < 0 && Vx == 0){
        if(switchingGraph == 13) switchingGraph = 7;  
        if(latence < latenceMax) latence++; 
        switchingGraph++;
    }
    //Droite
    if(Vx > 0 && Vy == 0){
        if(switchingGraph == 26) switchingGraph = 21; 
        if(latence < latenceMax) latence++; 
        switchingGraph++;
    }
    //Gauche
    if(Vx < 0 && Vy == 0){
        if(switchingGraph == 20) switchingGraph = 14;  
        if(latence < latenceMax) latence++; 
        switchingGraph++;
    } 
}

void spacejet::show(SDL_Surface *screen){
    translation();
    sj->show(screen,clip[switchingGraph]);
}

void spacejet::handleInput(SDL_Event event,SDL_Surface *screen){
     switch(event.type){
       case SDL_KEYDOWN:
           //Mouvement à gauche
           if(event.key.keysym.sym==SDLK_LEFT)   {
               switchingGraph = 14;
               Vx = -1;
           }
           //Mouvement à droite
           if(event.key.keysym.sym==SDLK_RIGHT)  {
               switchingGraph = 21;
               Vx = 1;
           }
           //Mouvement en haut
           if(event.key.keysym.sym==SDLK_UP)     {
               switchingGraph = 7;
               Vy = -1;
           }
           //Mouvement en bas
           if(event.key.keysym.sym==SDLK_DOWN)   {
              switchingGraph = 0;
              Vy = 1;
           }
     break;
     case SDL_KEYUP:
           //Mouvement à gauche
           if(event.key.keysym.sym==SDLK_LEFT)   {
               switchingGraph = 14;
               Vx = 0;
               latence = 0;
           }
           //Mouvement à droite
           if(event.key.keysym.sym==SDLK_RIGHT)  {
               switchingGraph = 21;
               Vx = 0;
               latence = 0;
           }
           //Mouvement en haut
           if(event.key.keysym.sym==SDLK_UP)     {
               switchingGraph = 7;
               Vy = 0;
               latence = 0;
           }
           //Mouvement en bas
           if(event.key.keysym.sym==SDLK_DOWN)   {
               switchingGraph = 0;
               Vy = 0;
               latence = 0;
           }
     break;     
     }
}

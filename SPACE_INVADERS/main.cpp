#include "enemy.h"
#include "tank.h"
#include "font.h"
#include "lazer.h"

//Declaration de mes objets
enemy enemy1,enemy2;
tank tank;
font font;
lazer lazer1,lazer2;

int main(int argc, char **argv){

    //--------------------------------------------------------------------------
    // VARIABLES
    //-------------------------------------------------------------------------- 
    //Variable de sortie
    int RUN = 1;
    
    //Gestion d'evenement
    SDL_Event event;
    
    //Gestion d'affichage
	SDL_Surface *screen;

    //--------------------------------------------------------------------------
    // INITIALISATION
    //--------------------------------------------------------------------------
    //initialisation des objets     
    font.init(); 
    enemy1.init(10,10);
    enemy2.init(50,10);
    tank.init(10,HEIGHT-50);  
    
    lazer1.init(enemy1.get_position().x,enemy1.get_position().y-5);
    lazer2.init(enemy2.get_position().x,enemy2.get_position().y-5);
    
    //Initialisation de la fenetre
    SDL_Init(SDL_INIT_VIDEO);
    
    //Titre de la fenêtre
    SDL_WM_SetCaption("PONG Version 1.0", NULL);
    
    //Ouverture de la fenetre
	screen = SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_DOUBLEBUF | 
                                              SDL_HWSURFACE | 
                                              SDL_RESIZABLE);

    //Gestion de la rapidité d'affichage
    unsigned int nouveauTemps = SDL_GetTicks();       

    //--------------------------------------------------------------------------
    // EVENEMENTS ET RAFRAICHISSEMENT
    //--------------------------------------------------------------------------
    //Gestion des evenements de sortie
    while(RUN){ 
        
       //Optimisation du programme afin de ne pas utiliser 100% du processeur        
       if(SDL_GetTicks() - nouveauTemps <= 20)
          SDL_Delay(20 - (SDL_GetTicks() - nouveauTemps));
       nouveauTemps = SDL_GetTicks();
                
       //Mouvement de l'ennemy 
       enemy1.move();
       enemy2.move();
       
       //mouvement de tire ennemy
       lazer1.move(enemy1.get_position().x);
       lazer2.move(enemy2.get_position().x);
       //Mise à feu tire ennemy
       lazer1.move();
       lazer2.move();
        
       //Test si le laser a raté sa cible ( une fois arriver sur le mur)
       if(lazer1.finCourse()){
       lazer1 = *new lazer;
       lazer1.init(enemy1.get_position().x,enemy1.get_position().y-5);
       } 
       //Test si le laser a raté sa cible ( une fois arriver sur le mur)
       if(lazer2.finCourse()){
       lazer2 = *new lazer;
       lazer2.init(enemy2.get_position().x,enemy2.get_position().y-5);
       } 
                     
       //mouvement tank initialisé
       tank.refresh();
    
       //Tantque l'on ne clic pas sur "fermer fenetre"
       while(SDL_PollEvent(&event)){
       if(event.type == SDL_QUIT) RUN = 0;  
       
           //Gestion des evenements clavier (ici)
           switch(event.type){
               
               case SDL_KEYDOWN:
               
               //Mouvement à droite initialisé
               if(event.key.keysym.sym==SDLK_LEFT) tank.captureEvent(tank.gauche);
               //Mouvement à gauche initialisé
               if(event.key.keysym.sym==SDLK_RIGHT) tank.captureEvent(tank.droite); 
               //Mise à Feu missile
               if(event.key.keysym.sym==SDLK_SPACE) tank.captureEvent(tank.feu);
               break;
               
               case SDL_KEYUP:
               //Mouvement à droite stoppé
               if(event.key.keysym.sym==SDLK_LEFT) tank.captureEvent(tank.stop);
               //Mouvement à gauche stoppé
               if(event.key.keysym.sym==SDLK_RIGHT) tank.captureEvent(tank.stop);
               break; 
           }                   
       }
       //Mise à jour de l'affichage
       font.show(screen);
       enemy1.show(screen);
       enemy2.show(screen);
       lazer1.show(screen);
       lazer2.show(screen);
       tank.show(screen);
       tank.missileD.show(screen);
       tank.missileG.show(screen);  
       SDL_Flip(screen);         
    }
    
    //--------------------------------------------------------------------------
    // LIBERATION MEMOIRE
    //--------------------------------------------------------------------------
    SDL_FreeSurface(screen);
    
    //--------------------------------------------------------------------------
    // SORTIE
    //--------------------------------------------------------------------------
    //Sortie du PGM
    SDL_Quit();
    return EXIT_SUCCESS;
}

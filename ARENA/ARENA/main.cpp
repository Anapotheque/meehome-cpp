#include "spacejet.h"
#include "font.h"

//On repeint la surface en noir
void clear(SDL_Surface *screen){
SDL_FillRect( screen,
              &screen->clip_rect,
              SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );     
}

int main(int argc, char **argv){
    //------------------------------------------------------------------------------
    // VARIABLES
    //------------------------------------------------------------------------------
    //Variable de sortie
    int RUN = 1;
    
    //Gestion d'evenement
    SDL_Event event;
    
    //Gestion d'affichage
    SDL_Surface *screen;
    
    //------------------------------------------------------------------------------
    // INITIALISATION
    //------------------------------------------------------------------------------    
    
    //Initialisation de la fenetre
    SDL_Init(SDL_INIT_VIDEO);
    
    //Titre de la fenêtre
    SDL_WM_SetCaption("RPG 1.0", NULL);
    
    //Ouverture de la fenetre
    screen = SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_DOUBLEBUF | 
                                              SDL_HWSURFACE |
                                              SDL_RESIZABLE );
       
    //------------------------------------------------------------------------------
    // Mes objets
    //------------------------------------------------------------------------------
    //Mon spaceJet
    spacejet *sj = new spacejet(80,80);
    
    //Le font
    font *f = new font(0,0);
       
    //------------------------------------------------------------------------------
    // GESTION TAUX DE RAFRAICHISSEMENT
    //------------------------------------------------------------------------------    
    FPSmanager manager;
    SDL_initFramerate(&manager);
    SDL_setFramerate(&manager,35);
    
    //------------------------------------------------------------------------------
    // EVENEMENTS ET RAFRAICHISSEMENT
    //------------------------------------------------------------------------------
    //Gestion des evenements de sortie
    while(RUN){
       // 24FPS
       SDL_framerateDelay(&manager);
       
       //On nettoie l'ecran          
       clear(screen);
    
       //Rafraichissement de la position de mon objet 
       f->show(screen);                          
       sj->show(screen);
    
       //---------------------------------------------------------------------------
       // BOUCLE D'EVENEMENTS
       //---------------------------------------------------------------------------
       while(SDL_PollEvent(&event)){
           //Si fermeture fenetre
           if(event.type == SDL_QUIT) RUN = 0; 
           sj->handleInput(event,screen);
       }
       //---------------------------------------------------------------------------
       // FIN BOUCLE D'EVENEMENTS
       //---------------------------------------------------------------------------  
       //Affichage de l'image calculée                     
       SDL_Flip(screen);            
    }
    
    //Sortie du PGM
    SDL_FreeSurface(screen);
    SDL_Quit();
    delete sj;
    return EXIT_SUCCESS;
}

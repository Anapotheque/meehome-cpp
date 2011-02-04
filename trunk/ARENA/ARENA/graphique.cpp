#include "graphique.h"

//Constructeur
graphique::graphique(int x, int y,string source){                                            
    position.x = x;
    position.y = y;
    
    src = source;       
    //Initialisation de l'objet à null        
    area = NULL;
}

//Destructeur
graphique::~graphique(){
    //Libération des surfaces  
    if(area != NULL) SDL_FreeSurface(area),area = NULL;
}

//Chargement d'une image optimisée
SDL_Surface *graphique::load_image(string source){
    //L'image qui est chargée
    SDL_Surface* loadedImage = NULL;

    //L'image optimisée qu'on va utiliser
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image
    loadedImage = IMG_Load(source.c_str());

    //Si l'image est chargée
    if( loadedImage != NULL )
    {
        //Création de l'image optimisée
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Libération de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //Si la création de l'image optimisée s'est bien passée
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY,SDL_MapRGB(optimizedImage->format,255,0,255));
            SDL_SetAlpha(optimizedImage, SDL_SRCALPHA, 255);
        }
    }
    //On retourne l'image optimisée
    return optimizedImage;
}

//Initialisation de l'objet
bool graphique::init(){ 
    
    //Vérification de l'allocation de la surface
    if(area!=NULL) SDL_FreeSurface(area), area = NULL;
        
    //On charge l'image dans la surface associée
    area = load_image(src);
     
    return true;
}

//Affichage de l'objet dans la fenetre
bool graphique::show(SDL_Surface *screen){
    //Dessiner l'image
    SDL_BlitSurface(area,NULL,screen,&position);	
    return true;
}

//Affichage de l'objet dans la fenetre avec sprites
bool graphique::show(SDL_Surface *screen,SDL_Rect pos){
    //Dessiner l'image
    SDL_BlitSurface(area,&pos,screen,&position);	
    return true;
}

//Affichage de l'objet dans la fenetre avec sprites
bool graphique::show(SDL_Surface *screen,SDL_Rect pos1,SDL_Rect pos2){
    //Dessiner l'image
    SDL_BlitSurface(area,&pos1,screen,&pos2);	
    return true;
}

//Deplacement de l'objet ( de la position + x idem pour y )
bool graphique::move(int x,int y){
    position.x += x;
    position.y += y;
    return true;
}

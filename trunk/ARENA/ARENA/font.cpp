#include "font.h"

//Lecture du fichier de configuration
string getFile(string file,int iteration){
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
font::font(int x,int y){
    //Mon fichier de configuration           
    sourceData = "DATA/font.txt";   
              
    //Configuration de l'image
    largeur_image = 793;
    hauteur_image = 760;
    largeur = largeur_image / 24;
    hauteur = hauteur_image / 22;
    
    //PELOUSE          
    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = largeur;
    clip[0].h = hauteur;        
              
    gp = new graphique(x,y,getFile(sourceData,1));
    gp->init();
}

//Destructeur
font::~font(){
    delete gp;
}

//Affichage du fond
void font::show(SDL_Surface *screen){
          
    pelouse.x = 0;
    pelouse.y = 0; 
    
    while(pelouse.x < WIDTH-largeur || pelouse.y < HEIGHT-hauteur){
    gp->show(screen,clip[0],pelouse); 
    pelouse.x += largeur;
    if(pelouse.x == WIDTH-largeur)
    pelouse.y += hauteur; 
    } 
    
    
    
}

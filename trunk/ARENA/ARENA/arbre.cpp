#include "arbre.h"

//Constructeur de l'arbre
arbre::arbre(int x, int y){  
    sourceData = "DATA/arbre.txt"; 
    feuille = new graphique(x,y,getFile(sourceData,1));
    feuille->init();
    tronc = new graphique(x,y+feuille->area->h,getFile(sourceData,2));
    tronc->init();  
    sol = new graphique(x,y+feuille->area->h+tronc->area->h,getFile(sourceData,3));
    sol->init();                
}

//Destructeur de l'arbre
arbre::~arbre(){
    delete feuille;
    delete tronc;   
    delete sol;               
}

//Affichage de mon objet
void arbre::show(SDL_Surface *screen){
     feuille->show(screen);
     tronc->show(screen);
     sol->show(screen);
}


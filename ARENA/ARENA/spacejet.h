#ifndef H_SPACEJET
#define H_SPACEJET

#include "graphique.h"

class spacejet{

public:
 
int Vx;                      //Deplacement lateral
int Vy;                      //Deplacement vertical
int Vitesse;                 //Vitesse de deplacement  
int switchingGraph;          //Switch le type affiché

int largeur_image;
int hauteur_image;
int largeur;
int hauteur;

int latence,latenceMax;

//Objet graphique de mon vaisseaux 
graphique *sj;
SDL_Rect clip[28];
 
//Constructeur, destructeur
spacejet(int,int);
~spacejet();

//Affichage de l'arbre
void show(SDL_Surface *);

//Gestion des evenements
void handleInput(SDL_Event,SDL_Surface *);

//Gestion des mouvement
void spacejet::translation();
void spacejet::mvt();

string sourceData;

};

#endif

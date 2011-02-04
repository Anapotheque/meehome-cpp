#include "ListeEnnemy.h"

void ListeEnnemy::ajoutEnnemy(ennemy *obj){
    //Creation de mon nouvel objet 
    ListeEnnemy *nouveau = new ListeEnnemy;
    
    //On assimile à cet objet un nouveau missile
    nouveau->obj = obj;
    
    //On affecte au suivant l'ancienne valeur de l'objet listMissile
    nouveau->suivant = suivant;
    
    //Le nouveau pointeur vaut l'ancien
    suivant = nouveau;
}

void ListeEnnemy::supprimeEnnemy(){
    //Creation de mon nouvel objet 
    ListeEnnemy *victime = suivant;
    
    if(victime == NULL) return;
    
    suivant = victime->suivant;
    
    delete suivant;
}

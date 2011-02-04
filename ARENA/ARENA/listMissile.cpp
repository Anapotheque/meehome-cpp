#include "listMissile.h"
#include "missile.h"

void listMissile::ajoutMissile(missile *objet){
    //Creation de mon nouvel objet 
    listMissile *nouveau = new listMissile;
    
    //On assimile à cet objet un nouveau missile
    nouveau->obj = objet;
    
    //On affecte au suivant l'ancienne valeur de l'objet listMissile
    nouveau->suivant = suivant;
    
    //Le nouveau pointeur vaut l'ancien
    suivant = nouveau;
}

void listMissile::supprimeMissile(missile *objet){
    //Creation de mon nouvel objet 
    listMissile *victime = suivant;
    
    if(victime == NULL) return;
    
    suivant = victime->suivant;
    
    delete suivant;
}

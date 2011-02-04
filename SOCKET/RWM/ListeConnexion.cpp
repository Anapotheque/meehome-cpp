#include "define.h"

void ListeConnexion::ajoutConnexion(){
    //Creation de mon nouvel objet 
    ListeConnexion *nouveau = new ListeConnexion;
    
    //On assimile à cet objet un nouveau client
    nouveau->obj = obj;
    
    //On affecte au suivant l'ancienne valeur de l'objet client
    nouveau->suivant = suivant;
    
    //Le nouveau pointeur vaut l'ancien
    suivant = nouveau;
}

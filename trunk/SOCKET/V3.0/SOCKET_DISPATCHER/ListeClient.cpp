#include "define.h"

void ListeClient::supprimeClient(){
    //Creation de mon nouvel objet 
    ListeClient *victime = suivant;
    if(victime == NULL) return;
    suivant = victime->suivant;
    delete suivant;
}

void ListeClient::ajoutClient(Client *obj){
    //Creation de mon nouvel objet 
    ListeClient *nouveau = new ListeClient;
    //On assimile à cet objet un nouveau client
    nouveau->obj = obj;
    //On affecte au suivant l'ancienne valeur de l'objet client
    nouveau->suivant = suivant;
    //Le nouveau pointeur vaut l'ancien
    suivant = nouveau;
}

int ListeClient::initClient(){
    
    ListeClient *ptr = this->suivant;
    // Initialisation des client
    while(ptr != NULL){
        if (ptr->obj->init() !=0){
    		return EXIT_FAILURE;                   
        }
        ptr = ptr->suivant;
    }
    delete ptr;
    return 0;
}

int ListeClient::startClient(){
    
    // Demarrage des clients
    ListeClient *ptr = this->suivant;
    // Initialisation des client
    while(ptr != NULL){
        if (ptr->obj->start() !=0){
    		return EXIT_FAILURE;                   
        }
        ptr = ptr->suivant;
    }
    delete ptr;
    return 0;
}

int ListeClient::writeClient(string str){
    ListeClient *ptr = this->suivant;
    while(ptr != NULL){
        if (ptr->obj->write(str) !=0){
    		return EXIT_FAILURE;                   
        }
        ptr = ptr->suivant;
    }
    delete ptr;
    return 0;
}

#ifndef H_LISTECONNEXION
#define H_LISTECONNEXION

class ListeConnexion { 
 
public :   

    ListeConnexion *obj;  
    ListeConnexion *suivant;
    
    void ajoutClient(Client *); 
 
};

#endif

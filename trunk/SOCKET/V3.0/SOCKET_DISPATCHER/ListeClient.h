#ifndef H_LISTECLIENT
#define H_LISTECLIENT

class ListeClient { 
 
public :   

    Client *obj;  
    ListeClient *suivant;
    
    void ajoutClient(Client *); 
    int writeClient(string );
    int startClient();
    int initClient();
    void supprimeClient();
        
};

#endif

#include "define.h"

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

int ListeClient::initListeClient(){
    
    ListeClient *ptr = this->suivant;
    // Initialisation des client
    while(ptr != NULL){
        if (ptr->obj->init() !=0){
            system("PAUSE");
    		return EXIT_FAILURE;                   
        }
        ptr = ptr->suivant;
    }
    delete ptr;
    return 0;
}

int ListeClient::startListeClient(){
    
    // Demarrage des clients
    ListeClient *ptr = this->suivant;
    // Initialisation des client
    while(ptr != NULL){
        if (ptr->obj->start() !=0){
            system("PAUSE");
    		return EXIT_FAILURE;                   
        }
        ptr = ptr->suivant;
    }
    delete ptr;
    return 0;
}

int ListeClient::runListeClient(){
    
    HANDLE                           hProcessThread;
	struct thread_param_ListeClient  c1;
	//struct thread_param_ListeClient  c2;
	//struct thread_param_ListeClient  c3;
	//struct thread_param_ListeClient  c4;
	
    c1.listeClient = this;
    //c2.listeClient = this;
    //c3.listeClient = this;
    //c4.listeClient = this;
    
    c1.ptr = this->suivant;
    //c2.ptr = c1.ptr->suivant;
    //c3.ptr = c2.ptr->suivant;
    //c4.ptr = c3.ptr->suivant;
    
    // Creation du thread pour lancement des clients
	if ((hProcessThread=CreateThread(NULL,0,&ListeClient::ThreadLauncherListeClient,&c1,0,NULL))==NULL ){
		cout << "CreateThread a échoué avec l'erreur " <<GetLastError()<< endl;
		return 1;
    } 
   /* // Creation du thread pour lancement des clients
	if ((hProcessThread=CreateThread(NULL,0,&ListeClient::ThreadLauncherListeClient,&c2,0,NULL))==NULL ){
		cout << "CreateThread a échoué avec l'erreur " <<GetLastError()<< endl;
		return 1;
    }
    // Creation du thread pour lancement des clients
	if ((hProcessThread=CreateThread(NULL,0,&ListeClient::ThreadLauncherListeClient,&c3,0,NULL))==NULL ){
		cout << "CreateThread a échoué avec l'erreur " <<GetLastError()<< endl;
		return 1;
    }
    // Creation du thread pour lancement des clients
	if ((hProcessThread=CreateThread(NULL,0,&ListeClient::ThreadLauncherListeClient,&c4,0,NULL))==NULL ){
		cout << "CreateThread a échoué avec l'erreur " <<GetLastError()<< endl;
		return 1;
    }*/
 
     /*   
   	ListeClient *list;
	list = this->suivant;
    c.listeClient = this;
    c.ptr = list; 
    // Initialisation des client
    while(list != NULL){       
        c.ptr = list;              
        // Creation du thread pour lancement des clients
    	if ((hProcessThread=CreateThread(NULL,0,&ListeClient::ThreadLauncherListeClient,&c,0,NULL))==NULL ){
    		cout << "CreateThread a échoué avec l'erreur " <<GetLastError()<< endl;
    		return 1;
        } 
       list = list->suivant;   
    }
    */
    
    while(1){ Sleep(100000);}
    
    return 0;
}

/* ======================================================================== */
/* ========================== thread proc ================================= */
/* ======================================================================== */

DWORD ListeClient::ListeClientThread(ListeClient *ptr){
    if (ptr->obj->connexion() !=0){
         cout << "ne peut demarrer le client"<< endl;
         return 1;                   
    }
}

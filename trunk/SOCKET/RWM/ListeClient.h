#ifndef H_LISTECLIENT
#define H_LISTECLIENT

class ListeClient;

struct thread_param_ListeClient{
       ListeClient* listeClient;
       ListeClient* ptr;
};

class ListeClient { 
 
private:
    DWORD ListeClientThread(ListeClient *listeClient); 
 
public :   

    Client *obj;  
    ListeClient *suivant;
    
    void ajoutClient(Client *); 
    int runListeClient();
    int startListeClient();
    int initListeClient();
    void supprimeClient();
    
    static DWORD WINAPI ThreadLauncherListeClient(void *p){
    	struct thread_param_ListeClient *Obj = reinterpret_cast<struct thread_param_ListeClient*>(p);               
    	ListeClient *s = Obj->listeClient;                                  
    	return s->ListeClientThread(Obj->ptr);
    }     
};

#endif

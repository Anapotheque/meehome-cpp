#ifndef H_RWM
#define H_RWM

#include "Client.h"
#include "Serveur.h"
#include "ListeClient.h"

class RWM;

struct thread_param_RWM{
       RWM* rwm;
};

class RWM{
      
   public :   
      
      ListeClient *listeClient;
      Client *client;
      Serveur *serveur;   
      DWORD RMWThread();
      
    public :
        
        //Constructeur
        RWM();
        
        // Prototypes fonctions
        int init();
        int start();
        int run();
        void color(int,int);
        
		static DWORD WINAPI ThreadLauncherRMW(void *p){
			struct thread_param_RWM *Obj = reinterpret_cast<struct thread_param_RWM*>(p);               
			RWM *rwm = Obj->rwm;                          
			return rwm->RMWThread();       
		}
};

#endif

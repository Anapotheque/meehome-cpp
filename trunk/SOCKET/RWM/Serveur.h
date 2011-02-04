#ifndef H_SERVEUR
#define H_SERVEUR

#include "ListeClient.h"

class Serveur;

struct thread_param{
       Serveur* ser;
       SOCKET soc;
       SOCKADDR_IN Addr;
};

class Serveur{
      
   private :   
      
      bool running;
      SOCKET sock;
      SOCKADDR_IN Addr;
      DWORD ServeurThread(SOCKET,SOCKADDR_IN);
      
    public :
        
        //Constructeur
        Serveur(int port,ListeClient *listeClient);
        
        int port;
        char buffer_Recv[50];
        ListeClient *listeClient;
        
        // Prototypes fonctions
        int init();
        int start();
        int ecoute();
        int read(SOCKET soc, SOCKADDR_IN ClientAddr);
        void color(int,int);
        
        static DWORD WINAPI ThreadLauncherServeur(void *p){
			struct thread_param *Obj = reinterpret_cast<struct thread_param*>(p);               
			Serveur *s = Obj->ser;                          
			return s->ServeurThread(Obj->soc, Obj->Addr);       
		}
};

#endif

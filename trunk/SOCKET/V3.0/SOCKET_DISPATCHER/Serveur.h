#ifndef H_SERVEUR
#define H_SERVEUR

#include "ListeClient.h"

class Serveur;

struct thread_param{
       Serveur* ser;
       SOCKET soc;
       SOCKADDR_IN Addr;
       ListeClient *listeClient;
};

class Serveur{
      
   private :   
      
      bool running;
      SOCKET sock;
      SOCKADDR_IN Addr;
      DWORD ServeurThread(SOCKET,SOCKADDR_IN,ListeClient *);
      
    public :
        
        //Constructeur
        Serveur();
        
        ListeClient *listeClient;
        
        int port;
        char buffer_Recv[50];
        
        // Prototypes fonctions
        int init();
        int start();
        int ecoute();
        int read(SOCKET, SOCKADDR_IN,ListeClient *);
        void color(int,int);
        
        static DWORD WINAPI ThreadLauncherServeur(void *p){
			struct thread_param *Obj = reinterpret_cast<struct thread_param*>(p);               
			Serveur *s = Obj->ser;                          
			return s->ServeurThread(Obj->soc, Obj->Addr, Obj->listeClient);       
		}
};

#endif

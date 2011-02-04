#ifndef H_SERVEUR
#define H_SERVEUR

class Serveur;

struct thread_param{
       Serveur* ser;
       SOCKET soc;
       SOCKADDR_IN Addr;
};

class Serveur{
      
   private : 
      char* IP;  
      int port;
      bool running;
      SOCKET ListeningSocket; 
      SOCKADDR_IN ServerAddr;
      DWORD ClientThread(SOCKET,SOCKADDR_IN);
      char buffer_Recv[50];
      
    public :
        
        //Constructeur
        Serveur();
        
        // Prototypes fonctions
        int init();
        int start();
        int pause ();
        int write(SOCKET);
        int read(SOCKET, SOCKADDR_IN);
        void color(int,int);
        
        static DWORD WINAPI ThreadLauncher(void *p){
			struct thread_param *Obj = reinterpret_cast<struct thread_param*>(p);               
			Serveur *s = Obj->ser;                          
			return s->ClientThread(Obj->soc, Obj->Addr);       
		}
};

#endif

#ifndef H_SERVEUR
#define H_SERVEUR

class Serveur{
      
   private : 
   
      int port;
      bool running;
      SOCKET ListeningSocket; 
      SOCKADDR_IN ServerAddr;
      char buffer_Recv[50];
      
    public :
        
        //Constructeur
        Serveur();
        
        // Prototypes fonctions
        int init();
        int start();
        int write(SOCKET);
        int read(SOCKET, SOCKADDR_IN);
        void color(int,int);
};

#endif

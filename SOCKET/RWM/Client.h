#ifndef H_CLIENT
#define H_CLIENT

class Client{
      
   private :   
      
      SOCKET sock;
      SOCKADDR_IN Addr;
      string buffer;
      
    public :
        
        //Constructeur
        Client(string ip, int port);
        
        int port;
        const char *ip;
        int connecter;
        
        // Prototypes fonctions
        int init();
        int start();
        int connexion();
        void color(int,int);  
};

#endif

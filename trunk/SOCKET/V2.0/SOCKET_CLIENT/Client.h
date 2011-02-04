#ifndef H_CLIENT
#define H_CLIENT

class Client{
      
    private:
      
        // Distant
        string IPD;
        int PORTD;
        SOCKET SocketDistante;
        SOCKADDR_IN ServerAddrDistante;  
        
        // Local
        string IPL;
        int PORTL;
        SOCKET SocketLocale; 
        SOCKADDR_IN ServerAddrLocale; 
        
        bool running;
        string buffer_Send;
    
    public :
    
        //Constructeur
        Client();
        
        // Prototypes fonctions
        int init();
        int start();
        int write();
        void color(int,int);
};

#endif

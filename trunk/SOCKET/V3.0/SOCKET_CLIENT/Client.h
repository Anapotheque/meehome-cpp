#ifndef H_CLIENT
#define H_CLIENT

class Client{
      
    private:
      
        string PSEUDO;    
        string IP;
        int PORT;
        SOCKET Socket;
        SOCKADDR_IN ServerAddr; 
        
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

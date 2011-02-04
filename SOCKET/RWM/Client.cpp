#include "define.h"

// Constructeur
Client::Client(string ip, int port){
    this->ip = ip.c_str();
    this->port = port;               
	this->connecter = 0;
}

// Initialisation du serveur
int Client::init(){

    color(2,0);
    
    WSADATA wsaData;
    
    // Demarage du service
   	if(WSAStartup(MAKEWORD(2,2), &wsaData ) != 0 ){
        color(4,0); 
        cerr << "-----------------------------------------------"       << endl;
		cerr << "Client : WSAStartup a échoué "                         << endl;
		cerr << "-----------------------------------------------"       << endl;                         
		return 1;
	} 
    
    // Adresse Distante
    Addr.sin_addr.s_addr    = inet_addr(ip);    
    Addr.sin_family         = AF_INET;     
    Addr.sin_port           = htons(port);  
    
    cout << "Client  initialisation  -- OK " << endl;
    return 0;
}

// Demarrage du client
int Client::start(){
    
    // Creation de la socket d'ecoute
   	if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
		cout << "Client : Creation socket impossible "                  << endl;
		return 1;
	}

    cout << "Client  demarrage       -- OK "                            << endl;
    
    return 0;
}

// Connexion du client
int Client::connexion(){  
    
    std::stringstream out;
    out << port;
    string str = out.str();  
       
    while(1){   
        // On tente une connexion si celle ci n'est pas deja active
        if (connecter == 0){
            // On essaye de se connectéer à un serveur distant
            if(connect(sock,(SOCKADDR *)&Addr,sizeof(Addr))==INVALID_SOCKET){
                connecter = 0;
        	}else{
                connecter = 1;  
                color(3,0);
            }
         }else{              
            // Envoi du message au serveur distant pour tester si il fonctionne toujours
            if (send(sock,str.c_str(),str.size(),0)==SOCKET_ERROR){
               connecter = 0;
            }
         }
         Sleep(1000);
    }
    return 0;
}

void Client::color(int couleurDuTexte,int couleurDeFond){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}



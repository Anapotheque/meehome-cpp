#include "Define.h"

// Constructeur
Client::Client(){
                      
    string str;
    color(7,0);
    
    cout << "IP local : " << flush;
    getline(cin, str);
    this->IPL = str; 
    
    cout << "Port local : " << flush;
    getline(cin, str);
    this->PORTL = atoi(str.c_str()); 
    
    cout << "IP distante : " << flush;
    getline(cin, str);
    this->IPD = str;
    
    cout << "Port distant : " << flush;
    getline(cin, str);
    this->PORTD = atoi(str.c_str()); 
    
    system("CLS");                    
    this->running = false;               
}

// Initialisation socket
int Client::init(){  
      
    color(2,0); 
    cout << "-----------------------------------------------"           << endl;
    cout << "    Initialisation du Client..."                           << endl;
    cout << "-----------------------------------------------"           << endl;
    
    WSADATA wsaData;  
    
    // Demarage du service
   	if(WSAStartup(MAKEWORD(2,2), &wsaData ) != 0 ){
        color(4,0); 
        cerr << "-----------------------------------------------" << endl;
		cerr << "WSAStartup a échoué "<< endl;
		cerr << "-----------------------------------------------" << endl;                         
		
		return 1;
	}   
	
    // Definition de l'adresse de la socket locale
    ServerAddrLocale.sin_addr.s_addr    = inet_addr(IPL.c_str());   
    ServerAddrLocale.sin_family         = AF_INET;       
    ServerAddrLocale.sin_port           = htons(PORTL);  
    
    // Definition de l'adresse de la socket distante
    ServerAddrDistante.sin_addr.s_addr    = inet_addr(IPD.c_str());   
    ServerAddrDistante.sin_family         = AF_INET;       
    ServerAddrDistante.sin_port           = htons(PORTD);  
    
    running = true;
    cout << "    Serveur Adresse locale  : " << IPL                     << endl;
    cout << "    Serveur Port local      : " << PORTL                   << endl;
    cout << "-----------------------------------------------"           << endl;
    cout << "    Serveur Adresse distante  : " << IPD                   << endl;
    cout << "    Serveur Port distant      : " << PORTD                 << endl;
    cout << "-----------------------------------------------"           << endl;
    cout << "    Initialisation du Client...OK"                         << endl;
    cout << "-----------------------------------------------"           << endl;
    system("PAUSE"); 
    return 0;  
}

// Connexion au serveur
int Client::start(){ 
    
    system("CLS");
    cout << "-----------------------------------------------"           << endl;
    cout << "    Demarrage du client..."                                << endl;
    cout << "-----------------------------------------------"           << endl;

    // Creation de la socket locale
   	if((SocketLocale=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
        color(4,0);
        cerr << "-----------------------------------------------"       << endl;
		cerr << "Creation socket locale impossible..."                  << endl;
		cerr << "Erreur : " << WSAGetLastError()                        << endl;
		cerr << "-----------------------------------------------"       << endl;
		WSACleanup();
		return 1;
	}
	
	cout << "    Socket locale : " << SocketLocale                      << endl;
	
    // Creation de la socket distante
   	if((SocketDistante=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
        color(4,0); 
        cerr << "-----------------------------------------------"       << endl;
		cerr << "Creation socket distante impossible..."                << endl;
		cerr << "Erreur : " << WSAGetLastError()                        << endl;
		cerr << "-----------------------------------------------"       << endl;
		WSACleanup();
		return 1;
	}
	
    cout << "    Socket distante : " << SocketDistante                  << endl;
	cout << "-----------------------------------------------"           << endl;
    cout << "    Demarrage du client...OK"                              << endl;
    cout << "-----------------------------------------------"           << endl;
    system("PAUSE");
    system("CLS");
    cout << "-----------------------------------------------"           << endl;
    cout << "    Connexion au serveur distant..."                       << endl; 
            
    // Tant que la connexion au serveur distant n'a pas été faite on boucle    
    if(connect(SocketDistante,(SOCKADDR *)&ServerAddrDistante,sizeof(ServerAddrDistante))==INVALID_SOCKET){
        color(4,0);
        cerr << "-----------------------------------------------"       << endl;
        cerr << "Connexion impossible au serveur distant..."            << endl;
		cerr << "Erreur : " << WSAGetLastError()                        << endl;
		cerr << "-----------------------------------------------"       << endl;
		closesocket(SocketDistante);
		WSACleanup();
		return 1;
	}
	
    cout << "    Connexion au serveur distant...OK"                     << endl;
    cout << "-----------------------------------------------"           << endl;
	cout << "-----------------------------------------------"           << endl;
    cout << "    Connexion au serveur local..."                         << endl;    
	
    // Tant que la connexion au serveur local n'a pas été faite on boucle    
    if(connect(SocketLocale,(SOCKADDR *)&ServerAddrLocale,sizeof(ServerAddrLocale))==INVALID_SOCKET){
        color(4,0);
        cerr << "-----------------------------------------------"       << endl;
        cerr << "Connexion impossible au serveur local..."              << endl;
		cerr << "Erreur : " << WSAGetLastError()                        << endl;
		cerr << "-----------------------------------------------"       << endl;
		closesocket(SocketLocale);
		WSACleanup();
		return 1;
	}
	
	cout << "    Connexion au serveur local...OK"                       << endl;
    cout << "-----------------------------------------------"           << endl;

    //------------------------------------------------------
    // LANCEMENT
    //------------------------------------------------------
    
    while(1) if (write()!=0) break;	
    
    //------------------------------------------------------
    // FIN
    //------------------------------------------------------
    
    return 0;
}

// Envoie du message au serveur
int Client::write(){ 
    color(7,0);
    system("CLS");
    cout << IPL << ":" << PORTL << " >> ";
    getline(cin, buffer_Send);
    
    // Envoi du message au serveur distant
    if (send(SocketDistante,buffer_Send.c_str(),buffer_Send.size(),0)==SOCKET_ERROR){
       color(4,0);    
       cerr << "-----------------------------------------------"        << endl; 
       cerr << "Le serveur distant est en arret..."                     << endl;
       cerr << "-----------------------------------------------"        << endl;
       return 1;
    }
    
    // Envoi du message au serveur local
    if (send(SocketLocale,buffer_Send.c_str(),buffer_Send.size(),0)==SOCKET_ERROR){
       color(4,0);    
       cerr << "-----------------------------------------------"        << endl; 
       cerr << "Le serveur local est en arret..."                       << endl;
       cerr << "-----------------------------------------------"        << endl;
       return 1;
    }
    return 0;
}

// Methode de coloration texte
void Client::color(int couleurDuTexte,int couleurDeFond){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

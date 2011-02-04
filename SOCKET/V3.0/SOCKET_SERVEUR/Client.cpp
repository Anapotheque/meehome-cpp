#include "Define.h"

// Constructeur
Client::Client(){
                    
    string str;
    color(7,0);
    
    cout << "Pseudo : " << flush;
    getline(cin, str);
    this->PSEUDO = str; 
    
    cout << "IP du serveur : " << flush;
    getline(cin, str);
    this->IP = str;
    
    cout << "Port du serveur : " << flush;
    getline(cin, str);
    this->PORT = atoi(str.c_str()); 
    
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
    
    // Definition de l'adresse de la socket distante
    ServerAddr.sin_addr.s_addr    = inet_addr(IP.c_str());   
    ServerAddr.sin_family         = AF_INET;       
    ServerAddr.sin_port           = htons(PORT);  
    
    running = true;
    cout << "    Serveur Adresse distante  : " << IP                    << endl;
    cout << "    Serveur Port distant      : " << PORT                  << endl;
    cout << "-----------------------------------------------"           << endl;
    cout << "    Initialisation du Client...OK"                         << endl;
    cout << "-----------------------------------------------"           << endl;
    return 0;  
}

// Connexion au serveur
int Client::start(){ 
    
    system("CLS");
    cout << "-----------------------------------------------"           << endl;
    cout << "    Demarrage du client..."                                << endl;
    cout << "-----------------------------------------------"           << endl;
	
    // Creation de la socket distante
   	if((Socket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
        color(4,0); 
        cerr << "-----------------------------------------------"       << endl;
		cerr << "Creation socket distante impossible..."                << endl;
		cerr << "Erreur : " << WSAGetLastError()                        << endl;
		cerr << "-----------------------------------------------"       << endl;
		WSACleanup();
		return 1;
	}
	
    cout << "    Socket : " << Socket                  					<< endl;
	cout << "-----------------------------------------------"           << endl;
    cout << "    Demarrage du client...OK"                              << endl;
    cout << "-----------------------------------------------"           << endl;
    system("CLS");
        
    cout << "Tentative de connexion au serveur " << IP << ":" << PORT   << endl;    
            
    // Tant que la connexion au serveur distant n'a pas été faite on boucle    
    if(connect(Socket,(SOCKADDR *)&ServerAddr,sizeof(ServerAddr))==INVALID_SOCKET){
        color(4,0);
        cerr << "-----------------------------------------------"       << endl;
        cerr << "Connexion impossible au serveur..."            		<< endl;
		cerr << "Erreur : " << WSAGetLastError()                        << endl;
		cerr << "-----------------------------------------------"       << endl;
		closesocket(Socket);
		WSACleanup();
		return 1;
	}

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
    
    cout << PSEUDO << " >> ";
    getline(cin, buffer_Send);
    
    
    buffer_Send = PSEUDO + " >> " + buffer_Send;
    // Envoi du message au serveur
    if (send(Socket,buffer_Send.c_str(),buffer_Send.size(),0)==SOCKET_ERROR){
       color(4,0);    
       cerr << "-----------------------------------------------"        << endl; 
       cerr << "Le serveur en arret..."                     			<< endl;
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

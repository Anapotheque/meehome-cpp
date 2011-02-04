#include "define.h"

// Constructeur
Serveur::Serveur(){   
    
    string str;
    
    color(7,0);
    
    cout << "Port serveur : " << flush;
    getline(cin, str);
    system("CLS");
    
    this->port = atoi(str.c_str()); 
    this->running = false;
    this->listeClient = new ListeClient();
    this->listeClient->suivant = NULL;
}

// Initialisation du serveur
int Serveur::init(){

    color(2,0);
    
    WSADATA wsaData;
    
    // Demarage du service
   	if(WSAStartup(MAKEWORD(2,2), &wsaData ) != 0 ){
        color(4,0); 
        cerr << "-----------------------------------------------"       << endl;
		cerr << "WSAStartup a échoué "                                  << endl;
		cerr << "-----------------------------------------------"       << endl;                         
		return 1;
	} 
    
    // Adresse Distante
    Addr.sin_addr.s_addr    = htonl(INADDR_ANY);   
    Addr.sin_family         = AF_INET;       
    Addr.sin_port           = htons(port); 
    
    return 0;
}

// Demarrage du serveur
int Serveur::start(){
    
    // Creation de la socket d'ecoute
   	if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
		color(4,0);
        cerr << "ne peut créer la socket "                              << endl;
		cerr << "Erreur : " << WSAGetLastError()                        << endl;
        WSACleanup();
		return 1;
	}

    // On accroche la socket d'ecoute au port d'ecoute
	if(bind(sock,(SOCKADDR *)&Addr,sizeof(Addr))==SOCKET_ERROR){
		color(4,0);
        cerr << "bind a échoué "                                        << endl;
		cerr << "Erreur : " << WSAGetLastError()                        << endl;
        closesocket(sock);
		WSACleanup();
		return 1;
	}

    // Ecoute de la socket d'ecoute
	if(listen(sock,5)==SOCKET_ERROR){
		color(4,0);
        cerr << "    ---------------------------"<< endl;
        cerr << "    listen a échoué "                                      << endl;
		cerr << "    Erreur : " << WSAGetLastError()                        << endl;
		closesocket(sock);
		WSACleanup();
		return 1;
	}
    
    cerr << "En attente de connexion client..."                                << endl;
    
    running = true;
    return 0;   
}
 
// serveur en ecoute
int Serveur::ecoute(){   
    
   	SOCKADDR_IN                 ClientAddr;
	int                         ClientAddrLen;
	HANDLE                      hProcessThread;
	SOCKET                      NewConnection;
	struct thread_param         p;
    
    ClientAddrLen = sizeof(SOCKADDR);
    
    // On se met en mode ecoute
    while(running){                   
        if((NewConnection=accept(sock,(SOCKADDR *)&ClientAddr,&ClientAddrLen))==INVALID_SOCKET){
			color(4,0);
            cerr << "    ---------------------------"<< endl;
            cerr << "    accept down "                                  << endl;
			cerr << "    Erreur : " << WSAGetLastError()                << endl;
            closesocket(sock);
			WSACleanup();
			running = false;
			return 1;
		}
        
        // Initialisation de l'ecriture au serveur du client
        Client *client = new Client(ClientAddr);
        client->init();
        client->start();
        
        listeClient->ajoutClient(client);  
        
		p.ser = this;
		p.soc = NewConnection;
		p.Addr = ClientAddr;
		p.listeClient = listeClient;
		
		// lancement du thread serveur
		if ((hProcessThread=CreateThread(NULL,0,&Serveur::ThreadLauncherServeur,&p,0,NULL))==NULL ){
    		cerr << "CreateThread a échoué avec l'erreur " <<GetLastError()<< endl;
    		return 1;
    	}
	}
    return 0;
}

// Lecture data Client
int Serveur::read(SOCKET soc, SOCKADDR_IN ClientAddr,ListeClient *listeClient){  
    for(int i=0;i<50;i++) buffer_Recv[i] = '\0'; 
    // Reception message client          
    if (recv(soc,buffer_Recv,sizeof(buffer_Recv),0) == SOCKET_ERROR) {
       color(4,0);     
       cout << inet_ntoa( ClientAddr.sin_addr) << " se deconnecte..." << endl;
       return 1;
    }
    listeClient->writeClient(buffer_Recv);
    return 0;
}

void Serveur::color(int couleurDuTexte,int couleurDeFond){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

/* ======================================================================== */
/* ========================== thread proc ================================= */
/* ======================================================================== */

DWORD Serveur::ServeurThread(SOCKET soc,SOCKADDR_IN ClientAddr,ListeClient *listeClient){      	
	color(3,0);
	cout << inet_ntoa( ClientAddr.sin_addr ) << " se connecte..."<< endl;
    while(1) if (read(soc,ClientAddr,listeClient)!=0) break;
    return 0;
}





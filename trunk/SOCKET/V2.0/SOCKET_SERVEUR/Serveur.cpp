#include "Define.h"

// Constructeur
Serveur::Serveur(){
        
    color(7,0);   
    cout << "IP : " << flush;
    cin >> this->IP;
                  
    cout << "Port d'ecoute : " << flush;
    cin >> this->port;
        
    system("CLS");                 
                     
	this->running = false;
}

// Initialisation du serveur
int Serveur::init(){
    
    // Message en Vert
    color(2,0); 
    cout << "-----------------------------------------------" 	<< endl;
    cout << "    Initialisation de la socket Serveur..." 		<< endl;
    cout << "-----------------------------------------------" 	<< endl;
    
    WSADATA wsaData;                          
     
    // Demarage du service
   	if(WSAStartup(MAKEWORD(2,0), &wsaData ) != 0 ){
		cerr << "WSAStartup a échoué "<< endl;
		return 1;
	}
	
    // Definition de la socket 
    ServerAddr.sin_addr.s_addr    = inet_addr(IP);    
    ServerAddr.sin_family         = AF_INET;       
    ServerAddr.sin_port           = htons(port);  
    
    cout << "    Adresse  : " << IP << endl;
    cout << "    Port     : " << port << endl;
    cout << "    Initialisation de la socket Serveur...OK" << endl;
    cout << "-----------------------------------------------" << endl;
    system("PAUSE");
    return 0;
}

// Demarrage du serveur
int Serveur::start(){    
    system("CLS");
    cout << "-----------------------------------------------" << endl;
    cout << "    Demarrage du serveur..." << endl;
    
   	SOCKADDR_IN                 ClientAddr;
	int                         ClientAddrLen;
	HANDLE                      hProcessThread;
	SOCKET                      NewConnection;
	struct thread_param         p;
    
    // Creation de la socket d'ecoute
   	if((ListeningSocket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
		cerr << "ne peut créer la socket. Erreur n° " << WSAGetLastError()<< endl;
		WSACleanup();
		return 1;
	}

    // On accroche la socket au port d'ecoute
	if(bind(ListeningSocket,(SOCKADDR *)&ServerAddr,sizeof(ServerAddr))==SOCKET_ERROR){
		cerr << "bind a échoué avec l'erreur " << WSAGetLastError() << endl;
		cerr << "Le port est peut-être déjà utilisé par un autre processus " << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return 1;
	}

    // Ecoute de la socket
	if(listen(ListeningSocket,5)==SOCKET_ERROR){
		cout << "listen a échoué avec l'erreur " << WSAGetLastError() << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return 1;
	}
    
    running = true;
    cout << "    Socket d'ecoute : " << ListeningSocket << endl;
    cout << "    Demarrage du serveur...OK" << endl;
    cout << "-----------------------------------------------" << endl;
    system("PAUSE");
    system("CLS");
    cout << "    En attente connexion client..." << endl;

    int alreadyClear = 0;
    while(running){
        
        if((NewConnection=accept(ListeningSocket,(SOCKADDR *)&ClientAddr,&ClientAddrLen))==INVALID_SOCKET){
			cerr  << "accept a échoué avec l'erreur " << WSAGetLastError() << endl;
			closesocket(ListeningSocket);
			WSACleanup();
			return 1;
		}
       
		p.ser = this;
		p.soc = NewConnection;
		p.Addr = ClientAddr;

		if((hProcessThread = CreateThread(NULL,0,&Serveur::ThreadLauncher,&p,0,NULL))==NULL){
			cerr << "CreateThread a échoué avec l'erreur " <<GetLastError()<< endl;
			closesocket( ListeningSocket );
			WSACleanup();
			return 1;
		}		
		
        if (alreadyClear== 0){
            alreadyClear ++;
            system("CLS"); 
        }
	}
    return 0;
}

int Serveur::pause(){
	running = false;
	cout << "Serveur en pause" << endl;
	closesocket(ListeningSocket);
	return 0;
}

// Lecture data Client
int Serveur::read(SOCKET soc, SOCKADDR_IN ClientAddr){  
    for(int i=0;i<50;i++) buffer_Recv[i] = '\0'; 
    // Reception message client          
    if (recv(soc,buffer_Recv,sizeof(buffer_Recv),0) == SOCKET_ERROR) {
       color(4,0);     
       cout << inet_ntoa( ClientAddr.sin_addr) << " se deconnecte..." << endl;
       return 1;
    }
    color(7,0); 
    cout << inet_ntoa( ClientAddr.sin_addr) << " >> " << buffer_Recv << endl;
    return 0;
}

void Serveur::color(int couleurDuTexte,int couleurDeFond){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

/* ======================================================================== */
/* ========================== thread proc ================================= */
/* ======================================================================== */

DWORD Serveur::ClientThread(SOCKET soc,SOCKADDR_IN ClientAddr){ 
    color(3,0);
	cout << inet_ntoa( ClientAddr.sin_addr ) << " se connecte..."<< endl;
    while(1) if (read(soc,ClientAddr)!=0) break;
    return 0;
}





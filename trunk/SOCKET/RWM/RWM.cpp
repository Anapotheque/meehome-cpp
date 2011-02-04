#include "define.h"

// Constructeur
RWM::RWM(){
                              
    string str_port_clt,str_port_serv,str_ip;
    
    color(7,0);
    
    listeClient = new ListeClient();
    listeClient->suivant = NULL;
    
    cout << "Port serveur : " << flush;
    getline(cin, str_port_serv);
    serveur = new Serveur(atoi(str_port_serv.c_str()),listeClient);

    listeClient->ajoutClient(new Client("192.168.1.10",100));    
    //listeClient->ajoutClient(new Client("192.168.1.10",200));
    //listeClient->ajoutClient(new Client("192.168.1.10",300));
    //listeClient->ajoutClient(new Client("192.168.1.10",400));
}

// Initialisation du serveur
int RWM::init(){

    color(2,0);
 
     // Initialisation du serveur
    if (serveur->init() !=0) {
  		system("PAUSE");
		return EXIT_FAILURE;                   
    }
 
    listeClient->initListeClient();
    
    return 0;
}

// Demarrage du serveur
int RWM::start(){
    
    // Demarrage du serveur
    if (serveur->start() !=0) {
  		cout << "ne peut demarrer le serveur"<< endl;
		return 1;                    
    }
    
    listeClient->startListeClient();
    
    return 0;
}
    
// Mise ne route du RMW
int RWM::run(){    
    
	HANDLE                      hProcessThread;
	struct thread_param_RWM     c;
	
    c.rwm = this;
    
    // thread Serveur
    if ((hProcessThread=CreateThread(NULL,0,&RWM::ThreadLauncherRMW,&c,0,NULL))==NULL ){
		cout << "CreateThread a échoué avec l'erreur " <<GetLastError()<< endl;
		return 1;
	}
    
    system("CLS");
    
    // mise en route des clients
    if(listeClient->runListeClient() != 0){
        cout << "Probleme sur la liste des clients" << endl;
        return 1;
    }
        
    return 0;
}

void RWM::color(int couleurDuTexte,int couleurDeFond){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

/* ======================================================================== */
/* ========================== thread proc ================================= */
/* ======================================================================== */

DWORD RWM::RMWThread(){
    // Demarrage du serveur
    if (serveur->ecoute() !=0){
  		cerr << "    le serveur ne peut pas ecouter"<< endl;
  		cerr << "    ---------------------------"<< endl;
		return 1;                   
    }
    return 0;
}





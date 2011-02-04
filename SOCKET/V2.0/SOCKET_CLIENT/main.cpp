#include "define.h"

int main(int argc, char *argv[])
{   
        
    Client *client = new Client();
        
    // Initialisation du serveur
    if (client->init() !=0) {
  		system("PAUSE");
		return EXIT_FAILURE;                   
    }

    // Demarrage du serveur
    if (client->start() !=0) {
  		system("PAUSE");
		return EXIT_FAILURE;                   
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;    
}



/*
    struct in_addr  MyAddressLocale;
    struct in_addr  MyAddressDistante;
    
	struct hostent  *hostDistant;
	struct hostent  *hostLocal;
	
	char HostNameDistant[_MAX_HOST_LENGTH_]= "eripc208";"xpsp2-d03e1ac45";
	char HostNameLocal[_MAX_HOST_LENGTH_]= "eripc208";"xpsp2-d03e1ac45";                    
	
    // recuperation du type d'Hote
	if( (hostDistant = gethostbyname( HostNameLocal ) ) == NULL){
        color(4,0); 
        cerr << "-----------------------------------------------" << endl;
		cerr << "Le serveur local n'existe pas..." << endl;
		cerr << "Erreur : " << WSAGetLastError() << endl;
		cerr << "-----------------------------------------------" << endl;
		return 1;
	}
	
    // recuperation du type d'Hote
	if( (hostLocal = gethostbyname( HostNameDistant ) ) == NULL){
        color(4,0); 
        cerr << "-----------------------------------------------" << endl;
		cerr << "Le serveur distant n'existe pas..." << endl;
		cerr << "Erreur : " << WSAGetLastError() << endl;
		cerr << "-----------------------------------------------" << endl;
		return 1;
	}

    // Detecte mon adresse
	memcpy(&MyAddressLocale.s_addr, hostLocal->h_addr_list[0],sizeof(MyAddressLocale.s_addr));
	memcpy(&MyAddressDistante.s_addr, hostDistant->h_addr_list[0],sizeof(MyAddressDistante.s_addr));

  ServerAddrLocale.sin_addr.s_addr    = inet_addr(inet_ntoa(MyAddressLocale)); 
*/


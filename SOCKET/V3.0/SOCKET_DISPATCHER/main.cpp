#include "define.h"

int main(int argc, char *argv[])
{
    Serveur *serveur = new Serveur();

    // Initialisation
    if (serveur->init() !=0) {
  		cerr << "ne peut initialiser le RWM"<< endl;
  		system("PAUSE");
		return 1;                   
    }

    // Demarrage
    if (serveur->start() !=0) {
  		cerr << "ne peut démarrer le RWM"<< endl;
  		system("PAUSE");
		return 1;                   
    }
    
    // Ecoute
    if (serveur->ecoute() !=0) {
  		cerr << "ne peut démarrer le RWM"<< endl;
  		system("PAUSE");
		return 1;                   
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;    
}

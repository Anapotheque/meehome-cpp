#include "Define.h"

int main(int argc, char *argv[])
{
    // On instancie un nouveau serveur
    Serveur *serveur = new Serveur();

    // Initialisation du serveur
    if (serveur->init() !=0) {
  		cerr << "ne peut initialiser le serveur"<< endl;
  		system("PAUSE");                  
    }
    
    // Demarrage du serveur
    if (serveur->start() !=0) {
  		cerr << "ne peut démarrer le serveur"<< endl;
  		system("PAUSE");                
    }
    
    // Sortie
    system("PAUSE");
    return EXIT_SUCCESS;    
}

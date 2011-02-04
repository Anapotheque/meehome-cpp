#include "define.h"

int main(int argc, char *argv[])
{
    RWM *rwm = new RWM();

    // Initialisation
    if (rwm->init() !=0) {
  		cerr << "ne peut initialiser le RWM"<< endl;
  		system("PAUSE");
		return 1;                   
    }

    // Demarrage
    if (rwm->start() !=0) {
  		cerr << "ne peut démarrer le RWM"<< endl;
  		system("PAUSE");
		return 1;                   
    }
   
    // Plug
    if (rwm->run() !=0) {
  		cerr << "RWM ne roule pas"<< endl;
  		system("PAUSE");
		return 1;                   
    }
    
    system("PAUSE");
    return EXIT_SUCCESS;    
}

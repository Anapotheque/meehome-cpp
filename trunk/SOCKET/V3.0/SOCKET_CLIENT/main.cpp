#include "define.h"

int main(int argc, char *argv[])
{   
    
    Client *client;
    client = new Client();
    
    while(1){
             
        system("CLS");     
        
        // Initialisation du serveur
        if (client->init() !=0) system("PAUSE");
        
        // Demarrage du serveur
        if (client->start() !=0) system("PAUSE"); 
         
    }
    
    return EXIT_SUCCESS;   
     
}

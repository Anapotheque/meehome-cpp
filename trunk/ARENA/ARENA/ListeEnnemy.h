#ifndef H_LISTEENNEMY
#define H_LISTEENNEMY

#include "define.h"
#include "ennemy.h"

class ListeEnnemy {
 
public :   
  
ennemy *obj;  
ListeEnnemy *suivant;

void ajoutEnnemy(ennemy *); 
void supprimeEnnemy();       
       
};

#endif

#ifndef H_LISTMISSILE
#define H_LISTMISSILE

#include "define.h"
#include "missile.h"

class listMissile{

public: 
missile *obj;
listMissile *suivant;

void ajoutMissile(missile *); 
void supprimeMissile(missile *);     
};
#endif

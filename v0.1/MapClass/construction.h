#ifndef DEF_CONSTRUCTION
#define DEF_CONSTRUCTION

#include <string>

#include "../Fonctions/fonctions.h"
#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "position.h"

class Construction
{
    public :
        Construction(std::string const& nameFile) ;

        
    private :
        MapPos m_pos ;

        

};


#endif
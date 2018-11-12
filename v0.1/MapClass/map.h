#ifndef DEF_MAP
#define DEF_MAP

#include <string>
#include <vector>
#include <map>

#include "../Fonctions/fonctions.h"
#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/construction.h"
#include "../MapClass/terrain.h"
#include "../CharactersClass/AbstractUnit.h"
#include "../CharactersClass/AbstractPlayer.h"

#include "position.h"

class Map
{
    public :
        Map(std::vector <AbstractPlayer> const& list_player) ;
        unsigned short height() const ;
        unsigned short width() const;
        SurfaceAffichage const& getSurface() const ;
        
    private :
        std::vector <AbstractUnit> m_list_unit ;
        std::vector <Construction> m_list_cons ; //construction
        std::map <MapPos, AbstractUnit*> m_map_unit ;
        std::map <MapPos, Construction*> m_map_cons ;
        Terrain m_terrain ;

};


#endif
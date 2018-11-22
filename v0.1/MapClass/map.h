#ifndef DEF_MAP
#define DEF_MAP

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <map>
#include <list>

#include "../Fonctions/fonctions.h"
#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/construction.h"
#include "../MapClass/terrain.h"
#include "../CharactersClass/Unit.h"
#include "../CharactersClass/AbstractPlayer.h"
#include "position.h"

class Map
{
    public :
        Map(unsigned short x, unsigned short y) ;
        Map() ;
        ~Map() ;
        unsigned short height() const ;
        unsigned short width() const;
        SurfaceAffichage const& getSurface() const ;

        MapPos random_free_pos () ;
        unsigned int nb_free_pos () ;

        bool add_unit (Unit const& unit) ;
        bool add_cons (Construction const& cons) ;

    private :
        void add_unit_texture(Unit const& unit) ;
        void add_cons_texture(Construction const& cons) ;
        void del_unit_texture(Unit const& unit) ;
        void del_cons_texture(Construction const& cons) ;
        
    private :
        std::vector <Unit> m_list_unit ;
        std::vector <Construction> m_list_cons ; //construction
        std::map <MapPos, short> m_map_unit ;
        std::map <MapPos, short> m_map_cons ;
        SurfaceAffichage* m_graphic_map ;
        std::list <MapPos> m_free_pos ;
        Terrain m_terrain ;

};


#endif
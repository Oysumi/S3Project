#ifndef DEF_MAP
#define DEF_MAP

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <map>
#include <list>
#include "SDL/SDL.h"

#include "../Fonctions/fonctions.h"
#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/construction.h"
#include "../MapClass/terrain.h"
#include "../CharactersClass/Unit.h"
#include "position.h"

class AbstractPlayer ;

class Map
{
    public :
        Map(unsigned short x, unsigned short y) ;
        Map() ;
        ~Map() ;
        unsigned short height() const ;
        unsigned short width() const;
        unsigned short sprite_size() const ;
        SurfaceAffichage const& getSurface() const ;

        MapPos mapPos_of_click (SDL_Rect const& scroll, unsigned short const& x, unsigned short const& y) const ;
        Unit* unit_on (MapPos const& pos) const ;
        Construction* cons_on (MapPos const& pos) const ;

        MapPos random_free_pos () ;
        unsigned int nb_free_pos () const ;

        bool add_unit (Unit const& unit) ;
        bool add_cons (Construction const& cons) ;

        void add_symbol (SurfaceAffichage const& surface, MapPos const& pos, bool audessus = true) ;
        void delete_all_symbol() ;

    private :
        void add_unit_texture(Unit const& unit) ;
        void add_cons_texture(Construction const& cons, bool reecriture = true) ;
        
        void add_unit_texture(Unit* punit) ;
        void add_cons_texture(Construction* pcons, bool reecriture = true) ;

        void del_unit_texture(Unit const& unit) ;
        void del_cons_texture(Construction const& cons) ;

        void resest_texture(MapPos const& pos) ;
        void ajouter(SurfaceAffichage const& surf, MapPos const& pos) ;
        
    private :
        std::vector <Unit*> m_list_unit ;
        std::vector <Construction*> m_list_cons ; //construction
        std::map <MapPos, Unit*>* m_map_unit ;
        std::map <MapPos, Construction*>* m_map_cons ;
        SurfaceAffichage* m_graphic_map ;
        std::list <MapPos> m_free_pos ;
        std::vector <MapPos> m_list_pos_symbol ;
        Terrain m_terrain ;
        AbstractPlayer* m_current_player_vision ;
};


#endif
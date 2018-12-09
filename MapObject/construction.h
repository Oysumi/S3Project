#ifndef DEF_CONSTRUCTION
#define DEF_CONSTRUCTION

#include <string>
#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include "../MapObject/mapobject.h"
#include "../MapClass/terrain.h"

#define NB_COLOR 2

#define NB_TYPE_CONSTRUCTION  1
#define CONSTRUCTION_GROUND 0

class Construction : public MapObject
{
    public :
    	Construction(unsigned short type, MapPos const& pos, AbstractPlayer* const& player) ;
        Construction(Construction const& aCopier) ;

        virtual SurfaceAffichage getSurface() const ;
        static std::string sprite_construction_path ;

    protected :
    	unsigned short m_type ;
};


#endif
#ifndef DEF_CONSTRUCTION
#define DEF_CONSTRUCTION

#include <string>
#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include "../MapObject/mapobject.h"
#include "../MapClass/terrain.h"


#define NB_TYPE_CONSTRUCTION 6

#define CONSTRUCTION_CASTLE1  0
#define CONSTRUCTION_CASTLE2  1
#define CONSTRUCTION_ARCHERY1 2
#define CONSTRUCTION_ARCHERY2 3
#define CONSTRUCTION_FARM     4
#define CONSTRUCTION_TOWER    5

#define OBJECT_TYPE_CONSTRUCTION 1

class Construction : public MapObject
{
    public :
    	Construction(unsigned short type, MapPos const& pos, AbstractPlayer* const& player) ;
        Construction(Construction const& aCopier) ;

        virtual SurfaceAffichage const& getSurface() const ;
        virtual unsigned short type () const ;
        virtual bool canMove () const ;

        void capture_by (AbstractPlayer * new_propietaire) ;

        static std::string sprite_construction_path ;
        static SpriteTexture* sprite_construction ;
        static SurfaceAffichage*** construction_affichage ;
        static void initSprtiteTexture() ;
        static void deleteSprtiteTexture() ;

    protected :
    	unsigned short m_type ;
};


#endif
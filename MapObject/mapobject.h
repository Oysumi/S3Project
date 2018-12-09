#ifndef __MAPOBJECT_H__
#define __MAPOBJECT_H__

#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/position.h"

#include <string>

class AbstractPlayer ;

//La classe Abstraite MapObject représente toute les map
class MapObject
{
	public:
		MapObject(MapPos const& pos, AbstractPlayer* player) ;
		MapObject(MapObject const& aCopier) ;
		virtual ~MapObject();
		
		virtual SurfaceAffichage getSurface() const = 0 ;
		MapPos const& getPos() const ;
		AbstractPlayer* proprietaire () const ;

	protected:

		MapPos m_pos ;
		AbstractPlayer * m_proprietaire ;
} ;

#endif // __UNIT_H__
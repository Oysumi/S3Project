#ifndef __UNIT_H__
#define __UNIT_H__

#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include "../MapObject/mapobject.h"
#include "../MapClass/terrain.h"
#include <string>

#define NB_TYPE_UNIT  2
#define UNIT_CATAPULT 0
#define UNIT_BALISTE  1

#define OBJECT_TYPE_UNIT 0

class AbstractPlayer ;

class Unit : public MapObject
{
	public:
		Unit(unsigned short type, MapPos const& pos, AbstractPlayer* const& player) ;
		Unit(Unit const& aCopier) ;

		virtual SurfaceAffichage getSurface() const ;
		virtual unsigned short type () const ;
		virtual bool canMove () const ;

		bool move(MapPos const& pos) ;

		static std::string sprite_unit_path ;

	protected :
		void changePos (MapPos const& new_pos) ;

	protected:
		unsigned short m_type ;
		unsigned short m_vitesse ;
		unsigned short m_deplacement ;
		std::string m_name ;
		unsigned short int m_health ;
		short int m_strength ; // can be negative
		unsigned short int m_unit_size ;
		
} ;

#endif // __UNIT_H__
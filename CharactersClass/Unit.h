#ifndef __UNIT_H__
#define __UNIT_H__

#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include "../MapClass/objetmobile.h"
#include "../MapClass/terrain.h"
#include <string>

#define NB_COLOR 2

#define NB_TYPE_UNIT  2
#define UNIT_CATAPULT 0
#define UNIT_BALISTE  1

class AbstractPlayer ;

class Unit : public ObjetMobile
{
	public:
		Unit(unsigned short type, MapPos const& pos, AbstractPlayer* const& player) ;
		Unit(Unit const& aCopier) ;

		virtual SurfaceAffichage getSurface() const ;
		void changePos (MapPos const& new_pos) ;

		static std::string sprite_unit_path ;

	protected:
		unsigned short m_type ;
		std::string m_name ;
		unsigned short int m_health ;
		short int m_strength ; // can be negative
		unsigned short int m_unit_size ;
		
} ;

#endif // __UNIT_H__
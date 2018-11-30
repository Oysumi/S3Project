#ifndef __UNIT_H__
#define __UNIT_H__

#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include "../MapClass/objetmobile.h"
#include <string>

class AbstractPlayer ;

class Unit : public ObjetMobile
{
	public:
		Unit(std::string const& texture_path, MapPos const& pos, AbstractPlayer* const& player) ;
		Unit(Unit const& aCopier) ;
		~Unit() ;

		void changePos (MapPos const& new_pos) ;

	protected:
		std::string m_name ;
		unsigned short int m_health ;
		short int m_strength ; // can be negative
		unsigned short int m_unit_size ;
		
} ;

#endif // __UNIT_H__
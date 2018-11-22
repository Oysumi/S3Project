#ifndef __UNIT_H__
#define __UNIT_H__

#include "AbstractPlayer.h"
#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include <string>

class Unit
{
	public:
		Unit(std::string const& texture_path, MapPos const& pos) ;
		Unit(Unit const& aCopier) ;
		~Unit() ;
		Texture const& getSurface() const ;
		MapPos getPos() const ;
		void changePos (MapPos const& new_pos) ;

	private :
		void init_texture () ;

	protected:
		std::string m_name ;
		unsigned short int m_health ;
		short int m_strength ; // can be negative
		unsigned short int m_unit_size ;
		
		MapPos m_pos ;
		Texture * m_myTexture ;
		std::string m_texture_path ;
		AbstractPlayer * m_myOwner ;
} ;

#endif // __UNIT_H__
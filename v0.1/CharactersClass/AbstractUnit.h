#ifndef __ABSTRACTUNIT_H__
#define __ABSTRACTUNIT_H__

#include "AbstractPlayer.h"
#include "../DisplayClass/texture.h"
#include <string>

class AbstractUnit
{
	public:
		AbstractUnit() ;
		// we don't set the health to another value than 100 at the beginning
		AbstractUnit(std::string name, short int strength, unsigned short int size, unsigned short int posx, unsigned short int posy) ;
		// virtual void display() const ; virtuelle pure ?
		~AbstractUnit() ;
		// define two methods to set the owner and the texture


	protected:
		std::string m_name ;
		unsigned short int m_health ;
		short int m_strength ; // can be negative
		unsigned short int m_unit_size ;
		unsigned short int m_unit_posx ;
		unsigned short int m_unit_posy ;
		Texture * m_myTexture ;
		AbstractPlayer * m_myOwner ;
} ;

#endif // __ABSTRACTUNIT_H__
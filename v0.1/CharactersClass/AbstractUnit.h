#ifndef __ABSTRACTUNIT_H__
#define __ABSTRACTUNIT_H__

#include "AbstractPlayer.h"
#include "../DisplayClass/texture.h"
#include <string>

class AbstractUnit
{
	public:
		virtual void displayTo() = 0 ;

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
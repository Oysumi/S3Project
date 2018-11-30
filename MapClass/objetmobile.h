#ifndef __MOBILEOBJECT_H__
#define __MOBILEOBJECT_H__

#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include <string>

class AbstractPlayer ;

class ObjetMobile
{
	public:
		ObjetMobile(std::string const& texture_path, MapPos const& pos, AbstractPlayer* player) ;
		ObjetMobile(ObjetMobile const& aCopier) ;
		~ObjetMobile() ;
		
		Texture const& getSurface() const ;
		MapPos const& getPos() const ;
		AbstractPlayer* proprietaire () const ;

	protected :
		void init_texture () ;

	protected:

		MapPos m_pos ;
		Texture * m_texture ;
		std::string m_texture_path ;
		AbstractPlayer * m_proprietaire ;
} ;

#endif // __UNIT_H__
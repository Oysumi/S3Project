#ifndef __MOBILEOBJECT_H__
#define __MOBILEOBJECT_H__

#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/position.h"

#include <string>

class AbstractPlayer ;

//La classe Abstraite Objet Mobile représente toute les map
class ObjetMobile
{
	public:
		ObjetMobile(MapPos const& pos, AbstractPlayer* player) ;
		ObjetMobile(ObjetMobile const& aCopier) ;
		virtual ~ObjetMobile();
		
		virtual SurfaceAffichage getSurface() const = 0 ;
		MapPos const& getPos() const ;
		AbstractPlayer* proprietaire () const ;

	protected:

		MapPos m_pos ;
		AbstractPlayer * m_proprietaire ;
} ;

#endif // __UNIT_H__
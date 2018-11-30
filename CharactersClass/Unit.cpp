#include "Unit.h"
#include "SDL/SDL.h"
using namespace std ;


Unit::Unit(string const& texture_path, MapPos const& pos, AbstractPlayer* const& player) :
	ObjetMobile(texture_path, pos, player) {}

Unit::Unit(Unit const& aCopier) : 
	ObjetMobile(aCopier) {}

Unit::~Unit()
{
	if (m_texture != NULL)
	{
		delete m_texture ;
		m_texture = NULL ;
	}
}

void Unit::changePos (MapPos const& new_pos)
{
	m_pos = new_pos ;
}


#include "Unit.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std ;

string Unit::sprite_unit_path = "../ressources/catapult.bmp" ;

Unit::Unit(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	MapObject(pos,player),
	m_type(type%NB_TYPE_UNIT)
	{}

Unit::Unit(Unit const& aCopier) : 
	MapObject(aCopier),
	m_type(aCopier.m_type) 
	{}

SurfaceAffichage Unit::getSurface() const
{
	SurfaceAffichage s (MAP_CASE_SIZE,MAP_CASE_SIZE) ;
	s.ajouter(SpriteTexture(sprite_unit_path,MAP_CASE_SIZE,NB_COLOR,NB_TYPE_UNIT), m_proprietaire->colorId()) ;
	s.rendre_transparente() ;
	return s ;
}

unsigned short Unit::type () const
{
	return OBJECT_TYPE_UNIT ;
}

bool Unit::deplacer(MapPos const& pos)
{
	if (pos != m_pos && pos.adjacent(m_pos, m_deplacement))
	{
		m_deplacement -= m_pos.separation_value(pos) ;
		m_pos = pos ;
		return true ;
	}
	return false ;
}

void Unit::changePos (MapPos const& new_pos)
{
	m_pos = new_pos ;
}


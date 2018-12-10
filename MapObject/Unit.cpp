#include "Unit.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std ;

string Unit::sprite_unit_path = "../ressources/catapult.bmp" ;

Unit::Unit(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	MapObject(pos,player),
	m_type(type%NB_TYPE_UNIT)
	{
		m_vitesse = 2 ;
		m_deplacement = m_vitesse ;
	}

Unit::Unit(Unit const& aCopier) : 
	MapObject(aCopier),
	m_type(aCopier.m_type)
	{
		m_vitesse = aCopier.m_vitesse ;
		m_deplacement = m_vitesse ;
	}

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

void Unit::reset_deplacement()
{
	m_deplacement = m_vitesse ;
}

bool Unit::canMove_at (MapPos const& pos) const
{
	if (pos != m_pos && pos.adjacent(m_pos, m_deplacement))
		return true ;
	return false ;
}

bool Unit::move(MapPos const& pos)
{
	if (canMove_at(pos))
	{
		m_deplacement -= m_pos.separation_value(pos) ;
		m_pos = pos ;
		return true ;
	}
	return false ;
}

bool Unit::canMove () const
{
	return m_deplacement > 0 ;
}

void Unit::changePos (MapPos const& new_pos)
{
	m_pos = new_pos ;
}


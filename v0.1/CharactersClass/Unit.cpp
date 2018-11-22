#include "Unit.h"
#include "SDL/SDL.h"
using namespace std ;

Unit::Unit(string const& texture_path, MapPos const& pos) : m_pos(pos)
{
	m_texture_path = texture_path ;
	init_texture() ;
}

Unit::Unit(Unit const& aCopier) : m_pos(aCopier.m_pos)
{
	m_texture_path = aCopier.m_texture_path ;
	init_texture() ;
}

void Unit::init_texture ()
{
	m_myTexture = new Texture(m_texture_path) ;
	SDL_SetColorKey(m_myTexture->surface(), SDL_SRCCOLORKEY, SDL_MapRGB(m_myTexture->surface()->format, 255, 255, 255));
}

Unit::~Unit()
{
	delete m_myTexture ;
}

Texture const& Unit::getSurface() const
{
	return *m_myTexture ;
}

MapPos Unit::getPos() const
{
	return m_pos ;
}

void Unit::changePos (MapPos const& new_pos)
{
	m_pos = new_pos ;
}
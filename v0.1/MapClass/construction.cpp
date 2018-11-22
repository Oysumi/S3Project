#include "construction.h"
#include "SDL/SDL.h"
using namespace std;

Construction::Construction(std::string const& texture_path, MapPos const& pos, AbstractPlayer* proprietaire) : m_pos(pos)
{
	m_proprietaire = proprietaire ;
	m_texture_path = texture_path ;
	m_texture = new Texture(m_texture_path) ;
	SDL_SetColorKey(m_texture->surface(), SDL_SRCCOLORKEY, SDL_MapRGB(m_texture->surface()->format, 255, 255, 255));
}

Construction::Construction(Construction const& aCopier) : m_pos(aCopier.m_pos)
{
	m_proprietaire = aCopier.m_proprietaire ;
	m_texture_path = aCopier.m_texture_path ;
	m_texture = new Texture(m_texture_path) ;
	SDL_SetColorKey(m_texture->surface(), SDL_SRCCOLORKEY, SDL_MapRGB(m_texture->surface()->format, 255, 255, 255));
}

Construction::~Construction()
{
	delete m_texture ;
}

Texture const& Construction::getSurface() const
{
	return *m_texture ;
}

MapPos const& Construction::getPos() const
{
	return m_pos ;
}

void Construction::changePos (MapPos const& new_pos)
{
	m_pos = new_pos ;
}
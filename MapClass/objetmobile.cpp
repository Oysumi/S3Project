#include "objetmobile.h"
#include "SDL/SDL.h"
using namespace std;

ObjetMobile::ObjetMobile(std::string const& texture_path, MapPos const& pos, AbstractPlayer* proprietaire) : m_pos(pos)
{
	m_proprietaire = proprietaire ;
	m_texture_path = texture_path ;
	m_texture = new Texture(m_texture_path) ;
	SDL_SetColorKey(m_texture->surface(), SDL_SRCCOLORKEY, SDL_MapRGB(m_texture->surface()->format, 255, 255, 255));
}

ObjetMobile::ObjetMobile(ObjetMobile const& aCopier) : m_pos(aCopier.m_pos)
{
	m_proprietaire = aCopier.m_proprietaire ;
	m_texture_path = aCopier.m_texture_path ;
	m_texture = new Texture(m_texture_path) ;
	SDL_SetColorKey(m_texture->surface(), SDL_SRCCOLORKEY, SDL_MapRGB(m_texture->surface()->format, 255, 255, 255));
}

ObjetMobile::~ObjetMobile()
{
	cout << "===========================================" << endl ;
	cout << "Debut destruction objet..." << endl ;
	if (m_texture != NULL)
	{
		delete m_texture ;
		m_texture = NULL ;
	}
	cout << "Fin destruction object." << endl ;
	cout << "===========================================" << endl ;
}

Texture const& ObjetMobile::getSurface() const
{
	return *m_texture ;
}

MapPos const& ObjetMobile::getPos() const
{
	return m_pos ;
}
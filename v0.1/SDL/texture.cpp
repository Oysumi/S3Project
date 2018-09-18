#include "texture.h"
using namespace std;


//CONSTRUCTEUR
Texture::Texture(string const& path)
{

	m_surface = SDL_LoadBMP(path.c_str()) ;

    if(!m_surface)
    {
        erreur("Impossible de charger " + path + " : " + SDL_GetError()) ;
    }

    m_surface = SDL_DisplayFormat(m_surface) ;

    if(!m_surface)
    {
        erreur("Impossible de charger " + path + " (DisplayFormat a échoué) : " + SDL_GetError()) ;
    }

}

//DESTRUCTEUR
Texture::~Texture()
{
	SDL_FreeSurface(m_surface) ;
}


//ACCESSEUR
SDL_Surface * Texture::surface() const
{
	return m_surface ;
}
#include "Texte.h"
#include "../MenuClass/AbstractButton.h"

using namespace std ;

#define TYPEFACE 30
#define SHIFT_X 25

Texte::Texte(string textToWrite, SDL_Color font_color, int size, std::string font)
{
    m_size = size ;
	m_font = TTF_OpenFont (string("../font/"+font+".ttf").c_str(), size) ;
	if(!m_font)
    	erreur_message("Impossible de charger la police d'écriture du Jeu" + string(TTF_GetError())) ;

	m_surface = NULL ;
	changeText(textToWrite, font_color, size) ;
}

Texte::Texte() : Texte("")
{}

Texte::~Texte()
{
	freeSurface() ;
	TTF_CloseFont(m_font) ;
}

void Texte::changeText (std::string textToWrite, SDL_Color font_color, int size)
{
	/* Writting the text in the SDL_Surface */
	m_text = TTF_RenderText_Blended(m_font,textToWrite.c_str(),font_color) ;
	freeSurface() ;
	m_surface = new SurfaceAffichage (m_text->w, m_text->h, this->m_text) ;
}

void Texte::addTexture (SurfaceAffichage const& surface, unsigned short x, unsigned short y)
{
	m_surface->ajouter(surface,x,y) ;
}

void Texte::freeSurface()
{
	if(m_surface != NULL)
	{
		delete(m_surface) ;
		m_surface = NULL ;
	}
}

/***************************************************************************************/

int Texte::width() const
{
	return m_text->w ;
}

int Texte::height() const
{
	return m_text->h ;
}

SurfaceAffichage const& Texte::surfaceAffichage() const
{
	return *m_surface ;
}

void Texte::displayText(SurfaceAffichage& surf, AbstractButton const& b, unsigned short pos_font) const
{
	if (pos_font == LEFT_TEXT)
		surf.ajouter(*m_surface, 0, (surf.height()-m_text->h)/2) ;
	else
		surf.ajouter(*m_surface, (surf.width()-m_text->w)/2, (surf.height()-m_text->h)/2) ;
}
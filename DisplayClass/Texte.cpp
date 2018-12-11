#include "Texte.h"
#include "../MenuClass/AbstractButton.h"

using namespace std ;

#define TYPEFACE 30
#define SHIFT_X 25

Texte::Texte(string textToWrite, SDL_Color font_color, int size)
{
    m_size = size ;
	m_font = TTF_OpenFont ("../font/04B_30__.TTF", size) ;
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

void Texte::displayText(Fenetre& screen, AbstractButton const& b) const
{

	int pos_x = b.getPosX() + ( b.getWidth() - m_text->w )/2  ;
	int pos_y = b.getPosY() + ( b.getHeight() - m_text->h) /2 ;
	screen.ajouter(*m_surface, pos_x, pos_y) ;
}
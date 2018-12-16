#include "ActionButton.h"
#include "../DisplayClass/Texte.h"
#include <string>

using namespace std ;

// We are going to redefine these constructor according to our choice of the representation of the action ID

/**************************************************************************************************************
 *                                             CONSTRUCTORS                                                   *
 **************************************************************************************************************/

ActionButton::ActionButton()
{ 
	m_id = 0 ;
	m_surface = NULL ;
}

ActionButton::ActionButton(unsigned short int idToSet)
{ 
	m_id = idToSet ;
	m_surface = NULL ;
}

ActionButton::ActionButton( unsigned short int idToSet,
							string textToWrite,
							unsigned short int width,
							unsigned short int height,
							SDL_Color back,
							SDL_Color text,
							int size_text,
							unsigned short pos_text_auto,
							string font)
{
	if (idToSet == SUBMENU)
		erreur_message("Try to create not SubMenuButton with id SUBMENU") ;
	m_id = idToSet ;
	m_text = textToWrite ;
  	m_sizeText = size_text ;
  	m_pos_text = pos_text_auto ;
	this->setSize(width, height) ;
	this->setButtonColors(back, text) ;

	m_surface = NULL ;
	m_texte = NULL ;
	if(font == "")
		m_font = "montserrat-regular" ;
	setText(m_text,font) ;
}

void ActionButton::setColor(SDL_Color* background, SDL_Color* text)
{
	if (background != NULL)
		m_back_color = *background ;
	if (text != NULL)
		m_text_color = *text ;
	prepareSurface() ;
}

void ActionButton::setText(std::string text, string font)
{
	if (font != "")
		m_font = font ;
	m_text = text ;
	prepareSurface() ;
}

void ActionButton::prepareSurface()
{
	freeSurface() ;
    m_surface = new SurfaceAffichage(m_width, m_height) ;
	m_texte = new Texte(m_text,m_text_color,m_sizeText,m_font) ;
	if(SDL_FillRect(m_surface->surface(), NULL, SDL_MapRGB(m_surface->surface()->format, m_back_color.r, m_back_color.g, m_back_color.b)) != 0)
		erreur_message("Impossible de colorer l'un des boutons du menu :  " + string(SDL_GetError())) ;
	m_texte->displayText(*m_surface, *this, m_pos_text) ;
}

void ActionButton::addTexture (SurfaceAffichage const& surface, unsigned short x, unsigned short y)
{
	m_surface->ajouter(surface, x, y) ;
}


/**************************************************************************************************************
 *                                                  SETTERS                                                   *
 **************************************************************************************************************/
void ActionButton::setId(unsigned short int idToSet)
{
	m_id = idToSet ;
}

void ActionButton::setSize(unsigned short int width, unsigned short int height)
{
	m_width = width ;
	m_height = height ;
}

void ActionButton::setTextColor(SDL_Color const& text)
{
	m_text_color = text ;
}

void ActionButton::setBackgroundColor(SDL_Color const& back)
{
	m_back_color = back ;
}

void ActionButton::setButtonColors(SDL_Color const& background, SDL_Color const& text)
{
	this->setTextColor(text) ;
	this->setBackgroundColor(background) ;
}

/**************************************************************************************************************
 *                                                  GETTERS                                                   *
 **************************************************************************************************************/

SurfaceAffichage const& ActionButton::getSurfaceAffichage() const
{
	return *m_surface ;
}

Texte const& ActionButton::getTexte() const
{
	return *m_texte ;
}

// DESTRUCTEUR ET FONCTIONS ASSOCIEES

void ActionButton::freeSurface()
{
	if (m_surface!=NULL)
    {
        delete(m_surface) ;
        m_surface = NULL ;
    }
    if (m_texte!=NULL)
    {
        delete(m_texte) ;
        m_texte = NULL ;
    }
}

ActionButton::~ActionButton()
{
    freeSurface() ;
}
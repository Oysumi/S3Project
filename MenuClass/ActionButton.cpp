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

ActionButton::ActionButton(unsigned short int idToSet, const char * textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text, int size_text)
: ActionButton(idToSet, string(textToWrite), width, height, pos_x, pos_y, back, text, size_text)
{}

ActionButton::ActionButton(unsigned short int idToSet, string textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text, int size_text)
{
	if (idToSet == SUBMENU)
		erreur_message("Try to create not SubMenuButton with id SUBMENU") ;
	m_id = idToSet ;
	m_text = textToWrite ;
  	m_sizeText = size_text ;
	this->setSize(width, height) ;
	this->setPos(pos_x, pos_y) ;
	this->setButtonColors(back, text) ;

	m_surface = NULL ;
	m_texte = NULL ;
	setText(m_text) ;
}

void ActionButton::setText(std::string text)
{
	m_text = text ;
	freeSurface() ;
    m_surface = new SurfaceAffichage(m_width, m_height) ;
	m_texte = new Texte(m_text,m_text_color,m_sizeText) ;

}

void ActionButton::addTexture (SurfaceAffichage const& surface, unsigned short x, unsigned short y)
{
	m_surface->ajouter(surface,x,y) ;
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

void ActionButton::setPos(unsigned short int pos_x, unsigned short int pos_y)
{
	m_posx = pos_x ;
	m_posy = pos_y ;
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

void ActionButton::displayButton(Fenetre& screen) const
{
	SDL_Surface* surface = m_surface->surface() ;
	SDL_Rect* srcect = NULL ;
	SDL_Rect* pos = (SDL_Rect*)malloc(sizeof(SDL_Rect)) ;
	pos->x = this->getPosX() ;
	pos->y = this->getPosY() ;
	SDL_Color couleur = this->getBackColor() ;

	if(SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, couleur.r, couleur.g, couleur.b)) != 0)
		erreur_message("Impossible de créer une surface pour afficher le menu :  " + string(SDL_GetError())) ;
	if(SDL_BlitSurface(surface, srcect, screen.surface(), pos))
        erreur_message("Impossible d'afficher le menu sur l'écran :  " + string(SDL_GetError())) ;

    free(pos) ;
}

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
#include "ActionButton.h"
#include <string>

using namespace std ;

// We are going to redefine these constructor according to our choice of the representation of the action ID

/**************************************************************************************************************
 *                                             CONSTRUCTORS                                                   *
 **************************************************************************************************************/

ActionButton::ActionButton()
{ 
	m_id = 0 ;
}

ActionButton::ActionButton(unsigned short int idToSet)
{ 
	m_id = idToSet ;
}

ActionButton::ActionButton(unsigned short int idToSet, const char * textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text, int size_text)
: ActionButton(idToSet, string(textToWrite), width, height, pos_x, pos_y, back, text, size_text)
{}

ActionButton::ActionButton(unsigned short int idToSet, string textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text, int size_text)
{
	m_id = idToSet ;
	m_text = textToWrite ;
  m_sizeText = size_text ;
	this->setSize(width, height) ;
	this->setPos(pos_x, pos_y) ;
	this->setButtonColors(back, text) ;
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

void ActionButton::setTextColor(SDL_Color text)
{
	m_text_color = text ;
}

void ActionButton::setBackgroundColor(SDL_Color back)
{
	m_back_color = back ;
}

void ActionButton::setButtonColors(SDL_Color background, SDL_Color text)
{
	this->setTextColor(text) ;
	this->setBackgroundColor(background) ;
}

/**************************************************************************************************************
 *                                                  GETTERS                                                   *
 **************************************************************************************************************/

SurfaceAffichage ActionButton::getSurfaceAffichage()
{
	SurfaceAffichage surface(m_width, m_height) ;

	return surface ;
}

void ActionButton::displayButton(Fenetre screen)
{
	SurfaceAffichage button = this->getSurfaceAffichage() ;
	SDL_Surface* surface = button.surface() ;
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

ActionButton::~ActionButton()
{ }
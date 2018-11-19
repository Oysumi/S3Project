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

ActionButton::ActionButton(unsigned short int idToSet, const char * textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text)
{
	m_id = idToSet ;
	m_text = textToWrite ;
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

unsigned short int ActionButton::getPosX() const
{
	return this->m_posx ;
}

unsigned short int ActionButton::getPosY() const
{
	return this->m_posy ;
}

SDL_Color ActionButton::getBackgroundColor() const
{
	return this->m_back_color ;
}

SDL_Color ActionButton::getTextColor() const
{
	return this->m_text_color ;
}

ActionButton::~ActionButton()
{ }
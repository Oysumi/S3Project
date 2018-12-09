#include "AbstractButton.h"

using namespace std ;

unsigned int AbstractButton::getPosX() const
{
	return this->m_posx ;
}

unsigned int AbstractButton::getPosY() const
{
	return this->m_posy ;
}

unsigned int AbstractButton::getWidth() const
{
	return this->m_width ;
}

unsigned int AbstractButton::getHeight() const
{
	return this->m_height ;
}

int AbstractButton::getID() const
{
	return this->m_id ;
}

void AbstractButton::setPosX(unsigned int x)
{
	m_posx = x ;
}

void AbstractButton::setPosY(unsigned int y)
{
	m_posy = y ;
}

void AbstractButton::setText(std::string text)
{
	m_text = text ;
}

SDL_Color AbstractButton::getBackColor() const
{
	return this->m_back_color ;
}

SDL_Color AbstractButton::getTextColor() const
{
	return this->m_text_color ;
}

const char * AbstractButton::getText() const
{
	return m_text.c_str() ;
}

AbstractButton::~AbstractButton() { };
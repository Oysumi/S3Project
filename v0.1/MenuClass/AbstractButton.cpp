#include "AbstractButton.h"

unsigned int AbstractButton::getPosX()
{
	return this->m_posx ;
}

unsigned int AbstractButton::getPosY()
{
	return this->m_posy ;
}

unsigned int AbstractButton::getSize()
{
	return this->m_size ;
}

void AbstractButton::setPosX(unsigned int x)
{
	m_posx = x ;
}

void AbstractButton::setPosY(unsigned int y)
{
	m_posy = y ;
}
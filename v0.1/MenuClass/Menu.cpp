#include "Menu.h"

void Menu::setSize(unsigned short int size)
{
	m_size = size ;
}

void Menu::setPos(unsigned short int x, unsigned short int y)
{
	m_pos_x = x ;
	m_pos_y = y ;
}

void Menu::setColor(SDL_Color col)
{
	m_background = col ;
}
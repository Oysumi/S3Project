#ifndef __MENU_H__
#define __MENU_H__

#include "AbstractButton.h"
#include <SDL/SDL.h>
#include <list>

class Menu
{
	public:
		void setSize(unsigned short int size) ;
		void setPos(unsigned short int x, unsigned short int y) ;
		void setColor(SDL_Color col) ;

	protected:
		std::list<AbstractButton> m_myButtons ;
		unsigned short int m_size ;
		unsigned short int m_pos_x ;
		unsigned short int m_pos_y ;
		SDL_Color m_background ;
		static std::list<AbstractButton> * m_listButtons ;
};

#endif // __MENU_H__
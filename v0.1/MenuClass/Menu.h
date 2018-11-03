#ifndef __MENU_H__
#define __MENU_H__

#include "AbstractButton.h"
#include <SDL/SDL.h>
#include <vector>
#include "../DisplayClass/fenetre.h"

class Menu
{
	protected:
		std::vector<AbstractButton> m_myButtons ;
		unsigned short int m_height ;
		unsigned short int m_width ;
		unsigned short int m_pos_x ; // coin en haut à gauche
		unsigned short int m_pos_y ; // coin en haut à gauche
		SDL_Color m_background ;

	private:
		void calculPosButton(std::vector<AbstractButton> buttons) ;
	
	public:
		Menu(std::vector<AbstractButton> buttons, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back) ;
		SurfaceAffichage getMenu() ;
		SDL_Color getColor() ;
		unsigned short getPosX() ;
		unsigned short getPosY() ;
		void displayMenu(Fenetre screen) ;
		
};

#endif // __MENU_H__
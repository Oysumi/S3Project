#ifndef __MENU_H__
#define __MENU_H__

#include "AbstractButton.h"
#include <SDL/SDL.h>
#include <vector>
#include "../DisplayClass/fenetre.h"

#include <vector>

class Menu
{
	protected:
		std::vector<AbstractButton*> m_myButtons ;
		unsigned short int m_height ;
		unsigned short int m_width ;
		unsigned short int m_pos_x ; // coin en haut à gauche
		unsigned short int m_pos_y ; // coin en haut à gauche
		int m_id ;
		bool m_open ;
		SDL_Color m_background ;

		static unsigned short nb_menu ;

	public :
		static std::vector<Menu*> allMenu ;

	private:
		void calculPosButton(std::vector<AbstractButton*> buttons) ;
		bool clickIsOnThisMenu(unsigned int x, unsigned int y) ;
		int receiveAction(unsigned int x, unsigned int y);
	
	public:
		Menu(); 
		Menu(std::vector<AbstractButton*> buttons, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, int id) ;
		SurfaceAffichage getMenu() ;
		~Menu();
		SDL_Color getColor() ;
		unsigned short getPosX() ;
		unsigned short getPosY() ;
		void displayMenu(Fenetre& screen) ;
		int getID() ;
		void openCloseMenu();
		bool isOpen() ;
		
		static void openMenu(int id, Fenetre screen, bool openclose) ;
		static void keepOpening(Fenetre screen);
		static bool isAMenuOpened() ;
		static bool displayMenuWithId(int id, Fenetre& screen) ;
		static int getIdButtonOn(unsigned int x, unsigned int y) ; // Reçoit des coordonnées qui seront comparées avec la position des boutons du menu
										 // Retourne l'ID du bouton
		
};

#endif // __MENU_H__
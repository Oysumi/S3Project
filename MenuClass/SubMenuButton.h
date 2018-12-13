#ifndef __SUBMENUBUTTON_H__
#define __SUBMENUBUTTON_H__

#include "ActionButton.h"
#include <list>

class Menu ;

class SubMenuButton : public ActionButton
{
	public:
		SubMenuButton (int menu_id, std::string textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text, int size_text = 30) ;
		~SubMenuButton();

		void displayNewMenu(Menu* to_replace = NULL) ;
		static void initAllSubMenu() ;
	protected:
		Menu* m_menu ;
		unsigned short m_menu_id ;

		//Une fois que les menus sont crées on appelle cette méthode statique pour récupérer tous les pointeurs des Menu grâce à leurs ID
		static std::list<SubMenuButton*> listSubMenuButton ;
};

#endif // __SUBMENUBUTTON_H__
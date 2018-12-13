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
		SurfaceAffichage* m_surface ;
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
		void calculPosButton(std::vector<AbstractButton*> const& buttons) ;
		bool clickIsOnThisMenu(unsigned int x, unsigned int y) ;
		AbstractButton* receiveAction(unsigned int x, unsigned int y) const ;
	
	public:
		static std::vector <Menu*>* getAllMenu(std::vector <AbstractButton*> const& all_buttons, unsigned short const width, unsigned short const height) ;

		Menu(); 
		Menu(std::vector<AbstractButton*> const& buttons, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, int id) ;
		SurfaceAffichage const& getMenu() const ;
		~Menu();
		SDL_Color getColor() const ;
		unsigned short getPosX() const ;
		unsigned short getPosY() const ;
		void displayMenu(Fenetre& screen) const ;
		int getID() const ;
		void openCloseMenu();
		bool isOpen() const ;
		bool setTextButton(unsigned short nb, std::string const& text) ;
		
		static Menu* getMenuById(int id) ;
		static void openMenu(int id, Fenetre& screen) ;
		static void keepOpened(Fenetre& screen);
		static bool isAMenuOpened() ;
		static bool displayMenuWithId(int id, Fenetre& screen) ;
		static bool isOnOneMenu(unsigned int x, unsigned int y) ;
		static int getIdButtonOn(unsigned int x, unsigned int y) ; // Reçoit des coordonnées qui seront comparées avec la position des boutons du menu
										 // Retourne l'ID du bouton
		static bool openSubAssocTo(unsigned int x, unsigned int y) ;
		
};

#define ESCAPE_MENU 50
#define CHATEAU_MENU 51
#define CONSTRUCTION_UNIT_MENU 52
#define CONSTRUCTION_BATIMENT_MENU 53

#define LARGEUR_MENU1 450
#define HAUTEUR_MENU1 100
#define LARGEUR_MENU2 200
#define HAUTEUR_MENU2 60
#define LARGEUR_MENU3 200
#define HAUTEUR_MENU3 60

#endif // __MENU_H__
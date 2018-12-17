#ifndef __MENU_H__
#define __MENU_H__

#include "AbstractButton.h"
#include <SDL/SDL.h>
#include <vector>
#include "../DisplayClass/fenetre.h"

#include <vector>


#define DEFAULT_SEPARATION_W 10
#define DEFAULT_SEPARATION_H 3

class Menu
{
	protected:
		SurfaceAffichage* m_surface ;
		std::vector<AbstractButton*> m_myButtons ;
		std::vector< std::pair < unsigned short, unsigned short > > m_buttonsPos ;
		unsigned short int m_height ;
		unsigned short int m_width ;
		unsigned short m_separation_width ;
		unsigned short m_separation_height ;
		unsigned short int m_pos_x ; // coin en haut à gauche
		unsigned short int m_pos_y ; // coin en haut à gauche
		int m_id ;
		bool m_open ;
		SDL_Color m_background ;
		unsigned short const m_alpha ;

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
		Menu(std::vector<AbstractButton*> const& buttons,
			unsigned short int pos_x,
			unsigned short int pos_y,
			SDL_Color back,
			int id,
			unsigned short const transparenceAlpha = 255,
			unsigned short const separation_width = DEFAULT_SEPARATION_W,
			unsigned short const separation_height = DEFAULT_SEPARATION_H) ;
		
		SurfaceAffichage const& getMenu() const ;
		~Menu();
		SDL_Color getColor() const ;
		unsigned short getPosX() const ;
		unsigned short getPosY() const ;
		void displayMenu(Fenetre& screen) const ;
		int getID() const ;
		void openCloseMenu();
		bool isOpen() const ;
		unsigned short nb_button () const ;

		//Méthodes de modification des menu après leur création / Ne pas oublier d'appeler prepareSurface() pour recharger les modifications dans la Surface du Menu
		bool changeAssocTo(unsigned short nb_button, unsigned short id_menu) ; //modifie le menu associé du SubMenuButton numéro nb
		bool setTextButton(unsigned short nb, std::string const& text, std::string font = "") ; 
		bool setColorButton(unsigned short nb, SDL_Color* background, SDL_Color* text = NULL) ;
		AbstractButton* button (unsigned short nb) ;
		void prepareSurface() ;  //Actualise la surface d'Affichage du Menu
		
		static unsigned short widthTakeBy(std::vector<AbstractButton*> const& buttons, unsigned short const separation_width = DEFAULT_SEPARATION_W) ;
		static unsigned short heightTakeBy(std::vector<AbstractButton*> const& buttons, unsigned short const separation_height = DEFAULT_SEPARATION_H) ;

		static AbstractButton* getButtonById(int id) ;
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

#define ESCAPE_MENU 150

#define PETIT_CHATEAU_MENU 151
#define GRAND_CHATEAU_MENU 152
#define FERME_MENU 153
#define PETIT_ATELIER_MENU 154
#define GRAND_ATELIER_MENU 155
#define TOWER_MENU 156

#define PETIT_BATIMENT_MENU 160
#define GRAND_BATIMENT_MENU 161

#define PETITE_UNITE_MENU 162
#define GRANDE_UNITE_MENU 163

#define AMELIORER_CHATEAU_MENU 164
#define AMELIORER_FERME_MENU 165

#define UPGRADES_CHATEAU_MENU 170
#define UPGRADES_ATELIER_MENU 171

#define LARGEUR_MENU1 450
#define HAUTEUR_MENU1 60
#define LARGEUR_MENU2 245
#define HAUTEUR_MENU2 60
#define LARGEUR_MENU3 255
#define HAUTEUR_MENU3 60

#endif // __MENU_H__
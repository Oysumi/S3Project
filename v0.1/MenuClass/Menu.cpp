#include "Menu.h"
#include "ActionButton.h"
#include "../fonctions.h"

using namespace std ;

#define ID 5878 // id fixé au hasard pour les boutons

Menu::Menu(vector<AbstractButton> buttons, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back)
{
	m_pos_x = pos_x ;
	m_pos_y = pos_y ;
	m_background = back ;
	this->calculPosButton(buttons) ;
}

void Menu::calculPosButton(vector<AbstractButton> buttons)
{
	/**
	 * On calcule la taille du menu (lxL) en fonction des boutons qu'on suppose ici de taille fixe
	 * si l'on a une liste de x boutons, alors L = (x+1)*dx + x*largeur boutons + BANDE_MENU où dx est le shift avec le bord
	 *                                         l = 2*dy + largeur boutons où dy est le shift avec le bord du menu
	 */
	int nbButton = buttons.size() ;
	m_myButtons = vector<AbstractButton>(nbButton) ;
	int const DX = 10 ;
	int const DY = 10 ;
	int longueur = buttons[0].getSize(); // on suppose ici que tous les boutons ont la même taille pour le moment

	m_size_y = nbButton*(DY+longueur) + DX ;
	m_size_x = 2*DX + longueur ;

	/**
	 * Placement des boutons sur l'écran
	 */
	int i = 0 ;
	for ( AbstractButton b : buttons ){
		b.setPosX(m_pos_x + DY);
		b.setPosY(m_pos_y + i*(DX + longueur));
		m_myButtons[i] = b ;
		cout << "indice : " << i << " ; pos x : " << m_myButtons[i].getPosX() << " ; pos y : " << m_myButtons[i].getPosY() << endl ;
		i++ ;
	}
}

SDL_Color Menu::getColor()
{
	return this->m_background ;
}

SurfaceAffichage Menu::getMenu()
{
	SurfaceAffichage surface(m_size_x, m_size_y) ;

	return surface ;
}

void Menu::displayMenu(Fenetre screen)
{
	SurfaceAffichage menu = this->getMenu() ;
	SDL_Surface* surface = menu.surface() ;
	SDL_Rect* srcect = NULL ;
	SDL_Rect* pos = NULL ;
	SDL_Color couleur = this->getColor() ;

	if(SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, couleur.r, couleur.g, couleur.b)) != 0)
		erreur_message("Impossible de créer une surface pour afficher le menu :  " + string(SDL_GetError())) ;
	if(SDL_BlitSurface(surface, srcect, screen.surface(), pos))
        erreur_message("Impossible d'afficher le menu sur l'écran :  " + string(SDL_GetError())) ;

    for ( AbstractButton b : m_myButtons ){
    	b.displayButton(screen) ;
    }

    screen.actualiser() ;
}
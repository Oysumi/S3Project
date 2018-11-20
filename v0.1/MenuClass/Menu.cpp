#include "Menu.h"
#include "ActionButton.h"
#include "../Fonctions/fonctions.h"
#include "../DisplayClass/Texte.h"
#include "../ID/idbuttons.h"
#include "../ID/idmenus.h"

#include <iostream>

using namespace std ;

Menu::Menu(){ 
	m_id = NOTHING ;
} ; // Est utile pour la création d'un vector de Menu dans MatriceGameGestion.cpp

Menu::Menu(vector<AbstractButton*> buttons, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, int id)
{
	m_pos_x = pos_x ;
	m_pos_y = pos_y ;
	m_background = back ;
	m_id = id ;
	m_open = false ;
	this->calculPosButton(buttons) ;
}

SDL_Color Menu::getColor()
{
	return this->m_background ;
}

SurfaceAffichage Menu::getMenu()
{
	SurfaceAffichage surface(m_width, m_height) ;

	return surface ;
}

unsigned short Menu::getPosX()
{
	return this->m_pos_x ;
}

unsigned short Menu::getPosY()
{
	return this->m_pos_y ;
}

void Menu::calculPosButton(vector<AbstractButton*> buttons)
{
	/**
	 * On calcule la taille du menu (lxL) en fonction des boutons qu'on suppose ici de taille fixe
	 * si l'on a une liste de x boutons, alors L = (x+1)*dx + x*largeur boutons + BANDE_MENU où dx est le shift avec le bord
	 *                                         l = 2*dy + largeur boutons où dy est le shift avec le bord du menu
	 */
	int nbButton = buttons.size() ;
	m_myButtons = vector<AbstractButton*>(nbButton) ;
	int const LARGEUR = 10 ;
	int const HAUTEUR = 10 ;

	int boutonLargeur = buttons[0]->getWidth(); // on suppose ici que tous les boutons ont la même taille pour le moment
	int boutonHauteur = buttons[0]->getHeight() ; // idem

	m_height = nbButton*(HAUTEUR+boutonHauteur) + HAUTEUR ;
	m_width = 2*LARGEUR + boutonLargeur ;

	/**
	 * Placement des boutons sur l'écran
	 */
	int i = 0 ;
	for ( AbstractButton * b : buttons ){
		b->setPosX(m_pos_x + LARGEUR);
		b->setPosY(m_pos_y + (i+1)*HAUTEUR + i*boutonHauteur);
		m_myButtons[i] = b ;
		i++;
	}
}

void Menu::displayMenu(Fenetre screen)
{
	SurfaceAffichage menuAffichage = this->getMenu() ;
	SDL_Surface* menuSurface = menuAffichage.surface() ;
	SDL_Color couleur = this->getColor() ;

	if(SDL_FillRect(menuSurface, NULL, SDL_MapRGB(menuSurface->format, couleur.r, couleur.g, couleur.b)) != 0){
		erreur_message("Impossible de colorer le menu :  " + string(SDL_GetError())) ;
	}

	unsigned int posX = this->getPosX() ;
	unsigned int posY = this->getPosY() ;

	screen.ajouter(menuAffichage, posX, posY) ;
 
    for ( AbstractButton * b : m_myButtons ){
    	SurfaceAffichage bouton = b->getSurfaceAffichage() ;
    	SDL_Surface* boutonSurface = bouton.surface() ;
    	SDL_Color col = b->getBackColor() ;

    	posX = b->getPosX() ;
    	posY = b->getPosY() ;

    	if(SDL_FillRect(boutonSurface, NULL, SDL_MapRGB(boutonSurface->format, col.r, col.g, col.b)) != 0){
			erreur_message("Impossible de colorer l'un des boutons du menu :  " + string(SDL_GetError())) ;
    	}

    	screen.ajouter(bouton, posX, posY) ;
    	Texte text(b->getText()) ;
    	text.displayText(screen, b) ;
    }

    screen.actualiser() ;
}

int Menu::getID(){
	return m_id ;
}

void Menu::openCloseMenu(){
	m_open = ( m_open ) ? false : true ;
}

bool Menu::isOpen(){
	return m_open;
}

int Menu::receiveAction(unsigned int x, unsigned int y){
	unsigned int pos_x, pos_y, width, height ;
	unsigned short int id = NOTHING ;

	for (AbstractButton * b : m_myButtons){
		if (id == NOTHING){
			pos_x = b->getPosX();
			pos_y = b->getPosY();
			width = b->getWidth();
			height = b->getHeight();

			if (x >= pos_x && x <= pos_x + width && y >= pos_y && y <= pos_y + height){
				id = b->getID();
			}	 
		}
	}

	switch (id)
	{
		case RETOUR:
			break;
		case QUITTER:
			break;
		case ATTAQUER:
			break;
		case DEFENDRE:
			break;
		case ALLER_A:
			break;
	}

	return id ;
}
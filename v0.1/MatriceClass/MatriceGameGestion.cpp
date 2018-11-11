#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

MatriceGameGestion::MatriceGameGestion(){
	m_allMenu = vector<Menu>();

	// Création du menu principal (quand on appuie sur la touche escape)
	vector<AbstractButton> escapeButtons(3) ;
    SDL_Color font = {255, 255, 255} ; 
    SDL_Color text = {0, 0, 0} ;

    escapeButtons[0] = ActionButton(12, "RETOUR", 200, 100, 110, 110, font, text) ;
    escapeButtons[1] = ActionButton(12, "MUSIQUE", 200, 100, 110, 110, font, text) ;
    escapeButtons[2] = ActionButton(12, "QUITTER", 200, 100, 110, 110, font, text) ;

    SDL_Color font_menu = {0, 0, 0} ;
    unsigned short int x(SCREEN_WIDTH/2 - 100), y(SCREEN_HEIGHT/4) ;
    Menu menuEscape(escapeButtons, x, y, font_menu, 32) ;

    // Ajout du menu dans le tableau de menu de la matrice
    m_allMenu.push_back(menuEscape);

    // Création du menu prise de décision (attaquer, défendre, aller à, ...)
    vector<AbstractButton> decisionButtons(4) ;

    decisionButtons[0] = ActionButton(12, "ATTAQUER", 200, 100, 110, 110, font, text) ;
    decisionButtons[1] = ActionButton(12, "DEFENDRE", 200, 100, 110, 110, font, text) ;
    decisionButtons[2] = ActionButton(12, "ALLER A", 200, 100, 110, 110, font, text) ;
    decisionButtons[3] = ActionButton(12, "FERMER", 200, 100, 110, 110, font, text) ;

    x = 0 ; y = 0 ;
    Menu menuDecision(decisionButtons, x, y, font_menu, 45);

    // Ajout du menu dans le tableau de menu de la matrice
    m_allMenu.push_back(menuDecision);
}

void MatriceGameGestion::openMenu(int id, Fenetre screen){
	// On parcourt l'ensemble des menus présents de la matrice pour consulter leur ID et ouvrir le menu voulu
	bool open = false ;

	cout << "Taille menu vector : " << m_allMenu.size() << endl ;
	for (Menu men : m_allMenu){
		if (!open){
			if (id == men.getID()){
				men.displayMenu(screen);
				open = true ;
			}
		}
	}
}
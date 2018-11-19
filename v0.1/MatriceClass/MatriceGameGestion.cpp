#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../IDButtons/idbuttons.h"
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

    escapeButtons[0] = ActionButton(RETOUR, "RETOUR", 200, 100, 110, 110, font, text) ;
    escapeButtons[1] = ActionButton(12, "MUSIQUE", 200, 100, 110, 110, font, text) ;
    escapeButtons[2] = ActionButton(QUITTER, "QUITTER", 200, 100, 110, 110, font, text) ;

    SDL_Color font_menu = {0, 0, 0} ;
    unsigned short int x(SCREEN_WIDTH/2 - 100), y(SCREEN_HEIGHT/4) ;
    Menu menuEscape(escapeButtons, x, y, font_menu, 32) ;

    // Ajout du menu dans le tableau de menu de la matrice
    m_allMenu.push_back(menuEscape);

    // Création du menu prise de décision (attaquer, défendre, aller à, ...)
    vector<AbstractButton> decisionButtons(4) ;

    decisionButtons[0] = ActionButton(ATTAQUER, "ATTAQUER", 200, 100, 110, 110, font, text) ;
    decisionButtons[1] = ActionButton(DEFENDRE, "DEFENDRE", 200, 100, 110, 110, font, text) ;
    decisionButtons[2] = ActionButton(ALLER_A, "ALLER A", 200, 100, 110, 110, font, text) ;
    decisionButtons[3] = ActionButton(RETOUR, "RETOUR", 200, 100, 110, 110, font, text) ;

    x = 0 ; y = 0 ;
    Menu menuDecision(decisionButtons, x, y, font_menu, 45);

    // Ajout du menu dans le tableau de menu de la matrice
    m_allMenu.push_back(menuDecision);
}

void MatriceGameGestion::openMenu(int id, Fenetre screen, bool openclose){
	// On parcourt l'ensemble des menus présents de la matrice pour consulter leur ID et ouvrir le menu voulu
	bool done = false ;
    int size = m_allMenu.size();

	for (int i = 0 ; i < size ; i++){
		if (!done){
			if (id == m_allMenu[i].getID()){
				m_allMenu[i].displayMenu(screen);
                if (openclose){
                    m_allMenu[i].openCloseMenu();
                }
				done = true ;
			}
		}
	}
}

bool MatriceGameGestion::receiveAction(unsigned int x, unsigned int y){
    int id_button ;

    for (Menu men : m_allMenu){
        if (men.isOpen()){
            id_button = men.receiveAction(x, y);
        }
    }

    return ( id_button == QUITTER ) ? true : false ;
}
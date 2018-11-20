#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../ID/idbuttons.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

MatriceGameGestion::MatriceGameGestion(vector<AbstractButton*> all_buttons){
	m_allMenu = vector<Menu>();

    // Création du menu principal (quand on appuie sur la touche escape)
    SDL_Color font_menu = {0, 0, 0} ;

    // Ajout du menu dans le tableau de menu de la matrice
    vector<AbstractButton*> escapeButtons ;
    escapeButtons.push_back(all_buttons[RETOUR]);
    escapeButtons.push_back(all_buttons[MUSIQUE]);
    escapeButtons.push_back(all_buttons[QUITTER]);

    unsigned short int x(SCREEN_WIDTH/2 - 100), y(SCREEN_HEIGHT/4) ;

    Menu menuEscape(escapeButtons, x, y, font_menu, ESCAPE_MENU) ;

    m_allMenu.push_back(menuEscape);

    // Création du menu prise de décision (attaquer, défendre, aller à, ...)
    vector<AbstractButton*> decisionButtons ;

    decisionButtons.push_back(all_buttons[ATTAQUER]);
    decisionButtons.push_back(all_buttons[DEFENDRE]);
    decisionButtons.push_back(all_buttons[ALLER_A]);
    decisionButtons.push_back(all_buttons[FERMER]);

    x = 0 ; y = 0 ;
    Menu menuDecision(decisionButtons, x, y, font_menu, ATTACK_MENU);

    // Ajout du menu dans le tableau de menu de la matrice
    m_allMenu.push_back(menuDecision);

    // Initialisation du tableau de menus ouverts [0] : fermé ||   [1] : ouvert
    for (int i = 0; i < NUMBER_OF_MENUS ; i++){
        m_menus_opened[i] = 0 ;
    }
}

void MatriceGameGestion::openMenu(int id, Fenetre screen, bool openclose){
	// On parcourt l'ensemble des menus présents de la matrice pour consulter leur ID et ouvrir le menu voulu
	bool done = false ;
    int size = m_allMenu.size();
    int biais = 50 ;

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

    m_menus_opened[id-biais] = ( m_menus_opened[id-biais] ) ? 0 : 1 ;
    cout << m_menus_opened[id-biais] << endl ;
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

void MatriceGameGestion::keepOpening(Fenetre screen){
    for (int i = 0 ; i < NUMBER_OF_MENUS ; i++){
        if (m_menus_opened[i]){
            m_allMenu[i].displayMenu(screen);
        }
    }
}

bool MatriceGameGestion::isAMenuOpened(){
    bool menu_opened = false ;
    int i = 0 ;

    while (i < NUMBER_OF_MENUS && !menu_opened){
        menu_opened = ( m_menus_opened[i] ) ? true : false ;
        i++ ;
    }

    return menu_opened ;
}
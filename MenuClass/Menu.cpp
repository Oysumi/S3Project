#include "Menu.h"
#include "ActionButton.h"
#include "../Fonctions/fonctions.h"
#include "../DisplayClass/Texte.h"

#include <iostream>

using namespace std ;

vector<Menu*> Menu::allMenu ;

vector<Menu*>* Menu::getAllMenu(vector <AbstractButton*> const& all_buttons, unsigned short const width, unsigned short const height)
{

	vector <Menu*>* menu = new vector<Menu*> ;

	//Création des menus
    //Couleur de menu
    SDL_Color font_menu = {0, 0, 0} ;

    // Création et ajout dans la mémoire du menu principal (quand on appuie sur la touche escape)
    vector<AbstractButton*> escapeButtons ;
    escapeButtons.push_back(all_buttons[AFFICHAGE]);
    escapeButtons.push_back(all_buttons[RETOUR]);
    escapeButtons.push_back(all_buttons[FIN_DU_TOUR]);
    escapeButtons.push_back(all_buttons[QUITTER]);
    unsigned short int x(width/2 - LARGEUR_MENU1/2), y(height/6) ;
    menu->push_back(new Menu (escapeButtons, x, y, font_menu, ESCAPE_MENU)) ;

    // Création et ajout dans la mémoire du menu prise de décision (attaquer, défendre, aller à, ...)
    vector<AbstractButton*> decisionButtons ;
    decisionButtons.push_back(all_buttons[ATTAQUER]);
    decisionButtons.push_back(all_buttons[DEFENDRE]);
    decisionButtons.push_back(all_buttons[ALLER_A]);
    decisionButtons.push_back(all_buttons[FERMER]);
    menu->push_back(new Menu (decisionButtons, 0, 0, font_menu, ATTACK_MENU)) ;

    // Création et ajout dans la mémoire du menu création (construction, unité...)
    vector<AbstractButton*> constructionButtons ;
    constructionButtons.push_back(all_buttons[CREATION]);
    constructionButtons.push_back(all_buttons[CREER_UNITE]);
    constructionButtons.push_back(all_buttons[CREER_CONSTRUCTION]);
    menu->push_back(new Menu (constructionButtons, 0, 500, font_menu, CREATION_MENU));
    
    // Création et ajout dans la mémoire du menu selection spécifique aux unités
    vector<AbstractButton*> unitButtons ;
    unitButtons.push_back(all_buttons[SELECTION]);
    unitButtons.push_back(all_buttons[ARCHER]);
    unitButtons.push_back(all_buttons[CATAPULTE]);
    menu->push_back(new Menu (unitButtons, 0, 500, font_menu, UNITES_MENU));

    // Création et ajout dans la mémoire du menu selection spécifique aux constructions
    vector<AbstractButton*> consButtons ;
    consButtons.push_back(all_buttons[SELECTION]);
    consButtons.push_back(all_buttons[CHATEAU]);
    consButtons.push_back(all_buttons[FERME]);
    menu->push_back(new Menu (consButtons, 0, 500, font_menu, CONS_MENU));

    return menu ;

}

Menu::Menu(){
	m_id = NOTHING ;
	m_surface = NULL ;
	allMenu.push_back(this) ;
} ; // Est utile pour la création d'un vector de Menu dans MatriceGameGestion.cpp

Menu::Menu(vector<AbstractButton*> const& buttons, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, int id)
{
	m_pos_x = pos_x ;
	m_pos_y = pos_y ;
	m_background = back ;
	m_id = id ;
	m_open = false ;
	this->calculPosButton(buttons) ;
	allMenu.push_back(this) ;
	m_surface = new SurfaceAffichage(m_width, m_height) ;
}

Menu::~Menu()
{
	for (unsigned short i = 0 ; i < allMenu.size() ; i++)
	{
		if(allMenu[i]==this)
			allMenu.erase(allMenu.begin()+i) ;
	}

	if(m_surface!=NULL)
	{
		delete(m_surface) ;
		m_surface = NULL ;
	}
}

SDL_Color Menu::getColor() const
{
	return this->m_background ;
}

SurfaceAffichage const& Menu::getMenu() const
{
	return *m_surface ;
}

unsigned short Menu::getPosX() const
{
	return this->m_pos_x ;
}

unsigned short Menu::getPosY() const
{
	return this->m_pos_y ;
}

bool Menu::setTextButton(unsigned short nb, string const& text)
{
	if (nb >= m_myButtons.size())
		return false ;
	m_myButtons[nb]->setText(text) ;
	return true ;
}

bool Menu::clickIsOnThisMenu(unsigned int x, unsigned int y)
{
	return getPosX() < x && x < getPosX()+m_width &&
		   getPosY() < y && y < getPosY()+m_height ;
}

void Menu::calculPosButton(vector<AbstractButton*> const& buttons)
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
	for ( AbstractButton * b : buttons )
	{
		b->setPosX(m_pos_x + LARGEUR);
		b->setPosY(m_pos_y + (i+1)*HAUTEUR + i*boutonHauteur);
		m_myButtons[i] = b ;
		i++;
	}
}

void Menu::displayMenu(Fenetre& screen) const
{
	SDL_Surface* menuSurface = m_surface->surface() ;
	SDL_Color couleur = this->getColor() ;

	if(SDL_FillRect(menuSurface, NULL, SDL_MapRGB(menuSurface->format, couleur.r, couleur.g, couleur.b)) != 0)
	{
		erreur_message("Impossible de colorer le menu :  " + string(SDL_GetError())) ;
	}

	unsigned int posX = this->getPosX() ;
	unsigned int posY = this->getPosY() ;

	screen.ajouter(*m_surface, posX, posY) ;
 
    for ( AbstractButton * b : m_myButtons )
    {
    	SDL_Color col = b->getBackColor() ;

    	posX = b->getPosX() ;
    	posY = b->getPosY() ;

    	if(SDL_FillRect(b->getSurfaceAffichage().surface(), NULL, SDL_MapRGB(b->getSurfaceAffichage().surface()->format, col.r, col.g, col.b)) != 0)
			erreur_message("Impossible de colorer l'un des boutons du menu :  " + string(SDL_GetError())) ;

    	screen.ajouter(b->getSurfaceAffichage(), posX, posY) ;
    	b->getTexte().displayText(screen, *b) ;
    }

    screen.actualiser() ;
}

bool Menu::displayMenuWithId(int id, Fenetre& screen)
{
	for (unsigned short i = 0 ; i < allMenu.size() ; i++)
    {
        if (id == allMenu[i]->m_id)
        {
            allMenu[i]->displayMenu(screen) ;
            return true ;
        }
    }
    return false ;
}

int Menu::getID() const
{
	return m_id ;
}

void Menu::openCloseMenu()
{
	m_open = ( m_open ) ? false : true ;
}

bool Menu::isOpen() const
{
	return m_open;
}

int Menu::receiveAction(unsigned int x, unsigned int y){
	unsigned int pos_x, pos_y, width, height ;
	unsigned short int id = NOTHING ;

	for (AbstractButton * b : m_myButtons)
	{
		if (id == NOTHING)
		{
			pos_x = b->getPosX();
			pos_y = b->getPosY();
			width = b->getWidth();
			height = b->getHeight();

			if (x >= pos_x && x <= pos_x + width && y >= pos_y && y <= pos_y + height)
				id = b->getID(); 
		}
	}


	return id ;
}


bool Menu::isAMenuOpened(){
    bool menu_opened = false ;
    unsigned short i = 0 ;
    while (i < Menu::allMenu.size() && !menu_opened)
    {
        menu_opened = ( Menu::allMenu[i]->isOpen() ) ? true : false ;
        i++ ;
    }

    return menu_opened ;
}

void Menu::keepOpened(Fenetre& screen)
{
    for (unsigned short i = 0 ; i < Menu::allMenu.size() ; i++)
    {
        if (Menu::allMenu[i]->isOpen())
            Menu::allMenu[i]->displayMenu(screen) ;
    }
}


void Menu::openMenu(int id, Fenetre& screen)
{
	// On parcourt l'ensemble des menus présents de la matrice pour consulter leur ID et ouvrir le menu voulu
	bool done = false ;
	for (unsigned short i = 0 ; i < Menu::allMenu.size() ; i++)
	{
        if (!done)
			if (id == Menu::allMenu[i]->getID())
			{
				Menu::allMenu[i]->displayMenu(screen) ;
                Menu::allMenu[i]->openCloseMenu() ;
				done = true ;
			}
	}

}

int Menu::getIdButtonOn(unsigned int x, unsigned int y)
{
	int id_button = NOTHING ;

    for (unsigned short i = 0 ; i < allMenu.size() ; i++)
    {
        if (allMenu[i]->isOpen() && allMenu[i]->clickIsOnThisMenu(x,y)){
            id_button = allMenu[i]->receiveAction(x,y) ;
        }
    }

    return id_button ;
}

bool Menu::isOnOneMenu(unsigned int x, unsigned int y)
{
	for (unsigned short i = 0 ; i < allMenu.size() ; i++)
    {
        if (allMenu[i]->clickIsOnThisMenu(x,y) && allMenu[i]->m_open)
            return true ;
    }
    return false ;
}
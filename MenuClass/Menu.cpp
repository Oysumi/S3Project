#include "Menu.h"
#include "ActionButton.h"
#include "SubMenuButton.h"
#include "../Fonctions/fonctions.h"
#include "../DisplayClass/Texte.h"

#include <iostream>

using namespace std ;

vector<Menu*> Menu::allMenu ;

vector<Menu*>* Menu::getAllMenu(vector <AbstractButton*> const& all_buttons, unsigned short const width, unsigned short const height)
{
	//Création des menus
	vector <Menu*>* menu = new vector<Menu*> ;
	vector<AbstractButton*> buttons ;
	
    //Couleur de menu
    SDL_Color font_menu = {0, 0, 0} ;

    // Création et ajout dans la mémoire du menu principal (quand on appuie sur la touche escape)
    buttons.push_back(all_buttons[AFFICHAGE]);
    buttons.push_back(all_buttons[FIN_DU_TOUR]);
    buttons.push_back(all_buttons[RETOUR]);
    buttons.push_back(all_buttons[QUITTER]);
    unsigned short int x(width/2 - LARGEUR_MENU1/2), y(height/6) ;
    menu->push_back(new Menu (buttons, x, y, font_menu, ESCAPE_MENU)) ;
    buttons.clear() ;

    // Création et ajout dans la mémoire du menu selection spécifique aux constructions
    buttons.push_back(all_buttons[ENTETE_CONSTRUCTION]);
    buttons.push_back(all_buttons[CONSTRUIRE_BATIMENT]);
    buttons.push_back(all_buttons[CONSTRUIRE_UNIT]);
    menu->push_back(new Menu (buttons, 0, 500, font_menu, CHATEAU_MENU));
    buttons.clear() ;
    
    // Création et ajout dans la mémoire du menu
    buttons.push_back(all_buttons[ENTETE_CONSTRUCTION_UNITE]);
    buttons.push_back(all_buttons[BELIER]);
    buttons.push_back(all_buttons[CATAPULTE]);
    buttons.push_back(all_buttons[RETOUR2]);
    menu->push_back(new Menu (buttons, 0, 450, font_menu, CONSTRUCTION_UNIT_MENU));
    buttons.clear() ;

    // Création et ajout dans la mémoire du menu
    buttons.push_back(all_buttons[ENTETE_CONSTRUCTION_BATIMENT]);
    buttons.push_back(all_buttons[CHATEAU]);
    buttons.push_back(all_buttons[FERME]);
    buttons.push_back(all_buttons[RETOUR3]);
    menu->push_back(new Menu (buttons, 0, 450, font_menu, CONSTRUCTION_BATIMENT_MENU));
    buttons.clear() ;

	//Une fois que les menus sont crées on appelle cette méthode statique pour récupérer tous les pointeurs des Menu grâce à leurs ID
    SubMenuButton::initAllSubMenu() ;

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

Menu* Menu::getMenuById(int id)
{
	for (unsigned short i = 0 ; i < allMenu.size() ; i++)
        if (id == allMenu[i]->m_id)
            return allMenu[i] ;
    warning_message("Menu with id " + to_string(id) + "not find") ;
    return NULL ;
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

AbstractButton* Menu::receiveAction(unsigned int x, unsigned int y) const
{
	unsigned int pos_x, pos_y, width, height ;

	for (AbstractButton * b : m_myButtons)
	{
		pos_x = b->getPosX();
		pos_y = b->getPosY();
		width = b->getWidth();
		height = b->getHeight();

		if (x >= pos_x && x <= pos_x + width && y >= pos_y && y <= pos_y + height)
			return b  ;
	}

	return NULL ;
}


bool Menu::isAMenuOpened()
{
    for (unsigned short i = 0 ; i < Menu::allMenu.size() ; i++)
        if(Menu::allMenu[i]->isOpen())
        	return true ;
    return false ;
}

void Menu::keepOpened(Fenetre& screen)
{
    for (unsigned short i = 0 ; i < Menu::allMenu.size() ; i++)
        if (Menu::allMenu[i]->isOpen())
            Menu::allMenu[i]->displayMenu(screen) ;
}


void Menu::openMenu(int id, Fenetre& screen)
{
	// On parcourt l'ensemble des menus présents de la matrice pour consulter leur ID et ouvrir le menu voulu
	bool done = false ;
	for (unsigned short i = 0 ; i < Menu::allMenu.size() ; i++)
	{
        if (!done)
			if (id == allMenu[i]->getID())
			{
				allMenu[i]->displayMenu(screen) ;
                allMenu[i]->openCloseMenu() ;
				done = true ;
			}
	}

}

int Menu::getIdButtonOn(unsigned int x, unsigned int y)
{
    for (unsigned short i = 0 ; i < allMenu.size() ; i++)
        if (allMenu[i]->isOpen() && allMenu[i]->clickIsOnThisMenu(x,y))
        {
           	AbstractButton* b = allMenu[i]->receiveAction(x,y) ;
            if (b != NULL)
            	return b->getID() ;
        }

    return NOTHING ;
}

bool Menu::openSubAssocTo(unsigned int x, unsigned int y)
{
	for (unsigned short i = 0 ; i < allMenu.size() ; i++)
        if (allMenu[i]->isOpen() && allMenu[i]->clickIsOnThisMenu(x,y))
        {
           	AbstractButton* b = allMenu[i]->receiveAction(x,y) ;
            if (b != NULL)
            {
            	if (b->getID() == SUBMENU) //Si on arrive ici, c'est forcément un SubMenuButton
            	{
            		SubMenuButton* bsub = dynamic_cast<SubMenuButton*> (b) ;
            		bsub->displayNewMenu(allMenu[i]) ;
            		return true ;
            	}
            }
        }
    return false ;
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
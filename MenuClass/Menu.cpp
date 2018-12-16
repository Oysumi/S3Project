#include "Menu.h"
#include "ActionButton.h"
#include "SubMenuButton.h"
#include "../Fonctions/fonctions.h"
#include "../DisplayClass/Texte.h"

#include <iostream>

#define TRANSPARENCE_ALPHA 200

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
    unsigned short int x((width-Menu::widthTakeBy(buttons))/2), y((height-Menu::heightTakeBy(buttons))/2) ;
    menu->push_back(new Menu (buttons, x, y, font_menu, ESCAPE_MENU, 230, 15, 15)) ;
    buttons.clear() ;

    // Création et ajout dans la mémoire du menu selection spécifique aux constructions
    buttons.push_back(all_buttons[ENTETE_CHATEAU]);
    buttons.push_back(all_buttons[ENTETE_GOLD_CHATEAU]);
    buttons.push_back(all_buttons[ENTETE_FOOD_CHATEAU]);
    buttons.push_back(all_buttons[ENTETE_WOOD_CHATEAU]);
    buttons.push_back(all_buttons[CONSTRUIRE_BATIMENT]);
    buttons.push_back(all_buttons[CONSTRUIRE_UNIT]);
    buttons.push_back(all_buttons[AMELIORATION_CHATEAU]);
    menu->push_back(new Menu (buttons, 0, height-Menu::heightTakeBy(buttons), font_menu, CHATEAU_MENU, TRANSPARENCE_ALPHA, 10));
    buttons.clear() ;
    
    // Création et ajout dans la mémoire du menu
    buttons.push_back(all_buttons[ENTETE_CHATEAU]);
    buttons.push_back(all_buttons[ENTETE_CONSTRUCTION]);
    buttons.push_back(all_buttons[CATAPULTE]);
    buttons.push_back(all_buttons[BALISTE]);
    buttons.push_back(all_buttons[BELIER]);
    buttons.push_back(all_buttons[TREBUCHET]);
    buttons.push_back(all_buttons[TOWERSIEGE]);
    buttons.push_back(all_buttons[RETOUR2]);
    menu->push_back(new Menu (buttons, 0, height-Menu::heightTakeBy(buttons), font_menu, CONSTRUCTION_UNIT_MENU, TRANSPARENCE_ALPHA, 5));
    buttons.clear() ;

    // Création et ajout dans la mémoire du menu
    buttons.push_back(all_buttons[ENTETE_CHATEAU]);
    buttons.push_back(all_buttons[ENTETE_CONSTRUCTION]);
    buttons.push_back(all_buttons[CHATEAU]);
    buttons.push_back(all_buttons[ARCHERIE]);
    buttons.push_back(all_buttons[FERME]);
    buttons.push_back(all_buttons[TOWER]);
    buttons.push_back(all_buttons[RETOUR2]);
    menu->push_back(new Menu (buttons, 0, height-Menu::heightTakeBy(buttons), font_menu, CONSTRUCTION_BATIMENT_MENU, TRANSPARENCE_ALPHA, 5));
    buttons.clear() ;

    buttons.push_back(all_buttons[ENTETE_CHATEAU]) ;
    buttons.push_back(all_buttons[AMELIORER]) ;
	buttons.push_back(all_buttons[UP_GOLD]) ;
	buttons.push_back(all_buttons[UP_FOOD]) ;
	buttons.push_back(all_buttons[UP_WOOD]) ;
	buttons.push_back(all_buttons[UP_RANGE]) ;
	buttons.push_back(all_buttons[RETOUR2]) ;
	menu->push_back(new Menu (buttons, 0, height-Menu::heightTakeBy(buttons), font_menu, AMELIORER_CHATEAU_MENU, TRANSPARENCE_ALPHA, 5));
    buttons.clear() ;

	//Une fois que les menus sont crées on appelle cette méthode statique pour récupérer tous les pointeurs des Menu grâce à leurs ID
    SubMenuButton::initAllSubMenu() ;

    return menu ;

}

Menu::Menu() : m_alpha(255)
{
	m_id = NOTHING ;
	m_surface = NULL ;
	allMenu.push_back(this) ;
} ; // Est utile pour la création d'un vector de Menu dans MatriceGameGestion.cpp

Menu::Menu(vector<AbstractButton*> const& buttons, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, int id, unsigned short const transparenceAlpha, unsigned short const separation_width, unsigned short const separation_height) :
	m_alpha (transparenceAlpha%256)
{
	m_separation_width = separation_width ;
	m_separation_height = separation_height ;
	m_pos_x = pos_x ;
	m_pos_y = pos_y ;
	m_background = back ;
	m_id = id ;
	m_open = false ;
	this->calculPosButton(buttons) ;
	allMenu.push_back(this) ;
	m_surface = NULL ;
	prepareSurface() ;
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

void Menu::prepareSurface()
{
	if (m_surface != NULL)
		delete(m_surface) ;

	m_surface = new SurfaceAffichage(m_width, m_height) ;

	if(SDL_FillRect(m_surface->surface(), NULL, SDL_MapRGB(m_surface->surface()->format, m_background.r, m_background.g, m_background.b)) != 0)
		erreur_message("Impossible de colorer le menu :  " + string(SDL_GetError())) ;

    for (unsigned short i = 0 ; i < m_myButtons.size() ; i++)
    	m_surface->ajouter(m_myButtons[i]->getSurfaceAffichage(), m_buttonsPos[i].first, m_buttonsPos[i].second) ;
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

bool Menu::setTextButton(Fenetre& screen, unsigned short nb, string const& text, std::string font)
{
	if (nb >= m_myButtons.size())
		return false ;
	m_myButtons[nb]->setText(text, font) ;
	prepareSurface() ;
	if (isOpen())
           displayMenu(screen) ;
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
	 * On calcule la taille du menu en fonction de la tailles des boutons
	 * on a une liste de boutons
	 */
	m_myButtons = vector<AbstractButton*>(buttons.size()) ;

	/**
	 * Calcul des positions des boutons
	 * A l'intérieur de la Surface d'afichage du Menu
	 */
	int i = 0 ;
	m_width = 0 ;
	int compteur_hauteur = m_separation_height ;
	for ( AbstractButton * b : buttons )
	{
		if (b->getWidth() > m_width)
			m_width = b->getWidth() ;
		m_buttonsPos.push_back(std::make_pair(m_separation_width,compteur_hauteur)) ;
		compteur_hauteur += b->getHeight() + m_separation_height ;
		m_myButtons[i] = b ;
		i++ ;
	}
	m_width += 2*m_separation_width ;
	m_height = compteur_hauteur ;
}

unsigned short Menu::widthTakeBy(std::vector<AbstractButton*> const& buttons, unsigned short const separation_width)
{
	unsigned short width_max = 0, i = 0 ;
	for ( AbstractButton * b : buttons )
	{
		if (b->getWidth() > width_max)
			width_max = b->getWidth() ;
		i++ ;
	}
	return width_max + 2*separation_width ;
}

unsigned short Menu::heightTakeBy(std::vector<AbstractButton*> const& buttons, unsigned short const separation_height)
{
	int i = 0 ;
	int compteur_hauteur = separation_height ;
	for ( AbstractButton * b : buttons )
	{
		compteur_hauteur += b->getHeight() + separation_height ;
		i++ ;
	}
	return compteur_hauteur ;
}

void Menu::displayMenu(Fenetre& screen) const
{
	if (m_alpha != 0 && m_alpha != 255)
		SDL_SetAlpha(m_surface->surface(), SDL_SRCALPHA, m_alpha);
	screen.ajouter(*m_surface,m_pos_x,m_pos_y) ;
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

	for (unsigned short i = 0 ; i < m_myButtons.size() ; i++)
	{
		AbstractButton*  b = m_myButtons[i] ;
		pos_x = m_pos_x + m_buttonsPos[i].first ;
		pos_y = m_pos_y + m_buttonsPos[i].second ;
		width = b->getWidth() ;
		height = b->getHeight() ;

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
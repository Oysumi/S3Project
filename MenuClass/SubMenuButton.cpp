#include "SubMenuButton.h"
#include "Menu.h"
using namespace std ;

std::list<SubMenuButton*> SubMenuButton::listSubMenuButton ;

SubMenuButton::SubMenuButton (int menu_id, std::string textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text, int size_text)
{
	//ON APPELLE PAS LE CONSTRUCTEUR DE ACTIONBUTTON CAR IL NE RECOIT PAS D'ID = SUBMENU
	//On est ainsi sur que seul les SubMenuButton ont un ID égal à SUBMENU
	m_id = SUBMENU ;
	listSubMenuButton.push_back(this) ;
	m_menu_id = menu_id ;
	m_menu = NULL ;

	m_text = textToWrite ;
  	m_sizeText = size_text ;
	this->setSize(width, height) ;
	this->setPos(pos_x, pos_y) ;
	this->setButtonColors(back, text) ;

	m_surface = NULL ;
	m_texte = NULL ;
	setText(m_text) ;
}

SubMenuButton::~SubMenuButton ()
{
	listSubMenuButton.remove(this) ;
}

void SubMenuButton::displayNewMenu(Menu* to_replace)
{
	if (to_replace != NULL)
		if (to_replace->isOpen())
			to_replace->openCloseMenu() ;

	if (m_menu != NULL)
		if (!m_menu->isOpen())
			m_menu->openCloseMenu() ;
}

//Une fois que les menus sont crées on appelle cette méthode statique pour récupérer tous les pointeurs des Menu grâce à leurs ID
void SubMenuButton::initAllSubMenu()
{
	for (list<SubMenuButton*>::iterator it = listSubMenuButton.begin() ; it != listSubMenuButton.end() ; it++)
		(*it)->m_menu = Menu::getMenuById((*it)->m_menu_id) ;
}
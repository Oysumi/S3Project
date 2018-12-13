#include "AbstractButton.h"
#include "ActionButton.h"
#include "SubMenuButton.h"
#include "Menu.h"

using namespace std ;

vector<AbstractButton*>* AbstractButton::getAllButton()
{

	SDL_Color white = {255,255,255};
	SDL_Color black = {0,0,0};

	vector<AbstractButton*>* bouton = new vector<AbstractButton*> ;
	for (unsigned short i = 0 ; i < 45 ; i++)
		bouton->push_back(NULL) ;

	(*bouton)[RETOUR] = new ActionButton(RETOUR, "Retour", LARGEUR_MENU1, HAUTEUR_MENU1, 110, 110, white, black) ;
	(*bouton)[MUSIQUE] = new ActionButton(MUSIQUE, "MUSIQUE", 200, 100, 110, 110, white, black) ;
	(*bouton)[QUITTER] = new ActionButton(QUITTER, "Quitter", LARGEUR_MENU1, HAUTEUR_MENU1, 110, 110, white, black) ;
	(*bouton)[FIN_DU_TOUR] = new ActionButton(FIN_DU_TOUR, "Fin du tour", LARGEUR_MENU1, HAUTEUR_MENU1, 110, 110, white, black) ;
	(*bouton)[AFFICHAGE] = new ActionButton(AFFICHAGE, "Tour de ", LARGEUR_MENU1, HAUTEUR_MENU1, 110, 110, black, white) ;
	
	(*bouton)[ENTETE_CONSTRUCTION_UNITE] = new ActionButton(ENTETE_CONSTRUCTION_UNITE, "Construire ...", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, black, white, 15);
	(*bouton)[BELIER] = new ActionButton(BELIER, "Belier", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, white, black, 15);
	(*bouton)[CATAPULTE] = new ActionButton(CATAPULTE, "Catapulte", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, white, black, 15);
	(*bouton)[RETOUR2] = new SubMenuButton(CHATEAU_MENU, "RETOUR", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, white, black, 15);
	
	(*bouton)[ENTETE_CONSTRUCTION_BATIMENT] = new ActionButton(ENTETE_CONSTRUCTION_BATIMENT, "Construire ...", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, black, white, 15);
	(*bouton)[CHATEAU] = new ActionButton(CHATEAU, "Chateau", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, white, black, 15);
	(*bouton)[FERME] = new ActionButton(FERME, "Ferme", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, white, black, 15);
	(*bouton)[RETOUR3] = new SubMenuButton(CHATEAU_MENU, "RETOUR", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, white, black, 15);

	(*bouton)[ENTETE_CONSTRUCTION] = new ActionButton(ENTETE_CONSTRUCTION, "Construire ...", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, black, white, 15);
	(*bouton)[CONSTRUIRE_BATIMENT] = new SubMenuButton(CONSTRUCTION_BATIMENT_MENU, "Un batiment", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, white, black, 15);
	(*bouton)[CONSTRUIRE_UNIT] = new SubMenuButton(CONSTRUCTION_UNIT_MENU, "Une unite", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, white, black, 15);

	return bouton ;
}

/**************************************************************************************************************
 *                                                  GETTERS                                                   *
 **************************************************************************************************************/

unsigned int AbstractButton::getPosX() const
{
	return this->m_posx ;
}

unsigned int AbstractButton::getPosY() const
{
	return this->m_posy ;
}

unsigned int AbstractButton::getWidth() const
{
	return this->m_width ;
}

unsigned int AbstractButton::getHeight() const
{
	return this->m_height ;
}

int AbstractButton::getID() const
{
	return this->m_id ;
}

SDL_Color AbstractButton::getBackColor() const
{
	return this->m_back_color ;
}

SDL_Color AbstractButton::getTextColor() const
{
	return this->m_text_color ;
}

const char * AbstractButton::getText() const
{
	return m_text.c_str() ;
}

int AbstractButton::sizeText() const
{
  return m_sizeText ;
}

/**************************************************************************************************************
 *                                                  SETTERS                                                   *
 **************************************************************************************************************/

void AbstractButton::setPosX(unsigned int x)
{
	m_posx = x ;
}

void AbstractButton::setPosY(unsigned int y)
{
	m_posy = y ;
}

void AbstractButton::setText(std::string text)
{
	m_text = text ;
}


//DESTRUCTEUR
AbstractButton::~AbstractButton() { };
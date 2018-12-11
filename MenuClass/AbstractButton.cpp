#include "AbstractButton.h"
#include "ActionButton.h"
#include "Menu.h"

using namespace std ;

vector<AbstractButton*>* AbstractButton::getAllButton()
{

	SDL_Color font = {255,255,255};
	SDL_Color text = {0,0,0};

	vector<AbstractButton*>* bouton = new vector<AbstractButton*> ;

	bouton->push_back(new ActionButton(RETOUR, "Retour", LARGEUR_MENU1, HAUTEUR_MENU1, 110, 110, font, text)) ;
	bouton->push_back(new ActionButton(MUSIQUE, "MUSIQUE", 200, 100, 110, 110, font, text)) ;
	bouton->push_back(new ActionButton(QUITTER, "Quitter", LARGEUR_MENU1, HAUTEUR_MENU1, 110, 110, font, text)) ;
	bouton->push_back(new ActionButton(ATTAQUER, "ATATQUER", 200, 100, 110, 110, font, text)) ;
	bouton->push_back(new ActionButton(DEFENDRE, "DEFENDRE", 200, 100, 110, 110, font, text)) ;
	bouton->push_back(new ActionButton(ALLER_A, "ALLER_A", 200, 100, 110, 110, font, text)) ;
	bouton->push_back(new ActionButton(FERMER, "FERMER", 200, 100, 110, 110, font, text)) ;
	bouton->push_back(new ActionButton(FIN_DU_TOUR, "Fin du tour", LARGEUR_MENU1, HAUTEUR_MENU1, 110, 110, font, text)) ;
	bouton->push_back(new ActionButton(AFFICHAGE, "Tour de ", LARGEUR_MENU1, HAUTEUR_MENU1, 110, 110, text, font)) ;
	bouton->push_back(new ActionButton(CREATION, "Creation de :", LARGEUR_MENU2, HAUTEUR_MENU2, 50, 50, text, font, 15));
	bouton->push_back(new ActionButton(CREER_UNITE, "Unite", LARGEUR_MENU2, HAUTEUR_MENU2, 50, 50, font, text, 15));
	bouton->push_back(new ActionButton(CREER_CONSTRUCTION, "Construction", LARGEUR_MENU2, HAUTEUR_MENU2, 50, 50, font, text, 15));
	bouton->push_back(new ActionButton(SELECTION, "Selection :", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, text, font, 15));
	bouton->push_back(new ActionButton(ARCHER, "ARCHER", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, font, text, 15));
	bouton->push_back(new ActionButton(CATAPULTE, "CATAPULTE", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, font, text, 15));
	bouton->push_back(new ActionButton(CHATEAU, "CHATEAU", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, font, text, 15));
	bouton->push_back(new ActionButton(FERME, "FERME", LARGEUR_MENU3, HAUTEUR_MENU3, 50, 50, font, text, 15));

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
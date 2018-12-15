#include "AbstractButton.h"
#include "ActionButton.h"
#include "SubMenuButton.h"
#include "Menu.h"

using namespace std ;

vector<AbstractButton*>* AbstractButton::getAllButton()
{
	SurfaceAffichage gold(SurfaceAffichage("../ressources/icon/gold.bmp",TRANSPARENCE)) ,
					 food(SurfaceAffichage("../ressources/icon/food.bmp",TRANSPARENCE)) ,
					 wood(SurfaceAffichage("../ressources/icon/wood.bmp",TRANSPARENCE)) ;

	SDL_Color white = {255,255,255} ;
	SDL_Color black = {0,0,0} ;
	SDL_Color grey = {127,127,127} ;
	SDL_Color grey2 = {180,180,180} ;

	vector<AbstractButton*>* bouton = new vector<AbstractButton*> ;
	for (unsigned short i = 0 ; i < 45 ; i++)
		bouton->push_back(NULL) ;

	(*bouton)[RETOUR] = new ActionButton(RETOUR, "Retour", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[MUSIQUE] = new ActionButton(MUSIQUE, "MUSIQUE", 200, 100, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[QUITTER] = new ActionButton(QUITTER, "Quitter", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[FIN_DU_TOUR] = new ActionButton(FIN_DU_TOUR, "Fin du tour", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[AFFICHAGE] = new ActionButton(AFFICHAGE, "Tour de ", LARGEUR_MENU1, HAUTEUR_MENU1, black, white, 30, CENTER_TEXT, "extra") ;
	
	(*bouton)[ENTETE_CONSTRUCTION] = new ActionButton(ENTETE_CONSTRUCTION, "Construire ..       ", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[RETOUR2] = new SubMenuButton(CHATEAU_MENU, "RETOUR", LARGEUR_MENU3, 25, grey, black, 15, CENTER_TEXT, "extra") ;
	(*bouton)[CATAPULTE ] = new ActionButton(CATAPULTE,  "300              4         Catapulte", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[BALISTE   ] = new ActionButton(BALISTE  ,  "450              4         Baliste", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[BELIER    ] = new ActionButton(BELIER   ,  "650              5         Belier", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[TREBUCHET ] = new ActionButton(TREBUCHET,  "750              6         Trebuchet", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[TOWERSIEGE] = new ActionButton(TOWERSIEGE, "800             8         Tour de siege", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[CATAPULTE ]->addTexture(gold, 33, 3) ;
	(*bouton)[CATAPULTE ]->addTexture(food, 96, 3) ;
	(*bouton)[BALISTE   ]->addTexture(gold, 33, 3) ;
	(*bouton)[BALISTE   ]->addTexture(food, 96, 3) ;
	(*bouton)[BELIER    ]->addTexture(gold, 33, 3) ;
	(*bouton)[BELIER    ]->addTexture(food, 96, 3) ;
	(*bouton)[TREBUCHET ]->addTexture(gold, 33, 3) ;
	(*bouton)[TREBUCHET ]->addTexture(food, 96, 3) ;
	(*bouton)[TOWERSIEGE]->addTexture(gold, 33, 3) ;
	(*bouton)[TOWERSIEGE]->addTexture(food, 96, 3) ;

	(*bouton)[CHATEAU] = new ActionButton(CHATEAU, "Chateau", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[FERME] = new ActionButton(FERME, "Ferme", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[ARCHERIE] = new ActionButton(ARCHERIE, "Archerie", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[TOWER] = new ActionButton(TOWER, "Tour de defense", LARGEUR_MENU3, 20, grey2, black, 15) ;

	(*bouton)[AMELIORER] = new ActionButton(AMELIORER, "Augmenter ..    ", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[UP_GOLD] = new ActionButton(UP_GOLD, "la production d'or", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_FOOD] = new ActionButton(UP_FOOD, "la production de nourriture", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_WOOD] = new ActionButton(UP_WOOD, "la production de bois", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_RANGE] = new ActionButton(UP_RANGE, "la portee de construction", LARGEUR_MENU3, 20, grey2, black, 15) ;

	(*bouton)[ENTETE_CHATEAU] = new ActionButton(ENTETE_CHATEAU, "Petit chateau", LARGEUR_MENU3, 30, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[ENTETE_GOLD_CHATEAU] = new ActionButton(ENTETE_GOLD_CHATEAU, "+40", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[ENTETE_FOOD_CHATEAU] = new ActionButton(ENTETE_FOOD_CHATEAU, "+5", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[ENTETE_WOOD_CHATEAU] = new ActionButton(ENTETE_WOOD_CHATEAU, "+10", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[CONSTRUIRE_BATIMENT] = new SubMenuButton(CONSTRUCTION_BATIMENT_MENU, "Construire un batiment", LARGEUR_MENU3, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[CONSTRUIRE_UNIT] = new SubMenuButton(CONSTRUCTION_UNIT_MENU, "Construire une unite", LARGEUR_MENU3, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[AMELIORATION_CHATEAU] = new SubMenuButton(AMELIORER_CHATEAU_MENU, "Ameliorer le chateau", LARGEUR_MENU3, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[ENTETE_GOLD_CHATEAU]->addTexture(gold, 45, 3) ;
	(*bouton)[ENTETE_FOOD_CHATEAU]->addTexture(food, 48, 3) ;
	(*bouton)[ENTETE_WOOD_CHATEAU]->addTexture(wood, 48, 3) ;

	return bouton ;
}

/**************************************************************************************************************
 *                                                  GETTERS                                                   *
 **************************************************************************************************************/

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


//DESTRUCTEUR
AbstractButton::~AbstractButton() { };
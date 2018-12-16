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
	for (unsigned short i = 0 ; i < 95 ; i++)
		bouton->push_back(NULL) ;

	(*bouton)[RETOUR] = new ActionButton(RETOUR, "Retour", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[MUSIQUE] = new ActionButton(MUSIQUE, "MUSIQUE", 200, 100, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[QUITTER] = new ActionButton(QUITTER, "Quitter", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[FIN_DU_TOUR] = new ActionButton(FIN_DU_TOUR, "Fin du tour", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[AFFICHAGE] = new ActionButton(AFFICHAGE, "Tour de ", LARGEUR_MENU1, HAUTEUR_MENU1, black, white, 30, CENTER_TEXT, "extra") ;
	
	(*bouton)[ENTETE_CONSTRUCTION] = new ActionButton(ENTETE_CONSTRUCTION, "Construire ..       ", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[RETOUR2] = new SubMenuButton(CHATEAU_MENU, "RETOUR", LARGEUR_MENU3, 25, grey, black, 15, CENTER_TEXT, "extra") ;
	(*bouton)[CATAPULTE ] = new ActionButton(CATAPULTE,  "  300              4         Catapulte", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[BALISTE   ] = new ActionButton(BALISTE  ,  "  450              4         Baliste", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[BELIER    ] = new ActionButton(BELIER   ,  "  650              5         Belier", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[TREBUCHET ] = new ActionButton(TREBUCHET,  "  750              6         Trebuchet", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[TOWERSIEGE] = new ActionButton(TOWERSIEGE, "  800             8         Tour de siege", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[CATAPULTE ]->addTexture(gold, 42, 3) ;
	(*bouton)[CATAPULTE ]->addTexture(food, 106, 3) ;
	(*bouton)[BALISTE   ]->addTexture(gold, 42, 3) ;
	(*bouton)[BALISTE   ]->addTexture(food, 106, 3) ;
	(*bouton)[BELIER    ]->addTexture(gold, 42, 3) ;
	(*bouton)[BELIER    ]->addTexture(food, 106, 3) ;
	(*bouton)[TREBUCHET ]->addTexture(gold, 42, 3) ;
	(*bouton)[TREBUCHET ]->addTexture(food, 106, 3) ;
	(*bouton)[TOWERSIEGE]->addTexture(gold, 42, 3) ;
	(*bouton)[TOWERSIEGE]->addTexture(food, 106, 3) ;

	(*bouton)[CHATEAU1 ] = new ActionButton(CHATEAU1 , " 1000            80         Chateau", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[CHATEAU2 ] = new ActionButton(CHATEAU2 , " 1200           100         Grand Chateau", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[ARCHERIE1] = new ActionButton(ARCHERIE1, "  100             40         Archerie", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[ARCHERIE2] = new ActionButton(ARCHERIE2, "  200             50         Grande Archerie", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[FERME    ] = new ActionButton(FERME    , "  650             20          Ferme", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[TOWER    ] = new ActionButton(TOWER    , "  300             15          Tour de defense", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[CHATEAU1 ]->addTexture(gold, 41, 3) ;
	(*bouton)[CHATEAU1 ]->addTexture(wood, 106, 3) ;
	(*bouton)[CHATEAU2 ]->addTexture(gold, 41, 3) ;
	(*bouton)[CHATEAU2 ]->addTexture(wood, 106, 3) ;
	(*bouton)[ARCHERIE1]->addTexture(gold, 41, 3) ;
	(*bouton)[ARCHERIE1]->addTexture(wood, 106, 3) ;
	(*bouton)[ARCHERIE2]->addTexture(gold, 41, 3) ;
	(*bouton)[ARCHERIE2]->addTexture(wood, 106, 3) ;
	(*bouton)[FERME    ]->addTexture(gold, 41, 3) ;
	(*bouton)[FERME    ]->addTexture(wood, 106, 3) ;
	(*bouton)[TOWER    ]->addTexture(gold, 41, 3) ;
	(*bouton)[TOWER    ]->addTexture(wood, 106, 3) ;

	(*bouton)[AMELIORER] = new ActionButton(AMELIORER, "Augmenter ..    ", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[UP_GOLD] = new ActionButton(UP_GOLD, "  la production d'or (+1)", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_FOOD] = new ActionButton(UP_FOOD, "  la production de nourriture (+1)", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_WOOD] = new ActionButton(UP_WOOD, "  la production de bois (+1)", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_DEFENSE] = new ActionButton(UP_DEFENSE, "  la defense du batiment (+2)", LARGEUR_MENU3, 20, grey2, black, 15) ;

	(*bouton)[ENTETE_BATIMENT] = new ActionButton(ENTETE_BATIMENT, "construction", LARGEUR_MENU2, 30, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[ENTETE_GOLD] = new ActionButton(ENTETE_GOLD, "+", LARGEUR_MENU2, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[ENTETE_FOOD] = new ActionButton(ENTETE_FOOD, "+", LARGEUR_MENU2, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[ENTETE_WOOD] = new ActionButton(ENTETE_WOOD, "+", LARGEUR_MENU2, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[CONSTRUIRE_BATIMENT] = new SubMenuButton(CONSTRUCTION_BATIMENT_MENU, "Construire un batiment", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[CONSTRUIRE_UNIT] = new SubMenuButton(CONSTRUCTION_UNIT_MENU, "Construire une unite", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[AMELIORATION_BATIMENT] = new SubMenuButton(AMELIORER_MENU, "Ameliorer le batiment", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[AMELIORATION_CHATEAU] = new SubMenuButton(AMELIORER_CHATEAU_MENU, "Ameliorer le chateau", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	
	(*bouton)[UPGRADES] = new SubMenuButton(UPGRADES_MENU, "Ameliorations", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[DEPLACEMENTPLUS] = new ActionButton(DEPLACEMENTPLUS, "Deplacement en diagonale", LARGEUR_MENU3, 20, grey2, black, 15) ;

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
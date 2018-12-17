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
	(*bouton)[ENREGISTRER] = new ActionButton(ENREGISTRER, "Enregistrer la carte", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 27, CENTER_TEXT, "extra") ;
	(*bouton)[CAPTURE] = new ActionButton(CAPTURE, "CAPTURE D'ECRAN MAP", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 24, CENTER_TEXT, "extra") ;
	(*bouton)[MUSIQUE] = new ActionButton(MUSIQUE, "MUSIQUE", 200, 100, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[QUITTER] = new ActionButton(QUITTER, "Quitter", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[FIN_DU_TOUR] = new ActionButton(FIN_DU_TOUR, "Fin du tour", LARGEUR_MENU1, HAUTEUR_MENU1, white, black, 30, CENTER_TEXT, "extra") ;
	(*bouton)[AFFICHAGE] = new ActionButton(AFFICHAGE, "Tour de ", LARGEUR_MENU1, HAUTEUR_MENU1, black, white, 30, CENTER_TEXT, "extra") ;
	
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

	(*bouton)[CHATEAU1 ] = new ActionButton(CHATEAU1 , " 500              80         Chateau", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[CHATEAU2 ] = new ActionButton(CHATEAU2 , " 1200             150         Grand Chateau", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[ATELIER1 ] = new ActionButton(ATELIER1 , "  300             50         Atelier", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[ATELIER2 ] = new ActionButton(ATELIER2 , "  500             75         Grand Atelier", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[FERME    ] = new ActionButton(FERME    , "  200             40          Ferme", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[TOWER    ] = new ActionButton(TOWER    , "  500             75          Tour de defense", LARGEUR_MENU3, 20, grey2, black, 14) ;
	(*bouton)[CHATEAU1 ]->addTexture(gold, 41, 3) ;
	(*bouton)[CHATEAU1 ]->addTexture(wood, 116, 3) ;
	(*bouton)[CHATEAU2 ]->addTexture(gold, 41, 3) ;
	(*bouton)[CHATEAU2 ]->addTexture(wood, 116, 3) ;
	(*bouton)[ATELIER1]->addTexture(gold, 41, 3) ;
	(*bouton)[ATELIER1]->addTexture(wood, 116, 3) ;
	(*bouton)[ATELIER2]->addTexture(gold, 41, 3) ;
	(*bouton)[ATELIER2]->addTexture(wood, 116, 3) ;
	(*bouton)[FERME    ]->addTexture(gold, 41, 3) ;
	(*bouton)[FERME    ]->addTexture(wood, 116, 3) ;
	(*bouton)[TOWER    ]->addTexture(gold, 41, 3) ;
	(*bouton)[TOWER    ]->addTexture(wood, 116, 3) ;

	(*bouton)[ENTETE_BATIMENT] = new ActionButton(ENTETE_BATIMENT, "construction", LARGEUR_MENU2, 30, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[ENTETE_GOLD] = new ActionButton(ENTETE_GOLD, "+", LARGEUR_MENU2, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[ENTETE_FOOD] = new ActionButton(ENTETE_FOOD, "+", LARGEUR_MENU2, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[ENTETE_WOOD] = new ActionButton(ENTETE_WOOD, "+", LARGEUR_MENU2, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[ENTETE_DEFENSE] = new ActionButton(ENTETE_DEFENSE, "+", LARGEUR_MENU2, 20, black, grey, 15, CENTER_TEXT, "bold") ;
	(*bouton)[RETOUR2] = new SubMenuButton(PETIT_CHATEAU_MENU, "RETOUR", LARGEUR_MENU3, 25, grey, black, 15, CENTER_TEXT, "extra") ;

	(*bouton)[ENTETE_CONSTRUCTION] = new ActionButton(ENTETE_CONSTRUCTION, "Construire ..       ", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[CONSTRUIRE_PETIT_BATIMENT] = new SubMenuButton(PETIT_BATIMENT_MENU, "Construire un batiment", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[CONSTRUIRE_GRAND_BATIMENT] = new SubMenuButton(GRAND_BATIMENT_MENU, "Construire un batiment", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[CONSTRUIRE_PETITE_UNITE] = new SubMenuButton(PETITE_UNITE_MENU, "Construire une unite", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[CONSTRUIRE_GRANDE_UNITE] = new SubMenuButton(GRANDE_UNITE_MENU, "Construire une unite", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	
	(*bouton)[AMELIORATION_CHATEAU] = new SubMenuButton(AMELIORER_CHATEAU_MENU, "Ameliorer le chateau", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;
	(*bouton)[AMELIORATION_FERME] = new SubMenuButton(AMELIORER_FERME_MENU, "Ameliorer la ferme", LARGEUR_MENU2, 25, grey, black, 13, CENTER_TEXT, "extra") ;

	(*bouton)[AMELIORER] = new ActionButton(AMELIORER, "Augmenter ..    ", LARGEUR_MENU3, 20, black, grey, 15, CENTER_TEXT, "extra") ;
	(*bouton)[UP_GOLD] = new ActionButton(UP_GOLD, "  la production d'or (+1)", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_FOOD] = new ActionButton(UP_FOOD, "  la production de nourriture (+1)", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_WOOD] = new ActionButton(UP_WOOD, "  la production de bois (+1)", LARGEUR_MENU3, 20, grey2, black, 15) ;
	(*bouton)[UP_DEFENSE] = new ActionButton(UP_DEFENSE, "  la defense du batiment (+2)", LARGEUR_MENU3, 20, grey2, black, 15) ;

	(*bouton)[RECHERCHE] = new ActionButton(RECHERCHE, "Rechercher ...   ", LARGEUR_MENU2, 25, black, grey, 13, CENTER_TEXT, "extra") ;
	
	(*bouton)[UPGRADES_UNIT] = new SubMenuButton(UPGRADES_ATELIER_MENU, "Rechercher et Ameliorer", LARGEUR_MENU2, 25, grey, black, 12, CENTER_TEXT, "extra") ;
	(*bouton)[DEPLACEMENTPLUS] = new ActionButton(DEPLACEMENTPLUS, " 1500               Deplacement en diagonale", LARGEUR_MENU3, 20, grey2, black, 12) ;
	(*bouton)[DEPLACEMENTPLUS]->addTexture(gold, 32, 3) ;
	(*bouton)[MOREDEGATS     ] = new ActionButton(MOREDEGATS     , " 1500               Degats +15 pour les unites", LARGEUR_MENU3, 20, grey2, black, 12) ;
	(*bouton)[MOREDEGATS     ]->addTexture(gold, 32, 3) ;
	
	(*bouton)[UPGRADES_CONS] = new SubMenuButton(UPGRADES_CHATEAU_MENU, "Rechercher et Ameliorer", LARGEUR_MENU2, 25, grey, black, 12, CENTER_TEXT, "extra") ;
	(*bouton)[MOREGOLD       ] = new ActionButton(MOREGOLD       , " 1250               +10 d'Or pour les batiments", LARGEUR_MENU3, 20, grey2, black, 12) ;
	(*bouton)[MOREGOLD       ]->addTexture(gold, 32, 3) ;
	(*bouton)[MOREDEFENSE    ] = new ActionButton(MOREDEFENSE    , " 1600               +10 defense pour les batiments", LARGEUR_MENU3, 20, grey2, black, 12) ;
	(*bouton)[MOREDEFENSE    ]->addTexture(gold, 32, 3) ;

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
#ifndef __MATRICEGAMEGESTION_H__
#define __MATRICEGAMEGESTION_H__

#include "SDL/SDL.h"
#include <SDL/SDL_ttf.h>

#include "../Fonctions/fonctions.h"
#include "../Fonctions/remplissage.h"

#include "../DisplayClass/fenetre.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/Menu.h"

#include "../CharactersClass/AbstractPlayer.h"
#include "../MapClass/construction.h"
#include "../MapClass/map.h"
#include "../MatriceClass/MatriceGameGestion.h"

#include <vector>

class MatriceGameGestion
{
	public:
		MatriceGameGestion();
		~MatriceGameGestion();

		void init() ;
		void gameLoop() ;

	private :	
		Fenetre m_fenetre ;
		std::vector <Menu*> m_saveMenu ;
		std::vector <AbstractButton*> * m_all_buttons ;

		Map m_map ;
		SDL_Rect m_scroll ; //Représente le rectangle de la map affichée sur la fenêtre
		std::vector <AbstractPlayer*>* m_player_list ;	

	private :
		//static Unit* current_select_unit ;
		//static AbstractPlayer* current_turn_player ;

	private :
		void updateDisplay() ;
		//void initTurnPlayer() ;
		//void moveUnit() ;
		//void defeatPlayer() ;
		//void winPlayer() ;

};

#endif // __MATRICEGAMEGESTION_H__
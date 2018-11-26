#ifndef __MATRICEGAMEGESTION_H__
#define __MATRICEGAMEGESTION_H__

#include "SDL/SDL.h"
#include <SDL/SDL_ttf.h>

#include "../Fonctions/fonctions.h"
#include "../Fonctions/remplissage.h"

#include "../DisplayClass/fenetre.h"
#include "../ID/idbuttons.h"
#include "../MenuClass/ActionButton.h"
#include "../ID/idmenus.h"
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
		std::vector <AbstractPlayer> m_player_list ;
		Fenetre m_fenetre ;
		Map m_map ;
		std::vector <Menu*> m_saveMenu ;
		std::vector <AbstractButton*> * m_all_buttons ;

	private :
		//void initTurnPlayer() ;
		//void moveUnit() ;
		//void defeatPlayer() ;
		//void winPlayer() ;

};

#endif // __MATRICEGAMEGESTION_H__
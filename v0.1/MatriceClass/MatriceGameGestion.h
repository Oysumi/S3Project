#ifndef __MATRICEGAMEGESTION_H__
#define __MATRICEGAMEGESTION_H__

/*#include "../CharactersClass/AbstractPlayer.h"
#include "../CharactersClass/AbstractUnit.h"
#include "../ConstructionClass/AbstractConstruction.h"*/
/* include the map file */
#include "../MenuClass/Menu.h"
#include "../DisplayClass/fenetre.h"

#include <vector>

class MatriceGameGestion
{
	public:
		MatriceGameGestion();
		void gameLoop(/*TO DEFINE*/);
		void addMenu(Menu menuToAdd);
		void openMenu(int id, Fenetre screen) ;

	private:
		void initTurnPlayer() ;
		void moveUnit() ;
		void defeatPlayer() ;
		void winPlayer() ;

		std::vector<Menu> m_allMenu ;
		/* [...] */

		/*Map m_myMap ;
		std::vector<AbstractPlayer> m_myPlayers ;
		std::vector<AbstractConstruction> m_myConstructions ;
		std::vector<AbstractUnit> m_myUnit ;*/

};

#endif // __MATRICEGAMEGESTION_H__
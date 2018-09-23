#ifndef __MATRICEGAMEGESTION_H__
#define __MATRICEGAMEGESTION_H__

#include "../CharactersClass/AbstractPlayer.h"
#include "../CharactersClass/AbstractUnit.h"
//#include "../ConstructionClass/AbstractConstruction.h"
/* include the map file */

#include <list>

class MatriceGameGestion
{
	public:
		MatriceGameGestion();
		~MatriceGameGestion();
		void gameLoop(/*TO DEFINE*/);

	private:
		void initTurnPlayer() ;
		void moveUnit() ;
		void defeatPlayer() ;
		void winPlayer() ;
		/* [...] */

		/*Map m_myMap ;
		std::list<AbstractPlayer> m_myPlayers ;
		std::list<AbstractConstruction> m_myConstructions ;*/
		std::list<AbstractUnit> m_myUnit ;
};

#endif // __MATRICEGAMEGESTION_H__
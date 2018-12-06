#ifndef __ABSTRACTPLAYER_H__
#define __ABSTRACTPLAYER_H__

#include "SDL/SDL.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/map.h"
#include "../MatriceClass/decision.h"

class AbstractPlayer
{
	public :
		virtual ~AbstractPlayer() ;
		virtual Decision takeDecision(Fenetre& fenetre, Map const& map, SDL_Rect scroll) = 0 ;
};

#endif // __ABSTRACTPLAYER_H__

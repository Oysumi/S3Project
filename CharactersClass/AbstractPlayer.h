#ifndef __ABSTRACTPLAYER_H__
#define __ABSTRACTPLAYER_H__

#include "SDL/SDL.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/map.h"

class AbstractPlayer
{
	public :
		virtual ~AbstractPlayer() ;
		virtual void takeDecision(Fenetre fenetre, Map map, SDL_Rect scroll) = 0 ;
};

#endif // __ABSTRACTPLAYER_H__

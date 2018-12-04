#ifndef __ARTIFICIALPLAYER_H__
#define __ARTIFICIALPLAYER_H__

#include "AbstractPlayer.h"
#include "SDL/SDL.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/map.h"

class ArtificialPlayer : AbstractPlayer 
{
	public:
	 	virtual void takeDecision(Fenetre& fenetre, Map const& map, SDL_Rect scroll);
};

#endif // __ARTIFICIALPLAYER_H__
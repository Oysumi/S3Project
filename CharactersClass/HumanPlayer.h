#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include "AbstractPlayer.h"
#include "SDL/SDL.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/map.h"

class HumanPlayer : public AbstractPlayer
{
	public :
		HumanPlayer() ;
		virtual ~HumanPlayer() ;
		virtual void takeDecision(Fenetre fenetre, Map map, SDL_Rect scroll) ;
};

#endif // __HUMANPLAYER_H__
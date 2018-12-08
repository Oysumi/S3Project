#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include <string>

#include "AbstractPlayer.h"
#include "SDL/SDL.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/map.h"

class HumanPlayer : public AbstractPlayer
{
	public :
		HumanPlayer(std::string name, unsigned short color_id) ;
		virtual ~HumanPlayer() ;
		virtual Decision takeDecision(Fenetre& fenetre, Map const& map, SDL_Rect scroll) ;
};

#endif // __HUMANPLAYER_H__
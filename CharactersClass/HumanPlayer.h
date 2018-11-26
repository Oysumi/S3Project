#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include "AbstractPlayer.h"

class HumanPlayer : public AbstractPlayer
{
	public :
		virtual void takeDecision() ;
};

#endif // __HUMANPLAYER_H__
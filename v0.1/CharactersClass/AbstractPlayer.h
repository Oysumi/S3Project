#ifndef __ABSTRACTPLAYER_H__
#define __ABSTRACTPLAYER_H__

class AbstractPlayer
{
	public:
		AbstractPlayer() ;
		virtual void takeDecision() = 0 ;
		virtual ~AbstractPlayer() ;
};

#endif // __ABSTRACTPLAYER_H__

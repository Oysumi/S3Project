#include "AbstractPlayer.h"

using namespace std ;

AbstractPlayer::~AbstractPlayer()
{}

unsigned short AbstractPlayer::colorId() const
{
	return m_color_id ;
}

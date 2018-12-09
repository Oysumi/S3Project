#include "AbstractPlayer.h"

using namespace std ;

AbstractPlayer::AbstractPlayer(std::string name, unsigned short color_id) : m_name(name), m_color_id(color_id)
{}

AbstractPlayer::~AbstractPlayer()
{}

unsigned short AbstractPlayer::colorId() const
{return m_color_id ;}

string AbstractPlayer::name () const
{return m_name ;}
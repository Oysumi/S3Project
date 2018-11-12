#include "MapPos.h"

MapPos::MapPos(unsigned short const& x, unsigned short const& y)
{
	m_x = x ;
	m_y = y ;
}

MapPos::unsigned short x () const
{
	return m_x ;
}

MapPos::unsigned short y () const
{
	return m_y ;
}

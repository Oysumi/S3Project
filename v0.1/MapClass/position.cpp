#include "MapPos.h"

MapPos::MapPos(unsigned int const& x, unsigned int const& y)
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

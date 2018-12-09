#include "position.h"
using namespace std ;

MapPos::MapPos(unsigned short const& x, unsigned short const& y)
{
	m_x = x ;
	m_y = y ;
}

MapPos::MapPos(MapPos const& aCopier)
{
	m_x = aCopier.m_x ;
	m_y = aCopier.m_y ;
}

unsigned short MapPos::x () const
{
	return m_x ;
}

unsigned short MapPos::y () const
{
	return m_y ;
}

unsigned short MapPos::separation_value(MapPos const& pos) const
{
	unsigned short separation = 0 ;
	short diff = m_x - pos.m_x ;
	if (diff > 0)
		separation += diff ;
	else
		separation -= diff ;

	diff = m_y - pos.m_y ;
	if (diff > 0)
		separation += diff ;
	else
		separation -= diff ;

	return separation ;
}

bool MapPos::adjacent(MapPos const& pos, unsigned short nb_cases_de_separation) const
{
	return nb_cases_de_separation >= separation_value(pos) ;
}




bool MapPos::estegala(MapPos const& b) const
{
	return m_x == b.m_x && m_y == b.m_y ;
}

bool operator==(MapPos const& a, MapPos const& b)
{
	return a.estegala(b) ;
}

bool operator!=(MapPos const& a, MapPos const& b)
{
	return !(a==b) ;
}

bool MapPos::estpluspetitque(MapPos const& b) const
{
	if (m_x < b.m_x) return true ;
	if (m_x > b.m_x) return false ;
	if (m_y < b.m_y) return true ;
	return false ;
}

bool operator<(MapPos const& a, MapPos const& b)
{
	return a.estpluspetitque(b) ;
}

void MapPos::afficher(ostream &flux) const
{
    flux << m_x << ";" << m_y ;
}

ostream &operator<<( ostream &flux, MapPos const& pos)
{
    pos.afficher(flux) ;
    return flux;
}
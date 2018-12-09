#include "mapobject.h"
#include "SDL/SDL.h"
using namespace std;

MapObject::MapObject(MapPos const& pos, AbstractPlayer* proprietaire) : m_pos(pos)
{
	m_proprietaire = proprietaire ;
}

MapObject::MapObject(MapObject const& aCopier) : m_pos(aCopier.m_pos)
{
	m_proprietaire = aCopier.m_proprietaire ;
}

MapPos const& MapObject::getPos() const
{
	return m_pos ;
}

AbstractPlayer* MapObject::proprietaire () const
{
	return m_proprietaire ;
}

MapObject::~MapObject() {}
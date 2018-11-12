#include "map.h"
using namespace std ;

Map::Map(vector <AbstractPlayer> const& list_player) : m_terrain(250,250)
{
	
}

unsigned short Map::height() const
{
	return m_terrain.terrainComplet().height() ;
}

unsigned short Map::width() const
{
	return m_terrain.terrainComplet().width() ;
}

SurfaceAffichage const& Map::getSurface() const
{
	return m_terrain.terrainComplet() ;
}
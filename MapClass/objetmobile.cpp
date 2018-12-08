#include "objetmobile.h"
#include "SDL/SDL.h"
using namespace std;

ObjetMobile::ObjetMobile(MapPos const& pos, AbstractPlayer* proprietaire) : m_pos(pos)
{
	m_proprietaire = proprietaire ;
}

ObjetMobile::ObjetMobile(ObjetMobile const& aCopier) : m_pos(aCopier.m_pos)
{
	m_proprietaire = aCopier.m_proprietaire ;
}

MapPos const& ObjetMobile::getPos() const
{
	return m_pos ;
}
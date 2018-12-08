#include "construction.h"
#include "../CharactersClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std;

std::string Construction::sprite_construction_path = "../ressources/ground.bmp" ;

Construction::Construction(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	ObjetMobile(pos,player),
	m_type(type)
	{}

Construction::Construction(Construction const& aCopier) : 
	ObjetMobile(aCopier),
	m_type(aCopier.m_type) 
	{}

SurfaceAffichage Construction::getSurface() const
{
	SurfaceAffichage s (MAP_CASE_SIZE,MAP_CASE_SIZE) ;
	s.ajouter(SpriteTexture(sprite_construction_path,MAP_CASE_SIZE,NB_COLOR,NB_TYPE_CONSTRUCTION), m_proprietaire->colorId()) ;
	s.rendre_transparente() ;
	return s ;
}
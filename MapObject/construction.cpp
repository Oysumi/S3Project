#include "construction.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std;

std::string Construction::sprite_construction_path = "../ressources/constructions.bmp" ;

Construction::Construction(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	MapObject(pos,player),
	m_type(type%NB_TYPE_CONSTRUCTION)
	{}

Construction::Construction(Construction const& aCopier) : 
	MapObject(aCopier),
	m_type(aCopier.m_type) 
	{}

SurfaceAffichage Construction::getSurface() const
{
	SurfaceAffichage s (MAP_CASE_SIZE,MAP_CASE_SIZE) ;
	s.ajouter(SpriteTexture(sprite_construction_path,MAP_CASE_SIZE,NB_TYPE_CONSTRUCTION), m_type) ;
	s.rendre_transparente() ;
	return s ;
}

unsigned short Construction::type () const
{
	return OBJECT_TYPE_CONSTRUCTION ;
}
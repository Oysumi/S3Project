#include "construction.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std;

std::string Construction::sprite_construction_path = "../ressources/constructions.bmp" ;
SpriteTexture* Construction::sprite_construction = NULL ;

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
	s.ajouter(*sprite_construction, m_type) ;
	s.rendre_transparente() ;
	return s ;
}

void Construction::capture_by (AbstractPlayer * new_propietaire)
{
	m_proprietaire = new_propietaire ;
}

bool Construction::canMove () const
{
	return false ;
}

unsigned short Construction::type () const
{
	return OBJECT_TYPE_CONSTRUCTION ;
}




//DEUX METHODES STATIQUES PERMETTANT D'ÉVITER DE MULTIPLE CREATION DE SPRITETEXTURE
void Construction::initSprtiteTexture()
{
	sprite_construction = new SpriteTexture(sprite_construction_path,MAP_CASE_SIZE,NB_TYPE_CONSTRUCTION) ;
}
void Construction::deleteSprtiteTexture()
{
	if(sprite_construction != NULL)
	{
		delete(sprite_construction) ;
		sprite_construction = NULL ;
	}
	else
        warning_message("FUITE DE MEMOIRES : Impossible de supprimer sprite_construction in void Construction::deleteSprtiteTexture") ;
}
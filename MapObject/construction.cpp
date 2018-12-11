#include "construction.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std;

std::string Construction::sprite_construction_path = "../ressources/constructions.bmp" ;
SpriteTexture* Construction::sprite_construction = NULL ;
SurfaceAffichage*** Construction::construction_affichage = NULL ;

Construction::Construction(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	MapObject(pos,player),
	m_type(type%NB_TYPE_CONSTRUCTION)
	{
	}

Construction::Construction(Construction const& aCopier) : 
	MapObject(aCopier),
	m_type(aCopier.m_type)
	{
	}

SurfaceAffichage const& Construction::getSurface() const
{
	return *construction_affichage[m_proprietaire->colorId()][m_type] ;
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

	//Création d'un tableau servant au stockage des surfaces d'affichage des constructions pour ne pas les reconstruire à chaque affichage
    construction_affichage = (SurfaceAffichage***)malloc(NB_COLOR * sizeof(SurfaceAffichage**));
    for (unsigned short i = 0 ; i < NB_COLOR ; i++)
    {
        construction_affichage[i] = (SurfaceAffichage**)malloc(NB_TYPE_CONSTRUCTION * sizeof(SurfaceAffichage*));
    }

    for (unsigned short color = 0 ; color < NB_COLOR ; color++)
    {
        for (unsigned short type = 0 ; type < NB_TYPE_CONSTRUCTION ; type++)
        {
            construction_affichage[color][type] = new SurfaceAffichage (MAP_CASE_SIZE,MAP_CASE_SIZE) ;
			construction_affichage[color][type]->ajouter(*sprite_construction, type) ;
			construction_affichage[color][type]->rendre_transparente() ;
        }
    }
}
void Construction::deleteSprtiteTexture()
{
	for (unsigned short color = 0 ; color < NB_COLOR ; color++)
        for (unsigned short type = 0 ; type < NB_TYPE_CONSTRUCTION ; type++)
            delete(construction_affichage[color][type]) ;
    for (unsigned short i = 0 ; i < NB_COLOR ; i++)
        free(construction_affichage[i]) ;
    free(construction_affichage) ;


	if(sprite_construction != NULL)
	{
		delete(sprite_construction) ;
		sprite_construction = NULL ;
	}
	else
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer sprite_construction in void Construction::deleteSprtiteTexture") ;
}
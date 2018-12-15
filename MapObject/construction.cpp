#include "construction.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std;

std::string Construction::sprite_construction_path = "../ressources/constructions.bmp" ;
SpriteTexture* Construction::sprite_construction = NULL ;
SurfaceAffichage*** Construction::construction_affichage = NULL ;

void Construction::initCaracteristique()
{
	m_type = m_type % NB_TYPE_CONSTRUCTION ;
	if (m_type == CONSTRUCTION_CASTLE1)
	{
		m_name = "Petit chateau" ;
		m_apport = Ressource(40,5,10) ;
		m_defense = 40 ;
	}
	else if (m_type == CONSTRUCTION_CASTLE2)
	{
		m_name = "Grand chateau";
		m_apport = Ressource(50,10,20) ;
		m_defense = 60 ;
	}
	else if (m_type == CONSTRUCTION_ARCHERY1)
	{
		m_name = "Archerie niveau 1" ;
		m_apport = Ressource(20,-2,-5) ;
		m_defense = 25 ;
	}
	else if (m_type == CONSTRUCTION_ARCHERY2)
	{
		m_name = "Archerie niveau 2" ;
		m_apport = Ressource(60,-4,-10) ;
		m_defense = 30 ;
	}
	else if (m_type == CONSTRUCTION_FARM)
	{
		m_name = "Ferme";
		m_apport = Ressource(5,0,15) ;
		m_defense = 15 ;
	}
	else if (m_type == CONSTRUCTION_TOWER)
	{
		m_name = "Tour de defense";
		m_apport = Ressource(0,-1,-2) ;
		m_defense = 40 ;
	}
	else
		warning_message("Construction without type") ;
}



Construction::Construction(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	MapObject(pos,player),
	m_type(type%NB_TYPE_CONSTRUCTION)
	{
		initCaracteristique() ;
	}

Construction::Construction(Construction const& aCopier) : 
	MapObject(aCopier),
	m_type(aCopier.m_type)
	{
		m_name = aCopier.m_name ;
		m_apport = aCopier.m_apport ;
		m_defense = aCopier.m_defense ;
	}

SurfaceAffichage const& Construction::getSurface() const
{
	return *construction_affichage[m_proprietaire->colorId()][m_type] ;
}

void Construction::capture_by (AbstractPlayer * new_propietaire)
{
	m_proprietaire = new_propietaire ;
}

Ressource const& Construction::apport () const
{
	return m_apport ;
}

bool Construction::isInRangeOfConstruction(MapPos const& pos)
{
	if (m_type <= CONSTRUCTION_CASTLE2)
		return (m_pos.separation_value(pos) <= 3);
	else
		return (m_pos.separation_value(pos) <= 1);
}

bool Construction::canMove () const
{
	return false ;
}

string Construction::info() const
{
	return m_name + " de " + m_proprietaire->name() + ", defense : " + to_string(m_defense) ;
}

unsigned short Construction::type () const
{
	return OBJECT_TYPE_CONSTRUCTION ;
}




//DEUX METHODES STATIQUES PERMETTANT D'ÉVITER DE MULTIPLE CREATION DE SPRITETEXTURE
void Construction::initSprtiteTexture()
{
	sprite_construction = new SpriteTexture(sprite_construction_path,MAP_CASE_SIZE,MAP_CASE_SIZE,NB_TYPE_CONSTRUCTION) ;

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
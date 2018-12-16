#include "construction.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std;

std::string Construction::sprite_construction_path = "../ressources/constructions.bmp" ;
SpriteTexture* Construction::sprite_construction = NULL ;
SurfaceAffichage*** Construction::construction_affichage = NULL ;

std::string Construction::sprite_construction_placement_path = "../ressources/constructionsplacement.bmp" ;
SpriteTexture* Construction::sprite_construction_placement = NULL ;
SurfaceAffichage*** Construction::construction_affichage_placement = NULL ;

void Construction::initCaracteristique()
{
	m_type = m_type % NB_TYPE_CONSTRUCTION ;
	m_prix = prix(m_type) ;
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

Ressource Construction::prix (unsigned short type)
{
	type = type % NB_TYPE_CONSTRUCTION ;
	if (type == CONSTRUCTION_CASTLE1)
		return Ressource(1000,25,0) ;
	else if (type == CONSTRUCTION_CASTLE2)
		return Ressource(1200,40,0) ;
	else if (type == CONSTRUCTION_ARCHERY1)
		return Ressource(400,10,0) ;
	else if (type == CONSTRUCTION_ARCHERY2)
		return Ressource(750,20,0) ;
	else if (type == CONSTRUCTION_FARM)
		return Ressource(650,8,0) ;
	else // CONSTRUCTION TOWER
		return Ressource(300,5,0) ;
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
		m_prix = aCopier.m_prix ;
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

Ressource const& Construction::prix () const
{
	return m_prix ;
}

bool Construction::canBuyWith (unsigned short type, Ressource const& res, unsigned short population_use)
{
	type = type % NB_TYPE_CONSTRUCTION ;
	return res.gold() >= prix(type).gold() &&
        res.wood() >= prix(type).wood() ;
        // && res.food() - prix(type).food() <= population_use ;
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


SurfaceAffichage const& Construction::getSurfacePlacement(unsigned short type, bool correct)
{
	if (correct)
		return *construction_affichage_placement[0][type] ;
	else
		return *construction_affichage_placement[1][type] ;
}

unsigned short Construction::defense () const
{
	return m_defense ;
}



//DEUX METHODES STATIQUES PERMETTANT D'ÉVITER DE MULTIPLE CREATION DE SPRITETEXTURE & SURFACE D'AFFICHAGE POUR CHAQUE INSTANCE
void Construction::initSprtiteTexture()
{
	sprite_construction = new SpriteTexture(sprite_construction_path,MAP_CASE_SIZE,MAP_CASE_SIZE,NB_TYPE_CONSTRUCTION) ;
	//Création d'un tableau servant au stockage des surfaces d'affichage des constructions pour ne pas les reconstruire à chaque affichage
    construction_affichage = (SurfaceAffichage***)malloc(NB_COLOR * sizeof(SurfaceAffichage**));
    for (unsigned short i = 0 ; i < NB_COLOR ; i++)
        construction_affichage[i] = (SurfaceAffichage**)malloc(NB_TYPE_CONSTRUCTION * sizeof(SurfaceAffichage*));
    for (unsigned short color = 0 ; color < NB_COLOR ; color++)
        for (unsigned short type = 0 ; type < NB_TYPE_CONSTRUCTION ; type++)
        {
            construction_affichage[color][type] = new SurfaceAffichage (MAP_CASE_SIZE,MAP_CASE_SIZE) ;
			construction_affichage[color][type]->ajouter(*sprite_construction, type) ;
			construction_affichage[color][type]->rendre_transparente() ;
        }

    sprite_construction_placement = new SpriteTexture(sprite_construction_placement_path,MAP_CASE_SIZE,MAP_CASE_SIZE, NB_TYPE_CONSTRUCTION,2) ;
	//Création d'un tableau servant au stockage des surfaces d'affichage des constructions pour ne pas les reconstruire à chaque affichage
    construction_affichage_placement = (SurfaceAffichage***)malloc(2 * sizeof(SurfaceAffichage**));
    for (unsigned short i = 0 ; i < 2 ; i++)
        construction_affichage_placement[i] = (SurfaceAffichage**)malloc(NB_TYPE_CONSTRUCTION * sizeof(SurfaceAffichage*));
    for (unsigned short color = 0 ; color < 2 ; color++)
    {
        for (unsigned short type = 0 ; type < NB_TYPE_CONSTRUCTION ; type++)
        {
            construction_affichage_placement[color][type] = new SurfaceAffichage (MAP_CASE_SIZE,MAP_CASE_SIZE) ;
			construction_affichage_placement[color][type]->ajouter(*sprite_construction_placement, type, color) ;
			construction_affichage_placement[color][type]->rendre_transparente() ;
			SDL_SetAlpha(construction_affichage_placement[color][type]->surface(), SDL_SRCALPHA, 200 - color*72) ;
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

    //Destruction du tableau de Surface d'affichage
	for (unsigned short color = 0 ; color < 2 ; color++)
        for (unsigned short type = 0 ; type < NB_TYPE_CONSTRUCTION ; type++)
            delete(construction_affichage_placement[color][type]) ;
    for (unsigned short i = 0 ; i < 2 ; i++)
        free(construction_affichage_placement[i]) ;
    free(construction_affichage_placement) ;

    if(sprite_construction_placement != NULL)
	{
		delete(sprite_construction_placement) ;
		sprite_construction_placement = NULL ;
	}
	else
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer sprite_construction_placement in void Construction::deleteSprtiteTexture") ;

	if(sprite_construction != NULL)
	{
		delete(sprite_construction) ;
		sprite_construction = NULL ;
	}
	else
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer sprite_construction in void Construction::deleteSprtiteTexture") ;
}
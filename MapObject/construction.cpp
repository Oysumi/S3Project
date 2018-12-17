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
	if (m_type == CONSTRUCTION_CHATEAU1)
	{
		m_name = "Petit chateau" ;
		m_apport = Ressource(5,0,0) ;
		m_defense = 10 ;
		m_defense_max = 70 ;
		m_range = 2 ;
	}
	else if (m_type == CONSTRUCTION_CHATEAU2)
	{
		m_name = "Grand chateau";
		m_apport = Ressource(10,0,-10) ;
		m_defense = 20 ;
		m_defense_max = 80 ;
		m_range = 2 ;
	}
	else if (m_type == CONSTRUCTION_ATELIER1)
	{
		m_name = "Atelier niveau 1" ;
		m_apport = Ressource(-25,-5,-5) ;
		m_defense = 10 ;
		m_defense_max = 50 ;
		m_range = 1 ;
	}
	else if (m_type == CONSTRUCTION_ATELIER2)
	{
		m_name = "Atelier niveau 2" ;
		m_apport = Ressource(-50,-15,-10) ;
		m_defense = 20 ;
		m_defense_max = 60 ;
		m_range = 1 ;
	}
	else if (m_type == CONSTRUCTION_FERME)
	{
		m_name = "Ferme";
		m_apport = Ressource(15,-5,2) ;
		m_defense = 15 ;
		m_defense_max = 15 ;
		m_range = 1 ;
	}
	else if (m_type == CONSTRUCTION_TOUR)
	{
		m_name = "Tour de defense";
		m_apport = Ressource(-20,-15,-3) ;
		m_defense = 20 ;
		m_defense_max = 65 ;
		m_range = 3 ;
	}
	else
		warning_message("Construction without type") ;
}

Ressource Construction::prix (unsigned short type)
{
	type = type % NB_TYPE_CONSTRUCTION ;
	if (type == CONSTRUCTION_CHATEAU1)
		return Ressource(500,80,0) ;
	else if (type == CONSTRUCTION_CHATEAU2)
		return Ressource(1200,150,0) ;
	else if (type == CONSTRUCTION_ATELIER1)
		return Ressource(300,50,0) ;
	else if (type == CONSTRUCTION_ATELIER2)
		return Ressource(500,75,0) ;
	else if (type == CONSTRUCTION_FERME)
		return Ressource(200,40,0) ;
	else // CONSTRUCTION TOWER
		return Ressource(500,75,0) ;
}

Construction::Construction(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	MapObject(pos,player),
	m_type(type%NB_TYPE_CONSTRUCTION)
	{
		initCaracteristique() ;
		m_action_possible = false ;
	}

Construction::Construction(Construction const& aCopier) : 
	MapObject(aCopier),
	m_type(aCopier.m_type)
	{
		m_name = aCopier.m_name ;
		m_apport = aCopier.m_apport ;
		m_defense = aCopier.m_defense ;
		m_prix = aCopier.m_prix ;
		m_action_possible = aCopier.m_action_possible ;
		m_range = aCopier.m_range ;
		m_defense_max = aCopier.m_defense_max ;
	}

SurfaceAffichage const& Construction::getSurface() const
{
	return *construction_affichage[m_proprietaire->colorId()][m_type] ;
}

unsigned short Construction::constructionType () const
{
	return m_type ;
}

std::string Construction::name() const
{
	return m_name ;
}

void Construction::capture_by (AbstractPlayer * new_propietaire)
{
	m_proprietaire = new_propietaire ;
}

void Construction::reset_action_turn ()
{
	m_action_possible = true ;
}

void Construction::up_apport (Ressource to_add_at_apport_turn)
{
	m_apport += to_add_at_apport_turn ;
}

void Construction::up_range (unsigned short ajout)
{
	m_range += ajout ;
}

void Construction::up_defense (unsigned short ajout)
{
	m_defense += ajout ;
	if (m_defense > m_defense_max)
		m_defense = m_defense_max ;
}

void Construction::up_defense_max (unsigned short ajout)
{
	m_defense_max += ajout ;
	if (m_defense_max > 99)
		m_defense_max = 99 ;
}

bool Construction::canDoAction () const
{
	return m_action_possible ;
}

void Construction::noMoreAction()
{
	m_action_possible = false ;
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

bool Construction::isInRangeOfConstruction(MapPos const& pos) const
{
	return (m_pos.separation_value(pos) <= m_range) ;
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

unsigned short Construction::defense_max () const
{
	return m_defense_max ;
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
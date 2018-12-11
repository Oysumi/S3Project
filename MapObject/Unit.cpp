#include "Unit.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std ;

string Unit::sprite_unit_path = "../ressources/unit.bmp" ;
SpriteTexture* Unit::sprite_unit = NULL ;
SurfaceAffichage*** Unit::unit_affichage = NULL ;

void Unit::initCaracteristique()
{
	m_type = m_type % NB_TYPE_UNIT ;
	if (m_type == UNIT_CATAPULT)
	{
		m_name = "Catapulte" ;
		m_graphicEraseCons = false ;
		m_vitesse = 2 ;
	}
	else if (m_type == UNIT_SIEGE_TOWER)
	{
		m_name = "Tour de siège";
		m_graphicEraseCons = true ;
		m_vitesse = 1 ;
	}
	else if (m_type == UNIT_BALISTE)
	{
		m_name = "Baliste";
		m_graphicEraseCons = false ;
		m_vitesse = 2 ;
	}
	else if (m_type == UNIT_TREBUCHET)
	{
		m_name = "Trébuchet" ;
		m_graphicEraseCons = true ;
		m_vitesse = 2 ;
	}
	else if (m_type == UNIT_SIEGE_RAW)
	{
		m_name = "Bélier" ;
		m_graphicEraseCons = false ;
		m_vitesse = 2 ;
	}
}

Unit::Unit(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	MapObject(pos,player),
	m_type(type)
{
		initCaracteristique() ;
		m_deplacement = m_vitesse ;
}

Unit::Unit(Unit const& aCopier) : 
	MapObject(aCopier),
	m_type(aCopier.m_type)
{
	initCaracteristique() ;
	m_deplacement = aCopier.m_deplacement ;
}

SurfaceAffichage const& Unit::getSurface() const
{
	return *unit_affichage[m_proprietaire->colorId()][m_type] ;
}

unsigned short Unit::type () const
{
	return OBJECT_TYPE_UNIT ;
}

bool Unit::graphicEraseCons() const
{
	return m_graphicEraseCons ;
}

void Unit::reset_deplacement()
{
	m_deplacement = m_vitesse ;
}

bool Unit::canMove_at (MapPos const& pos) const
{
	if (pos != m_pos && pos.adjacent(m_pos, m_deplacement))
		return true ;
	return false ;
}

bool Unit::move(MapPos const& pos)
{
	if (canMove_at(pos))
	{
		m_deplacement -= m_pos.separation_value(pos) ;
		m_pos = pos ;
		return true ;
	}
	return false ;
}

bool Unit::canMove () const
{
	return m_deplacement > 0 ;
}

void Unit::changePos (MapPos const& new_pos)
{
	m_pos = new_pos ;
}



//DEUX METHODES STATIQUES PERMETTANT D'ÉVITER DE MULTIPLE CREATION DE SPRITETEXTURE
void Unit::initSprtiteTexture()
{
	sprite_unit = new SpriteTexture(sprite_unit_path,MAP_CASE_SIZE,NB_COLOR,NB_TYPE_UNIT) ;

	//Création d'un tableau servant au stockage des surfaces d'affichage des unités pour ne pas les reconstruire à chaque affichage
    unit_affichage = (SurfaceAffichage***)malloc(NB_COLOR * sizeof(SurfaceAffichage**));
    for (unsigned short i = 0 ; i < NB_COLOR ; i++)
    {
        unit_affichage[i] = (SurfaceAffichage**)malloc(NB_TYPE_UNIT * sizeof(SurfaceAffichage*));
    }

    for (unsigned short color = 0 ; color < NB_COLOR ; color++)
    {
        for (unsigned short type = 0 ; type < NB_TYPE_UNIT ; type++)
        {
            unit_affichage[color][type] = new SurfaceAffichage (MAP_CASE_SIZE,MAP_CASE_SIZE) ;
			unit_affichage[color][type]->ajouter(*sprite_unit, color, type) ;
			unit_affichage[color][type]->rendre_transparente() ;
        }
    }


}
void Unit::deleteSprtiteTexture()
{
	//Destruction du tableau de Surface d'affichage
	for (unsigned short color = 0 ; color < NB_COLOR ; color++)
        for (unsigned short type = 0 ; type < NB_TYPE_UNIT ; type++)
            delete(unit_affichage[color][type]) ;
    
    for (unsigned short i = 0 ; i < NB_COLOR ; i++)
        free(unit_affichage[i]) ;

    free(unit_affichage) ;

	if(sprite_unit != NULL)
	{
		delete(sprite_unit) ;
		sprite_unit = NULL ;
	}
	else
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer sprite_unit in void Unit::deleteSprtiteTexture") ;
}
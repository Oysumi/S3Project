#include "Unit.h"
#include "../PlayerClass/AbstractPlayer.h"
#include "SDL/SDL.h"
using namespace std ;

string Unit::sprite_unit_path = "../ressources/unit.bmp" ;
string Unit::sprite_unit_placement_path = "../ressources/unitplacement.bmp" ;
string Unit::sprite_life_path = "../ressources/life.bmp" ;
SpriteTexture* Unit::sprite_unit = NULL ;
SpriteTexture* Unit::sprite_unit_placement = NULL ;
SpriteTexture* Unit::sprite_life = NULL ;
SurfaceAffichage*** Unit::unit_affichage = NULL ;
SurfaceAffichage*** Unit::unit_affichage_placement = NULL ;
std::vector<SurfaceAffichage*> Unit::life_affichage ;

#define NB_SPRITE_LIFE 48
#define SPRITE_LIFE_WIDTH 50
#define SPRITE_LIFE_HEIGHT 5

void Unit::initCaracteristique()
{
	m_type = m_type % NB_TYPE_UNIT ;
	m_prix = prix(m_type) ;
	if (m_type == UNIT_CATAPULT)
	{
		m_name = "Catapulte" ;
		m_graphicEraseCons = false ;
		m_vitesse = 2 ;
		m_vieMax = 100 ;
		m_degats = 35 ;
	}
	else if (m_type == UNIT_BALISTE)
	{
		m_name = "Baliste";
		m_graphicEraseCons = false ;
		m_vitesse = 3 ;
		m_vieMax = 75 ;
		m_degats = 35 ;
	}
	else if (m_type == UNIT_SIEGE_RAW)
	{
		m_name = "Belier" ;
		m_graphicEraseCons = false ;
		m_vitesse = 2 ;
		m_vieMax = 250 ;
		m_degats = 50 ;
	}
	else if (m_type == UNIT_TREBUCHET)
	{
		m_name = "Trebuchet" ;
		m_graphicEraseCons = true ;
		m_vitesse = 1 ;
		m_vieMax = 200 ;
		m_degats = 125 ;
	}
	else if (m_type == UNIT_SIEGE_TOWER)
	{
		m_name = "Tour de siege";
		m_graphicEraseCons = true ;
		m_vitesse = 1 ;
		m_vieMax = 400 ;
		m_degats = 85 ;
	}
	else
		warning_message("Unit without type") ;
}

Ressource Unit::prix (unsigned short type)
{
	type = type % NB_TYPE_UNIT ;
	if (type == UNIT_CATAPULT)
		return Ressource(300,0,4) ;
	else if (type == UNIT_BALISTE)
		return Ressource(450,0,4) ;
	else if (type == UNIT_SIEGE_RAW)
		return Ressource(650,0,5) ;
	else if (type == UNIT_TREBUCHET)
		return Ressource(750,0,6) ;
	else // CONSTRUCTION SIEGE TOWER
		return Ressource(800,0,8) ;
}

Unit::Unit(unsigned short type , MapPos const& pos, AbstractPlayer* const& player) :
	MapObject(pos,player),
	m_type(type)
{
		initCaracteristique() ;

		m_deplacement = 0 ;
		m_vie = m_vieMax ;

		m_last_vitcory_pos = NULL ;
}

Unit::Unit(Unit const& aCopier) : 
	MapObject(aCopier),
	m_type(aCopier.m_type)
{
	m_name = aCopier.m_name ;
	m_graphicEraseCons = aCopier.m_graphicEraseCons ;

	m_vieMax = aCopier.m_vieMax ;
	m_vitesse = aCopier.m_vitesse ;
	m_degats = aCopier.m_degats ;
	m_prix = aCopier.m_prix ;
		
	m_vie = aCopier.m_vie ;
	m_deplacement = aCopier.m_deplacement ;

	m_last_vitcory_pos = NULL ;
	if (aCopier.m_last_vitcory_pos != NULL)
		newVictoryPos(*aCopier.m_last_vitcory_pos) ;
}

Unit::~Unit()
{
	if (m_last_vitcory_pos != NULL)
	{
		delete(m_last_vitcory_pos) ;
		m_last_vitcory_pos = NULL ;
	}
}

SurfaceAffichage const& Unit::getSurface() const
{
	return *unit_affichage[m_proprietaire->colorId()][m_type] ;
}

SurfaceAffichage const& Unit::getLifeSurface() const
{
	return *life_affichage[ (((m_vieMax-m_vie)*NB_SPRITE_LIFE)/m_vieMax) % NB_SPRITE_LIFE] ;
}

bool Unit::fullLife() const
{
	return m_vie == m_vieMax ;
}

bool Unit::isDead() const
{
	return m_vie <= 0 ;
}


string Unit::name() const
{
	return m_name ;
}

string Unit::info() const
{
	return m_name + " de " + m_proprietaire->name() + "\n degats: " + to_string(m_degats) + "\n deplacement: " + to_string(m_deplacement) + "/" + to_string(m_vitesse) + "\n vie: " + to_string(m_vie) + "/" + to_string(m_vieMax) ;
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

void Unit::up_degats(unsigned short quantite)
{
	m_degats += quantite ;
}

//Position adjacente ?
bool Unit::canAttack_at (MapPos const& pos) const
{
	return m_pos.separation_value(pos) == 1 && m_deplacement > 0 ;
}

bool Unit::subirAttaque(Unit* attaquant, unsigned short pourcentage_reduction)
{
	if (!attaquant->canAttack_at(m_pos))
		return false ; // Pas d'attaque

	if (pourcentage_reduction > 99)
	{
		warning_message("try to do attack with reduction percentage more than 99") ;
		return false ;
	}
	
	recevoirDegats( ((100-pourcentage_reduction)*attaquant->degats())/100 ) ;
	attaquant->m_deplacement = 0 ;

	if (isDead())
		attaquant->newVictoryPos(m_pos) ;

	return true ;
}

void Unit::recevoirDegats(unsigned short nb_degats)
{
	if (nb_degats > m_vie)
		m_vie = 0 ;
	else
		m_vie -= nb_degats ;
}

bool Unit::canMove_at (MapPos const& pos, bool diagonale) const
{
	if (pos != m_pos && pos.adjacent(m_pos, 1))
		return true ;
	if (m_last_vitcory_pos != NULL)
		if (pos == *m_last_vitcory_pos)
			return true ;
	if (diagonale)
	{		
       	if (m_pos == MapPos(pos.x()-1,pos.y()-1))
            return true ;
        if (m_pos == MapPos(pos.x()+1,pos.y()+1))
        	return true ;
        if (m_pos == MapPos(pos.x()+1,pos.y()-1))
        	return true ;
        if (m_pos == MapPos(pos.x()-1,pos.y()+1))
        	return true ;
    }
	return false ;
}

unsigned short Unit::degats () const
{
	return m_degats ;
}

Ressource const& Unit::prix () const
{
	return m_prix ;
}

bool Unit::canBuyWith (unsigned short type, Ressource const& res, unsigned short population_use)
{
	type = type % NB_TYPE_UNIT ;
	return res.gold() >= prix(type).gold() &&
        res.wood() >= prix(type).wood() &&
        res.food() >= prix(type).food() + population_use ;
}

bool Unit::move(MapPos const& pos, bool diagonale)
{
	if (canMove_at(pos, diagonale))
	{
		if (m_last_vitcory_pos != NULL)
			if (pos == *m_last_vitcory_pos) /*Aller à l'emplacement de la victoire après un combat est normal
										bien que l'unité est perdue ses points de déplacement dans la bataille*/
			{
				delete(m_last_vitcory_pos) ;
				m_last_vitcory_pos = NULL ;
				changePos(pos) ;
				return true ;
			}

		m_deplacement -= 1 ;
		changePos(pos) ;
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

void Unit::newVictoryPos(MapPos const& pos)
{
	if (m_last_vitcory_pos != NULL)
		delete(m_last_vitcory_pos) ;
	m_last_vitcory_pos = new MapPos(pos) ;
}


SurfaceAffichage const& Unit::getSurfacePlacement(unsigned short type, bool correct)
{
	if (correct)
		return *unit_affichage_placement[0][type] ;
	else
		return *unit_affichage_placement[1][type] ;
}




//DEUX METHODES STATIQUES PERMETTANT D'ÉVITER DE MULTIPLE CREATION DE SPRITETEXTURE & SURFACE D'AFFICHAGE POUR CHAQUE INSTANCE
void Unit::initSprtiteTexture()
{
	sprite_life = new SpriteTexture(sprite_life_path,SPRITE_LIFE_WIDTH,SPRITE_LIFE_HEIGHT,1,NB_SPRITE_LIFE) ;
    for (unsigned short i = 0 ; i < NB_SPRITE_LIFE ; i++)
    {
        life_affichage.push_back(new SurfaceAffichage(SPRITE_LIFE_WIDTH,SPRITE_LIFE_HEIGHT)) ;
		life_affichage.back()->ajouter(*sprite_life, 0, 0, 0, i) ;
		life_affichage.back()->rendre_transparente() ;
    }


	sprite_unit = new SpriteTexture(sprite_unit_path,MAP_CASE_SIZE,MAP_CASE_SIZE,NB_COLOR,NB_TYPE_UNIT) ;
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

    sprite_unit_placement = new SpriteTexture(sprite_unit_placement_path,MAP_CASE_SIZE,MAP_CASE_SIZE,2,NB_TYPE_UNIT) ;
	//Création d'un tableau servant au stockage des surfaces d'affichage des unités pour ne pas les reconstruire à chaque affichage
    unit_affichage_placement = (SurfaceAffichage***)malloc(2 * sizeof(SurfaceAffichage**));
    for (unsigned short i = 0 ; i < 2 ; i++)
    {
        unit_affichage_placement[i] = (SurfaceAffichage**)malloc(NB_TYPE_UNIT * sizeof(SurfaceAffichage*));
    }
    for (unsigned short color = 0 ; color < 2 ; color++)
    {
        for (unsigned short type = 0 ; type < NB_TYPE_UNIT ; type++)
        {
            unit_affichage_placement[color][type] = new SurfaceAffichage (MAP_CASE_SIZE,MAP_CASE_SIZE) ;
			unit_affichage_placement[color][type]->ajouter(*sprite_unit_placement, color, type) ;
			unit_affichage_placement[color][type]->rendre_transparente() ;
			SDL_SetAlpha(unit_affichage_placement[color][type]->surface(), SDL_SRCALPHA, 200 - color*72) ;
        }
    }


}


void Unit::deleteSprtiteTexture()
{

	//Destruction du tableau de Surface d'affichage
	for (unsigned short color = 0 ; color < 2 ; color++)
        for (unsigned short type = 0 ; type < NB_TYPE_UNIT ; type++)
            delete(unit_affichage_placement[color][type]) ;
    for (unsigned short i = 0 ; i < 2 ; i++)
        free(unit_affichage_placement[i]) ;
    free(unit_affichage_placement) ;


	//Destruction du tableau de Surface d'affichage
	for (unsigned short color = 0 ; color < NB_COLOR ; color++)
        for (unsigned short type = 0 ; type < NB_TYPE_UNIT ; type++)
            delete(unit_affichage[color][type]) ;
    for (unsigned short i = 0 ; i < NB_COLOR ; i++)
        free(unit_affichage[i]) ;
    free(unit_affichage) ;

    //Suppression des Surface d'affichage de la mémoire
	while(!life_affichage.empty())
    {
        if (life_affichage.back() != NULL)
        	delete(life_affichage.back()) ;
        else
        	warning_message("Potentielle fuite de mémoire : Impossible de supprimer life_affichage.back() in void Unit::deleteSprtiteTexture") ;
        life_affichage.pop_back() ;
    }


    if(sprite_life != NULL)
	{
		delete(sprite_life) ;
		sprite_life = NULL ;
	}
	else
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer sprite_life in void Unit::deleteSprtiteTexture") ;

	if(sprite_unit != NULL)
	{
		delete(sprite_unit) ;
		sprite_unit = NULL ;
	}
	else
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer sprite_unit in void Unit::deleteSprtiteTexture") ;
}
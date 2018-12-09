#include "map.h"
using namespace std ;

Map::Map(unsigned short x, unsigned short y) : m_terrain(x,y,m_free_pos)
{
	m_map_unit = new map <MapPos, Unit*> ;
    m_map_cons  = new map <MapPos, Construction*> ;

	m_graphic_map = new SurfaceAffichage(width(),height()) ;
	m_graphic_map->ajouter(m_terrain.terrainComplet()) ;
}

Map::Map() : Map(5,5)
{}

Map::~Map()
{
	//Suppression des graphismes de la map de la mémoire
	if (m_graphic_map != NULL)
	{
		delete(m_graphic_map) ;
		m_graphic_map = NULL ;
	}

	//Suppression des unités de la mémoire
	while(!m_list_unit.empty())
    {
        delete(m_list_unit.back()) ;
        m_list_unit.pop_back() ;
    }

    //Suppression des construction de la mémoire
	while(!m_list_cons.empty())
    {
        delete(m_list_cons.back()) ;
        m_list_cons.pop_back() ;
    }

    if(m_map_unit != NULL)
    {
    	delete m_map_unit ;
    	m_map_unit = NULL ;
    }
    if(m_map_cons != NULL)
    {
    	delete m_map_cons ;
    	m_map_cons = NULL ;
    }

    delete(m_free_pos) ;

}

unsigned short Map::height() const
{
	return m_terrain.terrainComplet().height() ;
}

unsigned short Map::width() const
{
	return m_terrain.terrainComplet().width() ;
}

SurfaceAffichage const& Map::getSurface() const
{
	return *m_graphic_map ;
}

MapPos Map::random_free_pos () const
{
	if (m_free_pos->size() > 0)
	{
		list<MapPos>::iterator it = m_free_pos->begin() ;
		unsigned short random_index = rand()%m_free_pos->size() ;
		for(unsigned int i = 0; i < random_index; i++)
    	{
        	it++;
    	}
		return *it ;
	}

	warning_message("Impossible de trouver un emplacement libre") ;
	return MapPos(0,0) ;
}

unsigned int Map::nb_free_pos () const
{
	return m_free_pos->size() ;
}

MapPos Map::mapPos_of_click (SDL_Rect const& scroll, unsigned short const& x, unsigned short const& y) const
{
	//Retourne la position associé au click sur l'écran en x y avec un décallage égal à Scroll 
    return MapPos((x+scroll.x)/m_terrain.sprite_size(),(height()-y-scroll.y)/m_terrain.sprite_size()) ;
}


bool Map::add_unit (Unit const& unit)
{
	MapPos pos (unit.getPos()) ;
	if (pos.x() >= m_terrain.posxOut() || pos.y() >= m_terrain.posyOut()) //Postion valide ?
	{
		warning_message("Try to add unit with position out the map") ;
		return false ;
	}
	if (m_map_unit->find(pos) != m_map_unit->end()) //Unité dejà presénte à cette postion ?
	{
		if(m_map_unit->at(pos) != NULL)
		{
			warning_message("Try to add unit with position out the map") ;
			return false ;
		}
	}
	//Ajout de l'unité à la map
	m_list_unit.push_back(new Unit (unit)) ;
	(*m_map_unit)[pos] = m_list_unit.back() ;
	m_free_pos->remove(pos) ;
	ajouter_texture_objets(unit.getPos()) ;
	return true ;
}

bool Map::add_cons(Construction const& cons)
{
	MapPos pos (cons.getPos()) ;
	if (pos.x() >= m_terrain.posxOut() || pos.y() >= m_terrain.posyOut()) //Postion valide ?
	{
		warning_message("Try to add unit with position out the map") ;
		return false ;
	}
	if (m_map_cons->find(pos) != m_map_cons->end()) //Construction dejà presénte à cette postion ?
	{
		if(m_map_cons->at(pos) != NULL)
		{
			warning_message("Try to add unit with position out the map") ;
			return false ;
		}
	}
	//Ajout de la construction à la map
	m_list_cons.push_back(new Construction (cons)) ;
	(*m_map_cons)[pos] = m_list_cons.back() ;
	m_free_pos->remove(pos) ;
	ajouter_texture_objets(cons.getPos()) ;
	return true ;
}

bool Map::have_unit_on (MapPos const& pos) const
{
	if (m_map_unit->find(pos) == m_map_unit->end()) //Rien d'enregistré à cette position
		return false ;
    return (m_map_unit->at(pos) != NULL) ;
}

bool Map::have_cons_on (MapPos const& pos) const
{
	if (m_map_cons->find(pos) == m_map_cons->end()) //Rien d'enregistré à cette position
		return false ;
    return (m_map_cons->at(pos) != NULL) ;
}

Unit* Map::unit_on (MapPos const& pos)
{
	if (m_map_unit->find(pos) == m_map_unit->end()) //Rien d'enregistré à cette position
		return NULL ;
    return m_map_unit->at(pos) ;
}

Construction* Map::cons_on (MapPos const& pos)
{
	if (m_map_cons->find(pos) == m_map_cons->end()) //Rien d'enregistré à cette position
		return NULL ;
    return m_map_cons->at(pos) ;
}

void Map::add_symbol (SurfaceAffichage const& surface, MapPos const& pos, bool audessus)
{
	m_list_pos_symbol.push_back(pos) ;
	if (!audessus)
	{
		resest_texture(pos) ;
		m_graphic_map->ajouter(surface) ;
		ajouter_texture_objets(pos) ;
	}
	else
		ajouter(surface,pos) ;
}

void Map::delete_all_symbol() //Supprime tous les symboles de la map
{
	MapPos pos (0,0) ;
	while(!m_list_pos_symbol.empty())
	{
		pos = m_list_pos_symbol.back() ;
		resest_texture(pos) ;
		ajouter_texture_objets(pos) ;
		m_list_pos_symbol.pop_back() ;
	}
}





void Map::del_unit_texture(Unit const& unit)
{
	resest_texture(unit.getPos()) ;
	ajouter_texture_objets(unit.getPos()) ;
}

void Map::del_cons_texture(Construction const& cons)
{
	resest_texture(cons.getPos()) ;
	ajouter_texture_objets(cons.getPos()) ;
}

//Permet d'ajouter un graphisme sur une certaine case
void Map::ajouter(SurfaceAffichage const& surf, MapPos const& pos)
{
	m_graphic_map->ajouter(surf, pos.x()*MAP_CASE_SIZE, height()-(1+pos.y())*MAP_CASE_SIZE) ;
}

void Map::ajouter_texture_objets(MapPos const& pos)
{
	Unit* pu = unit_on(pos) ;
	if (pu != NULL)
		add_unit_texture(*pu) ;

	Construction* pc = cons_on(pos) ;
	if (pc != NULL)
		add_cons_texture(*pc) ;
}









//La map affiche le terrain sur cette case ce qui écrase et supprime tous les graphismes présents sur cette case
void Map::resest_texture(MapPos const& pos)
{
	m_graphic_map->ajouter(m_terrain.sprite(), pos.x()*MAP_CASE_SIZE, height()-(1+pos.y())*MAP_CASE_SIZE, m_terrain.sprite_code(pos)) ; //Réecriture du terrain (effacer)
}


void Map::add_unit_texture(Unit const& unit)
{
	ajouter(unit.getSurface(), unit.getPos()) ;
}

void Map::add_cons_texture(Construction const& cons)
{
	ajouter(cons.getSurface(), cons.getPos()) ;
}
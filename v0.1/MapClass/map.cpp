#include "map.h"
using namespace std ;

#define EMPTY_POS -1

Map::Map(unsigned short x, unsigned short y) : m_terrain(x,y,&m_free_pos)
{
	m_graphic_map = new SurfaceAffichage(width(),height()) ;
	m_graphic_map->ajouter(m_terrain.terrainComplet()) ;
}

Map::Map() : Map(5,5)
{}

Map::~Map()
{
	delete(m_graphic_map) ;
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

MapPos Map::random_free_pos ()
{
	if (m_free_pos.size() > 0)
	{
		list<MapPos>::iterator it = m_free_pos.begin() ;
		unsigned short random_index = rand()%m_free_pos.size() ;
		for(unsigned int i = 0; i < random_index; i++)
    	{
        	it++;
    	}
		return *it ;
	}

	warning_message("Impossible de trouver un emplacement libre") ;
	return MapPos(0,0) ;
}

unsigned int Map::nb_free_pos ()
{
	return m_free_pos.size() ;
}

bool Map::add_unit (Unit const& unit)
{
	MapPos pos (unit.getPos()) ;
	if (pos.x() >= m_terrain.posxOut() || pos.y() >= m_terrain.posyOut()) //Postion valide ?
	{
		warning_message("Try to add unit with position out the map") ;
		return false ;
	}
	if (m_map_unit.find(pos) != m_map_unit.end()) //Unité dejà presénte à cette postion ?
	{
		if(m_map_unit[pos] != EMPTY_POS)
		{
			warning_message("Try to add unit with position out the map") ;
			return false ;
		}
	}
	//Ajout de l'unité à la map
	m_list_unit.push_back(unit) ;
	m_map_unit[pos] = m_list_unit.size()-1 ;
	m_free_pos.remove(pos) ;
	add_unit_texture(unit) ;
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
	if (m_map_cons.find(pos) != m_map_cons.end()) //Construction dejà presénte à cette postion ?
	{
		if(m_map_cons[pos] != EMPTY_POS)
		{
			warning_message("Try to add unit with position out the map") ;
			return false ;
		}
	}
	//Ajout de la construction à la map
	m_list_cons.push_back(cons) ;
	m_map_cons[pos] = m_list_cons.size()-1 ;
	m_free_pos.remove(pos) ;
	add_cons_texture(cons) ;
	return true ;
}

void Map::add_unit_texture(Unit const& unit)
{
	m_graphic_map->ajouter(unit.getSurface(), unit.getPos().x()*MAP_CASE_SIZE, height()-(1+unit.getPos().y())*MAP_CASE_SIZE) ;
}

void Map::add_cons_texture(Construction const& cons)
{
	MapPos pos (cons.getPos()) ;
	m_graphic_map->ajouter(cons.getSurface(), pos.x()*MAP_CASE_SIZE, height()-(1+pos.y())*MAP_CASE_SIZE) ;
	
	if (m_map_unit.find(pos) != m_map_unit.end()) //Unité presénte à cette postion ?
	{
		if(m_map_unit[pos] != EMPTY_POS) //Unité à réécrire par dessus
		{
			add_unit_texture(m_list_unit[m_map_unit[pos]]) ;
		}
	}
}

void Map::del_unit_texture(Unit const& unit)
{
	MapPos pos (unit.getPos()) ;
	m_graphic_map->ajouter(m_terrain.sprite(), pos.x()*MAP_CASE_SIZE, height()-(1+pos.y())*MAP_CASE_SIZE, m_terrain.sprite_code(pos)) ; //Réecriture du terrain (effacer)
	if (m_map_cons.find(pos) != m_map_cons.end()) //Construction dejà presénte à cette postion ?
	{
		if(m_map_cons[pos] != EMPTY_POS) //Construction à réécrire par dessus
		{
			add_cons_texture(m_list_cons[m_map_cons[pos]]) ;
		}
	}
}

void Map::del_cons_texture(Construction const& cons)
{
	MapPos pos (cons.getPos()) ;
	m_graphic_map->ajouter(m_terrain.sprite(), pos.x()*MAP_CASE_SIZE, height()-(1+pos.y())*MAP_CASE_SIZE, m_terrain.sprite_code(pos)) ; //Réecriture du terrain (effacer)
	if (m_map_unit.find(pos) != m_map_unit.end()) //Unité dejà presénte à cette postion ?
	{
		if(m_map_unit[pos] != EMPTY_POS) //Unité à réécrire par dessus
		{
			add_unit_texture(m_list_unit[m_map_unit[pos]]) ;
		}
	}
}
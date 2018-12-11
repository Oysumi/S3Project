#include "map.h"
using namespace std ;

Map::Map(unsigned short x, unsigned short y) : m_terrain(x,y,m_free_pos)
{
	m_map_unit = new map <MapPos, Unit*> ;
    m_map_cons  = new map <MapPos, Construction*> ;

	m_graphic_map = new SurfaceAffichage(width(),height()) ;
	m_graphic_map->ajouter(m_terrain.terrainComplet()) ;

	Unit::initSprtiteTexture() ;
	Construction::initSprtiteTexture() ;
}

Map::Map() : Map(5,5)
{}

Map::~Map()
{
	Unit::deleteSprtiteTexture() ;
	Construction::deleteSprtiteTexture() ;

	//Suppression des graphismes de la map de la mémoire
	if (m_graphic_map != NULL)
	{
		delete(m_graphic_map) ;
		m_graphic_map = NULL ;
	}
	else
        warning_message("FUITE DE MEMOIRES : Impossible de supprimer m_graphic_map in ~Map()") ;

	//Suppression des unités de la mémoire
	while(!m_list_unit.empty())
    {
        if (m_list_unit.back() != NULL)
        	delete(m_list_unit.back()) ;
        else
        	warning_message("FUITE DE MEMOIRES : Impossible de supprimer m_list_unit.back() in ~Map()") ;
        m_list_unit.pop_back() ;
    }

    //Suppression des construction de la mémoire
	while(!m_list_cons.empty())
    {
        if (m_list_cons.back() != NULL)
        	delete(m_list_cons.back()) ;
        else
        	warning_message("FUITE DE MEMOIRES : Impossible de supprimer m_list_cons.back() in ~Map()") ;
        m_list_cons.pop_back() ;
    }


    if(m_map_unit != NULL)
    {
    	delete m_map_unit ;
    	m_map_unit = NULL ;
    }
    else 
        warning_message("FUITE DE MEMOIRES : Impossible de supprimer m_map_unit in ~Map()") ;


    if(m_map_cons != NULL)
    {
    	delete m_map_cons ;
    	m_map_cons = NULL ;
    }
    else 
        warning_message("FUITE DE MEMOIRES : Impossible de supprimer m_map_cons in ~Map()") ;


    if(m_free_pos != NULL)
    {
    	delete m_free_pos ;
    	m_free_pos = NULL ;
    }
    else 
        warning_message("FUITE DE MEMOIRES : Impossible de supprimer m_free_pos in ~Map()") ;

}

unsigned short Map::height() const
{
	return m_terrain.terrainComplet().height() ;
}

unsigned short Map::width() const
{
	return m_terrain.terrainComplet().width() ;
}

MapPos Map::posOut() const
{
	return MapPos(m_terrain.posxOut(),m_terrain.posyOut()) ;
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

bool Map::terrain_adapt_to_unit(MapPos const& pos, Unit const& unit) const
{
	return m_terrain.sprite_code(pos) == GRASS ;
}

unsigned short Map::nb_construction_of(AbstractPlayer* player) const
{
	unsigned short compt = 0 ;
	for (unsigned short i = 0 ; i < m_list_cons.size() ; i++)
		if (m_list_cons[i]->proprietaire() == player)
			compt ++ ;
	return compt ;
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
			warning_message("We have unit at pos try to add other unit") ;
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

bool Map::del_unit (Unit const& unit)
{
	MapPos const pos (unit.getPos()) ;
	
	if (!have_unit_on(pos)) // Aucune unité à supprimer
		return false ;

	Unit* pu = unit_on(pos); // On prend le pointeur de l'unité à cette position

	//Supression de la mémoire et du vecteur
	bool suppression = false ;
	for (vector<Unit*>::iterator it = m_list_unit.begin() ; it != m_list_unit.end() && !suppression ; it++)
		if(*it == pu)
		{
			if(!suppression)
				delete(pu) ;
			suppression = true ;
			m_list_unit.erase(it) ;
		}

	//supression de l'association avec la position
	m_map_unit->erase(pos) ;

	//cout << "			supression de l'association avec la position" << endl ;
	if (!have_cons_on(pos) && m_terrain.sprite_code(pos)==GRASS) //Si la position est libre, on l'ajoute
		m_free_pos->push_back(pos) ;

	//mises à jour des textures
	actualiser(pos) ;
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
			warning_message("We have construction at pos try to add other unit") ;
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

bool Map::move_unit_at(MapPos const& source, MapPos const& destination, bool erase_source_unit)
{
	if (!have_unit_on(source)) // Y a t-il une unité ?
		return false ;

	Unit* u = unit_on(source) ; // Si oui on prend cette unité
	
	//Si l'unité peut bouger et doit détruire l'autre à son arrivée
	if (u->canMove_at(destination) && erase_source_unit && have_unit_on(destination))
		del_unit(*unit_on(destination)) ; //Alors on la supprime avant d'y placer la nouvelle unité

	if (have_unit_on(destination)) // Déjà une unité à l'emplacement de destination
		return false ;

	bool result = u->move(destination) ;
	if (!result) // L'unité ne peut pas effectuer ce déplacement
		return false ;


	//mise à jour map d'association
	(*m_map_unit)[destination] = u ;
	m_map_unit->erase(source) ;

	//mise à jour de la liste des positions libres
	m_free_pos->remove(destination) ;
	if (!have_cons_on(source) && m_terrain.sprite_code(source)==GRASS) //Si la position est libre, on l'ajoute
		m_free_pos->push_back(source) ;

	//mises à jour des textures
	actualiser(source) ;
	actualiser(destination) ;
	
	return true ;
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

void Map::reset_deplacement_all_unit ()
{
	for (unsigned int i = 0 ; i < m_list_unit.size() ; i++)
	{
		if(m_list_unit[i] != NULL)
			m_list_unit[i]->reset_deplacement() ;
	}
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





void Map::actualiser (MapPos const& pos)
{
	resest_texture(pos) ;
	ajouter_texture_objets(pos) ;
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

//Permet d'ajouter un graphisme sur une certaine case
void Map::ajouter(SurfaceAffichage const& surf, MapPos const& pos)
{
	m_graphic_map->ajouter(surf, pos.x()*MAP_CASE_SIZE, height()-(1+pos.y())*MAP_CASE_SIZE) ;
}


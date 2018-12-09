#include "selection.h"
#include "../MapClass/map.h"
using namespace std ;

Selection::Selection(MapObject* selection, Map const& map, AbstractPlayer* current_player)
{
	m_selection = selection ;
    m_possible_to_move = NULL ;
	if (m_selection->type() == OBJECT_TYPE_UNIT)
	{
		m_select_unit = dynamic_cast<Unit*> (m_selection) ;

		MapPos const pos(m_select_unit->getPos()), out(map.posOut()) ;
		vector <MapPos> adjacent ;

        if (m_select_unit->proprietaire() == current_player)
        {
            if (pos.x() > 0)
                adjacent.push_back(MapPos(pos.x()-1,pos.y())) ;
            if (pos.x()+1 < out.x())
                adjacent.push_back(MapPos(pos.x()+1,pos.y())) ;
            if (pos.y() > 0)
                adjacent.push_back(MapPos(pos.x(),pos.y()-1)) ;
            if (pos.y()+1 < out.y())
                adjacent.push_back(MapPos(pos.x(),pos.y()+1)) ;

            m_possible_to_move = new std::vector <MapPos> ;
            for (unsigned short i = 0 ; i < adjacent.size() ; i++)
                if (map.terrain_adapt_to_unit(adjacent[i], *m_select_unit) && !map.have_unit_on(adjacent[i]))
                    m_possible_to_move->push_back(adjacent[i]) ;
        }
	}
    m_valid = true ;
}

Selection::Selection()
{
    m_selection = NULL ;
    m_possible_to_move = NULL ;
    m_valid = false ;
}

bool Selection::valid () const
{
    return m_valid ;
}

Selection::~Selection()
{
    if (m_possible_to_move != NULL)
    {
        delete(m_possible_to_move) ;
        m_possible_to_move = NULL ;
    }
}

bool Selection::possible_move_at (MapPos const& pos) const
{
    if (!m_valid)
        return false ;
    if (m_possible_to_move == NULL)
        return false ;
    for (unsigned short i = 0 ; i < m_possible_to_move->size() ; i++)
        if ((*m_possible_to_move)[i] == pos)
            return true ;
    return false ;
}

unsigned short Selection::type () const
{
    return Selection::m_selection->type() ;
}

MapPos Selection::getPos () const
{
    return m_selection->getPos() ;
}

MapObject* Selection::value()
{
    return m_selection ;
}

//Si l'objet selectionné est une unité
vector <MapPos> Selection::possible_to_move_unit () const
{
	return *m_possible_to_move ;
}

Unit* Selection::unit()
{
    return m_select_unit ;
}

AbstractPlayer* Selection::proprietaire_objet()
{
    return m_selection->proprietaire() ;
}

Unit const& Selection::see_select_unit() const
{
	return *m_select_unit ;
}
#include "selection.h"
#include "../MapClass/map.h"
using namespace std ;

Selection::Selection(MapObject* selection)
{
	m_selection = selection ;
    m_possible_to_move = NULL ;
    m_select_unit = NULL ;
    m_select_construction = NULL ;
	if (m_selection->type() == OBJECT_TYPE_UNIT)
	{
		m_select_unit = dynamic_cast<Unit*> (m_selection) ;
        m_possible_to_move = new vector <MapPos> ;
	}
    if (m_selection->type() == OBJECT_TYPE_CONSTRUCTION)
    {
        m_select_construction = dynamic_cast<Construction*> (m_selection) ;
    }
    m_valid = true ;
}

Selection::Selection()
{
    m_selection = NULL ;
    m_possible_to_move = NULL ;
    m_valid = false ;
}

MapObject const& Selection::see () const
{
    if (m_selection == NULL)
        erreur_message("Try to see Object on nul selection") ;
    return *m_selection ;
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
    else if (m_selection != NULL)
        if (m_selection->type() == OBJECT_TYPE_UNIT)
            warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_possible_to_move in ~Selection()") ;
}

bool Selection::add_possible_move_for_select_unit(MapPos const& pos)
{
    if(!m_valid || m_possible_to_move == NULL)
        return false ;
    m_possible_to_move->push_back(pos) ;
    return true ;
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

bool Selection::isObjectOf(AbstractPlayer* player) const
{
    return m_selection->proprietaire() == player ;
}

string Selection::info () const
{
    return m_selection->info() ;
}

short Selection::type () const
{
    if (m_selection == NULL)
        return -1 ;
    return m_selection->type() ;
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
vector <MapPos> Selection::possible_move_for_unit () const
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

Construction const& Selection::seeConstruction() const
{
    if (m_select_construction == NULL)
        erreur_message("Try to see Construction on non construction selection") ;
    return *m_select_construction ;
}

Construction* Selection::construction()
{
    return m_select_construction ;
}

Unit const& Selection::seeUnit() const
{
    if (m_select_unit == NULL)
        erreur_message("Try to see Unit on non unit selection") ;
    return *m_select_unit ;
}
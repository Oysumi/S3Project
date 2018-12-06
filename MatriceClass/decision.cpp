#include "decision.h"
using namespace std;

#include "../Fonctions/fonctions.h"
#include "../MatriceClass/decisionID.h"

std::vector<std::pair<std::string,bool>> Decision::list_of_choice ;

void Decision::init_list_of_choice()
{
	add_choice(    "QUITTER",             WITHOUT_POS   ) ;
	add_choice(    "TOUR_SUIVANT",        WITHOUT_POS   ) ;
	add_choice(    "CHANGE_SELECT_UNIT",  NEED_POS      ) ;
	add_choice(    "MOVE_SELECT_UNIT",    NEED_POS      ) ;
}

void Decision::add_choice(string name, bool choice_need_pos)
{
	list_of_choice.push_back(make_pair(name,choice_need_pos)) ;
}


Decision::Decision() : m_target(0,0)
{
	m_id_decision = -1 ;
	m_valid = false ;
}

bool Decision::set_decision (unsigned short const& id, MapPos* pos)
{
	if (id < list_of_choice.size())
	{

		if(!list_of_choice[m_id_decision].second) // Si cette décision n'a pas besoin d'être associée à une position
		{
			m_id_decision = (short) id ;
			m_valid = true ;
			return true ;
		}
		if (pos != NULL)
		{
			m_id_decision = (short) id ;
			set_target(*pos) ;
			m_valid = true ;
			return true ;
		}
		warning_message("Try to set decision need pos without") ;
		return false ;
	}
	return false ;
}

bool Decision::set_decision (unsigned short const& id)
{
	return set_decision (id,NULL) ;
}

bool Decision::set_target (MapPos const& pos)
{
	if(!is_valid())
		return false ;
	if(!list_of_choice[m_id_decision].second) // Si la décision ne nécessite pas de cible
		return false ;
	m_target = pos ;
	return true ;
}

bool Decision::is_valid() const
{
	return m_valid ;
}

unsigned short Decision::decision() const
{
	return m_id_decision ;
}

void Decision::afficher(ostream &flux) const
{
    flux << list_of_choice[m_id_decision].first ;
}

ostream &operator<<( ostream &flux, Decision const& dec)
{
    dec.afficher(flux) ;
    return flux ;
}
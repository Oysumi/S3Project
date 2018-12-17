#include "decision.h"
using namespace std;

#include "../Fonctions/fonctions.h"

std::vector< std::pair<std::string,std::pair<bool,bool>> > Decision::list_of_choice ;

#define NEED_POS            true
#define WITHOUT_POS         false

#define NEED_ID            true
#define WITHOUT_ID         false

void Decision::init_list_of_choice()
{
	add_choice(    "QUITTER",                WITHOUT_POS,   WITHOUT_ID) ;
	add_choice(    "TOUR_SUIVANT",           WITHOUT_POS,   WITHOUT_ID) ;
	add_choice(    "CHANGE_SELECT_UNIT",     NEED_POS,      WITHOUT_ID) ;
	add_choice(    "MOVE_SELECT_UNIT",       NEED_POS,      WITHOUT_ID) ;
	add_choice(    "CONSTRUIRE_UNIT",        NEED_POS,      NEED_ID   ) ;
	add_choice(    "CONSTRUIRE_BATIMENT",    NEED_POS,      NEED_ID   ) ;
	add_choice(    "AMELIORER_BATIMENT",     WITHOUT_POS,   NEED_ID   ) ;
	add_choice(    "AMELIORATION_UNIT",      WITHOUT_POS,   NEED_ID   ) ;
	add_choice(    "AMELIORATION_CONS",      WITHOUT_POS,   NEED_ID   ) ;
	add_choice(    "ENREGISTRER_PARTIE",     WITHOUT_POS,   WITHOUT_ID) ;
	add_choice(    "CAPTURE_ECRAN_PARTIE",   WITHOUT_POS,   WITHOUT_ID) ;
}

void Decision::add_choice(string name, bool choice_need_pos, bool choice_need_id)
{
	list_of_choice.push_back(make_pair(name,make_pair(choice_need_pos,choice_need_id))) ;
}


Decision::Decision() : m_target(0,0)
{
	m_decision = -1 ;
	m_valid = false ;
}

bool Decision::set_decision (unsigned short const& decision, MapPos* pos, int* id)
{
	m_valid = false ;

	if (decision >= list_of_choice.size())
		return false ;

	if(list_of_choice[decision].second.first && pos == NULL)
		return false ;

	if (list_of_choice[decision].second.second && id == NULL)
		return false ;

	//DANS CE CAS LA DECISION EST CORRECTE
	m_valid = true ;
	m_decision = (short) decision ;

	if(list_of_choice[decision].second.first)
		set_target(*pos) ;

	if (list_of_choice[decision].second.second)
		set_id(*id) ;

	return true ;
}

bool Decision::set_decision (unsigned short const& decision, MapPos* pos)
{
	return set_decision (decision,pos,NULL) ;
}

bool Decision::set_decision (unsigned short const& decision, int* id)
{
	return set_decision (decision,NULL,id) ;
}

bool Decision::set_decision (unsigned short const& decision)
{
	return set_decision (decision,NULL,NULL) ;
}



bool Decision::set_target (MapPos const& pos)
{
	if(!is_valid())
		return false ;
	if(!list_of_choice[m_decision].second.first) // Si la décision ne nécessite pas de cible
		return false ;
	m_target = pos ;
	return true ;
}

bool Decision::set_id (unsigned short id)
{
	if(!is_valid())
		return false ;
	if(!list_of_choice[m_decision].second.second) // Si la décision ne nécessite d'id
		return false ;
	m_id = id ;
	return true ;
}


bool Decision::is_valid() const
{
	return m_valid ;
}



unsigned short Decision::decision() const
{
	return m_decision ;
}

MapPos Decision::target () const
{
	return m_target ;
}

int Decision::id () const
{
	return m_id ;
}




void Decision::afficher(ostream &flux) const
{
	if (!m_valid)
		flux << "Invalid decision" ;
	else
	{
		flux << list_of_choice[m_decision].first ;
		if (list_of_choice[m_decision].second.first)
			flux << " with target " << m_target ;
		if (list_of_choice[m_decision].second.second)
			flux << " with id " << m_id ;
	}
}

ostream &operator<<( ostream &flux, Decision const& dec)
{
    dec.afficher(flux) ;
    return flux ;
}
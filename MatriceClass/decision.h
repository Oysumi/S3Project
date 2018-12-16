#ifndef __DECISION_H__
#define __DECISION_H__

#include <vector>
#include <string>

#include "../MapClass/position.h"



#define DECISION_QUITTER                 0
#define DECISION_TOUR_SUIVANT            1
#define DECISION_CHANGE_SELECT_UNIT      2
#define DECISION_MOVE_SELECT_UNIT        3
#define DECISION_CONSTRUIRE_UNIT         4
#define DECISION_CONSTRUIRE_BATIMENT     5
#define DECISION_AMELIORER_BATIMENT      6
#define DECISION_AMELIORATION            7

class Decision
{

	public :
		Decision() ;

		bool set_decision (unsigned short const& decision, MapPos* pos, int* id) ;
		bool set_decision (unsigned short const& decision, MapPos* pos) ;
		bool set_decision (unsigned short const& decision, int* id) ;
		bool set_decision (unsigned short const& decision) ;

		bool set_target (MapPos const& pos) ;
		bool set_id (unsigned short id) ;

		bool is_valid() const ;

		unsigned short decision() const ;
		MapPos target () const ;
		int id () const ;

		friend std::ostream &operator<<( std::ostream &flux, Decision const& dec);
		static void add_choice(std::string name, bool choice_need_pos, bool choice_need_id) ;
		static void init_list_of_choice() ;

		static std::vector< std::pair< std::string,std::pair<bool,bool> > > list_of_choice ;

	private :
		void afficher(std::ostream &flux) const;

	private :
		short m_decision ;
		unsigned short m_id ;
		MapPos m_target ;
		bool m_valid ;
	
};

std::ostream &operator<<( std::ostream &flux, Decision const& dec);

#endif // __HUMANPLAYER_H__
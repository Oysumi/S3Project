#ifndef __DECISION_H__
#define __DECISION_H__

#include <vector>
#include <string>

#include "../MapClass/position.h"

class Decision
{

	public :
		Decision() ;

		bool set_decision (unsigned short const& id, MapPos* pos) ;
		bool set_decision (unsigned short const& id) ;
		bool set_target (MapPos const& pos) ;
		bool is_valid() const ;
		unsigned short decision() const ;
		MapPos target () const ;

		friend std::ostream &operator<<( std::ostream &flux, Decision const& dec);
		static void add_choice(std::string name, bool choice_need_pos) ;
		static void init_list_of_choice() ;

		static std::vector<std::pair<std::string,bool>> list_of_choice ;

	private :
		void afficher(std::ostream &flux) const;

	private :
		short m_id_decision ;
		MapPos m_target ;
		bool m_valid ;
	
};

std::ostream &operator<<( std::ostream &flux, Decision const& dec);

#endif // __HUMANPLAYER_H__
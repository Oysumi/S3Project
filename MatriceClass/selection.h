#ifndef __SELECTION_H__
#define __SELECTION_H__

#include "../MapObject/mapobject.h"
#include "../MapObject/construction.h"
#include "../MapObject/Unit.h"

#include <vector>

class Map ;

class AbstractPlayer ;

// Représente la sélection d'un MapObject avec des méthodes spécifique aux unités
class Selection
{
	public:
		Selection(MapObject* selection, Map const& map, AbstractPlayer* current_player) ;
		Selection() ;
		~Selection() ;
		bool valid () const ;

		unsigned short type () const ;
		MapPos getPos () const ;
		MapObject* value() ; //Permet de modifier l'unité du pointeur donc méthode non constante
		AbstractPlayer* proprietaire_objet() ;
		//Si l'objet selectionné est une unité
		std::vector <MapPos> possible_to_move_unit () const ;
		bool possible_move_at (MapPos const& pos) const ;
		Unit const& see_select_unit() const ;
		Unit* unit() ;
		
	private :
		MapObject* m_selection ;
		std::vector <MapPos>* m_possible_to_move ;
		Unit* m_select_unit ;
		bool m_valid ;
};

#endif // __SELECTION_H__
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
		Selection(MapObject* selection) ;
		Selection() ;
		~Selection() ;

		//vérifier si cette selection est valable
		bool valid () const ;

		//méthodes constantes
		short type () const ;
		MapPos getPos () const ;
		std::string info () const ;
		MapObject const& see () const ;

		//A utiliser si l'objet selectionné est une unité
		Unit* unit() ;
		Unit const& seeUnit() const ;
		std::vector <MapPos> possible_move_for_unit () const ;
		bool possible_move_at (MapPos const& pos) const ;
		bool isObjectOf(AbstractPlayer*) const ;

		//A utiliser si l'objet selectionné est une construction
		Construction* construction() ;
		Construction const& seeConstruction() const ;
		
		//Méthodes pour la matrice
		MapObject* value() ; //Permet de modifier l'unité du pointeur donc méthode non constante
		AbstractPlayer* proprietaire_objet() ;
		bool add_possible_move_for_select_unit(MapPos const& pos) ;
		
	private :
		MapObject* m_selection ;
		std::vector <MapPos>* m_possible_to_move ;
		Unit* m_select_unit ;
		Construction* m_select_construction ;
		bool m_valid ;
};

#endif // __SELECTION_H__
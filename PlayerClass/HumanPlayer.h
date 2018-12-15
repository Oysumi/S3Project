#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include <string>
#include "../DisplayClass/Texte.h"
#include "AbstractPlayer.h"

class HumanPlayer : public AbstractPlayer
{
	public :
		HumanPlayer(std::string name, unsigned short color_id) ;
		virtual ~HumanPlayer() ;

		//Utilisée par la matrice pour demander au joueur de prendre une décision, seul interraction d'un joueur
		virtual Decision takeDecision(
			Map const& map, //Ici la Map est une référence constante, ainsi le joueur est en lecture seule, il doit passer par la matrice pour tout changement
			Selection const& selection, // Permet au joueur d'avoir des infos sur l'unité séléctionée, sans changer la sélécion directement pour autant
			Ressource const& ressource, //Permet au joueur de connaître ses ressources pour prendre ses décisions (sans les modifier)
			Fenetre& fenetre //Passage par référence, une seule et même fenêtre dont le joueur peut changer le contenu pendant son tour
			) ;

	private :
		void updateDisplay(Map const& map, Selection const& selection, Fenetre& fenetre) ;
		void setConstructionCursor(Map const& map, Selection const& selection, Fenetre& fenetre, unsigned short x, unsigned short y) ;
		void delConstructionCursor(Map const& map) ;
		void deleteTexte() ;

	private :
		bool m_gauche_ecran, m_droite_ecran, m_bas_ecran, m_haut_ecran ;
		int m_temps_precedent ;
		
		int m_type_unit ;
		int m_type_construction ;
		MapPos* m_pos_construction ;

		SDL_Rect m_scroll ; //Représente le rectangle de la map affichée sur la fenêtre
		Texte* m_quantite_gold ;
		Texte* m_quantite_wood ;
		Texte* m_quantite_food ;
		Texte* m_select_info ;
		std::map <std::string, SurfaceAffichage*> m_all_symbol ;
};

#endif // __HUMANPLAYER_H__
#ifndef __MATRICEGAMEGESTION_H__
#define __MATRICEGAMEGESTION_H__

#include "../Fonctions/fonctions.h"
#include "../Fonctions/remplissage.h"

#include "../DisplayClass/fenetre.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/Menu.h"

#include "../PlayerClass/AbstractPlayer.h"
#include "../MapObject/construction.h"
#include "../MapClass/map.h"
#include "../MatriceClass/selection.h"

#include <vector>

class MatriceGameGestion
{
	public:
		MatriceGameGestion();
		~MatriceGameGestion();

		void init() ;
		void gameLoop() ;

	private :	
		Fenetre m_fenetre ;
		std::vector <Menu*> m_saveMenu ;
		std::vector <AbstractButton*> * m_all_buttons ;

		Map* m_map ; //Contient la plupart des données du jeu
		SDL_Rect m_scroll ; //Représente le rectangle de la map affichée sur la fenêtre
		
	/* 	Liste des joueurs dont le seul rôle est de prendre des décisions que la Matrice
		de Gestion du jeu interprète. En fonction de ces décisions celle-ci modifie les
		données de la Map que le joueur ne peut pas modifier directement mais seulement lire */
		std::vector <AbstractPlayer*> * m_player_list ;
		std::map <AbstractPlayer*, unsigned short> m_player_gold ;
		AbstractPlayer* m_current_player_turn ;
		unsigned short m_tour ;
		bool m_fin_de_la_partie ;

		Selection* m_current_selection ;

	private :
		bool new_selection(MapPos const pos, bool force_unit = false) ;
		void selection_unit() ;
		void verification_defaite() ;
		//void defeatPlayer() ;
		//void winPlayer() ;

		void updateDisplay() ;
		void deleteSelection() ;
		bool validSelection(short type = -1) const ;
		void addPlayer(std::string name) ;
		void initNewTurn(AbstractPlayer* new_current_player) ;
};

#endif // __MATRICEGAMEGESTION_H__
#ifndef __ARTIFICIALPLAYER_H__
#define __ARTIFICIALPLAYER_H__

#include "AbstractPlayer.h"

class ArtificialPlayer : AbstractPlayer 
{
	public:
		
		//Utilisée par la matrice pour demander au joueur de prendre une décision, seul interraction d'un joueur
		virtual Decision takeDecision(
			Map const& map, //Ici la Map est une référence constante, ainsi le joueur est en lecture seule, il doit passer par la matrice pour tout changement
			Selection const& selection, // Permet au joueur d'avoir des infos sur l'unité séléctionée, sans changer la sélécion
			Fenetre& fenetre //Passage par référence, une seule et même fenêtre dont le joueur peut changer le contenu pendant son tour
			) ;
};

#endif // __ARTIFICIALPLAYER_H__
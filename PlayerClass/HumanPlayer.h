#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include <string>
#include "AbstractPlayer.h"

class HumanPlayer : public AbstractPlayer
{
	public :
		HumanPlayer(std::string name, unsigned short color_id) ;
		virtual ~HumanPlayer() ;

		//Utilisée par la matrice pour demander au joueur de prendre une décision, seul interraction d'un joueur
		virtual Decision takeDecision(
			Map const& map, //Ici la Map est une référence constante, ainsi le joueur est en lecture seule, il doit passer par la matrice pour tout changement
			Selection const& selection, // Permet au joueur d'avoir des infos sur l'unité séléctionée, sans changer la sélécion
			Fenetre& fenetre, //Passage par référence, une seule et même fenêtre dont le joueur peut changer le contenu pendant son tour
			SDL_Rect& scroll //Permet juste à la matrice de savoir où regarde le joueur
			) ;

};

#endif // __HUMANPLAYER_H__
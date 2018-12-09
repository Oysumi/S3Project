#ifndef __HUMANPLAYER_H__
#define __HUMANPLAYER_H__

#include <string>

#include "AbstractPlayer.h"
#include "SDL/SDL.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/map.h"

class HumanPlayer : public AbstractPlayer
{
	public :
		HumanPlayer(std::string name, unsigned short color_id) ;
		virtual ~HumanPlayer() ;

		//Fonction utilisée par la matrice pour demander au joueur de prendre une décision, seul interraction d'un joueur
		virtual Decision takeDecision(
			Fenetre& fenetre, //Passage par référence, une seule et même fenêtre dont le joueur peut changer le contenu pendant son tour
			Map const& map, //Ici la Map est une référence constante, ainsi le joueur est en lecture seule, il doit passer par la matrice pour tout changement
			SDL_Rect& scroll //Permet juste à la matrice de savoir où regarde le joueur
		) ;

};

#endif // __HUMANPLAYER_H__
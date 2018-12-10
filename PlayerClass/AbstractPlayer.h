#ifndef __ABSTRACTPLAYER_H__
#define __ABSTRACTPLAYER_H__

#include "../DisplayClass/fenetre.h"
#include "../MatriceClass/selection.h"
#include "../MapClass/map.h"
#include "../MatriceClass/decision.h"

class AbstractPlayer
{
	public :
		AbstractPlayer(std::string name, unsigned short color_id) ;
		virtual ~AbstractPlayer() ;
		unsigned short colorId() const ;
		std::string name () const ;
		
		//Méthode virtuelle pure utilisée par la matrice pour demander au joueur de prendre une décision, seul interraction d'un joueur
		virtual Decision takeDecision(
			Map const& map, //Ici la Map est une référence constante, ainsi le joueur est en lecture seule, il doit passer par la matrice pour tout changement
			Selection const& selection, // Permet au joueur d'avoir des infos sur l'unité séléctionée, sans changer la sélécion
			Fenetre& fenetre, //Passage par référence, une seule et même fenêtre dont le joueur peut changer le contenu pendant son tour
			SDL_Rect& scroll //Permet juste à la matrice de savoir où regarde le joueur
		) = 0 ;
		
	protected :
		std::string m_name ;
		unsigned short m_color_id ;
};

#endif // __ABSTRACTPLAYER_H__
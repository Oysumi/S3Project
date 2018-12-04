#include "remplissage.h"
#include "../ID/idbuttons.h"
#include "iostream"

using namespace std ;

void remplissage(vector<AbstractButton*>* bouton)
{

	SDL_Color font = {255,255,255};
	SDL_Color text = {0,0,0};

	bouton->push_back(new ActionButton(RETOUR, "RETOUR", 200, 100, 110, 110, font, text)) ;
    bouton->push_back(new ActionButton(MUSIQUE, "MUSIQUE", 200, 100, 110, 110, font, text)) ;
    bouton->push_back(new ActionButton(QUITTER, "QUITTER", 200, 100, 110, 110, font, text)) ;
    bouton->push_back(new ActionButton(ATTAQUER, "ATATQUER", 200, 100, 110, 110, font, text)) ;
    bouton->push_back(new ActionButton(DEFENDRE, "DEFENDRE", 200, 100, 110, 110, font, text)) ;
    bouton->push_back(new ActionButton(ALLER_A, "ALLER_A", 200, 100, 110, 110, font, text)) ;
    bouton->push_back(new ActionButton(FERMER, "FERMER", 200, 100, 110, 110, font, text)) ;

}
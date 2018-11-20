#ifndef __TEXTE_H__
#define __TEXTE_H__

#include "../DisplayClass/fenetre.h"
#include "../MenuClass/AbstractButton.h"
#include <string>
#include <SDL/SDL_ttf.h>

class Texte{

	public:
		Texte(const char * textToWrite) ;
		int width() ;
		int height() ;
		SurfaceAffichage surfaceAffichage() ;
		void displayText(Fenetre screen, AbstractButton * b) ;
		~Texte() ;

	private:
		TTF_Font* m_font ;
		SDL_Surface* m_text ;
};

#endif // __TEXTE_H__
#ifndef __TEXTE_H__
#define __TEXTE_H__

#include "../DisplayClass/fenetre.h"
#include "../MenuClass/AbstractButton.h"
#include <string>
#include <SDL/SDL_ttf.h>

class Texte{

	public:
		Texte(const char * textToWrite, SDL_Color font_color = {0, 0, 0}, int size = 30) ;
		Texte(std::string textToWrite, SDL_Color font_color = {0, 0, 0}, int size = 30) ;
		int width() ;
		int height() ;
		SurfaceAffichage surfaceAffichage() ;
		void displayText(Fenetre screen, AbstractButton * b) ;
		~Texte() ;

	private:
		TTF_Font* m_font ;
		SDL_Surface* m_text ;
    int m_size ;
};

#endif // __TEXTE_H__
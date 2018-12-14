#ifndef __TEXTE_H__
#define __TEXTE_H__

#include "../DisplayClass/fenetre.h"
#include <string>
#include <SDL/SDL_ttf.h>

class AbstractButton ;

class Texte
{

	public:
		Texte() ;
		Texte(std::string textToWrite, SDL_Color font_color = {0, 0, 0}, int size = 30, std::string font = "montserrat-regular") ;
		void changeText (std::string textToWrite, SDL_Color font_color = {0, 0, 0}, int size = 30) ;
		void addTexture (SurfaceAffichage const& surface, unsigned short x, unsigned short y) ;
		int width() const ;
		int height() const ;
		SurfaceAffichage const& surfaceAffichage() const ;
		void displayText(SurfaceAffichage& surf, AbstractButton const& b, unsigned short pos_font) const;
		~Texte() ;

	private :
		void freeSurface() ;

	private:
		TTF_Font* m_font ;
		SDL_Surface* m_text ;
		SurfaceAffichage* m_surface ;
    int m_size ;
};

#endif // __TEXTE_H__
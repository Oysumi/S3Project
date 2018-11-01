#ifndef __ABSTRACTBUTTON_H__
#define __ABSTRACTBUTTON_H__

#include <string>
#include <SDL/SDL.h>
#include "../DisplayClass/fenetre.h"

// We put the constructor in protected so that we can't instanciate this class in the main code, making it a sort of abstract class

class AbstractButton
{
	protected:
		unsigned int m_size ;
		unsigned int m_posx ;
		unsigned int m_posy ;
		std::string m_text ;
		SDL_Color m_back_color ;
		SDL_Color m_text_color ;

	public:
		unsigned int getPosX() ;
		unsigned int getPosY() ;
		unsigned int getSize() ;
		void setPosX(unsigned int x) ;
		void setPosY(unsigned int y) ;
		void displayButton(Fenetre screen) ;
		SurfaceAffichage getSurface() ;
		SDL_Color getBackColor() ;

		// à définir méthode virtuelle qui renvoit la surface d'affichage du bouton
};

#endif // __ABSTRACTBUTTON_H__
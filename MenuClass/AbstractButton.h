#ifndef __ABSTRACTBUTTON_H__
#define __ABSTRACTBUTTON_H__

#include <string>
#include <SDL/SDL.h>
#include "../DisplayClass/fenetre.h"

// We put the constructor in protected so that we can't instanciate this class in the main code, making it a sort of abstract class

class AbstractButton
{
	protected:
		unsigned int m_width ;
		unsigned int m_height ;
		unsigned int m_posx ;
		unsigned int m_posy ;
		int m_id ;
		const char * m_text ;
		SDL_Color m_back_color ;
		SDL_Color m_text_color ;
		
	public:
		unsigned int getPosX() const ;
		unsigned int getPosY() const ;
		unsigned int getWidth() const ;
		unsigned int getHeight() const ;
		int getID() const ;
		void setPosX(unsigned int x) ;
		void setPosY(unsigned int y) ;
		virtual void displayButton(Fenetre screen) = 0 ;
		virtual SurfaceAffichage getSurfaceAffichage() = 0 ;
		SDL_Color getBackColor() const ;
		const char * getText() const ;
		virtual ~AbstractButton() ;

		// à définir méthode virtuelle qui renvoit la surface d'affichage du bouton
};

#endif // __ABSTRACTBUTTON_H__
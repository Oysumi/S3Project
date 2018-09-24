#ifndef __ABSTRACTBUTTON_H__
#define __ABSTRACTBUTTON_H__

#include <string>
#include <SDL/SDL.h>

// We put the constructor in protected so that we can't instanciate this class in the main code, making it a sort of abstract class

class AbstractButton
{
	protected:
		AbstractButton() ;
		unsigned short int m_size ;
		unsigned short int m_posx ;
		unsigned short int m_posy ;
		std::string m_text ;
		SDL_Color m_back_color ;
		SDL_Color m_text_color ;
};

#endif // __ABSTRACTBUTTON_H__
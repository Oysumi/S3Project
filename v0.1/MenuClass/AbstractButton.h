#ifndef __ABSTRACTBUTTON_H__
#define __ABSTRACTBUTTON_H__
#include <string>
#include <SDL/SDL.h>

class AbstractButton
{
	protected :
		unsigned short int m_size ;
		unsigned short int m_posx ;
		unsigned short int m_posy ;
		std::string m_text ; // will be displayed on the menu (we'll need probably more of these string fields)
		SDL_Color m_back_color ; // color of the background
		SDL_Color m_text_color ; // color of the text
};

#endif // __ABSTRACTBUTTON_H__
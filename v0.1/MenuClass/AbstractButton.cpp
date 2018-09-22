#include "AbstractButton.h"

using namespace std ;

AbstractButton::AbstractButton() : m_size(0), m_posx(0), m_posy(0), m_text("Menu"), m_back_color({255,255,255}), m_text_color({0,0,0}) 
{ }

AbstractButton::AbstractButton(unsigned short int size, unsigned short int pos_x, unsigned short int pos_y, std::string text, SDL_Color background, SDL_Color textColor)
{
	// According to the lack of space, we'll assignate the values directly in the body of the constructor
	// rather than initialise them by the list enumeration (just like above this constructor)
	m_size = size ;
	m_posx = pos_x ;
	m_posy = pos_y ;
	m_text = text ;
	m_back_color = background ;
	m_text_color = textColor ;
}
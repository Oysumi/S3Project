#ifndef __ACTIONBUTTON_H__
#define __ACTIONBUTTON_H__

#include "AbstractButton.h"
#include <string>

class ActionButton : public AbstractButton
{ 
	public:
		// Constructors
		ActionButton() ; 
		ActionButton(unsigned short int idToSet) ;
		ActionButton(unsigned short int idToSet, std::string textToWrite, unsigned short int size, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text) ;

		// Getters
		unsigned short int getId() const ;
		std::string getText() const ; // get the text which represents what is written in the button
		unsigned short int getSize() const ;
		unsigned short int getPosX() const ;
		unsigned short int getPosY() const ;
		SDL_Color getBackgroundColor() const ;
		SDL_Color getTextColor() const ;
		
		~ActionButton() ;

	protected:
		unsigned short int m_id ;
		std::string m_text ;

		// Setters
		void setId(unsigned short int idToSet) ;
		void setSize(unsigned short int size) ;
		void setPos(unsigned short int pos_x, unsigned short int pos_y) ;
		void setTextColor(SDL_Color text) ;
		void setBackgroundColor(SDL_Color back) ;
		void setButtonColors(SDL_Color background, SDL_Color text) ; // set the text and background color at the same time
		void setButton(unsigned short int idToSet, unsigned short int size, unsigned short int pos_x, unsigned short int pos_y, SDL_Color text, SDL_Color back) ;
};

#endif // __ACTIONBUTTON_H__
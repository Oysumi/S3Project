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
		ActionButton(std::string idToSet) ;
		ActionButton(unsigned short int idToSet, unsigned short int size, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text) ;
		ActionButton(std::string idToSet, unsigned short int size, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text) ;

		// Setters
		void setId(unsigned short int idToSet) ;
		void setId(std::string idToSet) ;
		void setSize(unsigned short int size) ;
		void setPos(unsigned short int pos_x, unsigned short int pos_y) ;
		void setTextColor(SDL_Color text) ;
		void setBackgroundColor(SDL_Color back) ;
		void setButtonColors(SDL_Color background, SDL_Color text) ; // set the text and background color at the same time

		// Getters
		// We have to decide which one we choose between the string one and the integer one
		unsigned short int getId() const ;
		//std::string getId() const ;
		std::string getText() const ; // get the text which represents what is written in the button
		unsigned short int getSize() const ;
		unsigned short int getPosX() const ;
		unsigned short int getPosY() const ;
		SDL_Color getBackgroundColor() const ;
		SDL_Color getTextColor() const ;
		
		~ActionButton() ;

	protected:
		// we're going to choose which one is the better between these two options (int vs string)
		unsigned short int m_id_f ; // 1)
		std::string m_id_s ; // 2)
};

#endif // __ACTIONBUTTON_H__
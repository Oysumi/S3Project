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
		ActionButton(unsigned short int idToSet, const char * textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text, int size_text = 30) ;
		ActionButton(unsigned short int idToSet, std::string textToWrite, unsigned short int width, unsigned short int height, unsigned short int pos_x, unsigned short int pos_y, SDL_Color back, SDL_Color text, int size_text = 30) ;
		~ActionButton() ;

		// Actions
		virtual SurfaceAffichage getSurfaceAffichage() ;
		virtual void displayButton(Fenetre screen) ; 

	protected:
		// Setters non publics
		void setId(unsigned short int idToSet) ;
		void setSize(unsigned short int width, unsigned short int height) ;
		void setPos(unsigned short int pos_x, unsigned short int pos_y) ;
		void setTextColor(SDL_Color text) ;
		void setBackgroundColor(SDL_Color back) ;
		void setButtonColors(SDL_Color background, SDL_Color text) ; // set the text and background color at the same time
};

#endif // __ACTIONBUTTON_H__
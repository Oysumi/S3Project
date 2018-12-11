#ifndef __ACTIONBUTTON_H__
#define __ACTIONBUTTON_H__

#include "AbstractButton.h"
#include "../DisplayClass/Texte.h"
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
		virtual SurfaceAffichage const& getSurfaceAffichage() const ;
		virtual Texte const& getTexte() const ;
		virtual void displayButton(Fenetre& screen) const ;

		virtual void setText(std::string text) ;

	protected:
		// Setters non publics
		void setId(unsigned short int idToSet) ;
		void setSize(unsigned short int width, unsigned short int height) ;
		void setPos(unsigned short int pos_x, unsigned short int pos_y) ;
		void setTextColor(SDL_Color const& text) ;
		void setBackgroundColor(SDL_Color const& back) ;
		void setButtonColors(SDL_Color const& background, SDL_Color const& text) ; // set the text and background color at the same time
		void freeSurface() ;

	private :
		SurfaceAffichage* m_surface ;
		Texte* m_texte ;
};

#endif // __ACTIONBUTTON_H__
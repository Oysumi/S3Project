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
		
		ActionButton(unsigned short int idToSet,
					std::string textToWrite,
					unsigned short int width,
					unsigned short int height,
					SDL_Color back, SDL_Color text,
					int size_text = 30,
					unsigned short pos_text_auto = LEFT_TEXT,
					std::string font = "montserrat-regular") ;
		
		~ActionButton() ;

		// Actions
		virtual SurfaceAffichage const& getSurfaceAffichage() const ;
		virtual Texte const& getTexte() const ;

		virtual void setText(std::string text, std::string font = "") ;
		virtual void setColor(SDL_Color* background, SDL_Color* text = NULL) ;
		virtual void addTexture (SurfaceAffichage const& surface, unsigned short x, unsigned short y) ;

	protected:
		// Setters non publics
		void setId(unsigned short int idToSet) ;
		void setSize(unsigned short int width, unsigned short int height) ;
		void setTextColor(SDL_Color const& text) ;
		void setBackgroundColor(SDL_Color const& back) ;
		void setButtonColors(SDL_Color const& background, SDL_Color const& text) ; // set the text and background color at the same time
		void freeSurface() ;
		void prepareSurface() ;

	protected :
		SurfaceAffichage* m_surface ;
		Texte* m_texte ;
		unsigned short m_pos_text ;
		std::string m_font ;
};

#endif // __ACTIONBUTTON_H__
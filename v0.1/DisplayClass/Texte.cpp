#include "Texte.h"

using namespace std ;

#define TYPEFACE 30
#define SHIFT_X 10

Texte::Texte(string textToWrite){
	/* Loading of the font */
	m_font = TTF_OpenFont ("", TYPEFACE) ;

	/* Defining the color of the text (here black) */
	SDL_Color font_color = {0, 0, 0} ;

	/* Writting the text in the SDL_Surface */
	const char * text = textToWrite.c_str();
	m_text = TTF_RenderText_Blended(m_font,text, font_color);
}

Texte::~Texte(){
	TTF_CloseFont(m_font) ;
	SDL_FreeSurface(m_text) ;
}

/***************************************************************************************/

int Texte::width(){
	return m_text->w ;
}

int Texte::height(){
	return m_text->h ;
}

SurfaceAffichage Texte::surfaceAffichage(){

	SurfaceAffichage surface(this->width(), this->height(), false) ;
	SDL_Surface* temp = surface.surface() ;
	temp = m_font ;
	return surface ;
}

void Texte::displayText(Fenetre screen, AbstractButton b){

	int pos_x = b.getPosX() + SHIFT_X ;
	int pos_y = b.getPosY() + b.getHeight()/2 ;

	SurfaceAffichage surface = this->surfaceAffichage() ;
	SDL_Color col = {0, 0, 0} ;

	screen.ajouter(surface, pos_x, pos_y, col) ;
}
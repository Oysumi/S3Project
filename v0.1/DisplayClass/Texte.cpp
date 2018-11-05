#include "Texte.h"

using namespace std ;

#define TYPEFACE 30
#define SHIFT_X 25

Texte::Texte(const char * textToWrite){
	/* Loading of the font */
	m_font = TTF_OpenFont ("../font/04B_30__.TTF", TYPEFACE) ;
	if(!m_font) {
    	cout << TTF_GetError() << endl ;
    	exit(3) ;
	}

	/* Defining the color of the text (here black) */
	SDL_Color font_color = {0, 0, 0} ;

	/* Writting the text in the SDL_Surface */
	m_text = TTF_RenderText_Blended(m_font,textToWrite,font_color);
}

Texte::~Texte(){
	TTF_CloseFont(m_font) ;
}

/***************************************************************************************/

int Texte::width(){
	return m_text->w ;
}

int Texte::height(){
	return m_text->h ;
}

SurfaceAffichage Texte::surfaceAffichage(){

	SurfaceAffichage surface(this->width(), this->height(), this->m_text) ;
	return surface ;
}

void Texte::displayText(Fenetre screen, AbstractButton b){

	int pos_x = b.getPosX() + SHIFT_X ;
	int pos_y = b.getPosY() + b.getHeight()/2 ;

	SurfaceAffichage surface = this->surfaceAffichage() ;

	screen.ajouter(surface, pos_x, pos_y) ;
}
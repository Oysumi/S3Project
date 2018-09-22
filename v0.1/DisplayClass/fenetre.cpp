#include "fenetre.h"
bool Fenetre::instantiated = false ;


//CONSTRUCTEUR
Fenetre::Fenetre(std::string const& title, unsigned short const& width, unsigned short const& height, Uint32 flags)
{
	if (width >= SIZE_MIN)
		m_width = width ;
	else
	{
		m_width = SIZE_MIN ;
		warning("Largeur fenêtre minimale non repspéctée") ;
	} 

	if (height >= SIZE_MIN)
		m_height = height ;
	else
	{
		m_height = SIZE_MIN ;
		warning("Hauteur fenêtre minimale non repspéctée") ;
	}

	if (instantiated)
	{
		erreur("La SDL ne peut gérer qu'une fenêtre") ;
		m_screen = NULL ;
	}
	else
	{
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
	        erreur(SDL_GetError()) ;
	    
	    SDL_WM_SetCaption(title.c_str(), NULL) ;
	    
	    m_screen = SDL_SetVideoMode(m_width, m_height, 32, flags);
	    if (m_screen == NULL)
	        erreur(SDL_GetError()) ;
	}
	instantiated = true ;
}

//DESTRUCTEUR
Fenetre::~Fenetre()
{ 
	SDL_Quit() ;
	instantiated = false ;
}


//ACCESSEUR
SDL_Surface * Fenetre::screen() const
{
	return m_screen ;
}


// PERMET DE METTRE LA SURFACE DE LA FENETRE A JOUR
void Fenetre::actualiser()
{
	SDL_Flip(m_screen) ;
}
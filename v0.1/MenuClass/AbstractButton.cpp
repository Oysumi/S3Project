#include "AbstractButton.h"

using namespace std ;

unsigned int AbstractButton::getPosX()
{
	return this->m_posx ;
}

unsigned int AbstractButton::getPosY()
{
	return this->m_posy ;
}

unsigned int AbstractButton::getSize()
{
	return this->m_size ;
}

void AbstractButton::setPosX(unsigned int x)
{
	m_posx = x ;
}

void AbstractButton::setPosY(unsigned int y)
{
	m_posy = y ;
}

SurfaceAffichage AbstractButton::getSurface()
{
	SurfaceAffichage surface(m_size, m_size) ;

	return surface ;
}

SDL_Color AbstractButton::getBackColor()
{
	return this->m_back_color ;
}

void AbstractButton::displayButton(Fenetre screen)
{
	SurfaceAffichage button = this->getSurface() ;
	SDL_Surface* surface = button.surface() ;
	SDL_Rect* srcect = NULL ;
	SDL_Rect* pos = (SDL_Rect*)malloc(sizeof(SDL_Rect)) ;
	pos->x = this->getPosX() ;
	pos->y = this->getPosY() ;
	SDL_Color couleur = this->getBackColor() ;

	if(SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, couleur.r, couleur.g, couleur.b)) != 0)
		erreur_message("Impossible de créer une surface pour afficher le menu :  " + string(SDL_GetError())) ;
	if(SDL_BlitSurface(surface, srcect, screen.surface(), pos))
        erreur_message("Impossible d'afficher le menu sur l'écran :  " + string(SDL_GetError())) ;

    free(pos) ;
}
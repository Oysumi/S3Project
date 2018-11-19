#include "AbstractButton.h"

using namespace std ;

unsigned int AbstractButton::getPosX() const
{
	return this->m_posx ;
}

unsigned int AbstractButton::getPosY() const
{
	return this->m_posy ;
}

unsigned int AbstractButton::getWidth() const
{
	return this->m_width ;
}

unsigned int AbstractButton::getHeight() const
{
	return this->m_height ;
}

int AbstractButton::getID() const
{
	return this->m_id ;
}

void AbstractButton::setPosX(unsigned int x)
{
	m_posx = x ;
}

void AbstractButton::setPosY(unsigned int y)
{
	m_posy = y ;
}

SurfaceAffichage AbstractButton::getSurfaceAffichage() const
{
	SurfaceAffichage surface(m_width, m_height) ;

	return surface ;
}

SDL_Color AbstractButton::getBackColor() const
{
	return this->m_back_color ;
}

void AbstractButton::displayButton(Fenetre screen) const
{
	SurfaceAffichage button = this->getSurfaceAffichage() ;
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

const char * AbstractButton::getText() const
{
	return m_text ;
}
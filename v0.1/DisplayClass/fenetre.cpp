#include "fenetre.h"
using namespace std;

bool Fenetre::instantiated = false ;

//CONSTRUCTEUR
SurfaceAffichage::SurfaceAffichage(unsigned short const& width, unsigned short const& height)
{
	m_height = height ;
	m_width = width ;
	m_surface = SDL_CreateRGBSurface(SDL_HWSURFACE, m_width, m_height, 32, 0, 0, 0, 0);
}

//DESTRUCTEUR
SurfaceAffichage::~SurfaceAffichage()
{
	delete m_surface ;
}

//ACCESSEURS
unsigned short SurfaceAffichage::width() const 
{
	return m_width ;
}
unsigned short SurfaceAffichage::height() const
{
	return m_height ;
}



// AJOUT SURFACE D'AFFICHAGE SUR UNE SURFACE D'AFFICHAGE
void SurfaceAffichage::ajouter (SurfaceAffichage const& s, SDL_Rect* pos)
{
	if(SDL_BlitSurface(s.m_surface, NULL, m_surface, pos))
        erreur_message("L'ajout d'une SurfaceAffichage dans une autre à échoué :  " + string(SDL_GetError())) ;
}
void SurfaceAffichage::ajouter (SurfaceAffichage const& s, unsigned short const& posx, unsigned int short const& posy)
{
	SDL_Rect pos ;
    pos.x = posx ;
    pos.y = posy ;
    ajouter (s, &pos) ;
}
void SurfaceAffichage::ajouter (SurfaceAffichage const& s)
{
	ajouter (s, NULL) ;
}



// AJOUTE LA TEXTURE SUR LA SURFACE D'AFFICHAGE
void SurfaceAffichage::ajouter (Texture const& t, SDL_Rect* pos)
{
    if(SDL_BlitSurface(t.surface(), NULL, m_surface, pos))
        erreur_message("Impossible d'ajouter la texture " + t.path() + " à la SurfaceAffichage : " + string(SDL_GetError())) ;
}

void SurfaceAffichage::ajouter (Texture const& t, unsigned short const& posx, unsigned int short const& posy)
{
    SDL_Rect pos ;
    pos.x = posx ;
    pos.y = posy ;
    ajouter (t, &pos) ;
}

void SurfaceAffichage::ajouter (Texture const& t)
{
    ajouter (t, NULL) ;
}



//AJOUT D'UN SPRITE SUR LA SURFACE D'AFFICHAGE
void SurfaceAffichage::ajouter (SpriteTexture const& s, SDL_Rect* pos, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur)
{
    if(SDL_BlitSurface(s.surface(), new SDL_Rect(s.getRect(numero_sprite_longueur,numero_sprite_largeur)), m_surface, pos))
        erreur_message("Impossible d'ajouter le sprite" + s.path() + " à la SurfaceAffichage : " + string(SDL_GetError())) ;
}

void SurfaceAffichage::ajouter (SpriteTexture const& s, unsigned short const& posx, unsigned int short const& posy, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur)
{
    SDL_Rect pos ;
    pos.x = posx ;
    pos.y = posy ;
    ajouter (s, &pos, numero_sprite_longueur, numero_sprite_largeur) ;
}

void SurfaceAffichage::ajouter (SpriteTexture const& s, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur)
{
    SDL_Rect* p = NULL ;
    ajouter (s, p, numero_sprite_longueur, numero_sprite_largeur) ;
}



bool SurfaceAffichage::saveBMP(std::string const& name) const
{
	return (SDL_SaveBMP(m_surface, name.c_str()) == 0) ;
}





//CONSTRUCTEUR
Fenetre::Fenetre(std::string const& title, unsigned short const& width, unsigned short const& height, Uint32 flags) : SurfaceAffichage(width,height)
{
	if (width >= SIZE_MIN)
		m_width = width ;
	else
	{
		m_width = SIZE_MIN ;
		warning_message("Largeur fenêtre minimale non repspéctée") ;
	} 

	if (height >= SIZE_MIN)
		m_height = height ;
	else
	{
		m_height = SIZE_MIN ;
		warning_message("Hauteur fenêtre minimale non repspéctée") ;
	}

	if (instantiated)
	{
		erreur_message("La SDL ne peut gérer qu'une fenêtre") ;
		m_surface = NULL ;
	}
	else
	{
		if (SDL_Init(SDL_INIT_VIDEO) == -1)
	        erreur_message("Impssible d'initialiser la SDL pour la fenetre " + title + " : " + SDL_GetError()) ;
	    
	    SDL_WM_SetCaption(title.c_str(), NULL) ;
	    
	    m_surface = SDL_SetVideoMode(m_width, m_height, 32, flags);
	    if (m_surface == NULL)
	        erreur_message("Impssible de créer la fenetre " + title + " : " + SDL_GetError()) ;
	}
	instantiated = true ;
}

//DESTRUCTEUR
Fenetre::~Fenetre()
{ 
	SDL_Quit() ;
	instantiated = false ;
}


// PERMET DE METTRE LA SURFACE DE LA FENETRE A JOUR
void Fenetre::actualiser()
{
	SDL_Flip(m_surface) ;
}
#include "fenetre.h"
using namespace std;


SurfaceAffichage* SurfaceAffichage::fenetre = NULL ;

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
	cout << "Destruction surface affichage" << endl ;
	if(m_surface!=NULL){
		SDL_FreeSurface(m_surface);
		m_surface = NULL;
	}
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
SDL_Surface* SurfaceAffichage::surface() const
{
	return m_surface ;
}

//sauvegarder l'image
bool SurfaceAffichage::saveBMP(std::string const& name) const
{
	return (SDL_SaveBMP(m_surface, name.c_str()) == 0) ;
}



//CONSTRUCTEUR FENETRE
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

	if (fenetre == NULL)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
	        erreur_message("Impssible d'initialiser la SDL pour la fenetre " + title + " : " + SDL_GetError()) ;
	    
	    SDL_WM_SetCaption(title.c_str(), NULL) ;
	    
	    m_surface = SDL_SetVideoMode(m_width, m_height, 32, flags);

	    if (m_surface == NULL)
	        erreur_message("Impssible de créer la fenetre " + title + " : " + SDL_GetError()) ;
	    fenetre = this ;
	}
	else
	{
		m_surface = NULL ;
		erreur_message("La SDL ne peut gérer qu'une fenêtre") ;
	}
}
//DESTRUCTEUR
Fenetre::~Fenetre()
{
	if (fenetre!=NULL){
		fenetre = NULL ;
	}
	cout << "Destruction fenetre" << endl ;
}

// PERMET DE METTRE LA SURFACE DE LA FENETRE A JOUR
void Fenetre::actualiser()
{
	SDL_Flip(m_surface) ;
}


// ------------------- GESTION DE L'AFFICHAGE -------------------


// AJOUTE LA TEXTURE SUR LA SURFACE D'AFFICHAGE
void SurfaceAffichage::ajouter (Texture const& t, SDL_Rect* srcect, SDL_Rect* pos)
{
    if(SDL_BlitSurface(t.surface(), srcect, m_surface, pos))
        erreur_message("Impossible d'ajouter la texture " + t.path() + " à la SurfaceAffichage : " + string(SDL_GetError())) ;
}
void SurfaceAffichage::ajouter (Texture const& t, SDL_Rect* srcect, unsigned short const& posx, unsigned int short const& posy)
{
    SDL_Rect pos ;
    pos.x = posx ;
    pos.y = posy ;
    ajouter (t, srcect, &pos) ;
}
void SurfaceAffichage::ajouter (Texture const& t, unsigned short const& posx, unsigned int short const& posy)
{
    SDL_Rect pos ;
    pos.x = posx ;
    pos.y = posy ;
    ajouter (t, NULL, &pos) ;
}
void SurfaceAffichage::ajouter (Texture const& t)
{
	SDL_Rect* srcect = NULL ;
	SDL_Rect* pos = NULL ;
    ajouter (t, srcect, pos) ;
}


// AJOUT SURFACE D'AFFICHAGE SUR UNE SURFACE D'AFFICHAGE
void SurfaceAffichage::ajouter (SurfaceAffichage const& s, SDL_Rect* srcect, SDL_Rect* pos, SDL_Color col)
{
	SDL_Rect position ;
	position.x = 0 ;
	position.y = 0 ;
	if (pos == NULL)
	{
		pos = &position ;
	}
	//fprintf(stderr, " surface : %p\n Coord : %p\n Pos : %p\n Fsurface %p\n", s.m_surface, srcect, pos, m_surface);
	//if(SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 0, 0, 0)) != 0)
		//erreur_message("L'ajout d'une SurfaceAffichage dans une autre à échoué (impossible d'effacer l'ecran) :  " + string(SDL_GetError())) ;
	if(SDL_BlitSurface(s.m_surface, srcect, m_surface, pos))
        erreur_message("L'ajout d'une SurfaceAffichage dans une autre à échoué :  " + string(SDL_GetError())) ;
}
void SurfaceAffichage::ajouter (SurfaceAffichage const& s, SDL_Rect* srcect, unsigned short const& posx, unsigned int short const& posy, SDL_Color col)
{
	SDL_Rect pos ;
    pos.x = posx ;
    pos.y = posy ;
    ajouter (s, srcect, &pos, col) ;
}
void SurfaceAffichage::ajouter (SurfaceAffichage const& s, unsigned short const& posx, unsigned int short const& posy, SDL_Color col)
{
    ajouter (s, NULL, posx, posy, col) ;
}
void SurfaceAffichage::ajouter(SurfaceAffichage const& s, SDL_Color col)
{
	SDL_Rect* srcect = NULL ;
	SDL_Rect* pos = NULL ;
	ajouter (s, srcect, pos, col) ;
}
void SurfaceAffichage::ajouter (SurfaceAffichage const& s)
{
	SDL_Color couleur = {0,0,0} ;
    ajouter (s, couleur) ;
}

//AJOUT D'UN SPRITE SUR LA SURFACE D'AFFICHAGE
void SurfaceAffichage::ajouter (SpriteTexture const& s, SDL_Rect* pos, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur)
{
	SDL_Rect* screct = new SDL_Rect(s.getRect(numero_sprite_longueur,numero_sprite_largeur)) ;
    if(SDL_BlitSurface(s.surface(), screct, m_surface, pos))
        erreur_message("Impossible d'ajouter le sprite" + s.path() + " à la SurfaceAffichage : " + string(SDL_GetError())) ;
    if (screct != NULL){
    	delete screct ;
    }
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
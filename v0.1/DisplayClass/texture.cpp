#include "texture.h"
#include "fenetre.h"
using namespace std;


//CONSTRUCTEUR
Texture::Texture(string const& path)
{
    m_path = path ;

	m_surface = SDL_LoadBMP(path.c_str()) ;

    if(m_surface == NULL)
        erreur_message("Impossible de charger " + m_path + " : " + SDL_GetError()) ;

    m_surface = SDL_DisplayFormat(m_surface) ;

    if(m_surface == NULL)
        erreur_message("Impossible de charger " + m_path + " (DisplayFormat a échoué) : " + SDL_GetError()) ;

}

//DESTRUCTEUR
Texture::~Texture()
{
	SDL_FreeSurface(m_surface) ;
}


// AJOUTE LA TEXTURE SUR LA FENETRE
void Texture::ajouterA (Fenetre const& f, SDL_Rect* pos) const
{
    if(SDL_BlitSurface(m_surface, NULL, f.screen(), pos))
        erreur_message("Impossible d'ajouter " + m_path + " : " + SDL_GetError()) ;
}

void Texture::ajouterA (Fenetre const& f, unsigned short const& posx, unsigned int short const& posy) const
{
    SDL_Rect pos ;
    pos.x = posx ;
    pos.y = posy ;
    ajouterA(f, &pos) ;
}

void Texture::ajouterA (Fenetre const& f) const
{
    ajouterA(f, NULL) ;
}


//CONSTRUCTEUR
SpriteTexture::SpriteTexture (string const& path, unsigned short const& size_sprite, unsigned short const& nombre_de_sprite_longueur, unsigned short const& nombre_de_sprite_largeur) : Texture(path)
{
    m_taille = size_sprite ;
    m_nb_longueur = nombre_de_sprite_longueur ;
    m_nb_largeur = nombre_de_sprite_largeur ;
}

//DESTRUCTEUR
SpriteTexture::~SpriteTexture()
{
    
}



void SpriteTexture::ajouterA (Fenetre const& f, SDL_Rect* pos, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur) const
{

    if(numero_sprite_longueur >= m_nb_longueur || numero_sprite_largeur >= m_nb_largeur)
        erreur_message("Demande d'acces a une case du Sprite " + m_path + " qui n'existe pas") ;
    
    SDL_Rect image ; //the image
    image.x = numero_sprite_longueur*m_taille ;
    image.y = numero_sprite_largeur*m_taille ;
    image.h = m_taille ;
    image.w = m_taille ;
    if(SDL_BlitSurface(m_surface, &image, f.screen(), pos))
        erreur_message("Impossible d'ajouter " + m_path + " : " + SDL_GetError()) ;
}

void SpriteTexture::ajouterA (Fenetre const& f, unsigned short const& posx, unsigned int short const& posy, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur) const
{
    SDL_Rect pos ;
    pos.x = posx ;
    pos.y = posy ;
    ajouterA(f, &pos, numero_sprite_longueur, numero_sprite_largeur) ;
}

void SpriteTexture::ajouterA (Fenetre const& f, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur) const
{
    SDL_Rect* p = NULL ;
    ajouterA(f, p, numero_sprite_longueur, numero_sprite_largeur) ;
}
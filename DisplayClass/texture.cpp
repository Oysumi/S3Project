#include "texture.h"
using namespace std;


//CONSTRUCTEUR
Texture::Texture(string const& path) : m_path(path)
{
	m_surface = SDL_LoadBMP(path.c_str()) ;
    if(m_surface == NULL)
        erreur_message("Impossible de charger la  texture " + path + " : " + SDL_GetError()) ;
    m_surface = SDL_DisplayFormat(m_surface) ;
    if (m_surface == NULL)
        erreur_message("Impossible de charger la  texture " + path + " (displayFormat Fail) : " + SDL_GetError()) ;
}

//DESTRUCTEUR
Texture::~Texture()
{
    if(m_surface!=NULL)
    {
        SDL_FreeSurface(m_surface);
        m_surface = NULL ;
        //warning_message("libéreration de la texture \"" + m_path + "\" avec SDL_FreeSurface in ~Texture()") ;
    }
    else 
        warning_message("Potentielle fuite de mémoire : Impossible de libérer la texture \"" + m_path + "\" avec SDL_FreeSurface in ~Texture()") ;
}

//ACCESSEURS
SDL_Surface * Texture::surface() const
{
    return m_surface ;
}
string Texture::path() const
{
    return m_path ;
}

//CONSTRUCTEUR
SpriteTexture::SpriteTexture (string const& path, unsigned short const& size_sprite, unsigned short const& nombre_de_sprite_longueur, unsigned short const& nombre_de_sprite_largeur)
: Texture(path), m_taille(size_sprite), m_nb_longueur(nombre_de_sprite_longueur), m_nb_largeur(nombre_de_sprite_largeur)
{
}

//Obtenir la zone du sprite
SDL_Rect SpriteTexture::getRect (unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur) const
{
    if(numero_sprite_longueur >= m_nb_longueur || numero_sprite_largeur >= m_nb_largeur)
    {
        warning_message("Demande d'accès à une case du Sprite " + path() + " qui n'existe pas") ;
        cout << endl << endl << "ateiprieroi" << endl ;
    }
    
    SDL_Rect image ;
    image.x = numero_sprite_longueur*m_taille ;
    image.y = numero_sprite_largeur*m_taille ;
    image.h = m_taille ;
    image.w = m_taille ;
    return image ;
}

//DESTRUCTEUR
SpriteTexture::~SpriteTexture()
{
    //Après vérification le destructeur ~Texture() est appelé par défault donc rien ici
}
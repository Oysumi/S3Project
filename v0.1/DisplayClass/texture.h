#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include <string>
#include "SDL/SDL.h"

#include "../fonctions.h"

class Texture
{
    public:

        Texture(std::string const& path) ;
        ~Texture() ;

        std::string path() const ;
        SDL_Surface* surface() const ;

    private:

        std::string m_path ;
        SDL_Surface* m_surface ;
};


class SpriteTexture : public Texture
{

    public:

        SpriteTexture (std::string const& path, unsigned short const& size_sprite, unsigned short const& nombre_de_sprite_longueur, unsigned short const& nombre_de_sprite_largeur = 1) ;
        SDL_Rect getRect (unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur) const ;

    private:

        unsigned short m_taille ;
    	unsigned short m_nb_longueur, m_nb_largeur ;

};

#endif
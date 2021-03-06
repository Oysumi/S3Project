#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include <string>
#include "SDL/SDL.h"

#include "../Fonctions/fonctions.h"

class Texture
{
    public:

        Texture(std::string const& path) ;
        ~Texture() ;

        std::string path() const ;
        SDL_Surface* surface() const ;

    protected:

        std::string m_path ;
        SDL_Surface* m_surface ;

        //friend void SurfaceAffichage::ajouter (SurfaceAffichage const& s, SDL_Rect* pos) ;
};


class SpriteTexture : public Texture
{

    public:

        SpriteTexture (std::string const& path, unsigned short const& width, unsigned short const& height, unsigned short const& nombre_de_sprite_longueur, unsigned short const& nombre_de_sprite_largeur = 1) ;
        SDL_Rect getRect (unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur) const ;
        ~SpriteTexture() ;

    private:

        unsigned short m_width, m_height ;
    	unsigned short m_nb_longueur, m_nb_largeur ;

};

#endif
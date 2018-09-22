#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include <string>
#include "SDL/SDL.h"

#include "../fonctions.h"
#include "fenetre.h"

class Texture
{
    public:

        Texture(std::string const& path) ;
        void ajouterA (Fenetre const& f, SDL_Rect* pos) const ;
        void ajouterA (Fenetre const& f, unsigned short const& posx, unsigned int short const& posy) const ;
	    void ajouterA (Fenetre const& f) const ;
        ~Texture() ;

    protected:

        SDL_Surface* m_surface ;
        std::string m_path ;
};


class SpriteTexture : public Texture
{

    public:

        SpriteTexture (std::string const& path, unsigned short const& size_sprite, unsigned short const& nombre_de_sprite_longueur, unsigned short const& nombre_de_sprite_largeur = 1) ;
        ~SpriteTexture() ;
        void ajouterA (Fenetre const& f, SDL_Rect* pos, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) const ;
        void ajouterA (Fenetre const& f, unsigned short const& posx, unsigned int short const& posy, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) const ;
	    void ajouterA (Fenetre const& f, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) const ;

    private:

    	unsigned short m_nb_longueur, m_nb_largeur ;
    	unsigned short m_taille ;

};

#endif
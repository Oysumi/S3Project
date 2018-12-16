#ifndef DEF_FENETRE
#define DEF_FENETRE

#include <string>
#include "SDL/SDL.h"

#include "texture.h"
#include "../Fonctions/fonctions.h"

#define SIZE_MIN 100
#define TRANSPARENCE true

class SurfaceAffichage
{
    public :
        /* create permet de dire si oui ou non nous avons besoin de créer une SDL_Surface, car dans le cas des
         * textes à afficher, nous devons utiliser une fonction autre que celle proposée par SDL_RGB */
        SurfaceAffichage(unsigned short const& width, unsigned short const& height) ;
        SurfaceAffichage(unsigned short const& width, unsigned short const& height, SDL_Surface* surface) ;
        SurfaceAffichage(Texture const& texture, bool transparence = false) ;
        SurfaceAffichage(std::string const& texture_path, bool transparence = false) ;
        virtual ~SurfaceAffichage() ;

        bool saveBMP(std::string const& name) const ;

        unsigned short width() const ; 
        unsigned short height() const ; 
        SDL_Surface* surface() const ;

        SurfaceAffichage* rendre_transparente() ;

        //Affichage d'une texture
        void ajouter (Texture const& t, SDL_Rect* srcect, SDL_Rect* pos) ;
        void ajouter (Texture const& t, SDL_Rect* srcect, unsigned short const& posx, unsigned int short const& posy) ;
        void ajouter (Texture const& t, unsigned short const& posx, unsigned int short const& posy) ;
        void ajouter (Texture const& t) ;

        //Affichage d'une surface d'affichage
        void ajouter (SurfaceAffichage const& s, SDL_Rect* srcect, SDL_Rect* pos) ;
        void ajouter (SurfaceAffichage const& s, SDL_Rect* srcect, unsigned short const& posx, unsigned int short const& posy) ;
        void ajouter (SurfaceAffichage const& s, unsigned short const& posx, unsigned int short const& posy) ;
        void ajouter (SurfaceAffichage const& s) ;

        //Affichage d'un sprite
        void ajouter (SpriteTexture const& s, SDL_Rect* pos, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) ;
        void ajouter (SpriteTexture const& s, unsigned short const& posx, unsigned int short const& posy, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) ;
        void ajouter (SpriteTexture const& s, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) ;

    protected :
        void free() ;

    protected :

        SDL_Surface* m_surface ;
        unsigned short m_height ;
        unsigned short m_width ;
        static SurfaceAffichage* fenetre ;
};


//La fenêtre est une surface d'affichage, son instance est unique
class Fenetre : public SurfaceAffichage
{
    public:

	    Fenetre(std::string const& title, unsigned short const& width, unsigned short const& height, Uint32 flags = 0) ;
	    ~Fenetre() ;
	    void actualiser() ;

};

#endif
#ifndef DEF_FENETRE
#define DEF_FENETRE

#include <string>
#include "SDL/SDL.h"

#include "texture.h"
#include "../fonctions.h"

#define SIZE_MIN 100

class SurfaceAffichage
{
    public :
        SurfaceAffichage(unsigned short const& width, unsigned short const& height) ;
        ~SurfaceAffichage() ;

        void ajouter (Texture const& t, SDL_Rect* pos) ;
        void ajouter (Texture const& t, unsigned short const& posx, unsigned int short const& posy) ;
        void ajouter (Texture const& t) ;

        void ajouter (SurfaceAffichage const& s, SDL_Rect* pos) ;
        void ajouter (SurfaceAffichage const& s, unsigned short const& posx, unsigned int short const& posy) ;
        void ajouter (SurfaceAffichage const& s) ;

        void ajouter (SpriteTexture const& s, SDL_Rect* pos, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) ;
        void ajouter (SpriteTexture const& s, unsigned short const& posx, unsigned int short const& posy, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) ;
        void ajouter (SpriteTexture const& s, unsigned short const& numero_sprite_longueur, unsigned short const& numero_sprite_largeur = 0) ;

        bool saveBMP(std::string const& name) const ;

        unsigned short width() const ; 
        unsigned short height() const ; 

    protected :

        SDL_Surface* m_surface ;
        unsigned short m_height ;
        unsigned short m_width ;
};


//La fenêtre est une surface d'affichage, son instance est unique
class Fenetre : public SurfaceAffichage
{
    public:

	    Fenetre(std::string const& title, unsigned short const& width, unsigned short const& height, Uint32 flags = 0) ;
	    ~Fenetre() ;
	    void actualiser() ;

    private:

    	static bool instantiated ;
};

#endif
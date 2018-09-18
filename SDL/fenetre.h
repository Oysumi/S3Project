#ifndef DEF_FENETRE
#define DEF_FENETRE

#include <string>
#include "SDL/SDL.h"

#include "../fonctions.h"
#include "texture.h"

#define SIZE_MIN 10

class Fenetre
{
    public:

	    Fenetre(std::string const& title, unsigned short const& width, unsigned short const& height) ;
	    ~Fenetre() ;
        void ajouter (Texture const& t, SDL_Rect* pos) ;
        void ajouter (Texture const& t, unsigned short const& posx, unsigned int short const& posy) ;
	    void ajouter (Texture const& t) ;
	    void actualiser() ;

    private:

    	SDL_Surface* m_screen ;
    	unsigned short m_height ;
    	unsigned short m_width ;
    	static bool instantiated ;
};

#endif
#ifndef DEF_FENETRE
#define DEF_FENETRE

#include <string>
#include "SDL/SDL.h"

#include "../fonctions.h"

#define SIZE_MIN 10

class Fenetre
{
    public:

	    Fenetre(std::string const& title, unsigned short const& width, unsigned short const& height, Uint32 flags = 0) ;
	    ~Fenetre() ;
	    void actualiser() ;
        SDL_Surface* screen() const ;

    private:

    	SDL_Surface* m_screen ;
    	unsigned short m_height ;
    	unsigned short m_width ;
    	static bool instantiated ;
};

#endif
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
        SDL_Surface* surface() const ;

    private:

        SDL_Surface* m_surface ;
};

#endif
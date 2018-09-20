#include <cstdlib>
#include <cstdio>
#include <string>
#include "SDL/SDL.h"

#include "fonctions.h"
#include "DisplayClass/texture.h"
#include "DisplayClass/fenetre.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define GRASS_SIZE 32

int main ( int args, char * argv[] )
{
    Fenetre fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE || SDL_DOUBLEBUF) ;
    Texture herbe("ressources/grass.bmp") ; // Change the path to print a new image just for a test
    
    //EVENT LOOP
    SDL_Event event ;
    bool end = false ;
    while (!end)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    end = true ;
                    break ;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            end = true ;
                            break ;
                            
                        default:
                            break;
                    }
                    break;
            }
        }
        //ajoute un carré d'herbe
        fenetre.ajouter(herbe) ;
        fenetre.actualiser() ;

        //Rempli la fenêtre d'herbe
        for (unsigned short x = 0 ; x < SCREEN_WIDTH ; x+=GRASS_SIZE)
            for (unsigned short y = 0 ; y < SCREEN_HEIGHT ; y+=GRASS_SIZE)
                fenetre.ajouter(herbe,x,y) ;
        fenetre.actualiser() ;
    }

    return 0 ;
}
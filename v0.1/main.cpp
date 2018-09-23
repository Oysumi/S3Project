#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include "SDL/SDL.h"

#include "fonctions.h"
#include "DisplayClass/fenetre.h"
#include "MapClass/terrain.h"

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400


int main ( int args, char * argv[] )
{

    Fenetre fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE || SDL_DOUBLEBUF) ;
    Terrain terrain("ressources/map.txt","ressources/SpriteMap64.bmp") ;
    terrain.saveBMP("terrain.bmp") ;
    fenetre.ajouter(terrain.terrainComplet()) ;
    
    //EVENT LOOP
    debugage_message("Début du Jeu") ;
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
        
        fenetre.actualiser() ;

    }
    debugage_message("Fin du Jeu") ;
    return 0 ;
}
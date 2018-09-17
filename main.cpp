#include <cstdlib>
#include <cstdio>
#include "SDL/SDL.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main ( int args, char * argv[] )
{
    SDL_Init(SDL_INIT_VIDEO) ;
    
    SDL_WM_SetCaption("Project test", "Informatic S3 Project test") ;
    
    SDL_Surface * screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
    
    SDL_Surface * temp = SDL_LoadBMP("grass.bmp") ; // Change the path to print a new image just for a test
    
    SDL_Surface * background = SDL_DisplayFormat(temp) ;
    
    SDL_FreeSurface(temp) ;
    
    SDL_Event event ;
    int gameover = 0 ;
    
    while (!gameover)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    gameover = 1 ;
                    break ;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            gameover = 1 ;
                            break ;
                            
                        default:
                            break;
                    }
                    break;
            }
        }
        
        SDL_BlitSurface(background, NULL, screen, NULL);
        
        SDL_UpdateRect(screen,0,0,0,0);
    }
    
    SDL_FreeSurface(background) ;
    SDL_Quit() ;
    
    return 0 ;
}
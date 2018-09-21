#include <cstdlib>
#include <cstdio>
#include <string>
#include "SDL/SDL.h"

#include "fonctions.h"
#include "DisplayClass/texture.h"
#include "DisplayClass/fenetre.h"

using namespace std;

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 600
#define MAP_CASE_SIZE 64
#define NB_WATER_SPRITE 15

int main ( int args, char * argv[] )
{
    Fenetre fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE || SDL_DOUBLEBUF) ;
    Texture herbe("ressources/Grass64.bmp") ;
    SpriteTexture water("ressources/SpriteWater64.bmp", MAP_CASE_SIZE, NB_WATER_SPRITE) ; 
    
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
        herbe.ajouterA(fenetre) ;

        //Coordonnées d'affichage
        unsigned short x = 0 ;
        unsigned short y = 0 ;

        bool not_full = true ; // FLAG
        //Après le carré d'herbe afficher toutes les sprite de Water pour remplir la fenetre (Pour tester)
        for (unsigned short i = 0 ; not_full ; i = (i+1) % NB_WATER_SPRITE)
        {
            //Si les coordonées dépasse la largeur de l'écran
            if(x + MAP_CASE_SIZE > SCREEN_WIDTH )
            {

                //Si les coordonées dépasse la largeur de l'écran aussi il est rempli
                if (y + MAP_CASE_SIZE > SCREEN_HEIGHT)
                    not_full = false ;
                
                else //on retourne à la ligne
                {
                    x = 0 ;
                    y += MAP_CASE_SIZE ;
                }
            }
            else //Sinon on affiche à droite de la texture précedente
                x+= MAP_CASE_SIZE ;

            //Affichage en (x,y) du Slide i
            if (not_full)
                water.ajouterA(fenetre,x,y,i) ;

        }

        fenetre.actualiser() ;


    }

    return 0 ;
}
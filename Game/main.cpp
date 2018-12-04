#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <time.h>
#include "SDL/SDL.h"
#include <SDL/SDL_ttf.h>

#include "../MatriceClass/MatriceGameGestion.h"
#include "../Fonctions/fonctions.h"

using namespace std;

int main ( int args, char * argv[] )
{   
    //initialisation aléatoire et TTF
    srand(time(NULL)) ;
    TTF_Init() ;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        erreur_message("Impssible d'initialiser la SDL") ;
    
    {
        MatriceGameGestion matrice ;
        //Initialisation et boucle du jeu
        matrice.init() ;
        matrice.gameLoop() ;
    }

    TTF_Quit() ;
    SDL_Quit() ;

    return 0;
}
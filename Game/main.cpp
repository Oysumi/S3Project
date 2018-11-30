#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include "SDL/SDL.h"
#include <SDL/SDL_ttf.h>

#include "../Fonctions/fonctions.h"
#include "../Fonctions/remplissage.h"

#include "../ID/idbuttons.h"
#include "../MenuClass/ActionButton.h"

#include "../CharactersClass/AbstractPlayer.h"
#include "../MatriceClass/MatriceGameGestion.h"

using namespace std;

int main ( int args, char * argv[] )
{   
    //initialisation aléatoire et TTF
    srand(time(NULL)) ;
    TTF_Init() ;
    
    MatriceGameGestion matrice ;
    //Initialisation et boucle du jeu
    matrice.init() ;
    matrice.gameLoop() ;
    
    atexit(SDL_Quit) ;
    TTF_Quit() ;
    debugage_message("Fin du Jeu") ;

    return 0;
}
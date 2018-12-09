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
    //initialisation de l'aléatoire
    srand(time(NULL)) ;

    //Initialisation TTF et SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        erreur_message("Impssible d'initialiser la SDL" + string(SDL_GetError())) ;
    if (TTF_Init() != 0)
        erreur_message("Erreur d'initialisation de TTF_Init : " + string(TTF_GetError())) ;
    
    MatriceGameGestion* matrice =   //Matrice de gestion du jeu capable de gérer une partie
    new MatriceGameGestion() ;      //initialise le programme, fenetre, menus, boutons ...
    matrice->gameLoop() ;           //Cette fonction lance la partie après son initialisation
    delete(matrice) ;               //Ainsi la Matrice est détruite avant de quitter la SDL et TTF

    TTF_Quit() ;
    SDL_Quit() ;
    return 0;
}
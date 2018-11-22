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
    //initialisation aléatoire
    srand(time(NULL)) ;

    vector <AbstractButton*> bouton ;
    bouton = remplissage() ;

    //Initialisation du jeu
    MatriceGameGestion matrice(bouton) ;
    
    //Création des unités / Remplissage de la carte ...
    matrice.init() ;

    //Boucle du Jeu
    matrice.gameLoop() ;
    
    //Traitement fin du Jeu
    deleteVect(bouton) ;
    atexit(SDL_Quit) ;
    TTF_Quit() ;
    debugage_message("Fin du Jeu") ;

    return 0;
}
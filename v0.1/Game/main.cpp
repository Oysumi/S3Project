#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "SDL/SDL.h"
#include <vector>
#include <SDL/SDL_ttf.h>

#include "../Fonctions/fonctions.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/terrain.h"
#include "../MenuClass/ActionButton.h"
#include "../MatriceClass/MatriceGameGestion.h"
#include "../MenuClass/Menu.h"

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define ID_MENU_ESCAPE 32

int main ( int args, char * argv[] )
{
    //initialisation aléatoire
    srand(time(NULL)) ;
    
    //Création fenêtre et terrain
    Fenetre fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN) ;
    Terrain terrain("../ressources/map.txt") ;

    //enregistrement du terrai dans une image
    terrain.saveBMP("../terrain.bmp") ;

    //On affiche le terrain
    fenetre.ajouter(terrain.terrainComplet()) ;
    fenetre.actualiser() ;
    
    //EVENT LOOP
    debugage_message("Début du Jeu") ;

    bool changement, gauche_ecran = false, droite_ecran = false, bas_ecran = false, haut_ecran = false ;
    int temps_precedent = 0 ;
    SDL_Rect scroll ;
    scroll.x = 0 ;
    scroll.y = 0 ;
    scroll.h = SCREEN_HEIGHT ;
    scroll.w = SCREEN_WIDTH ;

    /*
    //TEST MENU
    vector<AbstractButton> test(3) ;
    SDL_Color font = {255, 255, 255} ; 
    SDL_Color text = {0, 0, 0} ;

    test[0] = ActionButton(12, "RETOUR", 200, 100, 110, 110, font, text) ;
    test[1] = ActionButton(12, "MUSIQUE", 200, 100, 110, 110, font, text) ;
    test[2] = ActionButton(12, "QUITTER", 200, 100, 110, 110, font, text) ;

    SDL_Color font_menu = {0, 0, 0} ;
    unsigned short int x(SCREEN_WIDTH/2 - 100), y(SCREEN_HEIGHT/4) ;
    Menu menu(test, x, y, font_menu, 32) ;*/

    // Initialisation de la matrice de gestion de jeu
    MatriceGameGestion matrice ;

    SDL_Event event ; 
    bool end = false ;
    bool menuOpen = false ;

    TTF_Init() ;

    int id_esc = ID_MENU_ESCAPE ;

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
                            if (!menuOpen){
                                menuOpen = true ;
                                /*menu.displayMenu(fenetre) ;
                                cout << "Menu ouvert" << endl ;*/
                                matrice.openMenu(id_esc, fenetre);
                            }
                            else{
                                menuOpen = false ;
                                fenetre.ajouter(terrain.terrainComplet(),&scroll,0,0) ;
                                fenetre.actualiser() ;
                                //cout << "Menu fermé" << endl ;
                            }
                            break ;

                        case SDLK_q:
                            end = true ;
                            break ;
                            
                        default:
                            break;
                            
                    }
                    break;

                //DECALAGE DE LA CARTE
                case SDL_MOUSEMOTION:
                {
                    if (event.motion.x <= SCROOL_ZONE)
                        gauche_ecran = true ;
                    else
                        gauche_ecran = false ;

                    if (event.motion.y <= SCROOL_ZONE)
                        haut_ecran = true ;
                    else
                        haut_ecran = false ;

                    if (event.motion.x >= SCREEN_WIDTH-SCROOL_ZONE)
                        droite_ecran = true ;
                    else
                        droite_ecran = false ;

                    if (event.motion.y >= SCREEN_HEIGHT-SCROOL_ZONE)
                        bas_ecran = true ;
                    else
                        bas_ecran = false ;

                    break ;
                }

            }
        }


        changement = false ;
        if (gauche_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.x > 0)
        {
            scroll.x -- ;
            changement = true ;
        }
        if (droite_ecran && SDL_GetTicks()-temps_precedent>= TIME_BETWEEN_SCROLL_CHANGE && scroll.x < terrain.terrainComplet().width() - SCREEN_WIDTH)
        {
            scroll.x ++ ;
            changement = true ;
        }
        if (haut_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y > 0)
        {
            scroll.y -- ;
            changement = true ;
        }
        if (bas_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y < terrain.terrainComplet().height() - SCREEN_HEIGHT)
        {
            scroll.y ++ ;
            changement = true ;
        }
        if (changement)
        {
            temps_precedent = SDL_GetTicks() ;
            fenetre.ajouter(terrain.terrainComplet(),&scroll,0,0) ;
            if (menuOpen){
                matrice.openMenu(id_esc, fenetre);
            }
            fenetre.actualiser() ;
        }

    }
    
    atexit(SDL_Quit);
    TTF_Quit() ;
    debugage_message("Fin du Jeu") ;

    return 0;
}
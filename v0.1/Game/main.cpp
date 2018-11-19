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
#include "../MapClass/map.h"
#include "../MenuClass/ActionButton.h"
#include "../MatriceClass/MatriceGameGestion.h"
#include "../MenuClass/Menu.h"
#include "../CharactersClass/AbstractPlayer.h"

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500
#define ID_MENU_ESCAPE 32

int main ( int args, char * argv[] )
{
    //initialisation aléatoire
    srand(time(NULL)) ;
    vector <AbstractPlayer> joueurs ;
    
    //Création fenêtre et terrain
    Fenetre fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN) ;
    Map map (joueurs) ;


    //On affiche le terrain
    fenetre.ajouter(map.getSurface()) ;
    fenetre.actualiser() ;
    
    //EVENT LOOP
    debugage_message("Début du Jeu") ;

    bool changement, gauche_ecran = false, droite_ecran = false, bas_ecran = false, haut_ecran = false ;
    int temps_precedent = 0 ;
    int temps_menu = 0 ;

    SDL_Rect scroll ;
    scroll.x = 0 ;
    scroll.y = 0 ;
    scroll.h = SCREEN_HEIGHT ;
    scroll.w = SCREEN_WIDTH ;

    // Initialisation de la matrice de gestion de jeu
    MatriceGameGestion matrice ;

    SDL_Event event ; 
    bool end = false ;
    bool menuOpen = false ;

    TTF_Init() ;

    int id_esc = ID_MENU_ESCAPE ;

    while (!end)
    {
        changement = false ;

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
                            if (!menuOpen && SDL_GetTicks()-temps_menu > TIME_LIMIT_TO_DISPLAY_MENU){
                                menuOpen = true ;
                                changement = true ;
                                matrice.openMenu(id_esc, fenetre, true);
                                temps_menu = SDL_GetTicks();
                            }
                            else{
                                menuOpen = false ;
                                changement = true ;
                                matrice.openMenu(id_esc, fenetre, true);
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

                //GESTION DES CLICS DE SOURIS
                case SDL_MOUSEBUTTONDOWN:
                    unsigned int mouse_x = event.motion.x ;
                    unsigned int mouse_y = event.motion.y ;
                    end = matrice.receiveAction(mouse_x, mouse_y);
                    break ;
            }
        }


        if (gauche_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.x > 0)
        {
            scroll.x -- ;
            changement = true ;
        }
        if (droite_ecran && SDL_GetTicks()-temps_precedent>= TIME_BETWEEN_SCROLL_CHANGE && scroll.x < map.width() - SCREEN_WIDTH)
        {
            scroll.x ++ ;
            changement = true ;
        }
        if (haut_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y > 0)
        {
            scroll.y -- ;
            changement = true ;
        }
        if (bas_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y < map.height() - SCREEN_HEIGHT)
        {
            scroll.y ++ ;
            changement = true ;
        }
        if (changement)
        {
            temps_precedent = SDL_GetTicks() ;
            fenetre.ajouter(map.getSurface(),&scroll,0,0) ;
            if (menuOpen){
                matrice.openMenu(id_esc, fenetre, false);
            }
            fenetre.actualiser() ;
        }

    }
    
    atexit(SDL_Quit);
    TTF_Quit() ;
    debugage_message("Fin du Jeu") ;

    return 0;
}
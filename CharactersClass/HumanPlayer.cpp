#include "HumanPlayer.h"

#include "../MenuClass/Menu.h"
#include "../ID/idbuttons.h"
#include "../ID/idmenus.h"

#include <string>
#include <iostream>

#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500

using namespace std ;

HumanPlayer::HumanPlayer()
{}

HumanPlayer::~HumanPlayer()
{}

void HumanPlayer::takeDecision(Fenetre& fenetre, Map const& map, SDL_Rect scroll)
{

	debugage_message("Début du Jeu") ;

    bool changement, gauche_ecran = false, droite_ecran = false, bas_ecran = false, haut_ecran = false ;
    int temps_precedent = 0 ;
    int temps_menu = 0 ;

    SDL_Event event ; 
    bool end = false ;

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
                            if (SDL_GetTicks()-temps_menu > TIME_LIMIT_TO_DISPLAY_MENU)
                            {
                                changement = true ;
                                Menu::openMenu(ESCAPE_MENU, fenetre);
                                temps_menu = SDL_GetTicks();
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

                    if (event.motion.x >= scroll.w-SCROOL_ZONE)
                        droite_ecran = true ;
                    else
                        droite_ecran = false ;

                    if (event.motion.y >= scroll.h-SCROOL_ZONE)
                        bas_ecran = true ;
                    else
                        bas_ecran = false ;

                    break ;
                }

                //GESTION DES CLICS DE SOURIS
                case SDL_MOUSEBUTTONDOWN:
                    if (Menu::getIdButtonOn(event.motion.x,event.motion.y)==QUITTER)
                    {
                        end = true ;
                    }
                    else
                    {
                        cout << map.unit_on(map.mapPos_of_click(scroll,event.motion.x,event.motion.y)) << endl ;
                    }
                    break ;
            }
        }


        if (gauche_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.x > 0)
        {
            scroll.x -- ;
            changement = true ;
        }
        if (droite_ecran && SDL_GetTicks()-temps_precedent>= TIME_BETWEEN_SCROLL_CHANGE && scroll.x < map.width() - scroll.w)
        {
            scroll.x ++ ;
            changement = true ;
        }
        if (haut_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y > 0)
        {
            scroll.y -- ;
            changement = true ;
        }
        if (bas_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y < map.height() - scroll.h)
        {
            scroll.y ++ ;
            changement = true ;
        }
        if (changement)
        {
            temps_precedent = SDL_GetTicks() ;
            fenetre.ajouter(map.getSurface(),&scroll,0,0) ;
            if (Menu::isAMenuOpened()){
                Menu::keepOpened(fenetre);
            }
            fenetre.actualiser() ;
        }

    }
}
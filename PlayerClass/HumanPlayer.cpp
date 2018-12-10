#include "HumanPlayer.h"

#include "../MenuClass/Menu.h"
#include "../ID/idbuttons.h"
#include "../ID/idmenus.h"
#include "../MatriceClass/decisionID.h"

#include <string>
#include <iostream>

#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500

using namespace std ;

HumanPlayer::HumanPlayer(string name, unsigned short color_id) : AbstractPlayer(name,color_id%NB_COLOR)
{
    m_gauche_ecran = false ;
    m_droite_ecran = false ;
    m_bas_ecran = false ;
    m_haut_ecran = false ;
    m_temps_precedent = 0 ;
}

HumanPlayer::~HumanPlayer()
{}

//Fonction utilisée par la matrice pour demander au joueur de prendre une décision, seul interraction d'un joueur
Decision HumanPlayer::takeDecision(
            Map const& map, //Ici la Map est une référence constante, ainsi le joueur est en lecture seule, il doit passer par la matrice pour tout changement
            Selection const& selection, // Permet au joueur d'avoir des infos sur l'unité séléctionée, sans changer la sélécion
            Fenetre& fenetre, //Passage par référence, une seule et même fenêtre dont le joueur peut changer le contenu pendant son tour
            SDL_Rect& scroll //Permet juste à la matrice de savoir où regarde le joueur
            )
{
    bool changement ;

    SDL_Event event ; 
    Decision decision_retour ; //Décision qui sera renvoyer à la matrice

    while (!decision_retour.is_valid()) // Tant que le joueur n'a pas pris de décision que la matrice doit traiter
    {
        changement = false ;

        if (SDL_PollEvent(&event)) // On attend un événement
        {
            switch (event.type)
            {

                case SDL_QUIT: // Si le programme reçoit un signal d'extinction
                    decision_retour.set_decision(DECISION_QUITTER) ;
                    break ;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                      case SDLK_x :
                        Menu::openMenu(CONS_MENU, fenetre);
                        break;
                        
                        case SDLK_ESCAPE: // Si le joueur ouvre le menu principal
                            changement = true ;
                            Menu::openMenu(ESCAPE_MENU, fenetre);
                            break ;

                        case SDLK_BACKSPACE: // Si le joueur ouvre le menu principal
                            decision_retour.set_decision(DECISION_TOUR_SUIVANT) ;
                            break ;

                        case SDLK_q: // Le joueur souhaite quitter grâce à la touche Q
                            decision_retour.set_decision(DECISION_QUITTER) ;
                            break ;
                            
                        default:
                            break;
                            
                    }
                    break;

                //Si l'utilisateur bouge le curseur sur le bord de l'écran on doit décaler la partie de la map affichée sur l'écran
                case SDL_MOUSEMOTION:
                {
                    if (event.motion.x <= SCROOL_ZONE)
                        m_gauche_ecran = true ;
                    else
                        m_gauche_ecran = false ;

                    if (event.motion.y <= SCROOL_ZONE)
                        m_haut_ecran = true ;
                    else
                        m_haut_ecran = false ;

                    if (event.motion.x >= scroll.w-SCROOL_ZONE)
                        m_droite_ecran = true ;
                    else
                        m_droite_ecran = false ;

                    if (event.motion.y >= scroll.h-SCROOL_ZONE)
                        m_bas_ecran = true ;
                    else
                        m_bas_ecran = false ;

                    break ;
                }


                //GESTION DES CLICS DE SOURIS
                case SDL_MOUSEBUTTONDOWN:

                    if (Menu::isOnOneMenu(event.motion.x,event.motion.y)) //GESTION CLICK SUR LES MENUS
                    {
                        if(Menu::getIdButtonOn(event.motion.x,event.motion.y)==QUITTER)
                            decision_retour.set_decision(DECISION_QUITTER) ; // Le joueur à decidé de quitter via le menu principal
                        else if(Menu::getIdButtonOn(event.motion.x,event.motion.y)==RETOUR)
                        {
                            changement = true ;
                            Menu::openMenu(ESCAPE_MENU, fenetre);
                        }
                        else if(Menu::getIdButtonOn(event.motion.x,event.motion.y)==FIN_DU_TOUR)
                            decision_retour.set_decision(DECISION_TOUR_SUIVANT) ;
                        else
                            cout << "MENU CLICK" << endl ;
                    }
                    else //GESTION CLICS SUR lA MAP
                    {
                        MapPos pos( map.mapPos_of_click(scroll,event.motion.x,event.motion.y) ) ;

                        if (selection.possible_move_at(pos)) //Si on peut déplacer l'unité séléctionnée sur cette case
                        {
                            decision_retour.set_decision(DECISION_MOVE_SELECT_UNIT, &pos) ;
                        }
                        else if(map.have_unit_on(pos) || map.have_cons_on(pos)) //Si il y a quelque chose à selectionner sur cette case
                            decision_retour.set_decision(DECISION_CHANGE_SELECT_UNIT, &pos) ;
                    }
                    break ;
            }
        }

        //Si le joueur a son curseur sur le côté, on doit progressivement décaler la partie de la map affichée sur l'écran grâce à la variable scroll
        if (m_gauche_ecran && SDL_GetTicks()-m_temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.x > 0)
        {
            scroll.x -- ;
            changement = true ;
        }
        if (m_droite_ecran && SDL_GetTicks()-m_temps_precedent>= TIME_BETWEEN_SCROLL_CHANGE && scroll.x < map.width() - scroll.w)
        {
            scroll.x ++ ;
            changement = true ;
        }
        if (m_haut_ecran && SDL_GetTicks()-m_temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y > 0)
        {
            scroll.y -- ;
            changement = true ;
        }
        if (m_bas_ecran && SDL_GetTicks()-m_temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y < map.height() - scroll.h)
        {
            scroll.y ++ ;
            changement = true ;
        }

        //Si la variable scroll à bougée on doit actualiser la nouvelle partie de la map affichée
        if (changement)
        {
            m_temps_precedent = SDL_GetTicks() ;
            decision_retour.set_decision(DECISION_UPDATE_GRAPHISME) ;
        }

    }

    return decision_retour ;
}
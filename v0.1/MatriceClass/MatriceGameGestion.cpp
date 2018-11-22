#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../ID/idbuttons.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500

MatriceGameGestion::MatriceGameGestion(vector<AbstractButton*> all_buttons) :
    m_fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN),
    m_map (35,15)
{

    //Couleur de menu
    SDL_Color font_menu = {0, 0, 0} ;

    // Création et ajout dans la mémoire du menu principal (quand on appuie sur la touche escape)
    vector<AbstractButton*> escapeButtons ;
    escapeButtons.push_back(all_buttons[RETOUR]);
    escapeButtons.push_back(all_buttons[MUSIQUE]);
    escapeButtons.push_back(all_buttons[QUITTER]);
    unsigned short int x(SCREEN_WIDTH/2 - 100), y(SCREEN_HEIGHT/4) ;
    m_saveMenu.push_back(new Menu (escapeButtons, x, y, font_menu, ESCAPE_MENU)) ;

    // Création et ajout dans la mémoire du menu prise de décision (attaquer, défendre, aller à, ...)
    vector<AbstractButton*> decisionButtons ;
    decisionButtons.push_back(all_buttons[ATTAQUER]);
    decisionButtons.push_back(all_buttons[DEFENDRE]);
    decisionButtons.push_back(all_buttons[ALLER_A]);
    decisionButtons.push_back(all_buttons[FERMER]);
    m_saveMenu.push_back(new Menu (decisionButtons, 0, 0, font_menu, ATTACK_MENU)) ;

}


MatriceGameGestion::~MatriceGameGestion()
{
    //Suppression des menus de la mémoire de la matrice
    for (unsigned short i = 0 ; i < m_saveMenu.size() ; i++)
    {
        delete(m_saveMenu[i]) ;
    }
}


void MatriceGameGestion::init()
{
    for (unsigned short i = 0 ; i < 10 && m_map.nb_free_pos() > 0 ; i++)
        m_map.add_unit( Unit("../ressources/catapult.bmp", m_map.random_free_pos()) ) ;
    
    for (unsigned short i = 0 ; i < 5 && m_map.nb_free_pos() > 0 ; i++)
        m_map.add_cons( Construction("../ressources/ground.bmp", m_map.random_free_pos(), NULL )) ;

    for (unsigned short i = 0 ; i < 5 && m_map.nb_free_pos() > 0 ; i++)
    {
        MapPos pos (m_map.random_free_pos()) ;
        m_map.add_cons( Construction("../ressources/ground.bmp", pos, NULL )) ;
        m_map.add_unit( Unit("../ressources/catapult.bmp", pos )) ;
    }

    //On affiche le terrain
    m_fenetre.ajouter(m_map.getSurface()) ;
    m_fenetre.actualiser() ;
}


void MatriceGameGestion::gameLoop()
{
    debugage_message("Début du Jeu") ;

    bool changement, gauche_ecran = false, droite_ecran = false, bas_ecran = false, haut_ecran = false ;
    int temps_precedent = 0 ;
    int temps_menu = 0 ;

    SDL_Rect scroll ;
    scroll.x = 0 ;
    scroll.y = 0 ;
    scroll.h = SCREEN_HEIGHT ;
    scroll.w = SCREEN_WIDTH ;

    SDL_Event event ; 
    bool end = false ;

    TTF_Init() ;

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
                            if (SDL_GetTicks()-temps_menu > TIME_LIMIT_TO_DISPLAY_MENU){
                                changement = true ;
                                Menu::openMenu(ESCAPE_MENU, m_fenetre, true);
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
                    if (Menu::getIdButtonOn(event.motion.x,event.motion.y)==QUITTER)
                        end = true ;
                    break ;
            }
        }


        if (gauche_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.x > 0)
        {
            scroll.x -- ;
            changement = true ;
        }
        if (droite_ecran && SDL_GetTicks()-temps_precedent>= TIME_BETWEEN_SCROLL_CHANGE && scroll.x < m_map.width() - SCREEN_WIDTH)
        {
            scroll.x ++ ;
            changement = true ;
        }
        if (haut_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y > 0)
        {
            scroll.y -- ;
            changement = true ;
        }
        if (bas_ecran && SDL_GetTicks()-temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && scroll.y < m_map.height() - SCREEN_HEIGHT)
        {
            scroll.y ++ ;
            changement = true ;
        }
        if (changement)
        {
            temps_precedent = SDL_GetTicks() ;
            m_fenetre.ajouter(m_map.getSurface(),&scroll,0,0) ;
            if (Menu::isAMenuOpened()){
                Menu::keepOpened(m_fenetre);
            }
            m_fenetre.actualiser() ;
        }

    }
}
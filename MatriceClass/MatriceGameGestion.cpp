#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../ID/idbuttons.h"
#include "../ID/idmenus.h"
#include "../CharactersClass/HumanPlayer.h"
#include "../MatriceClass/decisionID.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500



MatriceGameGestion::MatriceGameGestion() :
    m_fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN )
{

    // Création des boutons
    m_all_buttons = new vector<AbstractButton*> ;
    remplissage(m_all_buttons) ;

    //Création des menus
    //Couleur de menu
    SDL_Color font_menu = {0, 0, 0} ;

    // Création et ajout dans la mémoire du menu principal (quand on appuie sur la touche escape)
    vector<AbstractButton*> escapeButtons ;
    escapeButtons.push_back((*m_all_buttons)[RETOUR]);
    escapeButtons.push_back((*m_all_buttons)[MUSIQUE]);
    escapeButtons.push_back((*m_all_buttons)[QUITTER]);
    unsigned short int x(SCREEN_WIDTH/2 - 100), y(SCREEN_HEIGHT/4) ;
    m_saveMenu.push_back(new Menu (escapeButtons, x, y, font_menu, ESCAPE_MENU)) ;

    // Création et ajout dans la mémoire du menu prise de décision (attaquer, défendre, aller à, ...)
    vector<AbstractButton*> decisionButtons ;
    decisionButtons.push_back((*m_all_buttons)[ATTAQUER]);
    decisionButtons.push_back((*m_all_buttons)[DEFENDRE]);
    decisionButtons.push_back((*m_all_buttons)[ALLER_A]);
    decisionButtons.push_back((*m_all_buttons)[FERMER]);
    m_saveMenu.push_back(new Menu (decisionButtons, 0, 0, font_menu, ATTACK_MENU)) ;


    //Représente le rectangle de la map affichée sur la fenêtre
    m_scroll.x = 0 ;
    m_scroll.y = 0 ;
    m_scroll.h = SCREEN_HEIGHT ;
    m_scroll.w = SCREEN_WIDTH ;

}

void MatriceGameGestion::init()
{
    m_map = new Map (35,15) ;

    m_player_list = new std::vector <AbstractPlayer*> ;

    m_player_list->push_back(new HumanPlayer("testplayer")) ;

    for (unsigned short i = 0 ; i < 10 && m_map->nb_free_pos() > 0 ; i++)
        m_map->add_unit( Unit("../ressources/catapult.bmp", m_map->random_free_pos(), m_player_list->at(0) )) ;
    
    for (unsigned short i = 0 ; i < 5 && m_map->nb_free_pos() > 0 ; i++)
        m_map->add_cons( Construction("../ressources/ground.bmp", m_map->random_free_pos(), m_player_list->at(0) )) ;

    for (unsigned short i = 0 ; i < 5 && m_map->nb_free_pos() > 0 ; i++)
    {
        MapPos pos (m_map->random_free_pos()) ;
        m_map->add_cons( Construction("../ressources/ground.bmp", pos, m_player_list->at(0) )) ;
        m_map->add_unit( Unit("../ressources/catapult.bmp", pos, m_player_list->at(0) )) ;
    }

    Decision::init_list_of_choice() ;

    //On affiche le terrain
    updateDisplay() ;
}

void MatriceGameGestion::gameLoop()
{
    Decision d ;
    while(d.decision() != DECISION_QUITTER)
    {
        d = m_player_list->at(0)->takeDecision(m_fenetre, *m_map, m_scroll)  ;
        if (!d.is_valid())
            warning_message("Player as return an invalid decision") ;
        else
            cout << d << endl ;
    }
}

void MatriceGameGestion::updateDisplay()
{
    m_fenetre.ajouter(m_map->getSurface()) ;
    m_fenetre.actualiser() ;
}

MatriceGameGestion::~MatriceGameGestion()
{
    //Suppression des joueurs de m_player_list
    while(!m_player_list->empty())
    {
        delete(m_player_list->back()) ;
        m_player_list->pop_back() ;
    }

    if (m_player_list!=NULL)
    {
        delete(m_player_list) ;
        m_player_list = NULL ;
    }
    

    //Suppression des menus de la mémoire de la matrice
    while(!m_saveMenu.empty())
    {
        delete(m_saveMenu.back()) ;
        m_saveMenu.pop_back() ;
    }

    //Suppression des boutons de la mémoire de la matrice
    while(!m_all_buttons->empty())
    {
        delete(m_all_buttons->back()) ;
        m_all_buttons->pop_back() ;
    }

    if (m_all_buttons!=NULL)
    {
        delete(m_all_buttons) ;
        m_all_buttons = NULL ;
    }

    delete(m_map) ;

}
#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../ID/idbuttons.h"
#include "../ID/idmenus.h"
#include "../CharactersClass/HumanPlayer.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500



MatriceGameGestion::MatriceGameGestion() :
    m_fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN),
    m_map (35,15)
{

        // Création de la matrice de gestion de jeu
    m_all_buttons = new vector<AbstractButton*> ;
    remplissage(m_all_buttons) ;

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


MatriceGameGestion::~MatriceGameGestion()
{
    for (unsigned short i = 0 ; i < m_all_buttons->size() ; i++)
    {
        delete (*m_all_buttons)[i] ;
    }
    delete m_all_buttons ;
    
    //Suppression des menus de la mémoire de la matrice
    for (unsigned short i = 0 ; i < m_saveMenu.size() ; i++)
    {
        delete(m_saveMenu[i]) ;
    }

    //Suppression des joueurs de la mémoire de la matrice
    for (unsigned short i = 0 ; i < m_player_list->size() ; i++)
    {
        cout << "delete " << i+1 << "/" << m_player_list->size() << endl ;
        delete (*m_player_list)[i] ;
    }
    delete m_player_list ;
}


void MatriceGameGestion::init()
{
    m_player_list = new std::vector <AbstractPlayer*> ;

    m_player_list->push_back(new HumanPlayer()) ;

    for (unsigned short i = 0 ; i < 10 && m_map.nb_free_pos() > 0 ; i++)
        m_map.add_unit( Unit("../ressources/catapult.bmp", m_map.random_free_pos(), m_player_list->at(0) )) ;
    
    for (unsigned short i = 0 ; i < 5 && m_map.nb_free_pos() > 0 ; i++)
        m_map.add_cons( Construction("../ressources/ground.bmp", m_map.random_free_pos(), m_player_list->at(0) )) ;

    for (unsigned short i = 0 ; i < 5 && m_map.nb_free_pos() > 0 ; i++)
    {
        MapPos pos (m_map.random_free_pos()) ;
        m_map.add_cons( Construction("../ressources/ground.bmp", pos, m_player_list->at(0) )) ;
        m_map.add_unit( Unit("../ressources/catapult.bmp", pos, m_player_list->at(0) )) ;
    }

    //On affiche le terrain
    m_fenetre.ajouter(m_map.getSurface()) ;
    m_fenetre.actualiser() ;
}

void MatriceGameGestion::gameLoop()
{
    m_player_list->at(0)->takeDecision(m_fenetre, m_map, m_scroll) ;
}

void MatriceGameGestion::updateDisplay()
{
    m_fenetre.ajouter(m_map.getSurface()) ;
    m_fenetre.actualiser() ;
}
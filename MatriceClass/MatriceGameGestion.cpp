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

    m_player_list->push_back(new HumanPlayer("testplayer", 0)) ;
    m_player_list->push_back(new HumanPlayer("ennemi", 1)) ;

    for (unsigned short i = 0 ; i < 10 && m_map->nb_free_pos() > 0 ; i++)
        m_map->add_unit( Unit(UNIT_CATAPULT,m_map->random_free_pos(),m_player_list->at(1) )) ;
    
    for (unsigned short i = 0 ; i < 5 && m_map->nb_free_pos() > 0 ; i++)
        m_map->add_cons( Construction(CONSTRUCTION_GROUND,m_map->random_free_pos(),m_player_list->at(0)) ) ;

    for (unsigned short i = 0 ; i < 5 && m_map->nb_free_pos() > 0 ; i++)
    {
        MapPos pos (m_map->random_free_pos()) ;
        m_map->add_cons( Construction(CONSTRUCTION_GROUND, pos, m_player_list->at(0)) ) ;
        m_map->add_unit( Unit(UNIT_CATAPULT,pos,m_player_list->at(0)) ) ;
    }

    Decision::init_list_of_choice() ;
}

void MatriceGameGestion::gameLoop()
{
    Texture selection_current_player ("../ressources/green_circle.bmp") ;
    Texture selection_enemy ("../ressources/red_circle.bmp") ;
    
    Decision d ;
    for( unsigned short i = 0 ; d.decision() != DECISION_QUITTER ; i= (i+1) % m_player_list->size())
    {
        m_current_player = m_player_list->at(i) ;
        updateDisplay() ; //On affiche la map
        while (d.decision() != DECISION_TOUR_SUIVANT && d.decision() != DECISION_QUITTER) // Tour d'un joueur
        {
            //Attente d'une decision de la part du joueur qu'il soit un Humain ou IA
            d = m_current_player->takeDecision(m_fenetre, *m_map, m_scroll)  ;

            //Traitement de la decision
            if (!d.is_valid())
                warning_message("Player as return an invalid decision") ;
            else
            {
                cout << d << endl ;
                if (d.decision() == DECISION_CHANGE_SELECT_UNIT) //NOUVELLE SELECTION
                {
                    AbstractPlayer* select ;
                    if (m_map->unit_on(d.target()) != NULL)
                        select = m_map->unit_on(d.target())->proprietaire() ;
                    else
                        select = m_map->cons_on(d.target())->proprietaire() ;
                    if (select != NULL)
                    {
                        SurfaceAffichage* selection_symbol ;
                        if (select == m_current_player)
                            selection_symbol = new SurfaceAffichage(selection_current_player) ;
                        else
                            selection_symbol = new SurfaceAffichage(selection_enemy) ;
                        selection_symbol->rendre_transparente() ;
                        m_map->delete_all_symbol() ;
                        m_map->add_symbol(*selection_symbol,d.target()) ;
                        delete(selection_symbol) ;
                        updateDisplay() ;
                    }
                    else
                        warning_message("Player as try to select unit or construction at empty pos") ;
                }
            }
        }
    }
}

void MatriceGameGestion::updateDisplay()
{
    m_fenetre.ajouter(m_map->getSurface(),&m_scroll,0,0) ;
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
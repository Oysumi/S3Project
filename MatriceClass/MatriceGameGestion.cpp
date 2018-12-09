#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../ID/idbuttons.h"
#include "../ID/idmenus.h"
#include "../PlayerClass/HumanPlayer.h"
#include "../MatriceClass/decisionID.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500


//Initialise le programme, fenetre, menus, boutons ...
MatriceGameGestion::MatriceGameGestion() :
    m_fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)
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

    //On initialise tous les choix possibles
    Decision::init_list_of_choice() ;

    //Représente la partie de la map affichée sur l'écran (par défaut en haut à gauche)
    m_scroll.x = 0 ;
    m_scroll.y = 0 ;
    m_scroll.h = SCREEN_HEIGHT ;
    m_scroll.w = SCREEN_WIDTH ;

}

//initialise la partie, génération du terrain, créations des unités et joueurs ...
void MatriceGameGestion::init()
{
    //Création de la map (et chargement de tout le terrain et etc...)
    m_map = new Map (50,25) ;

    //Création des joueurs de la partie
    m_player_list = new std::vector <AbstractPlayer*> ;
    m_player_list->push_back(new HumanPlayer("testplayer", 0)) ;
    m_player_list->push_back(new HumanPlayer("ennemi", 1)) ;

    //Création de quelques unités
    for (unsigned short i = 0 ; i < 10 && m_map->nb_free_pos() > 0 ; i++)
        m_map->add_unit( Unit(UNIT_CATAPULT,m_map->random_free_pos(),m_player_list->at(1) )) ;
    
    for (unsigned short i = 0 ; i < 2 && m_map->nb_free_pos() > 0 ; i++)
    {
        m_map->add_cons( Construction(CONSTRUCTION_CASTLE1,m_map->random_free_pos(),m_player_list->at(i)) ) ;
        m_map->add_cons( Construction(CONSTRUCTION_CASTLE2,m_map->random_free_pos(),m_player_list->at(i)) ) ;
        m_map->add_cons( Construction(CONSTRUCTION_ARCHERY1,m_map->random_free_pos(),m_player_list->at(i)) ) ;
        m_map->add_cons( Construction(CONSTRUCTION_ARCHERY2,m_map->random_free_pos(),m_player_list->at(i)) ) ;
        m_map->add_cons( Construction(CONSTRUCTION_FARM,m_map->random_free_pos(),m_player_list->at(i)) ) ;
        m_map->add_cons( Construction(CONSTRUCTION_TOWER,m_map->random_free_pos(),m_player_list->at(i)) ) ;
    }

    for (unsigned short i = 0 ; i < 5 && m_map->nb_free_pos() > 0 ; i++)
    {
        MapPos pos (m_map->random_free_pos()) ;
        m_map->add_cons( Construction(CONSTRUCTION_TOWER, pos, m_player_list->at(0)) ) ;
        m_map->add_unit( Unit(UNIT_CATAPULT,pos,m_player_list->at(0)) ) ;
    }

}

void MatriceGameGestion::gameLoop()
{
    init() ; //initialise la partie, génération du terrain, créations des unités et joueurs ...
    
    Decision d ;
    debugage_message("Début du Jeu") ;
    for( unsigned short i = 0 ; d.decision() != DECISION_QUITTER ; i= (i+1) % m_player_list->size())
    {
        m_current_player = m_player_list->at(i) ;
        m_current_selection = NULL ;
        m_map->delete_all_symbol() ; // On deselectionne l'unité en passant au joueur suivant
        updateDisplay() ; //On affiche la map

        while (d.decision() != DECISION_TOUR_SUIVANT && d.decision() != DECISION_QUITTER) // Tour d'un joueur
        {
            //Attente d'une decision de la part du joueur qu'il soit un Humain ou IA
            d = m_current_player->takeDecision(m_fenetre, *m_map, m_scroll)  ;

            //Traitement de la decision
            if (d.is_valid())
            {
                cout << d << endl ;
                if (d.decision() == DECISION_CHANGE_SELECT_UNIT) //NOUVELLE SELECTION
                {
                    if (new_selection(d.target()))
                    {
                        if(m_current_selection->type() == OBJECT_TYPE_UNIT)
                        {
                            cout << "traitement selection unité at " << m_current_selection->getPos() << endl ;
                            //Afficher les symboles pour indiquer les possible déplacement de l'unité
                        }
                        else if(m_current_selection->type() == OBJECT_TYPE_CONSTRUCTION)
                        {
                            cout << "traitement selection construction at " << m_current_selection->getPos() << endl ;

                            /*
                            ... Affichage d'un menu proposant plusieurs décisions possibles comme créer une catpaulte, ou rencforcer le chateau ...
                            */
                        }
                    }
                    else //La selection a la position demandée n'est pas possible
                        warning_message("Player as try to select unit or construction at empty pos") ;
                }

            }
            else // Le joueur n'a pas réellement pris de décision, ce n'est pas normal
                warning_message("Player as return an invalid decision") ;
        }
    }
}

bool MatriceGameGestion::new_selection(MapPos const pos)
{
    //On charge les symboles que la Matrice est susceptible de rajouter sur la Map
    Texture selection_current_player ("../ressources/green_circle.bmp") ;
    Texture selection_enemy ("../ressources/red_circle.bmp") ;

    MapObject* new_selection ;
    //Selection de la construction ou de l'unité ?
    if (m_map->unit_on(pos) != NULL)
        new_selection = m_map->unit_on(pos) ;
    if (m_map->cons_on(pos) != NULL) //Par défault c'est plutôt la construction de la case qui sera sélectionée (affection après <=> écraser)
        new_selection = m_map->cons_on(pos) ;
    //Mais si il y a une construction actuellement séléctionnée à cette position, le joueur tente de selectionner l'unité de cette case
    if (m_map->cons_on(pos) != NULL && m_map->cons_on(pos) == m_current_selection)
        new_selection = m_map->unit_on(pos) ;


    if (new_selection != NULL) // si il y a bien une unite ou une construction à cette position selectionee
    {
        // a quel joueur appartient l'unite ou la construction selectionnée ?
        AbstractPlayer* select_player = new_selection->proprietaire() ;

        SurfaceAffichage* selection_symbol ;
        if (select_player == m_current_player) // cette unite ou cette construction appartient t-elle au joueur en train de faire son tour ?
            selection_symbol = new SurfaceAffichage(selection_current_player) ;
        else
            selection_symbol = new SurfaceAffichage(selection_enemy) ;

        m_current_selection = new_selection ;
        // dans tous les cas on affiche le cercle de selection
        selection_symbol->rendre_transparente() ;
        m_map->delete_all_symbol() ;
        m_map->add_symbol(*selection_symbol,pos) ;
        delete(selection_symbol) ;
        updateDisplay() ;
        return true ;

    }
    return false ;
}

//Affiche simplement la partie de la map voulue (et définie par m_scroll) sur la fenetre du jeu
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
    //Suppresion du vecteur
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
    //Suppression du vecteur
    if (m_all_buttons!=NULL)
    {
        delete(m_all_buttons) ;
        m_all_buttons = NULL ;
    }

    //La map est supprimée de la mémoire
    delete(m_map) ;

}
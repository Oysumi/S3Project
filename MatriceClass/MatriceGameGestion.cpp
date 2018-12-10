#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../ID/idbuttons.h"
#include "../ID/idmenus.h"
#include "../PlayerClass/HumanPlayer.h"
#include "../MatriceClass/decisionID.h"
#include "../DisplayClass/Texte.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define SCROOL_ZONE 15
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500

#define BEGIN_GOLD 200
#define GOLD_AUGMENTATION 10
#define PRIX_CATAPULTE 500


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
    escapeButtons.push_back((*m_all_buttons)[AFFICHAGE]);
    escapeButtons.push_back((*m_all_buttons)[RETOUR]);
    escapeButtons.push_back((*m_all_buttons)[FIN_DU_TOUR]);
    escapeButtons.push_back((*m_all_buttons)[QUITTER]);
    unsigned short int x(SCREEN_WIDTH/2 - LARGEUR_MENU1/2), y(SCREEN_HEIGHT/6) ;
    m_saveMenu.push_back(new Menu (escapeButtons, x, y, font_menu, ESCAPE_MENU)) ;

    // Création et ajout dans la mémoire du menu prise de décision (attaquer, défendre, aller à, ...)
    vector<AbstractButton*> decisionButtons ;
    decisionButtons.push_back((*m_all_buttons)[ATTAQUER]);
    decisionButtons.push_back((*m_all_buttons)[DEFENDRE]);
    decisionButtons.push_back((*m_all_buttons)[ALLER_A]);
    decisionButtons.push_back((*m_all_buttons)[FERMER]);
    m_saveMenu.push_back(new Menu (decisionButtons, 0, 0, font_menu, ATTACK_MENU)) ;

    // Création et ajout dans le mémoire du menu création (construction, unité...)
    vector<AbstractButton*> constructionButtons ;
    constructionButtons.push_back((*m_all_buttons)[CREATION]);
    constructionButtons.push_back((*m_all_buttons)[CREER_UNITE]);
    constructionButtons.push_back((*m_all_buttons)[CREER_CONSTRUCTION]);
    m_saveMenu.push_back(new Menu (constructionButtons, 0, 500, font_menu, CREATION_MENU));
    
    // On initialise tous les choix possibles
    Decision::init_list_of_choice() ;
    m_current_selection = NULL ;

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
    m_map = new Map (30,15) ;

    //Création des joueurs de la partie
    m_player_list = new std::vector <AbstractPlayer*> ;
    addPlayer("player1") ;
    addPlayer("player2") ;

    m_current_player_turn = NULL ;
    m_tour = 0 ;

    m_fin_de_la_partie = false ;

}

void MatriceGameGestion::addPlayer(string name)
{
    m_player_list->push_back(new HumanPlayer(name, m_player_list->size())) ;
    m_player_gold[m_player_list->back()] = BEGIN_GOLD ;

    //Création de quelques unités
    for (unsigned short i = 0 ; i < 5 && m_map->nb_free_pos() > 0 ; i++)
        m_map->add_unit( Unit(UNIT_CATAPULT,m_map->random_free_pos(),m_player_list->back() )) ;
    
    //Création des batiments
    for (unsigned short type_construction = 0 ; type_construction < NB_TYPE_CONSTRUCTION && m_map->nb_free_pos() > 0 ; type_construction++)
    {
        MapPos pos (m_map->random_free_pos()) ;
        m_map->add_cons( Construction(type_construction, pos, m_player_list->back()) ) ;
        m_map->add_unit( Unit(UNIT_CATAPULT,pos,m_player_list->back()) ) ;
    }

}

void MatriceGameGestion::gameLoop()
{
    init() ; //initialise la partie, génération du terrain, créations des unités et joueurs ...
    
    Decision d ;
    debugage_message("Début du Jeu") ;
    for( unsigned short i = 0 ; d.decision() != DECISION_QUITTER && !m_fin_de_la_partie ; i= (i+1) % m_player_list->size())
    {
        if(i==0)
            m_tour ++ ;
        initNewTurn(m_player_list->at(i)) ;
        d = Decision() ; //No remet les décisions à zéro (=> éviter une boucle infine avec decision tour_suivant)
        while (d.decision() != DECISION_TOUR_SUIVANT && d.decision() != DECISION_QUITTER && !m_fin_de_la_partie ) // Tour d'un joueur
        {
            //Attente d'une decision de la part du joueur qu'il soit un Humain ou IA
            if (m_current_selection == NULL)
                m_current_selection = new Selection() ;
            d = m_current_player_turn->takeDecision(*m_map, *m_current_selection, m_fenetre, m_scroll)  ;


            if (!d.is_valid()) // Le joueur n'a pas réellement pris de décision, ce n'est pas normal
                warning_message("Player as return an invalid decision") ;
            else if (d.decision() == DECISION_UPDATE_GRAPHISME)
                updateDisplay() ;

            //Traitement des autres decisions
            else
            {
                cout << d << endl ;

                //SELECTION D'UNE NOUVELLE UNITE OU D'UNE NOUVELLE CONSTRUCTION
                if (d.decision() == DECISION_CHANGE_SELECT_UNIT)
                    if (new_selection(d.target()))
                    {
                        if(m_current_selection->type() == OBJECT_TYPE_UNIT)
                            selection_unit() ;
                        else if(m_current_selection->type() == OBJECT_TYPE_CONSTRUCTION)
                        {
                            /*
                            ... Affichage d'un menu proposant plusieurs boutons permeetant de créer une catpaulte, de rencforcer le chateau, sa production en or ...
                            */
                        }
                        updateDisplay() ;
                    }
                    else //La selection a la position demandée n'est pas possible
                        warning_message("Player as try to select unit or construction at empty pos") ;


                //DEPLACEMENT DE L'UNITE SELECTIONNE
                else if (d.decision() == DECISION_MOVE_SELECT_UNIT)
                {
                    if (validSelection(OBJECT_TYPE_UNIT))
                    {
                        if (m_current_selection->unit()->proprietaire() == m_current_player_turn)
                        {
                            MapPos const pos (d.target()) ;
                            bool attaque = false ;
                            if (m_map->have_unit_on(pos)) //Si il y a une unité énnemie
                                if(m_map->unit_on(pos)->proprietaire() != m_current_player_turn)
                                    attaque = true ;

                            //LE SIEGE EST LA DESTRUCTION D'UNE UNITE DANS UNE CONSTRUCTION ENNEMIE
                            bool siege = false ;

                            if (attaque && m_map->have_cons_on(pos)) //Si on est en terrain ennemi
                                if (m_map->cons_on(pos)->proprietaire() != m_current_player_turn)
                                    siege = true ;

                            if (m_map->move_unit_at(m_current_selection->getPos(), pos, attaque))
                            {

                                if(siege) // En cas de siege on perd son unité
                                {
                                    m_map->del_unit(*m_map->unit_on(pos)) ;
                                    //Donc déselection
                                    deleteSelection() ;
                                }
                                else
                                {
                                    if(!siege && m_map->have_cons_on(pos))
                                    {
                                        m_map->cons_on(pos)->capture_by(m_current_player_turn) ;
                                        verification_defaite() ;
                                    }

                                    new_selection(m_current_selection->getPos(), true) ;
                                    selection_unit() ;
                                }

                                updateDisplay() ;
                            } 
                            else
                                warning_message("Player as try to move select unit at invalid position") ;
                        }
                        else
                            warning_message("Player as try to move unit of another player") ;
                    }
                    else
                        warning_message("Player as try to move select unit, but not unit selected") ;
                }
            }
        }
    }
}

void MatriceGameGestion::verification_defaite()
{
    unsigned short nb_construction ;
    for(unsigned short i = 0 ; i < m_player_list->size() ; i++)
    {
        nb_construction = m_map->nb_construction_of(m_player_list->at(i)) ;
        cout << "Le joueur " << m_player_list->at(i)->name() << " a encore " << nb_construction << " constructions " << endl ;
        
        if (nb_construction<=0)
        {
            cout << endl << " ------------------------ " << endl ;
            cout << m_player_list->at(i)->name() << " A PEDRU !!!" << endl ;
            cout << " ------------------------ " << endl ;
            m_fin_de_la_partie = true ;
        }
    }
}

void MatriceGameGestion::initNewTurn(AbstractPlayer* new_current_player)
{
    if(m_current_player_turn != NULL)
        m_player_gold[m_current_player_turn] += GOLD_AUGMENTATION*m_map->nb_construction_of(m_current_player_turn) ;

    if (m_player_gold[m_current_player_turn] >= PRIX_CATAPULTE && m_map->nb_free_pos() > 0)
    {
        m_map->add_unit( Unit(UNIT_CATAPULT,m_map->random_free_pos(),m_current_player_turn)) ;
        m_player_gold[m_current_player_turn] -= PRIX_CATAPULTE ;
    }

    m_current_player_turn = new_current_player ;
    m_map->reset_deplacement_all_unit (); //Les unités peuvent de nouveaux se déplacer
    deleteSelection() ; // On deselectionne l'unité en passant au joueur suivant
    m_saveMenu[0]->setTextButton(0,"tour " + to_string(m_tour) + " de " + m_current_player_turn->name()) ;
    updateDisplay() ; //On affiche la map
}

bool MatriceGameGestion::new_selection(MapPos const pos, bool force_unit)
{
    //On charge les symboles que la Matrice est susceptible de rajouter sur la Map
    Texture selection_current_player ("../ressources/green_circle.bmp") ;
    Texture selection_enemy ("../ressources/red_circle.bmp") ;

    MapObject* new_selection ;
    //Selection de la construction ou de l'unité ?
    if (m_map->unit_on(pos) != NULL)
        new_selection = m_map->unit_on(pos) ;
    if (m_map->cons_on(pos) != NULL && !force_unit) //Par défault c'est plutôt la construction de la case qui sera sélectionée (affection après <=> écraser)
        new_selection = m_map->cons_on(pos) ;
    //Mais si il y a une construction actuellement séléctionnée à cette position, le joueur tente de selectionner l'unité de cette case
    if (m_map->cons_on(pos) != NULL && m_current_selection != NULL)
        if (m_map->cons_on(pos) == m_current_selection->value())
            new_selection = m_map->unit_on(pos) ;


    if (new_selection != NULL) // si il y a bien une unite ou une construction à cette position selectionee
    {
        // a quel joueur appartient l'unite ou la construction selectionnée ?
        AbstractPlayer* select_player = new_selection->proprietaire() ;

        SurfaceAffichage* selection_symbol ;
        if (select_player == m_current_player_turn) // cette unite ou cette construction appartient t-elle au joueur en train de faire son tour ?
            selection_symbol = new SurfaceAffichage(selection_current_player) ;
        else
            selection_symbol = new SurfaceAffichage(selection_enemy) ;

        m_current_selection = new Selection(new_selection) ;

        // dans tous les cas on affiche le cercle de selection
        selection_symbol->rendre_transparente() ;
        m_map->delete_all_symbol() ;
        m_map->add_symbol(*selection_symbol,pos) ;
        delete(selection_symbol) ;
        return true ;

    }
    return false ;
}

void MatriceGameGestion::selection_unit()
{
    SurfaceAffichage deplacement (Texture("../ressources/green_circle.bmp")) ;
    SurfaceAffichage attaque (Texture("../ressources/red_circle.bmp")) ;
    deplacement.rendre_transparente() ;
    attaque.rendre_transparente() ;

    if (validSelection(OBJECT_TYPE_UNIT))
        if (m_current_selection->unit()->proprietaire() == m_current_player_turn)
        {

            MapPos const pos(m_current_selection->getPos()), out(m_map->posOut()) ;
            vector <MapPos> adjacent ;

            if(m_current_selection->unit()->canMove())
            {
                if (pos.x() > 0)
                    adjacent.push_back(MapPos(pos.x()-1,pos.y())) ;
                if (pos.x()+1 < out.x())
                    adjacent.push_back(MapPos(pos.x()+1,pos.y())) ;
                if (pos.y() > 0)
                    adjacent.push_back(MapPos(pos.x(),pos.y()-1)) ;
                if (pos.y()+1 < out.y())
                    adjacent.push_back(MapPos(pos.x(),pos.y()+1)) ;

                MapPos pos (0,0) ;
                for (unsigned short i = 0 ; i < adjacent.size() ; i++)
                    if (m_map->terrain_adapt_to_unit(adjacent[i], m_current_selection->seeUnit()))
                    {
                        pos = adjacent[i] ;
                        if(!m_map->have_unit_on(pos))
                        {
                            m_current_selection->add_possible_move_for_select_unit(pos) ; //Mise à jour des déplacement possible pour le joueur
                            m_map->add_symbol(deplacement, pos) ; //Et affichage
                        }
                        else if (m_map->unit_on(pos)->proprietaire() != m_current_player_turn)
                        {
                            m_current_selection->add_possible_move_for_select_unit(pos) ; //Mise à jour des déplacement possible pour le joueur
                            m_map->add_symbol(attaque, pos) ; //Et affichage en rouge
                        }
                    }
            }
        }
}

//Affiche simplement la partie de la map voulue (et définie par m_scroll) sur la fenetre du jeu
void MatriceGameGestion::updateDisplay()
{
    m_fenetre.ajouter(m_map->getSurface(),&m_scroll,0,0) ;
    if (validSelection(OBJECT_TYPE_UNIT))
        m_fenetre.ajouter(Texte(string("Catapulte de "+m_current_selection->proprietaire_objet()->name())).surfaceAffichage(), 0, SCREEN_HEIGHT - 30) ;
    if (validSelection(OBJECT_TYPE_CONSTRUCTION))
        m_fenetre.ajouter(Texte(string("Construction de "+m_current_selection->proprietaire_objet()->name())).surfaceAffichage(), 0, SCREEN_HEIGHT - 30) ;
    SurfaceAffichage gold ("../ressources/metal.bmp") ;
    gold.rendre_transparente() ;
    m_fenetre.ajouter(gold,1,0) ;
    m_fenetre.ajouter(Texte(std::to_string(m_player_gold[m_current_player_turn]),SDL_Color({252, 210, 28})).surfaceAffichage(), 72, 1) ;
    if (Menu::isAMenuOpened())
        Menu::keepOpened(m_fenetre);
    m_fenetre.actualiser() ;
}

bool MatriceGameGestion::validSelection(short type) const
{
    if (m_current_selection == NULL)
        return false ;
    if (!m_current_selection->valid())
        return false ;
    if (type < 0)
        return true ;
    return type == m_current_selection->type() ;
}

void MatriceGameGestion::deleteSelection()
{
    if (m_current_selection != NULL)
    {
        delete(m_current_selection) ;
        m_current_selection = NULL ;
        m_map->delete_all_symbol() ;
    }
}

MatriceGameGestion::~MatriceGameGestion()
{
    deleteSelection() ;

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
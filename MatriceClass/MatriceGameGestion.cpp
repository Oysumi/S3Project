#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../PlayerClass/HumanPlayer.h"
#include "../DisplayClass/Texte.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAP_WIDTH 20
#define MAP_HEIGHT 15

#define SCROOL_ZONE 50
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500

#define BEGIN_GOLD 200
#define GOLD_AUGMENTATION 10
#define PRIX_CATAPULTE 500

#define SMALL_FONT 18


//Initialise le programme, fenetre, menus, boutons ...
MatriceGameGestion::MatriceGameGestion() :
    m_fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)
{
    // Création des boutons
    m_all_buttons = AbstractButton::getAllButton() ;
    m_saveMenu = Menu::getAllMenu(*m_all_buttons, SCREEN_WIDTH, SCREEN_HEIGHT) ;
    
    
    // On initialise tous les choix possibles
    Decision::init_list_of_choice() ;
    m_current_selection = NULL ;

    debugage_message("Matrice construite") ;

}

//initialise la partie, génération du terrain, créations des unités et joueurs ...
void MatriceGameGestion::init()
{
    //Création de la map (et chargement de tout le terrain et etc...)
    //On adapate la taille de la Map pour qu'elle remplisse la fenetre si besoin !
    m_map = new Map ( (MAP_WIDTH*MAP_CASE_SIZE > SCREEN_WIDTH) ? MAP_WIDTH : 2+SCREEN_WIDTH/MAP_CASE_SIZE,
        (MAP_HEIGHT*MAP_CASE_SIZE > SCREEN_HEIGHT) ? MAP_HEIGHT : 2+SCREEN_HEIGHT/MAP_CASE_SIZE ) ;

    //Création des joueurs de la partie
    m_player_list = new std::vector <AbstractPlayer*> ;
    addPlayer("player1") ;
    addPlayer("player2") ;

    m_current_player_turn = NULL ;
    m_tour = 0 ;

    m_fin_de_la_partie = false ;

    debugage_message("Matrice initialisée pour une partie") ;
}

void MatriceGameGestion::addPlayer(string name)
{
    m_player_list->push_back(new HumanPlayer(name, m_player_list->size())) ;
    m_player_gold[m_player_list->back()] = BEGIN_GOLD ;

    //Création de quelques unités
    for (unsigned short type = 0 ; type < NB_TYPE_UNIT && m_map->nb_free_pos() > 0 ; type++)
        m_map->add_unit( Unit(type,m_map->random_free_pos(),m_player_list->back() )) ;
    
    //Création des batiments
    for (unsigned short type_construction = 0 ; type_construction < NB_TYPE_CONSTRUCTION && m_map->nb_free_pos() > 0 ; type_construction++)
    {
        MapPos pos (m_map->random_free_pos()) ;
        m_map->add_cons( Construction(type_construction, pos, m_player_list->back()) ) ;
        m_map->add_unit( Unit(rand()%NB_TYPE_UNIT,pos,m_player_list->back()) ) ; //On ajoute aléatoirement une unité sur la map
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
        debugage_message("Début du tour de " + m_current_player_turn->name()) ;
        d = Decision() ; //No remet les décisions à zéro (=> éviter une boucle infine avec decision tour_suivant)
        while (d.decision() != DECISION_TOUR_SUIVANT && d.decision() != DECISION_QUITTER && !m_fin_de_la_partie ) // Tour d'un joueur
        {
            //Attente d'une decision de la part du joueur qu'il soit un Humain ou IA
            debugage_message("En attente d'une decision de " + m_current_player_turn->name()) ;
            if (m_current_selection == NULL)
                m_current_selection = new Selection() ;
            d = m_current_player_turn->takeDecision(*m_map, *m_current_selection, m_fenetre)  ;
            debugage_message("Décison : " + to_string(d.decision()) + " / valide :" + to_string(d.is_valid())) ;

            if (!d.is_valid()) // Le joueur n'a pas réellement pris de décision, ce n'est pas normal
                warning_message("Player as return an invalid decision") ;

            //Traitement des autres decisions
            else
            {
                //SELECTION D'UNE NOUVELLE UNITE OU D'UNE NOUVELLE CONSTRUCTION
                if (d.decision() == DECISION_CHANGE_SELECT_UNIT)
                    if (new_selection(d.target()))
                    {
                        if(m_current_selection->type() == OBJECT_TYPE_UNIT)
                            selection_unit() ;
                        else if(validSelection(OBJECT_TYPE_CONSTRUCTION, m_current_player_turn))
                        {
                            if (!Menu::getMenuById(CHATEAU_MENU)->isOpen())
                                Menu::openMenu(CHATEAU_MENU, m_fenetre) ;
                        }
                    }
                    else //La selection a la position demandée n'est pas possible
                        warning_message("Player as try to select unit or construction at empty pos") ;


                //DEPLACEMENT DE L'UNITE SELECTIONNE
                else if (d.decision() == DECISION_MOVE_SELECT_UNIT)
                {
                    if (isAnAttack(d.target()))
                    {
                        if (attaque(d.target())) //Si l'unité à gagné on déplace le vainqueur avec supression de la précedente
                            move_select_unit(d.target(),true) ;
                        else
                            new_selection(m_current_selection->getPos(),true) ;
                    }
                    else
                        move_select_unit(d.target()) ;
                }

                else if (d.decision() == DECISION_CONSTRUIRE_UNIT)
                {
                    if(m_map->canConstructAt(d.target(), m_current_player_turn) && m_map->terrain_adapt_to_unit(d.target()))
                        m_map->add_unit( Unit(d.id()%NB_TYPE_UNIT,d.target(),m_current_player_turn) ) ;
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
        if (nb_construction<=0)
        {
            cout << " ------------------------ " << endl ;
            cout << " VICTOIRE DE " << m_player_list->at((i+1)%2)->name() << " !!!" << endl ;
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
    m_saveMenu->at(0)->setTextButton(m_fenetre, 0,"tour " + to_string(m_tour) + " de " + m_current_player_turn->name(), "04B-30") ;
}

bool MatriceGameGestion::new_selection(MapPos const pos, bool force_unit)
{

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
        deleteSelection() ; //Supression de l'ancienne selection
        m_current_selection = new Selection(new_selection) ;
        return true ;
    }
    return false ;
}

void MatriceGameGestion::selection_unit()
{
    if (validSelection(OBJECT_TYPE_UNIT, m_current_player_turn))
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
                        m_current_selection->add_possible_move_for_select_unit(pos) ; //Mise à jour des déplacement possible pour le joueur
                    else if (m_map->unit_on(pos)->proprietaire() != m_current_player_turn)
                        m_current_selection->add_possible_move_for_select_unit(pos) ; //Mise à jour des déplacement possible pour le joueur
                }
        }
    }
}

void MatriceGameGestion::move_select_unit(MapPos const& pos, bool afterVictoryAttack)
{
    if (validSelection(OBJECT_TYPE_UNIT), m_current_player_turn)
    {
        //LE SIEGE EST LA DESTRUCTION D'UNE UNITE DANS UNE CONSTRUCTION ENNEMIE
        bool siege = false ;
        if (afterVictoryAttack && m_map->have_cons_on(pos)) //Si on est en terrain ennemi
            if (m_map->cons_on(pos)->proprietaire() != m_current_player_turn)
                siege = true ;

        if (m_map->move_unit_at(m_current_selection->getPos(), pos, afterVictoryAttack))
        {

            if(siege) // En cas de siege on perd son unité
            {
                deleteSelection() ; //Donc déselection
                m_map->del_unit(*m_map->unit_on(pos)) ;
            }
            else
            {
                if(!siege && m_map->have_cons_on(pos)) //CAPTURE DE LA CONSTRUCTION
                {
                    m_map->cons_on(pos)->capture_by(m_current_player_turn) ;
                    verification_defaite() ;
                }

                new_selection(m_current_selection->getPos(), true) ;
                selection_unit() ;
            }
        } 
        else
            warning_message("Player as try to move select unit at invalid position") ;
    }
    else
        warning_message("Matrice as try to move but not player unit are selected") ;
}

//Is an attack ?
bool MatriceGameGestion::isAnAttack(MapPos const& target) const
{
    //Une unité nous appartenant est séléctionnée ?
    if ((validSelection(OBJECT_TYPE_UNIT), m_current_player_turn))
    {
        //La position à attaquer est elle suffisament proche ?
        if (m_current_selection->unit()->canAttack_at(target))
        {
            //Y a t'il une unité adverse à attaquer
            if (m_map->have_unit_on(target)) //Si il y a une unité énnemie
                if(m_map->unit_on(target)->proprietaire() != m_current_player_turn)
                    return true ;
            return false ;
        }
        else
            return false ;
    }
    else
        return false ;
}

//Retourne vrai en cas de victoire de l'attaque
bool MatriceGameGestion::attaque(MapPos const& target)
{
    if (isAnAttack(target))
    {
        cout << "attaque" << endl ;
        Unit* defenseur = m_map->unit_on(target) ;
        defenseur->subirAttaque(m_current_selection->unit()) ;
        return defenseur->isDead() ;
    }
    else
    {
        erreur_message("Matrice try an invalid attack") ;
        return false ;
    }
}

//Gestion de la création et du stockage du texte affiché qui est très souvent le même pour ne pas charger sans cesse les mêmes graphismes
void MatriceGameGestion::afficherTexte(string text, unsigned short w, unsigned short h, SDL_Color color)
{
    if(m_load_text.find(text) == m_load_text.end())
        m_load_text[text] = new Texte(text, color) ;
    m_fenetre.ajouter(m_load_text[text]->surfaceAffichage(), w, h) ; 
}

void MatriceGameGestion::clearLoadTexte()
{
    for (map<std::string,Texte*>::iterator it = m_load_text.begin() ; it != m_load_text.end() ; it++)
        delete(it->second) ;
    m_load_text.clear() ;
}

//Renvoi vrai si un objet du bon type appartient à proprietaire
bool MatriceGameGestion::validSelection(short type, AbstractPlayer* proprietaire) const
{
    if (m_current_selection == NULL)
        return false ;
    if (!m_current_selection->valid())
        return false ;
    if (type < 0 && proprietaire == NULL)
        return true ;
    return (proprietaire == NULL || proprietaire==m_current_selection->proprietaire_objet())
        && (type < 0 || type==m_current_selection->type()) ;
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
    clearLoadTexte() ;

    //Suppression des joueurs de m_player_list
    while(!m_player_list->empty())
    {
        if(m_player_list->back()!=NULL)
            delete(m_player_list->back()) ;
        else
            warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_list_player->back() in ~MatriceGameGestion()") ;
        m_player_list->pop_back() ;
    }

    //Suppresion du vecteur
    if (m_player_list!=NULL)
    {
        delete(m_player_list) ;
        m_player_list = NULL ;
    }
    else
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_list_player in ~MatriceGameGestion()") ;
    
    //Suppression des menus de la mémoire de la matrice
    while(!m_saveMenu->empty())
    {
        if(m_saveMenu->back() != NULL)
            delete(m_saveMenu->back()) ;
        else
            warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_saveMenu->back() in ~MatriceGameGestion()") ;
        m_saveMenu->pop_back() ;
    }

    //Suppression du vecteur
    if (m_saveMenu!=NULL)
    {
        delete(m_saveMenu) ;
        m_saveMenu = NULL ;
    }
    else 
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_saveMenu in ~MatriceGameGestion()") ;

    //Suppression des boutons de la mémoire de la matrice
    while(!m_all_buttons->empty())
    {
        if (m_all_buttons->back() != NULL)
            delete(m_all_buttons->back()) ;
        m_all_buttons->pop_back() ;
    }

    //Suppression du vecteur
    if (m_all_buttons!=NULL)
    {
        delete(m_all_buttons) ;
        m_all_buttons = NULL ;
    }
    else 
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_all_buttons in ~MatriceGameGestion()") ;

    //La map est supprimée de la mémoire
    if(m_map != NULL)
    {
        delete(m_map) ;
        m_map = NULL ;
    }
    else
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_map in ~MatriceGameGestion()") ;


}
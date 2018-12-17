#include "MatriceGameGestion.h"
#include "../MenuClass/ActionButton.h"
#include "../MenuClass/AbstractButton.h"
#include "../PlayerClass/HumanPlayer.h"
#include "../DisplayClass/Texte.h"

#include <iostream>

using namespace std;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MAP_WIDTH 25
#define MAP_HEIGHT 15

#define SCROOL_ZONE 50
#define TIME_BETWEEN_SCROLL_CHANGE 5
#define TIME_LIMIT_TO_DISPLAY_MENU 500

#define BEGIN_GOLD 50
#define GOLD_AUGMENTATION 100
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
    debugage_message("Construction de la map terminée") ;

    //Création des joueurs de la partie
    m_player_list = new std::vector <AbstractPlayer*> ;
    addPlayer("Antoine") ;
    addPlayer("Alexis") ;
    debugage_message("Ajout des joueurs") ;


    m_current_player_turn = NULL ;
    m_tour = 0 ;
    m_fin_de_la_partie = false ;

    debugage_message("Matrice initialisée pour une partie") ;
}

//ENSEMBLE DES AMELIORATIONS
void MatriceGameGestion::set_upgrades_for_last_player_add()
{
    add_upgrades(DEPLACEMENTPLUS,Ressource(1500,0,0)) ;
    add_upgrades(MOREDEGATS,Ressource(1500,0,0)) ;
    add_upgrades(MOREGOLD,Ressource(1250,0,0)) ;
    add_upgrades(MOREDEFENSE,Ressource(1600,0,0)) ;
}

//AJOUT ET INITIALISATION D'UN JOUEUR
void MatriceGameGestion::addPlayer(string name)
{
    m_player_list->push_back(new HumanPlayer(name, m_player_list->size())) ;

    //Création de quelques unités
    //for (unsigned short type = 0 ; type < 1 && m_map->nb_free_pos() > 0 ; type++)
        //m_map->add_unit( Unit(type,m_map->random_free_pos(),m_player_list->back() )) ;
    
    //Création des batiments
    m_map->add_cons( Construction(CONSTRUCTION_CHATEAU1, m_map->random_free_pos(), m_player_list->back()) ) ;

    m_ressource[m_player_list->back()] = Ressource(BEGIN_GOLD,0,m_map->ressourceApport(m_player_list->back()).food()) ;

    set_upgrades_for_last_player_add() ;

    debugage_message("ajout du joueur " + name) ;
}

void MatriceGameGestion::gameLoop()
{
    init() ; //initialise la partie, génération du terrain, créations des unités et joueurs ...
    
    Decision d ;
    int compteur_capture_ecran = 0 ;
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

            //On attends la décision du joueur
            d = m_current_player_turn->takeDecision(*m_map, *m_current_selection, m_ressource[m_current_player_turn], upgradesOf(m_current_player_turn), m_fenetre)  ;
            
            debugage_message("Décison : " + to_string(d.decision()) + " / valide :" + to_string(d.is_valid())) ;

            if (!d.is_valid()) // Le joueur n'a pas réellement pris de décision, ce n'est pas normal
                warning_message("Player as return an invalid decision") ;

            //Traitement des autres decisions
            else
            {
                //SELECTION D'UNE NOUVELLE UNITE OU D'UNE NOUVELLE CONSTRUCTION
                if (d.decision() == DECISION_CHANGE_SELECT_UNIT)
                {
                    if (new_selection(d.target()))
                    {
                        if(m_current_selection->type() == OBJECT_TYPE_UNIT)
                            selection_unit() ;
                    }
                    //La selection a la position demandée n'est pas possible
                    //else warning_message("Player as try to select unit or construction at empty pos") ;
                }

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

                //CONSTRUCTION D'UNE UNITE
                else if (d.decision() == DECISION_CONSTRUIRE_UNIT)
                {
                    build_unit(d) ;
                }

                //CONSTRUCTION D'UN BATIMENT
                else if (d.decision() == DECISION_CONSTRUIRE_BATIMENT)
                {
                    build_cons(d) ;
                }

                else if (d.decision() == DECISION_AMELIORER_BATIMENT)
                {
                    if(validSelection(OBJECT_TYPE_CONSTRUCTION, m_current_player_turn))
                    {
                        if (m_current_selection->seeConstruction().canDoAction())
                        {
                            bool upgrade = true ;
                            Construction* cons = m_current_selection->construction() ;
                            if(d.id() == UP_GOLD)
                                cons->up_apport(Ressource(1,0,0)) ;
                            else if(d.id() == UP_WOOD)
                                cons->up_apport(Ressource(0,1,0)) ;
                            else if(d.id() == UP_FOOD)
                                cons->up_apport(Ressource(0,0,1)) ;
                            else if(d.id() == UP_DEFENSE && cons->defense() < cons->defense_max())
                                cons->up_defense(2) ;
                            else
                                upgrade = false ;

                            if (upgrade)
                                cons->noMoreAction() ;
                        }
                        else
                            warning_message("Player have try to upgrades construction but upgrade is define for this turn") ;
                    }
                    else
                        warning_message("Player have try to upgrades selection but it's not construction of player current turn") ;
                }

                else if (d.decision() == DECISION_AMELIORATION_UNIT)
                {
                    new_upgrade(d,OBJECT_TYPE_UNIT) ;  
                }

                else if (d.decision() == DECISION_AMELIORATION_CONS)
                {
                    new_upgrade(d,OBJECT_TYPE_CONSTRUCTION) ;  
                }

                else if (d.decision() == DECISION_ENREGISTRER)
                {
                    std::ofstream m_fichier ("terrain.txt") ;
                    m_fichier << m_map->terrain_to_string() << endl ;
                    m_fichier.close() ;
                }

                else if (d.decision() == DECISION_CAPTURE)
                {
                    compteur_capture_ecran++ ;
                    m_map->getSurface().saveBMP("capture" + to_string(compteur_capture_ecran)) ;
                }

                //On met à jour la nourriture / population
                m_ressource[m_current_player_turn].set_food(m_map->ressourceApport(m_current_player_turn).food()) ;
                
            }
        }
    }
}

//VERIFICATION DE LA DEFAITE
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

//INITIALISATION DU TOUR D'UN JOUEUR
void MatriceGameGestion::initNewTurn(AbstractPlayer* new_current_player)
{
    if(m_current_player_turn != NULL)
    {
        //On ajoute les ressources au précédent, car il a fini son tour
        Ressource apport (m_map->ressourceApport(m_current_player_turn)) ;
        apport.set_food(0) ;
        m_ressource[m_current_player_turn] += apport ;
        m_ressource[m_current_player_turn].set_food(m_map->ressourceApport(m_current_player_turn).food()) ;
    }

    //On supprime les symbole que le joueurs précéédents à ajouté à la map
    m_map->delete_all_symbol() ;

    m_current_player_turn = new_current_player ;
    m_map->reset_player_object() ; //Les unités peuvent de nouveaux se déplacer et les batiments construire
    deleteSelection() ; // On deselectionne l'unité en passant au joueur suivant
    m_saveMenu->at(0)->setTextButton(0,"tour " + to_string(m_tour) + " de " + m_current_player_turn->name(), "04B-30") ;
}

//CONSTRUCTION D'UN BATIMENT
bool MatriceGameGestion::build_cons (Decision const& d)
{
    if (selectionCanConstruct(OBJECT_TYPE_CONSTRUCTION))
    {
        if(m_map->canConstructAt(d.target(), m_current_player_turn)
        && m_map->terrain_adapt_to_unit(d.target())
        && Construction::canBuyWith(d.id(), m_ressource[m_current_player_turn], m_map->population(m_current_player_turn)))
        {
            m_map->add_cons( Construction(d.id(),d.target(),m_current_player_turn)) ;
            if (player_have_upgrade(MOREGOLD))
            {
                m_map->cons_on(d.target())->up_apport(Ressource(15,0,0)) ;
            }
            if (player_have_upgrade(MOREDEFENSE))
            {
                m_map->cons_on(d.target())->up_defense_max(10) ;
                m_map->cons_on(d.target())->up_defense(10) ;
            }
            m_ressource[m_current_player_turn].del_gold(Construction::prix(d.id()).gold()) ;
            m_ressource[m_current_player_turn].del_wood(Construction::prix(d.id()).wood()) ;
            m_current_selection->construction()->noMoreAction() ;
            return true ;
        }
    }
    return false ;
}

//CONSTRUCTION D'UNE UNITE
bool MatriceGameGestion::build_unit (Decision const& d)
{
    if (selectionCanConstruct(OBJECT_TYPE_UNIT))
    {
        if(m_map->canConstructAt(d.target(), m_current_player_turn)
        && m_map->terrain_adapt_to_unit(d.target())
        && Unit::canBuyWith(d.id(), m_ressource[m_current_player_turn], m_map->population(m_current_player_turn)))
        {
            m_map->add_unit( Unit(d.id(),d.target(),m_current_player_turn)) ;
            if (player_have_upgrade(MOREDEGATS))
                m_map->unit_on(d.target())->up_degats(15) ;
            m_ressource[m_current_player_turn].del_gold(Unit::prix(d.id()).gold()) ;
            m_ressource[m_current_player_turn].del_wood(Unit::prix(d.id()).wood()) ;
            m_current_selection->construction()->noMoreAction() ;
            return true ;
        }
    }
    return false ;
}

//NOUVELLE AMELIORATION
bool MatriceGameGestion::new_upgrade(Decision const d, unsigned short object_type)
{
    if (selectionCanConstruct(object_type)) //Si ce batiment permet de construire des unités
    {
        if ((object_type == OBJECT_TYPE_UNIT && m_current_selection->seeConstruction().constructionType() == CONSTRUCTION_ATELIER2)
        ||  (object_type == OBJECT_TYPE_CONSTRUCTION && m_current_selection->seeConstruction().constructionType() == CONSTRUCTION_CHATEAU2))
        {
            if (m_upgrades.find(make_pair(m_current_player_turn, d.id())) != m_upgrades.end())
            {
                pair <Ressource, bool> upgrade_info = m_upgrades[make_pair(m_current_player_turn, d.id())] ;
                if (!upgrade_info.second
                  && upgrade_info.first.gold() <= m_ressource[m_current_player_turn].gold()
                  && upgrade_info.first.wood() <= m_ressource[m_current_player_turn].wood())
                {
                    //Amélioration effectuée
                    debugage_message(m_current_player_turn->name() + " have do upgrade with id " + to_string(d.id())) ;
                    m_upgrades[make_pair(m_current_player_turn, d.id())].second = true ;
                    m_ressource[m_current_player_turn].del_gold(upgrade_info.first.gold()) ;
                    m_ressource[m_current_player_turn].del_wood(upgrade_info.first.wood()) ;
                    apply_upgrades(d.id()) ;
                    m_current_selection->construction()->noMoreAction() ;
                    return true ;
                }
                else
                {
                    warning_message("Player have try to do upgrades but no have ressources or upgrades already made") ;
                    return false ;
                }
            }
            else
            {
                warning_message("Player try to do an existant upgrade") ;
                return false ;
            }
        }
    }
    warning_message("Player have try to do upgrade with incorrect selection") ;
    return false ;
}

//LA SELECTION ACTUELLE PERMET TELLE DE CONSTRUIRE UNE UNITE OU UN BATIMENT
bool MatriceGameGestion::selectionCanConstruct(unsigned short object_type)
{
    if(validSelection(OBJECT_TYPE_CONSTRUCTION, m_current_player_turn))
    {
        Construction const cons (m_current_selection->seeConstruction()) ;
        unsigned short batiment = cons.constructionType() ;
        if (cons.canDoAction())
            return   // Il faut un chateau pour faire un batiment
                (object_type == OBJECT_TYPE_CONSTRUCTION &&
                (batiment == CONSTRUCTION_CHATEAU1 || batiment == CONSTRUCTION_CHATEAU2))
                ||   // Ou un atelier pour une unitée
                (object_type == OBJECT_TYPE_UNIT &&
                (batiment == CONSTRUCTION_ATELIER1 || batiment == CONSTRUCTION_ATELIER2)) ;
    }
    return false ;
}

//NOUVELLE SELECTION
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

//LA NOUVELLE SELECTION EST UNE UNITE, ON REGARDE DU COTE DES DEPLACEMENTS
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

        if (player_have_upgrade(DEPLACEMENTPLUS)) //On ajoute les cases en diagonale
        {
            if (pos.x() > 0 && pos.y() > 0)
                adjacent.push_back(MapPos(pos.x()-1,pos.y()-1)) ;
            if (pos.x()+1 < out.x() && pos.y()+1 < out.y())
                adjacent.push_back(MapPos(pos.x()+1,pos.y()+1)) ;
            if (pos.x()+1 < out.x() && pos.y() > 0)
                adjacent.push_back(MapPos(pos.x()+1,pos.y()-1)) ;
            if (pos.x() > 0 && pos.y()+1 < out.y())
                adjacent.push_back(MapPos(pos.x()-1,pos.y()+1)) ;
        }

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

//FAIRE BOUGER UNE UNITE A UNE POSITION. SI ELLE EST OCCUPÉE PAR UN ENNEMI, C'EST UNE ATTAQUE
void MatriceGameGestion::move_select_unit(MapPos const& pos, bool afterVictoryAttack)
{
    if (validSelection(OBJECT_TYPE_UNIT), m_current_player_turn)
    {
        //LE SIEGE EST LA DESTRUCTION D'UNE UNITE DANS UNE CONSTRUCTION ENNEMIE
        bool siege = false ;
        if (afterVictoryAttack && m_map->have_cons_on(pos)) //Si on est en terrain ennemi
            if (m_map->cons_on(pos)->proprietaire() != m_current_player_turn)
                siege = true ;

        if (m_map->move_unit_at(m_current_selection->getPos(), pos, afterVictoryAttack, player_have_upgrade(DEPLACEMENTPLUS)))
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
        unsigned short pourcentage_reduction = 0 ;

        if (m_map->have_cons_on(target))
            if (m_map->cons_on(target)->proprietaire() != m_current_player_turn) //Si on est en terrain ennemi
                pourcentage_reduction = m_map->cons_on(target)->defense() ;

        Unit* defenseur = m_map->unit_on(target) ;
        defenseur->subirAttaque(m_current_selection->unit(), pourcentage_reduction) ;
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

//SUPRIME L'OBJET ACTUELLEMENT SELECTIONE PAR LE JOUEUR
void MatriceGameGestion::deleteSelection()
{
    if (m_current_selection != NULL)
    {
        delete(m_current_selection) ;
        m_current_selection = NULL ;
    }
}

//ON APPLIQUE LES CHANGEMENTS DE L'AMELIORATION RECHERCHEE SI ELLE A UN EFFET DIRECT
void MatriceGameGestion::add_upgrades(unsigned short id, Ressource const& res)
{
    m_upgrades [make_pair(m_player_list->back(), id)] = make_pair(Ressource(res), false) ;
}

//AJOUTER UNE AMELIORATION A RACHERCHER / LORS DE L'INITIALISATION DE LA MATRICE
void MatriceGameGestion::apply_upgrades(unsigned short id)
{
    if (id == MOREDEGATS)
    {
        for (unsigned short i = 0 ; i < m_map->nb_unit() ; i++)
            if (m_map->unit_n(i) != NULL)
                if (m_map->unit_n(i)->proprietaire() == m_current_player_turn)
                    m_map->unit_n(i)->up_degats(15) ;
    }
    else if (id == MOREGOLD)
    {
        for (unsigned short i = 0 ; i < m_map->nb_construction() ; i++)
            if (m_map->cons_n(i) != NULL)
                if (m_map->cons_n(i)->proprietaire() == m_current_player_turn)
                    m_map->cons_n(i)->up_apport(Ressource(15,0,0)) ;
    }
    else if (id == MOREDEFENSE)
    {
        for (unsigned short i = 0 ; i < m_map->nb_construction() ; i++)
            if (m_map->cons_n(i) != NULL)
                if (m_map->cons_n(i)->proprietaire() == m_current_player_turn)
                {
                    m_map->cons_n(i)->up_defense_max(10) ;
                    m_map->cons_n(i)->up_defense(10) ;
                }
    }
}

//LE JOUEUR POSSEDE T'IL CETTE AMELIORATION ?
bool MatriceGameGestion::player_have_upgrade(unsigned short id)
{
    //Cette amélioration n'existe pas
    if (m_upgrades.find(make_pair(m_current_player_turn, id)) == m_upgrades.end())
        return false ;
    return m_upgrades[make_pair(m_current_player_turn, id)].second ;
}

//EXTRAIRE LES INFOS SUR LES AMELIORATION D'UN UNIQUE JOUEUR
std::map <unsigned short,std::pair<Ressource,bool>> MatriceGameGestion::upgradesOf(AbstractPlayer* player)
{
    std::map <unsigned short,std::pair<Ressource,bool>> retour ;
    for (std::map < std::pair<AbstractPlayer*,unsigned short>, std::pair<Ressource,bool>>::iterator it = m_upgrades.begin() ; it != m_upgrades.end() ; it++)
        if (it->first.first == player)
            retour [it->first.second] = make_pair(it->second.first,it->second.second) ;
    return retour ;
}

//LIBERATION MEMOIRE DE LA MATRICE
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


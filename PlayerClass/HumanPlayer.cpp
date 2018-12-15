#include "HumanPlayer.h"

#include "../MenuClass/Menu.h"

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
    m_quantite_or = NULL ;
    m_select_info = NULL ;
    m_pos_construction = NULL ;

    //Représente la partie de la map affichée sur l'écran (par défaut en haut à gauche)
    m_scroll.x = 0 ;
    m_scroll.y = 0 ;

    m_all_symbol["red_circle"] = new SurfaceAffichage("../ressources/red_circle.bmp") ;
    m_all_symbol["green_circle"] = new SurfaceAffichage("../ressources/green_circle.bmp") ;
    m_all_symbol["gold"] = new SurfaceAffichage("../ressources/gold.bmp") ;
    for ( map<std::string,SurfaceAffichage*>::iterator it = m_all_symbol.begin() ; it != m_all_symbol.end() ; it++)
        it->second->rendre_transparente() ;
}

HumanPlayer::~HumanPlayer()
{
    if (m_select_info != NULL)
        delete(m_select_info) ;

    if (m_quantite_or != NULL)
        delete(m_quantite_or) ;

    if (m_pos_construction != NULL)
        delete(m_pos_construction) ;

    for ( map<std::string,SurfaceAffichage*>::iterator it = m_all_symbol.begin() ; it != m_all_symbol.end() ; it++)
    {
        if(it->second != NULL)
            delete(it->second) ;
        else
            warning_message("Potentielle fuite de mémoire : Impossible de supprimer it->second in ~MatriceGameGestion()") ;
    }
}

//Affiche simplement la partie de la map voulue (et définie par m_m_scroll) sur la fenetre du jeu
void HumanPlayer::updateDisplay(Map const& map, Selection const& selection, Fenetre& fenetre)
{
    fenetre.ajouter(map.getSurface(),&m_scroll,0,0) ;
    if (m_select_info)
        fenetre.ajouter(m_select_info->surfaceAffichage(), 10 , fenetre.height()-30) ;
    fenetre.ajouter(*m_all_symbol["gold"], fenetre.width()-172 ,0) ;
    fenetre.ajouter(m_quantite_or->surfaceAffichage(), fenetre.width()-100, 1) ;
    if (Menu::isAMenuOpened())
        Menu::keepOpened(fenetre);
    fenetre.actualiser() ;
}

//Fonction utilisée par la matrice pour demander au joueur de prendre une décision, seul interraction d'un joueur
Decision HumanPlayer::takeDecision(
            Map const& map, //Ici la Map est une référence constante, ainsi le joueur est en lecture seule, il doit passer par la matrice pour tout changement
            Selection const& selection, // Permet au joueur d'avoir des infos sur l'unité séléctionée, sans changer la sélécion
            Fenetre& fenetre //Passage par référence, une seule et même fenêtre dont le joueur peut changer le contenu pendant son tour
            )
{

    m_scroll.h = fenetre.height() ;
    m_scroll.w = fenetre.width() ;

    //On met à jour le texte des ressources
    if (m_quantite_or != NULL)
        delete(m_quantite_or) ;
    m_quantite_or = new Texte(to_string(200), SDL_Color({252, 210, 28}), 30, "04B-30") ;

    //Supression des infos en bas a gauche
    if (m_select_info != NULL)
        delete(m_select_info) ;

    delConstructionCursor(map) ;
    //Le choix de la construction actuel redevient num
    m_type_unit = -1 ;
    m_type_construction = -1 ;

    //On efface les symbole
    map.delete_all_symbol() ;
    m_select_info = NULL ;

    //On ferme les menus
    if (Menu::getMenuById(CHATEAU_MENU)->isOpen())
        Menu::openMenu(CHATEAU_MENU, fenetre) ;
    if (Menu::getMenuById(CONSTRUCTION_UNIT_MENU)->isOpen())
        Menu::openMenu(CONSTRUCTION_UNIT_MENU, fenetre) ;
    if (Menu::getMenuById(CONSTRUCTION_BATIMENT_MENU)->isOpen())
        Menu::openMenu(CONSTRUCTION_BATIMENT_MENU, fenetre) ;
    if (Menu::getMenuById(AMELIORER_CHATEAU_MENU)->isOpen())
        Menu::openMenu(AMELIORER_CHATEAU_MENU, fenetre) ;


    if(selection.valid())
    {
        MapPos pos = selection.getPos() ;

        //Affichage des infos en bas à gauche
        if (!selection.isObjectOf(this) || selection.type()!=OBJECT_TYPE_CONSTRUCTION)
            m_select_info = new Texte(selection.info(), SDL_Color({0,0,0}), 20) ;
        else // Ou le menu pour nos constructions
            if (!Menu::getMenuById(CHATEAU_MENU)->isOpen())
                Menu::openMenu(CHATEAU_MENU, fenetre) ;


        //Affichage du cercle de selection
        if (selection.isObjectOf(this)) // cette unite ou cette construction appartient t-elle au joueur en train de faire son tour ?
            map.add_symbol(*m_all_symbol["green_circle"],pos) ;
        else
            map.add_symbol(*m_all_symbol["red_circle"],pos) ;

        //Affichage symbole indiquant les déplacement possible
        if (selection.isObjectOf(this) && selection.type()==OBJECT_TYPE_UNIT)
        {
            std::vector <MapPos> moves = selection.possible_move_for_unit() ;
            for (unsigned short i = 0 ; i < moves.size() ; i++)
            {
                pos = moves[i] ;
                if(!map.have_unit_on(pos))
                    map.add_symbol(*m_all_symbol["green_circle"], pos) ; //Et affichage
                else if (map.see_unit_on(pos).proprietaire() != this)
                    map.add_symbol(*m_all_symbol["red_circle"], pos) ; //Et affichage en rouge
            }
        }
    }

    // On actualise l'écran
    updateDisplay(map,selection,fenetre) ;

    bool changement ;
    SDL_Event event ; 
    Decision decision_retour ; //Décision qui sera renvoyée à la matrice

    //On démarre la boucle de décision
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
                            changement = true ;
                            break;
                        
                        case SDLK_ESCAPE: // Si le joueur ouvre le menu principal
                            if (m_type_unit > 0 || m_type_construction > 0  || m_pos_construction != NULL)
                            {
                                m_type_construction = -1 ;
                                m_type_unit = -1 ;
                                delConstructionCursor(map) ;
                                if(!Menu::getMenuById(CHATEAU_MENU)->isOpen())
                                    Menu::openMenu(CHATEAU_MENU, fenetre) ;
                                updateDisplay(map,selection,fenetre) ;
                            }
                            else
                            {
                                Menu::openMenu(ESCAPE_MENU, fenetre) ;
                                updateDisplay(map,selection,fenetre) ;
                            }
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
                    if (m_pos_construction != NULL)
                    {
                        if (map.mapPos_of_click(m_scroll,event.motion.x,event.motion.y) != *m_pos_construction)
                        {
                            delConstructionCursor(map) ;
                            setConstructionCursor(map,selection,fenetre, event.motion.x,event.motion.y) ;
                            updateDisplay(map,selection,fenetre) ;
                        }
                    }

                    if (event.motion.x <= SCROOL_ZONE)
                        m_gauche_ecran = true ;
                    else
                        m_gauche_ecran = false ;

                    if (event.motion.y <= SCROOL_ZONE)
                        m_haut_ecran = true ;
                    else
                        m_haut_ecran = false ;

                    if (event.motion.x >= m_scroll.w-SCROOL_ZONE)
                        m_droite_ecran = true ;
                    else
                        m_droite_ecran = false ;

                    if (event.motion.y >= m_scroll.h-SCROOL_ZONE)
                        m_bas_ecran = true ;
                    else
                        m_bas_ecran = false ;

                    break ;
                }


                //GESTION DES CLICS DE SOURIS
                case SDL_MOUSEBUTTONDOWN:

                    

                    if (Menu::isOnOneMenu(event.motion.x,event.motion.y)) //GESTION CLICK SUR LES MENUS
                    {
                        int id = Menu::getIdButtonOn(event.motion.x,event.motion.y) ;

                        if (id == SUBMENU)
                        {
                            if (Menu::openSubAssocTo(event.motion.x,event.motion.y))
                                updateDisplay(map,selection,fenetre) ;
                        }

                        else if(id==QUITTER)
                            decision_retour.set_decision(DECISION_QUITTER) ; // Le joueur à decidé de quitter via le menu principal
                        
                        else if(id==RETOUR)
                        {
                            changement = true ;
                            Menu::openMenu(ESCAPE_MENU, fenetre);
                        }
                        else if(id==CATAPULTE)
                            m_type_unit = UNIT_CATAPULT ;

                        else if(id==BALISTE)
                            m_type_unit = UNIT_BALISTE ;

                        else if(id==BELIER)
                            m_type_unit = UNIT_SIEGE_RAW ;

                        else if(id==TREBUCHET)
                            m_type_unit = UNIT_TREBUCHET ;

                        else if(id==TOWERSIEGE)
                            m_type_unit = UNIT_SIEGE_TOWER ;
             
                        else if(id==FIN_DU_TOUR)
                            decision_retour.set_decision(DECISION_TOUR_SUIVANT) ;


                        if (m_type_unit >= 0)
                        {
                            m_type_unit %= NB_TYPE_UNIT ;
                            setConstructionCursor(map,selection,fenetre, event.motion.x, event.motion.y) ;
                            updateDisplay(map,selection,fenetre) ;
                        }
                    }
                    else //GESTION CLICS SUR lA MAP
                    {
                        MapPos pos( map.mapPos_of_click(m_scroll,event.motion.x,event.motion.y) ) ;

                        if (selection.possible_move_at(pos)) //Si on peut déplacer l'unité séléctionnée sur cette case
                        {
                            decision_retour.set_decision(DECISION_MOVE_SELECT_UNIT, &pos) ;
                        }
                        else if(map.have_unit_on(pos) || map.have_cons_on(pos)) //Si il y a quelque chose à selectionner sur cette case
                            decision_retour.set_decision(DECISION_CHANGE_SELECT_UNIT, &pos) ;
                        else
                            if (m_type_unit >= 0 && m_pos_construction != NULL) //Si l'on est en train de construire une unité
                                if (map.canConstructAt(*m_pos_construction, this) && map.terrain_adapt_to_unit(*m_pos_construction))
                                    {
                                        decision_retour.set_decision(DECISION_CONSTRUIRE_UNIT, &pos, &m_type_unit) ;
                                        return decision_retour ;
                                    }
                    }
                    break ;
            }
        }

        //Si le joueur a son curseur sur le côté, on doit progressivement décaler la partie de la map affichée sur l'écran grâce à la variable m_scroll
        if (m_gauche_ecran && SDL_GetTicks()-m_temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && m_scroll.x > 0)
        {
            m_scroll.x -- ;
            changement = true ;
        }
        if (m_droite_ecran && SDL_GetTicks()-m_temps_precedent>= TIME_BETWEEN_SCROLL_CHANGE && m_scroll.x < map.width() - m_scroll.w)
        {
            m_scroll.x ++ ;
            changement = true ;
        }
        if (m_haut_ecran && SDL_GetTicks()-m_temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && m_scroll.y > 0)
        {
            m_scroll.y -- ;
            changement = true ;
        }
        if (m_bas_ecran && SDL_GetTicks()-m_temps_precedent >= TIME_BETWEEN_SCROLL_CHANGE && m_scroll.y < map.height() - m_scroll.h)
        {
            m_scroll.y ++ ;
            changement = true ;
        }

        //Si la variable m_scroll à bougée on doit actualiser la nouvelle partie de la map affichée
        if (changement)
        {
            m_temps_precedent = SDL_GetTicks() ;
            updateDisplay(map,selection,fenetre) ;
        }

    }

    return decision_retour ;
}


void HumanPlayer::setConstructionCursor(Map const& map, Selection const& selection, Fenetre& fenetre, unsigned short x, unsigned short y)
{

    if (m_pos_construction == NULL)
        m_pos_construction = new MapPos(map.mapPos_of_click(m_scroll,x,y)) ;

    bool valid = map.canConstructAt(*m_pos_construction, this) && map.terrain_adapt_to_unit(*m_pos_construction) ;
    map.add_symbol(Unit::getSurfacePlacement(m_type_unit, valid), *m_pos_construction) ;
    
    //On ferme les menus
    if (Menu::getMenuById(CHATEAU_MENU)->isOpen())
         Menu::openMenu(CHATEAU_MENU, fenetre) ;
    if (Menu::getMenuById(CONSTRUCTION_UNIT_MENU)->isOpen())
        Menu::openMenu(CONSTRUCTION_UNIT_MENU, fenetre) ;
    if (Menu::getMenuById(CONSTRUCTION_BATIMENT_MENU)->isOpen())
        Menu::openMenu(CONSTRUCTION_BATIMENT_MENU, fenetre) ;
    if (Menu::getMenuById(AMELIORER_CHATEAU_MENU)->isOpen())
        Menu::openMenu(AMELIORER_CHATEAU_MENU, fenetre) ;
}

void HumanPlayer::delConstructionCursor(Map const& map)
{
    //Le choix de la position de la construction redevient nul
    if (m_pos_construction != NULL)
    {
        map.actualiser(*m_pos_construction) ;
        delete(m_pos_construction) ;
    }
    m_pos_construction = NULL ;
}
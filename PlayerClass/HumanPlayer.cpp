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

    m_pos_construction = NULL ;

    //Le texte est nul au début du premir tour
    m_quantite_gold = NULL ;
    m_quantite_wood = NULL ;
    m_quantite_food = NULL ;
    m_select_info = NULL ;
    m_info_unit_deplacement = NULL ;
    m_info_batiment_action = NULL ;

    //Représente la partie de la map affichée sur l'écran (par défaut en haut à gauche)
    m_scroll.x = 0 ;
    m_scroll.y = 0 ;

    //On charge une unique fois les textures
    m_all_symbol["red_circle"] = new SurfaceAffichage("../ressources/red_circle.bmp", TRANSPARENCE) ;
    m_all_symbol["green_circle"] = new SurfaceAffichage("../ressources/green_circle.bmp", TRANSPARENCE) ;
    m_all_symbol["gold"] = new SurfaceAffichage("../ressources/gold.bmp", TRANSPARENCE) ;
    m_all_symbol["wood"] = new SurfaceAffichage("../ressources/wood.bmp", TRANSPARENCE) ;
    m_all_symbol["food"] = new SurfaceAffichage("../ressources/food.bmp", TRANSPARENCE) ;
    m_all_symbol["gold_icon"] = new SurfaceAffichage("../ressources/icon/gold.bmp", TRANSPARENCE) ;
    m_all_symbol["wood_icon"] = new SurfaceAffichage("../ressources/icon/wood.bmp", TRANSPARENCE) ;
    m_all_symbol["food_icon"] = new SurfaceAffichage("../ressources/icon/food.bmp",TRANSPARENCE) ;
}

HumanPlayer::~HumanPlayer()
{
    deleteTexte() ;

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
    //afichage de la Map
    fenetre.ajouter(map.getSurface(),&m_scroll,0,0) ;

    //Info de séléction pouur les sélection qui n'ont pas de Menu
    if (m_select_info != NULL)
        fenetre.ajouter(m_select_info->surfaceAffichage(), 10 , fenetre.height()-30) ;

    //On affiche les actions restantes à faire dans ce tour pour le joueur
    short decalage_x = 0 ;
    short decalage_y = 0 ;
    if (selection.valid())
    {
        decalage_y = 30 ;
        if (selection.isObjectOf(this) && selection.type()==OBJECT_TYPE_CONSTRUCTION)
        {
            decalage_x = 260 ;
            decalage_y = 0 ;
        }
    }
    if (m_info_batiment_action != NULL)
    {
        SDL_SetAlpha(m_info_batiment_action->surfaceAffichage().surface(), SDL_SRCALPHA, 150) ;
        fenetre.ajouter(m_info_batiment_action->surfaceAffichage(),10+decalage_x,fenetre.height()-20-decalage_y) ;
    }
    else
        decalage_y -= 20 ;

    if (m_info_unit_deplacement != NULL)
    {
        SDL_SetAlpha(m_info_unit_deplacement->surfaceAffichage().surface(), SDL_SRCALPHA, 150) ;
        fenetre.ajouter(m_info_unit_deplacement->surfaceAffichage(),10+decalage_x,fenetre.height()-40-decalage_y) ;
    }
    
    //Ajout des ressources sur la fenetre
    fenetre.ajouter(m_quantite_gold->surfaceAffichage(), fenetre.width()-200, 2) ;
    fenetre.ajouter(*m_all_symbol["gold"], fenetre.width()-272 ,0) ;
    fenetre.ajouter(m_quantite_wood->surfaceAffichage(), fenetre.width()-408, 2) ;
    fenetre.ajouter(*m_all_symbol["wood"], fenetre.width()-470 ,0) ;
    fenetre.ajouter(m_quantite_food->surfaceAffichage(), fenetre.width()-580, 2) ;
    fenetre.ajouter(*m_all_symbol["food"], fenetre.width()-632 ,0) ;

    //Les menus ouverts son réafficher
    if (Menu::isAMenuOpened())
        Menu::keepOpened(fenetre);

    //On actualise l'écran
    fenetre.actualiser() ;
}

//Initialisation de toute l'interface qui permet la prise de décision du Joueur
void HumanPlayer::initialiserInterface(Map const& map, Selection const& selection, Ressource const& ressource, Fenetre& fenetre)
{
    m_scroll.h = fenetre.height() ;
    m_scroll.w = fenetre.width() ;

    //Definissons quelques couleurs
    SDL_Color grey2 = {180,180,180} ;
    SDL_Color red = {180,120,120} ;
    SDL_Color red2 = {35,0,0} ;
    //SDL_Color green = {134,104,15} ;

    //On supprime le curseur de construction
    delConstructionCursor(map) ;
    //Le choix de la construction actuel redevient num
    m_type_unit = -1 ;
    m_type_construction = -1 ;
        
    //On met à jour le texte des ressources
    deleteTexte() ;
    m_quantite_gold = new Texte(to_string(ressource.gold()) + "(+" + to_string(map.ressourceApport(this).gold()) + ")", SDL_Color({252, 210, 28}), 20, "extra") ;
    m_quantite_wood = new Texte(to_string(ressource.wood()) + "(+" + to_string(map.ressourceApport(this).wood()) + ")", SDL_Color({0, 0, 0}), 20, "extra") ;
    m_quantite_food = new Texte(to_string(map.population(this)) + "/" + to_string(ressource.food()), SDL_Color({0, 0, 0}), 20, "extra") ;

    //Permet au joueur de savoir si il lui reste des unités à déplacer et des actions dans les batiments à faire avant de passer au tour suivant
    unsigned short unit = map.nb_unit_of(this) ;
    unsigned short unit_restant = map.nb_unit_with_deplacement_of(this) ;
    if (unit_restant != 0)
        m_info_unit_deplacement = new Texte("Encore " + to_string(unit_restant) + "/" + to_string(unit) + " unite(s) a deplacer", red2, 15) ;

    unsigned short batiment = map.nb_construction_of(this) ;
    unsigned short batiment_restant = map.nb_construction_canDoAction_of(this) ;
    if (batiment_restant != 0)
        m_info_batiment_action = new Texte("Encore " + to_string(batiment_restant) + "/" + to_string(batiment) + " batiment(s) peuvent effectuer une action", red2, 15) ;

    //On efface les symboles de la map
    map.delete_all_symbol() ;
    
    //On ferme tous les menus sauf le principal
    closeSelectMenu(fenetre) ;
    
    //Affichage si quelque chose est sélectioné par le joueur
    if(selection.valid())
    {
        MapPos pos = selection.getPos() ;

         // GESTION DES MENUS DES CONSTRUCTIONS
        if (selection.isObjectOf(this) && selection.type()==OBJECT_TYPE_CONSTRUCTION)
        {
            //On prend un menu de batiment quelconque pour y changer les bouttons communs à tous les batiments
            Menu* menu = Menu::getMenuById(CHATEAU_MENU) ;

            //Pour toutes les constructions

            //On ajoute les ressources apportées par la construction dans l'entete
            int gold = selection.seeConstruction().apport().gold() ;
            int wood = selection.seeConstruction().apport().wood() ;
            int food = selection.seeConstruction().apport().food() ;
            menu->setTextButton(0, selection.see().name()) ;
            menu->setTextButton(1,((gold>=0)?"+":"")+to_string(gold)) ;
            menu->setTextButton(2,((wood>=0)?"+":"")+to_string(wood)) ;
            menu->setTextButton(3,((food>=0)?"+":"")+to_string(food)) ;
            menu->button(1)->addTexture(*m_all_symbol["gold_icon"], 45, 3) ;
            menu->button(2)->addTexture(*m_all_symbol["wood_icon"], 48, 3) ;
            menu->button(3)->addTexture(*m_all_symbol["food_icon"], 48, 3) ;

            //On adapte la couleurs des bouttons si le batiment peut ou non faire une action
            if (selection.seeConstruction().canDoAction())
            {
                menu->setColorButton(6, &grey2) ;
                Menu::getMenuById(FERME_MENU)->setColorButton(4, &grey2) ;
            }
            else
            {
                menu->setColorButton(6, &red) ;
                Menu::getMenuById(FERME_MENU)->setColorButton(4, &red) ;
            }

            // Peut on encore améliorer la défense
            if (selection.seeConstruction().defense() < selection.seeConstruction().defense_max())
                Menu::getMenuById(AMELIORER_CHATEAU_MENU)->setColorButton(5, &grey2) ;
            else
                Menu::getMenuById(AMELIORER_CHATEAU_MENU)->setColorButton(5, &red) ;

            //Quel menu de batiment doit être ouvert ?
            m_id_menu_to_open = CHATEAU_MENU ;
            if (  selection.seeConstruction().constructionType() == CONSTRUCTION_ARCHERY1
               || selection.seeConstruction().constructionType() == CONSTRUCTION_ARCHERY2)
                m_id_menu_to_open = ARCHERIE_MENU ;

            else if (  selection.seeConstruction().constructionType() == CONSTRUCTION_FARM)
                m_id_menu_to_open = FERME_MENU ;

            else if (  selection.seeConstruction().constructionType() == CONSTRUCTION_TOWER)
                m_id_menu_to_open = TOWER_MENU ;

            //On change le lien du boutton RETOUR2 pour qu'il ramène au menu associé au bon batiment
            //Le bouton retour 2 est le 7 eme bouton du menu de construction des unités
            Menu::getMenuById(CONSTRUCTION_UNIT_MENU)->changeAssocTo(7, m_id_menu_to_open) ;

            //On actualise la surface du Menu et on l'ajoute à la fenetre
            Menu::getMenuById(m_id_menu_to_open)->prepareSurface() ;
            if (!Menu::getMenuById(m_id_menu_to_open)->isOpen())
                Menu::openMenu(m_id_menu_to_open, fenetre) ;

            //On actualise aussi l'entete des Menus d'amélioration et de constrution même si il ne sont pas ouverts
            Menu::getMenuById(AMELIORER_MENU)->prepareSurface() ;
            Menu::getMenuById(UPGRADES_MENU)->prepareSurface() ;
            Menu::getMenuById(AMELIORER_CHATEAU_MENU)->prepareSurface() ;
            Menu::getMenuById(CONSTRUCTION_UNIT_MENU)->prepareSurface() ;
            Menu::getMenuById(CONSTRUCTION_BATIMENT_MENU)->prepareSurface() ;
        }
        else // Si aucun menu prévu pour ce qui est sélectionné on affiche les infos en bas à gauche
        {
            m_select_info = new Texte(selection.info(), SDL_Color({0,0,0}), 20, "bold") ;
        }

        //Affichage du cercle de selection
        if (selection.isObjectOf(this)) // cette unite ou cette construction appartient t-elle au joueur en train de faire son tour ?
            map.add_symbol(*m_all_symbol["green_circle"],pos) ;
        else
            map.add_symbol(*m_all_symbol["red_circle"],pos) ;

        //Affichage symbole indiquant les déplacement possibles
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
    debugage_message("Interface de " + m_name + " initialisée, il va maintenant prendre une décision") ;
}


//Fonction utilisée par la matrice pour demander au joueur de prendre une décision, seul interraction d'un joueur
Decision HumanPlayer::takeDecision(
            Map const& map, //Ici la Map est une référence constante, ainsi le joueur est en lecture seule, il doit passer par la matrice pour tout changement
            Selection const& selection, // Permet au joueur d'avoir des infos sur l'unité séléctionée, sans changer la sélécion
            Ressource const& ressource, //Permet au joueur de connaître ses ressources pour prendre ses décisions (sans les modifier)
            Fenetre& fenetre //Passage par référence, une seule et même fenêtre dont le joueur peut changer le contenu pendant son tour
            )
{
    //Initialisation de toute l'interface qui permet la prise de décision du Joueur
    initialiserInterface(map,selection,ressource,fenetre) ;

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
                                if(!Menu::getMenuById(m_id_menu_to_open)->isOpen())
                                    Menu::openMenu(m_id_menu_to_open, fenetre) ;
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
                        else if(id==FIN_DU_TOUR)
                            decision_retour.set_decision(DECISION_TOUR_SUIVANT) ;

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

                        else if(id==CHATEAU1)
                            m_type_construction = CONSTRUCTION_CASTLE1 ;
                        else if(id==CHATEAU2)
                            m_type_construction = CONSTRUCTION_CASTLE2 ;
                        else if(id==FERME)
                            m_type_construction = CONSTRUCTION_FARM ;
                        else if(id==ARCHERIE1)
                            m_type_construction = CONSTRUCTION_ARCHERY1 ;
                        else if(id==ARCHERIE2)
                            m_type_construction = CONSTRUCTION_ARCHERY2 ;
                        else if(id==TOWER)
                            m_type_construction = CONSTRUCTION_TOWER ;

                        else if(id==UP_GOLD || id==UP_WOOD || id==UP_FOOD || id==UP_DEFENSE)
                            if(selection.type() == OBJECT_TYPE_CONSTRUCTION)
                                if(selection.seeConstruction().canDoAction())
                                    if (id!=UP_DEFENSE || selection.seeConstruction().defense() < selection.seeConstruction().defense_max())
                                        if(decision_retour.set_decision(DECISION_AMELIORER_BATIMENT,&id))
                                            return decision_retour ;

                        if (id==DEPLACEMENTPLUS)
                            if(decision_retour.set_decision(DECISION_AMELIORATION,&id))
                                return decision_retour ;

                        if (m_type_unit >= 0)
                        {
                            m_type_unit %= NB_TYPE_UNIT ;
                            setConstructionCursor(map,selection,fenetre, event.motion.x, event.motion.y) ;
                            updateDisplay(map,selection,fenetre) ;
                        }

                        else if (m_type_construction >= 0)
                        {
                            m_type_unit %= NB_TYPE_CONSTRUCTION ;
                            setConstructionCursor(map,selection,fenetre,event.motion.x,event.motion.y) ;
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
                            if ((m_type_unit >= 0 || m_type_construction >= 0) && m_pos_construction != NULL) //Si l'on est en train de construire une unité
                                if (map.canConstructAt(*m_pos_construction, this)  &&
                                    map.terrain_adapt_to_unit(*m_pos_construction))
                                {
                                    bool manque_ressource = false ;
                                    if (m_type_unit >= 0)
                                    {
                                        if (Unit::canBuyWith(m_type_unit, ressource, map.population(this)))
                                        {
                                            decision_retour.set_decision(DECISION_CONSTRUIRE_UNIT, &pos, &m_type_unit) ;
                                            return decision_retour ;
                                        }
                                        else
                                            manque_ressource = true ;
                                    }
                                    else if (m_type_construction >= 0)
                                    {
                                        if (Construction::canBuyWith(m_type_construction, ressource, map.population(this)))
                                        {
                                            decision_retour.set_decision(DECISION_CONSTRUIRE_BATIMENT, &pos, &m_type_construction) ;
                                            return decision_retour ;
                                        }
                                        else
                                            manque_ressource = true ;
                                    }

                                    if (manque_ressource)
                                    {
                                        delConstructionCursor(map) ;
                                        m_type_unit = -1 ;
                                        m_type_construction = -1 ;
                                        if (!Menu::getMenuById(m_id_menu_to_open)->isOpen())
                                            Menu::openMenu(m_id_menu_to_open, fenetre) ;
                                        updateDisplay(map,selection,fenetre) ;
                                    }
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
    if (m_type_unit >= 0)
        map.add_symbol(Unit::getSurfacePlacement(m_type_unit, valid), *m_pos_construction) ;
    else
        map.add_symbol(Construction::getSurfacePlacement(m_type_construction, valid), *m_pos_construction) ;
    
    //On ferme les menus
    closeSelectMenu(fenetre) ;
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

void HumanPlayer::deleteTexte()
{
    if (m_info_unit_deplacement != NULL)
        delete(m_info_unit_deplacement) ;

    if (m_info_batiment_action != NULL)
        delete(m_info_batiment_action) ;

    if (m_quantite_gold != NULL)
        delete(m_quantite_gold) ;

    if (m_quantite_wood != NULL)
        delete(m_quantite_wood) ;

    if (m_quantite_food != NULL)
        delete(m_quantite_food) ;

    if (m_select_info != NULL)
        delete(m_select_info) ;

    m_info_unit_deplacement = NULL ;
    m_info_batiment_action = NULL ;
    m_quantite_gold = NULL ;
    m_quantite_wood = NULL ;
    m_quantite_food = NULL ;
    m_select_info = NULL ;
}

void HumanPlayer::closeSelectMenu(Fenetre& fenetre)
{
    //On ferme les menus
    if (Menu::getMenuById(CHATEAU_MENU)->isOpen())
        Menu::openMenu(CHATEAU_MENU, fenetre) ;

    if (Menu::getMenuById(AMELIORER_CHATEAU_MENU)->isOpen())
        Menu::openMenu(AMELIORER_CHATEAU_MENU, fenetre) ;

    if (Menu::getMenuById(CONSTRUCTION_UNIT_MENU)->isOpen())
        Menu::openMenu(CONSTRUCTION_UNIT_MENU, fenetre) ;

    if (Menu::getMenuById(CONSTRUCTION_BATIMENT_MENU)->isOpen())
        Menu::openMenu(CONSTRUCTION_BATIMENT_MENU, fenetre) ;

    if (Menu::getMenuById(AMELIORER_MENU)->isOpen())
        Menu::openMenu(AMELIORER_MENU, fenetre) ;

    if (Menu::getMenuById(ARCHERIE_MENU)->isOpen())
        Menu::openMenu(ARCHERIE_MENU, fenetre) ;

    if (Menu::getMenuById(FERME_MENU)->isOpen())
        Menu::openMenu(FERME_MENU, fenetre) ;

    if (Menu::getMenuById(TOWER_MENU)->isOpen())
        Menu::openMenu(TOWER_MENU, fenetre) ;

    if (Menu::getMenuById(UPGRADES_MENU)->isOpen())
        Menu::openMenu(UPGRADES_MENU, fenetre) ;
}
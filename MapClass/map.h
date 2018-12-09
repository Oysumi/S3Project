#ifndef DEF_MAP
#define DEF_MAP

#include <string>
#include <vector>
#include <map>
#include <list>

#include "../MapObject/construction.h"
#include "../MapClass/terrain.h"
#include "../MapObject/Unit.h"
#include "position.h"

class AbstractPlayer ;

// La map est l'objet principal de stockage et de gestion des données
// Les joueurs peuvent la lire pour prendre des décisions (sans la modifier)
// En fonction des décision des joueurs la Matrice modifie les données nécessaires via la map

/*
La map est optimisée pour que chaque changement sur les données n'implique que des opérations très rapides
En effet les changements ne nécessitent pas de recharger intégrallement la surface d'affichage de la
map, ni l'ensemble des positions positions libres, ces informations sont mises à jour petit à petit

Le parcourt du tableau d'unités ou de constructions n'a lieu que lors de la destruction et toutes les
méthodes, qu'elles soient privées, publiques, constantes ou non ont recourt à d'autres moyens pour
effectuer leurs opérations
*/

class Map
{
    public : // I) Méthodes non constantes, ne pouvant pas être utilisée directement par les joueurs
            // Utiliée en principe par la Matrice de gestion du jeu

        Map(unsigned short x, unsigned short y) ;
        Map() ;
        ~Map() ;

        //Accès aux données des unités et des construction (pointeurs <=> potenitelles modifications par la matrice)
        Unit* unit_on (MapPos const& pos) ;
        Construction* cons_on (MapPos const& pos) ;

        //Ajouter une unités ou une construction sur la Map
        bool add_unit (Unit const& unit) ;
        bool add_cons (Construction const& cons) ;

        bool move_unit_at(MapPos const& source, MapPos const& destination) ;

        void add_symbol (SurfaceAffichage const& surface, MapPos const& pos, bool audessus = true) ;
        void delete_all_symbol() ;

    public : // II) Méthodes constantes, les seules utilisables pour une map en lecture seule, pour les joueurs
        
        unsigned short height() const ;
        unsigned short width() const ;

        MapPos posOut() const ;

        unsigned short sprite_size() const ;
        SurfaceAffichage const& getSurface() const ;

        MapPos mapPos_of_click (SDL_Rect const& scroll, unsigned short const& x, unsigned short const& y) const ;

        bool have_unit_on (MapPos const& pos) const ;
        bool have_cons_on (MapPos const& pos) const ;

        MapPos random_free_pos () const ;
        unsigned int nb_free_pos () const ;

        bool terrain_adapt_to_unit(MapPos const& pos, Unit const& unit) const ;

    private : // III) Méthodes privées permettant surtout de gérer les différents affichages simplement
        void ajouter_texture_objets(MapPos const& pos) ;

        void actualiser (MapPos const& pos) ;
        void resest_texture(MapPos const& pos) ; //affiche le terrain sur cette case ce qui écrase et supprime tous les graphismes présents sur cette case
        
        void add_unit_texture(Unit const& unit) ;
        void add_cons_texture(Construction const& cons) ;

        void ajouter(SurfaceAffichage const& surf, MapPos const& pos) ; //ajouter un graphisme sur une certaine case
        
    private : // Le stockage des données !

        //Toutes les constructions et unités du jeu sont stockés dans ce vecteur (tabealu <=> parcourt rapide)
        std::vector <Unit*> m_list_unit ;
        std::vector <Construction*> m_list_cons ;

        //Structure de données map permettant d'associer une position à une unité ou une construction
      /*Ne gère pas le stockage des données mais permet seulement de trouver
        rapidement une unité ou une construction à une certaine postion */
        std::map <MapPos, Unit*>* m_map_unit ;
        std::map <MapPos, Construction*>* m_map_cons ;

        //Contient la surface d'affichage de la map entière
      /*Celle-ci est générée intégralement en début de partie
        elle est ensuite mise à jour partiellement à chaque
        changement sans jamais être rechargée complétement */
        SurfaceAffichage* m_graphic_map ;

        //Contient l'ensemble des positions libres de la map
        //Gain de temps quand la matrice cherche ou placer des unités
        //Elle est mise à jour à chaque placement d'unité
        std::list <MapPos>* m_free_pos ;

        //Contient la liste des symboles (affiché) par la matrice par dessus le terrain, les constructions et les unités
        std::vector <MapPos> m_list_pos_symbol ;

        //Permet la génération et le stockage de toutes les données liées au terrain
        Terrain m_terrain ;
};


#endif
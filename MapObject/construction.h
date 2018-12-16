#ifndef DEF_CONSTRUCTION
#define DEF_CONSTRUCTION

#include <string>
#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include "../MapObject/mapobject.h"
#include "../MapClass/terrain.h"
#include "../MatriceClass/Ressource.h"


#define NB_TYPE_CONSTRUCTION 6

#define CONSTRUCTION_CASTLE1  0
#define CONSTRUCTION_CASTLE2  1
#define CONSTRUCTION_ARCHERY1 2
#define CONSTRUCTION_ARCHERY2 3
#define CONSTRUCTION_FARM     4
#define CONSTRUCTION_TOWER    5

#define OBJECT_TYPE_CONSTRUCTION 1

class Construction : public MapObject
{
    public :
    	Construction(unsigned short type, MapPos const& pos, AbstractPlayer* const& player) ;
        Construction(Construction const& aCopier) ;

        virtual SurfaceAffichage const& getSurface() const ;
        virtual unsigned short type () const ;
        virtual bool canMove () const ; // Renvoie false pour les constructions
        virtual std::string info() const ;
        virtual std::string name() const ;

        static Ressource prix (unsigned short type) ;
        static bool canBuyWith (unsigned short type, Ressource const& res, unsigned short population_use) ;
        
        Ressource const& prix () const ;
        bool isInRangeOfConstruction(MapPos const& pos) const ;
        Ressource const& apport () const ;
        unsigned short defense () const ;
        unsigned short defense_max () const ;
        bool canDoAction () const ;
        unsigned short constructionType () const ;

        void capture_by (AbstractPlayer * new_propietaire) ;
        void reset_action_turn () ;
        void up_apport (Ressource to_add_at_apport_turn) ;
        void up_range (unsigned short ajout) ;
        void up_defense (unsigned short ajout) ;
        void up_defense_max (unsigned short ajout) ;
        void noMoreAction() ;

        static std::string sprite_construction_path ;
        static SpriteTexture* sprite_construction ;
        static SurfaceAffichage*** construction_affichage ;

        static std::string sprite_construction_placement_path ;
        static SurfaceAffichage*** construction_affichage_placement ;
        static SpriteTexture* sprite_construction_placement ;

        //DEUX METHODES STATIQUES PERMETTANT D'ÉVITER DE MULTIPLE CREATION DE SPRITETEXTURE & SURFACE D'AFFICHAGE POUR CHAQUE INSTANCE
        static void initSprtiteTexture() ;
        static void deleteSprtiteTexture() ;

        static SurfaceAffichage const& getSurfacePlacement(unsigned short type, bool correct) ;

    protected :
        void initCaracteristique() ;

    protected :
    	unsigned short m_type ;
        std::string m_name ;

        unsigned short m_defense ;
        unsigned short m_defense_max ; // Jusqu'a combien la défense peut-être améliorée
        Ressource m_apport ;
        Ressource m_prix ;
        bool m_action_possible ;
        unsigned short m_range ;
};


#endif
#ifndef __UNIT_H__
#define __UNIT_H__

#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include "../MapObject/mapobject.h"
#include "../MapClass/terrain.h"
#include "../MatriceClass/Ressource.h"
#include <string>
#include <vector>

#define NB_TYPE_UNIT     5

#define UNIT_CATAPULT    0
#define UNIT_SIEGE_TOWER 1
#define UNIT_BALISTE     2
#define UNIT_TREBUCHET   3
#define UNIT_SIEGE_RAW   4

#define UNIT_DOWN_CONSTRUCTION false
#define UNIT_TOP_CONSTRUCTION  true

#define OBJECT_TYPE_UNIT 0

class AbstractPlayer ;

class Unit : public MapObject
{
	public:
		Unit(unsigned short type, MapPos const& pos, AbstractPlayer* const& player) ;
		Unit(Unit const& aCopier) ;
		~Unit() ;

		virtual SurfaceAffichage const& getSurface() const ;
		virtual SurfaceAffichage const& getLifeSurface() const ;
		virtual unsigned short type () const ;
		virtual bool canMove () const ;
		virtual std::string info() const ;

		static Ressource prix (unsigned short type) ;
		static bool canBuyWith (unsigned short type, Ressource const& res, unsigned short population_use) ;
		Ressource const& prix () const ;
		bool graphicEraseCons() const ;
		std::string name() const ;

		bool canAttack_at (MapPos const& pos) const ; //Position adjacente ?
		bool canMove_at (MapPos const& pos) const ;
		unsigned short degats () const ;
		bool fullLife() const ;
		bool isDead() const ;

		bool move(MapPos const& pos) ;
		bool subirAttaque(Unit* attaquant) ;
		void reset_deplacement() ;

		//stockage des surfaces d'affichage des unités pour ne pas les reconstruire à chaque affichage => grosse optimisation niveau mémoire
		static std::string sprite_unit_path ;
		static SpriteTexture* sprite_unit ;
		static SurfaceAffichage*** unit_affichage ;

		static std::string sprite_unit_placement_path ;
		static SurfaceAffichage*** unit_affichage_placement ;
		static SpriteTexture* sprite_unit_placement ;

		static std::string sprite_life_path ;
		static SpriteTexture* sprite_life ;
		static std::vector<SurfaceAffichage*> life_affichage ;

		static void initSprtiteTexture() ;
		static void deleteSprtiteTexture() ;

		static SurfaceAffichage const& getSurfacePlacement(unsigned short type, bool correct) ;

	protected :
		void newVictoryPos(MapPos const& pos) ;
		void recevoirDegats(unsigned short nb_degats) ;
		void changePos (MapPos const& new_pos) ;
		void initCaracteristique () ;

	protected:
		unsigned short m_type ;

		std::string m_name ;
		bool m_graphicEraseCons ;

		Ressource m_prix ;
		unsigned short m_vieMax ;
		unsigned short m_vitesse ;
		unsigned short m_degats ;	
		
		unsigned short m_vie ;
		unsigned short m_deplacement ;

		MapPos* m_last_vitcory_pos ;
} ;

#endif // __UNIT_H__
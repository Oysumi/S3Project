#ifndef __UNIT_H__
#define __UNIT_H__

#include "../DisplayClass/texture.h"
#include "../MapClass/position.h"
#include "../MapObject/mapobject.h"
#include "../MapClass/terrain.h"
#include <string>

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

		virtual SurfaceAffichage const& getSurface() const ;
		virtual unsigned short type () const ;
		virtual bool canMove () const ;

		bool graphicEraseCons() const ;
		std::string name() const ;

		bool canMove_at (MapPos const& pos) const ;

		bool move(MapPos const& pos) ;
		void reset_deplacement() ;

		//stockage des surfaces d'affichage des unités pour ne pas les reconstruire à chaque affichage => grosse optimisation niveau mémoire
		static std::string sprite_unit_path ;
		static SpriteTexture* sprite_unit ;
		static SurfaceAffichage*** unit_affichage ;
		static void initSprtiteTexture() ;
		static void deleteSprtiteTexture() ;

	protected :
		void changePos (MapPos const& new_pos) ;
		void initCaracteristique () ;

	protected:
		unsigned short m_type ;

		std::string m_name ;
		bool m_graphicEraseCons ;
		unsigned short m_vitesse ;

		unsigned short m_deplacement ;	
} ;

#endif // __UNIT_H__
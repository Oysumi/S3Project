#ifndef __MAPOBJECT_H__
#define __MAPOBJECT_H__

#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "../MapClass/position.h"

#include <string>

#define NB_COLOR 2

class AbstractPlayer ;

//La classe Abstraite MapObject représente toutes les entités placées sur la map
//En pratique il s'agit de la classe mère des classes d'unités et de constructions
class MapObject
{
	public:
		MapObject(MapPos const& pos, AbstractPlayer* player) ;
		MapObject(MapObject const& aCopier) ;
		virtual ~MapObject();
		
		//Récupérer la surface d'affichage pour éventuellement afficher l'objet sur la Map
		virtual SurfaceAffichage const& getSurface() const = 0 ;
		//Retourne le type d'objet, construction, unité ...
		virtual unsigned short type () const = 0 ;
		virtual bool canMove () const = 0 ;

		//accesseurs
		MapPos const& getPos() const ;
		AbstractPlayer* proprietaire () const ;

	protected:
		MapPos m_pos ;
		AbstractPlayer * m_proprietaire ;
} ;

#endif // __UNIT_H__
Ces objets sont plac� sur la map, il s'agit pour le moment des unit�s et des constructions
Cette partie utilise directement des instances de SurfaceAffichage et de SpriteTexture de la partie displayClass
et �galement les objets d�finis dans MapObject qui sont les objets plac�s sur la Map 

Programmation de 3 objets r�partis dans 3 fichiers

mapobject.h :
  - MapObject : Classe abstraite dont les instances peuvent �tre plac�es sur la map

Unit.h : 
  - Unit, h�rit� de MapObject, gestion de l'unit� via de nombreuses m�thodes
Unit.cpp : contient touts les types d'unit�s ainsi que les caract�stiques associ�es, degats, vitesse, prix etc...

Construction.h : 
  - Construction, h�rit� de MapObject, gestion d'une construction
Construction.cpp : contient touts les types de construction ainsi que les caract�stiques associ�es, defense, prix, cout par tour, nom ...


Remarques :

   -  Les objets de type unit� et construction utilise des textures et des surfaces communes � toutes les
      instances. Elles doivent �tre initialis�e apr�s l'appel de SDL_Init puis lib�r�e via des m�thodes statiques
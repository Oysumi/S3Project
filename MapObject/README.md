Ces objets sont placé sur la map, il s'agit pour le moment des unités et des constructions
Cette partie utilise directement des instances de SurfaceAffichage et de SpriteTexture de la partie displayClass
et également les objets définis dans MapObject qui sont les objets placés sur la Map 

Programmation de 3 objets répartis dans 3 fichiers

mapobject.h :
  - MapObject : Classe abstraite dont les instances peuvent être placées sur la map

Unit.h : 
  - Unit, hérité de MapObject, gestion de l'unité via de nombreuses méthodes
Unit.cpp : contient touts les types d'unités ainsi que les caractéstiques associées, degats, vitesse, prix etc...

Construction.h : 
  - Construction, hérité de MapObject, gestion d'une construction
Construction.cpp : contient touts les types de construction ainsi que les caractéstiques associées, defense, prix, cout par tour, nom ...


Remarques :

   -  Les objets de type unité et construction utilise des textures et des surfaces communes à toutes les
      instances. Elles doivent être initialisée après l'appel de SDL_Init puis libérée via des méthodes statiques
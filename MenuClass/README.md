Ces objets permettent la mise en place de Menu.
Cette partie utilise directement des instances de la partie displayClass, Ainsi que la SDL

Programmation de 4 objets r�partis dans 4 fichiers

AbstractButton.h :
  - AbstractButton : Classe abstraite des bouttons pouvant �tre ajout� aux diff�rents menu
AbstractButton.cpp : D�finition de tous les boutons, contenu, police, placement du texte, couleur, id ..

ActionButton.h : 
  - ActionButton, h�rit� de AbstractButton, gestion des bouttons associ�s � des actions, ainsi que la modification de leur style

SubMenuBoutton.h : 
  - SubMenuBoutton, gestion des boutons dont le r�le est de renvoyer directement vers un autre Menu

Menu.h
  - Menu est la classe permettant la cr�ation du Menu contenant une liste de Boutons, la gestion de sa taille,
    du style, de r�cup�ration de l'id du boutons lors d'un clic etc...
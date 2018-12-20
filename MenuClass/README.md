Ces objets permettent la mise en place de Menu.
Cette partie utilise directement des instances de la partie displayClass, Ainsi que la SDL

Programmation de 4 objets répartis dans 4 fichiers

AbstractButton.h :
  - AbstractButton : Classe abstraite des bouttons pouvant être ajouté aux différents menu
AbstractButton.cpp : Définition de tous les boutons, contenu, police, placement du texte, couleur, id ..

ActionButton.h : 
  - ActionButton, hérité de AbstractButton, gestion des bouttons associés à des actions, ainsi que la modification de leur style

SubMenuBoutton.h : 
  - SubMenuBoutton, gestion des boutons dont le rôle est de renvoyer directement vers un autre Menu

Menu.h
  - Menu est la classe permettant la création du Menu contenant une liste de Boutons, la gestion de sa taille,
    du style, de récupération de l'id du boutons lors d'un clic etc...
Jeux de Stratégie Médiéval en C++
V1.0 Première version finalisée et équillibrée
Par Aurélien et Alexis

Version 1.1 en cours de dévellopement :
     - ajout d'un système de sauvegarde
     - ajout d'un système permettant aux joueurs de naviguer d'un de ses objets à l'autre (via la séléction)
         cela permet de gagner un temps précieux lors des longues parties
     - touche Q ne sera plus associée à la décision de quitter. Trop dangereux pour les longues parties
     - ajout d'une confirmation lorsqu'on passe au tour suivant et que l'on a pas effectué toutes ses actions
     - ajout de nouvelles actions possibles pour enrichir le Jeu 

Réfléxion autour de la version 1.2
     - ajout d'un Menu de début de partie, choix de la taille de la carte, nombres et noms des joueurs,
       situation de départ etc...
     - génération automatique de la carte et positionnement des constructions amélioré pour des parties encore plus intéressantes



Contenus des dossiers :

   - Game : ce dossier contient le programme, de quoi le compiler, le débuguer, ainsi que les différents fichiers générés par celui-ci
   
   - Ressources : le dossier contient les fichiers (textures) nécessaire au bon fonctionnement du programme

   - font : ce dossier contient les trois polices utilisées par le programme

   - RessourcesOriginales : ce dossier contient tous les graphismes (tous libre de droits) utilisés avant d'être modifié pour les besoins du Jeu

   - Doc : ce dossier contient quelques fichiers qui expliquent la logique avec laquelle nous avons débutée ce projet avant de commencer à le programmer

   - DisplayClass et Menu : deux parties utilisées dans le reste du programme, qui permettent l'affichage nottament du 
        texte de manière simple et l'implémentation d'un système de Menu facile à utiliser

   - Fonctions : partie contenant les fonctions communes à l'ensemble du programme,
        nottament celles facilitant le débugage, pratique sur de gros projets !

   - MapObject, MapClass, PlayerClass et MatriceClass : quatres parties principales où sont implémentées les parties les plus importantes du programme


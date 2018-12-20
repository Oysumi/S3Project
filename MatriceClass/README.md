Ces classes permettent de faire fonctionner directement le Jeu
Cette partie utilise directement ou non toutes les autres parties

Programmation de 4 objets répartis dans 4 fichiers

MatriceGameGestion.h :
  - MatriceGameGestion : Matrice dans laquelle est programmé tous les mécanismes du jeu en fonction des joueurs.
    Le code de l'interface utilisé par le joueur est appelé par la fonction take decision et la Matrice ne gère que le
    Jeu et non les différents, menus, symboles etc...

Decision.h : 
  - Decison, objet représentant les différentes décisions pouvant être prise par le joueur. Peuvent contenir une position et un id
Decision.cpp : ici sont implémentées toutes les decisions possibles qui peuvent être prise par le joueur

Ressource.h : 
  - Ressource : une classe assez simple permettant de gérer les ressources


Remarques :
    - Ainsi grâce au fonctionnement de la Matrice de Gestion du Jeu, le code de l'interface et les mécanismes du Jeu sont séparées dans des parties distantes
    - De plus la matrice interpretant seulement les décisions des joueurs peu importe comment elles sont prises. Il sera beaucoup plus simple d'ajouter
      une version réseaux avec un Joueur Distant et également une IA. Ces derniers renverront des décisions qui seront interprétées par la Matrice de la même façon
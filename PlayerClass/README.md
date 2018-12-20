Ces classes représentent les joueurs de la partie, l'implémentation de l'IA arrivera dans une des versions suivantes

Programmation de 3 objets répartis dans 3 fichiers

AbstractPlayer.h :
  - AbstractPlayer : Classe abstraite réprensentant un joueur. La matrice de gestion du Jeu appelle la 
    méthode virtuelle takeDecision qui renvoie la décision prise par le joueur

HumanPLayer.h : 
  - HumanPlayer.h : cette partie contient l'interface programmée pour permettre à un joueur en local de prendre des
    décisions en fonction des éléments envoyée par la matrice comme la Map en Lecture Seule

ArtificialPlayer.h : 
  - ArtificalPlayer.h : dans cette partie sera implémentée la future "IA" du jeu


Remarques :

   -  Les décisions renvoyées par les joueurs sont traités de la même manière indépendamment de leur type
   -  Le joueur n'a accès aux données du jeu qu'en lecture seule, il doit donc obligatoirement passer par
      des décisions pour agir sur la partie. Celles-ci sont traitées par la matrice qui veille alors au
      respect des règles du Jeu
   -  Ainsi une IA ou une nouvelle interface peut un être codée, sans avoir à s'inquiéter du respect des règles
   -  Le système actuel permet facilement de programmer une version réseau du Jeu avec l'ajout d'une classe distantPlayer
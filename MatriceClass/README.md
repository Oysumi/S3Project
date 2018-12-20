Ces classes permettent de faire fonctionner directement le Jeu
Cette partie utilise directement ou non toutes les autres parties

Programmation de 4 objets r�partis dans 4 fichiers

MatriceGameGestion.h :
  - MatriceGameGestion : Matrice dans laquelle est programm� tous les m�canismes du jeu en fonction des joueurs.
    Le code de l'interface utilis� par le joueur est appel� par la fonction take decision et la Matrice ne g�re que le
    Jeu et non les diff�rents, menus, symboles etc...

Decision.h : 
  - Decison, objet repr�sentant les diff�rentes d�cisions pouvant �tre prise par le joueur. Peuvent contenir une position et un id
Decision.cpp : ici sont impl�ment�es toutes les decisions possibles qui peuvent �tre prise par le joueur

Ressource.h : 
  - Ressource : une classe assez simple permettant de g�rer les ressources


Remarques :
    - Ainsi gr�ce au fonctionnement de la Matrice de Gestion du Jeu, le code de l'interface et les m�canismes du Jeu sont s�par�es dans des parties distantes
    - De plus la matrice interpretant seulement les d�cisions des joueurs peu importe comment elles sont prises. Il sera beaucoup plus simple d'ajouter
      une version r�seaux avec un Joueur Distant et �galement une IA. Ces derniers renverront des d�cisions qui seront interpr�t�es par la Matrice de la m�me fa�on
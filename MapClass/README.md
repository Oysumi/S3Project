Ces objets permettent de gérer l'affichage, la création, l'accès et le stockage des unités, des constructions et du terrain
Cette partie utilise directement des instances de SurfaceAffichage de la partie displayClass
et également les objets définis dans MapObject qui sont les objets placés sur la Map 

Programmation de 3 objets répartis dans 3 fichiers

terrain.h :
  - Terrain : permet la génération du terrain, aléatoire ou à partir d'un fichier en trois étapes.
     1) Génération alétoire ou lecture du fichier
     2) Vérification du format texte du Terrain + correction
     3) Choix des sprites adapatées selon les cases adjacentes

position.h : 
  - MapPos comme son nom l'indique, répresente une position sur la Map. Classe très simple permettant calculs et affichage des positions grâce à la définition d'opérateurs

map.h :
  - Map, est un des objets principaux du jeux
    Elle permet :
      1) Le stockage et l'accès à la quasi totalité des données du Jeu
      2) La gestion de l'affichage de la carte de manière optimisée
      3) Gestion du déplacament, de la création et de la destruction d'objets sur la Map
      4) Permet un accès direct aux objets contenu à une certaine position / le parcours des objets est cependant aussi très rapide


Remarques :

   -  La map est utlisée par la Matrice de Gestion du Jeu et par le joueur en lecture seule (voir MatriceClass et PlayerClass)
      Ainsi le joueur ne peut utiliser que les méthodes constantes.
      Le joueur ne peut donc pas modifier directement les données du Jeu et doit donc repasser par la Matrice de Gestion du Jeu qui veille au respect des règles

   -  Le joueur (via une interface) est libre d'ajouter des symboles partout sur la carte (méthodes non constantes), ceux si sont de toute façon détruit par la matrice entre chaque tour

   -  Utlisation de nombreux pointeurs. Ainsi des méthodes modifiant des attributs (qui ne sont pas stockée directement dans la Map) peuvent être déclarées comme constantes et donc utilisable par le joueur
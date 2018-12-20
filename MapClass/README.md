Ces objets permettent de g�rer l'affichage, la cr�ation, l'acc�s et le stockage des unit�s, des constructions et du terrain
Cette partie utilise directement des instances de SurfaceAffichage de la partie displayClass
et �galement les objets d�finis dans MapObject qui sont les objets plac�s sur la Map 

Programmation de 3 objets r�partis dans 3 fichiers

terrain.h :
  - Terrain : permet la g�n�ration du terrain, al�atoire ou � partir d'un fichier en trois �tapes.
     1) G�n�ration al�toire ou lecture du fichier
     2) V�rification du format texte du Terrain + correction
     3) Choix des sprites adapat�es selon les cases adjacentes

position.h : 
  - MapPos comme son nom l'indique, r�presente une position sur la Map. Classe tr�s simple permettant calculs et affichage des positions gr�ce � la d�finition d'op�rateurs

map.h :
  - Map, est un des objets principaux du jeux
    Elle permet :
      1) Le stockage et l'acc�s � la quasi totalit� des donn�es du Jeu
      2) La gestion de l'affichage de la carte de mani�re optimis�e
      3) Gestion du d�placament, de la cr�ation et de la destruction d'objets sur la Map
      4) Permet un acc�s direct aux objets contenu � une certaine position / le parcours des objets est cependant aussi tr�s rapide


Remarques :

   -  La map est utlis�e par la Matrice de Gestion du Jeu et par le joueur en lecture seule (voir MatriceClass et PlayerClass)
      Ainsi le joueur ne peut utiliser que les m�thodes constantes.
      Le joueur ne peut donc pas modifier directement les donn�es du Jeu et doit donc repasser par la Matrice de Gestion du Jeu qui veille au respect des r�gles

   -  Le joueur (via une interface) est libre d'ajouter des symboles partout sur la carte (m�thodes non constantes), ceux si sont de toute fa�on d�truit par la matrice entre chaque tour

   -  Utlisation de nombreux pointeurs. Ainsi des m�thodes modifiant des attributs (qui ne sont pas stock�e directement dans la Map) peuvent �tre d�clar�es comme constantes et donc utilisable par le joueur
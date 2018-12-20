Ces fichiers permettent de gérer simplement et avec une logique objet les affichages basiques du Jeu.
Cette partie utilise directement la SDL et TTF pour le texte
Programmation de 5 objets répartis dans 3 fichiers

Texture.h :
  - Texture est un objet permettant de charger simplement une texture via la SDL
  - SpriteTexture permet de charger et d'utiliser facilement des textures sous forme de sprites de tailles différentes

Fenetre.h : 
  - SurfaceAffichage comme son nom l'indique, répresente une surface dans laquelle des textures et d'autres surfaces d'affichages peuvent être ajoutées
  - Fenetre, héritée de SurfaceAffichage, instance censé être unique, car SDL1 ne permet pas l'affichage de plusieurs fenêtres à la fois

Texte.h :
  - Texte, cette classe permet d'ajouter simplement du texte à une Surface d'Affichage, en adapatant, texte couleur et police
Ces fichiers permettent de g�rer simplement et avec une logique objet les affichages basiques du Jeu.
Cette partie utilise directement la SDL et TTF pour le texte
Programmation de 5 objets r�partis dans 3 fichiers

Texture.h :
  - Texture est un objet permettant de charger simplement une texture via la SDL
  - SpriteTexture permet de charger et d'utiliser facilement des textures sous forme de sprites de tailles diff�rentes

Fenetre.h : 
  - SurfaceAffichage comme son nom l'indique, r�presente une surface dans laquelle des textures et d'autres surfaces d'affichages peuvent �tre ajout�es
  - Fenetre, h�rit�e de SurfaceAffichage, instance cens� �tre unique, car SDL1 ne permet pas l'affichage de plusieurs fen�tres � la fois

Texte.h :
  - Texte, cette classe permet d'ajouter simplement du texte � une Surface d'Affichage, en adapatant, texte couleur et police
Ces classes repr�sentent les joueurs de la partie, l'impl�mentation de l'IA arrivera dans une des versions suivantes

Programmation de 3 objets r�partis dans 3 fichiers

AbstractPlayer.h :
  - AbstractPlayer : Classe abstraite r�prensentant un joueur. La matrice de gestion du Jeu appelle la 
    m�thode virtuelle takeDecision qui renvoie la d�cision prise par le joueur

HumanPLayer.h : 
  - HumanPlayer.h : cette partie contient l'interface programm�e pour permettre � un joueur en local de prendre des
    d�cisions en fonction des �l�ments envoy�e par la matrice comme la Map en Lecture Seule

ArtificialPlayer.h : 
  - ArtificalPlayer.h : dans cette partie sera impl�ment�e la future "IA" du jeu


Remarques :

   -  Les d�cisions renvoy�es par les joueurs sont trait�s de la m�me mani�re ind�pendamment de leur type
   -  Le joueur n'a acc�s aux donn�es du jeu qu'en lecture seule, il doit donc obligatoirement passer par
      des d�cisions pour agir sur la partie. Celles-ci sont trait�es par la matrice qui veille alors au
      respect des r�gles du Jeu
   -  Ainsi une IA ou une nouvelle interface peut un �tre cod�e, sans avoir � s'inqui�ter du respect des r�gles
   -  Le syst�me actuel permet facilement de programmer une version r�seau du Jeu avec l'ajout d'une classe distantPlayer
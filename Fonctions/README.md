Dans cette partie, il s'agit des fonctions communes � l'ensemble du programme.
En l'occurence les seules fonctions impl�ment�es pour l'instant permettent la gestion des warnings, des erreur et des messages de debugages
Elle utilise directement l'�criture dans des fichiers
Programmation de 3 foncteurs

fonctions.h :
  - Erreur, Warning et Debugage sont trois foncteurs (avec un fonctionnement et une utilit� diff�rente) qui permettent l'�criture de mutliples messages
  - Par d�faut, les 3 instances erreur_message, warning_message et debugage_message de cette partie sont utilis�es dans l'ensemble du projet
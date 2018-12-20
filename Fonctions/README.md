Dans cette partie, il s'agit des fonctions communes à l'ensemble du programme.
En l'occurence les seules fonctions implémentées pour l'instant permettent la gestion des warnings, des erreur et des messages de debugages
Elle utilise directement l'écriture dans des fichiers
Programmation de 3 foncteurs

fonctions.h :
  - Erreur, Warning et Debugage sont trois foncteurs (avec un fonctionnement et une utilité différente) qui permettent l'écriture de mutliples messages
  - Par défaut, les 3 instances erreur_message, warning_message et debugage_message de cette partie sont utilisées dans l'ensemble du projet
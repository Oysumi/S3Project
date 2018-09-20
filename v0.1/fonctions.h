#ifndef DEF_FONCTIONS
#define DEF_FONCTIONS

#include <string>
#include "SDL/SDL.h"
#include <iostream>
#include <fstream>

/*
Fonctions communes à l'esemble du
programme : Gestions des erreurs,
des warnings et des messages utiles 
au débogage du programme
*/

void erreur (std::string const& message) ;
void warning (std::string const& message) ;
void test_message (std::string const& message) ;

#endif
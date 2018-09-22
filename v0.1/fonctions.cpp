﻿#include "fonctions.h"
#include "SDL/SDL.h"
using namespace std;


Erreur erreur ("erreurs.txt") ;
Warning warning  ("warnings.txt");
Debugage debugage ("debugage_messages.txt");


//Gestion des Erreurs
Erreur::Erreur(string nom_fichier) : m_fichier (nom_fichier.c_str())
{
    m_nomFichier = nom_fichier ;
}
Erreur::~Erreur()
{
    m_fichier.close() ;
}
void Erreur::operator()(string const& contenu)
{
    m_fichier << endl << contenu ;
    exit( EXIT_FAILURE ) ;
}


//Gestion des Warnings
Warning::Warning(string const& nom_fichier, bool arret) : m_fichier (nom_fichier.c_str())
{
    m_nomFichier = nom_fichier ;
    m_arret = arret ;
}
Warning::~Warning()
{
    m_fichier.close() ;
}
void Warning::operator()(string const& contenu, bool arret)
{
    m_fichier << endl << contenu ;
    if (m_arret || arret)
        exit( EXIT_FAILURE ) ;
}


//Gestion des Warnings
Debugage::Debugage(string const& nom_fichier) : m_fichier (nom_fichier.c_str())
{
    m_nomFichier = nom_fichier ;
}
Debugage::~Debugage()
{
    m_fichier.close() ;
}
void Debugage::operator()(string const& contenu)
{
    m_fichier << endl << contenu ;
}
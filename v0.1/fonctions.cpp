#include "fonctions.h"
#include "SDL/SDL.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


erreur_messages erreur_messages_messages ("erreur_messages_messages.txt") ;
Warning warning  ("warning_messages.txt");
Debugage debugage ("debugage_messages.txt");


//Gestion des erreur_messagess
erreur_messages::erreur_messages(string const& nom_fichier)
{
    m_fichier = NULL ;
    m_existence_fichier = false ;
    m_nomFichier = nom_fichier ;
}
erreur_messages::~erreur_messages()
{
    m_fichier->close() ;
    delete m_fichier ;
}
void erreur_messages::operator()(string const& contenu)
{
    if (!m_existence_fichier)
    {
        m_fichier = new ofstream (m_nomFichier.c_str()) ;
        m_fichier->close() ;
        delete m_fichier ;
        m_fichier = new ofstream (m_nomFichier.c_str(), ios::app) ;
        m_existence_fichier = true ;
    }
    *m_fichier << endl << contenu ;
}


//Gestion des Warnings
Warning::Warning(string const& nom_fichier, bool arret)
{
    m_fichier = NULL ;
    m_existence_fichier = false ;
    m_nomFichier = nom_fichier ;
    m_arret = arret ;
}
Warning::~Warning()
{
    m_fichier->close() ;
    delete m_fichier ;
}
void Warning::operator()(string const& contenu, bool arret)
{
    if (!m_existence_fichier)
    {
        m_fichier = new ofstream (m_nomFichier.c_str()) ;
        m_fichier->close() ;
        delete m_fichier ;
        m_fichier = new ofstream (m_nomFichier.c_str(), ios::app) ;
        m_existence_fichier = true ;
    }
    *m_fichier << endl << contenu ;
    if (m_arret || arret)
        exit( EXIT_FAILURE ) ;
}


//Gestion des messages de debugages
Debugage::Debugage(string const& nom_fichier)
{
    m_fichier = NULL ;
    m_existence_fichier = false ;
    m_nomFichier = nom_fichier ;
}
Debugage::~Debugage()
{
    m_fichier->close() ;
    delete m_fichier ;
}
void Debugage::operator()(string const& contenu)
{
    if (!m_existence_fichier)
    {
        m_fichier = new ofstream (m_nomFichier.c_str()) ;
        m_fichier->close() ;
        delete m_fichier ;
        m_fichier = new ofstream (m_nomFichier.c_str(), ios::app) ;
        m_existence_fichier = true ;
    }
    *m_fichier << endl << contenu ;
}
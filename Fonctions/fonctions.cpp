#include "fonctions.h"
#include "SDL/SDL.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Erreur erreur_message ("erreur_messages.txt") ;
Warning warning_message  ("warning_messages.txt");
Debugage debugage_message ("debugage_messages.txt");


//Gestion des erreur_messages
Erreur::Erreur(string const& nom_fichier)
{
    m_fichier = NULL ;
    m_existence_fichier = false ;
    m_nomFichier = nom_fichier ;
}
Erreur::~Erreur()
{
    if (m_existence_fichier && DEBUG) //le fichier à été créé donc il y a une erreur, on le signale avant la fermeture du programme
        cout << "Erreur survenue lors de l'éxécution, ouvrir le fichier " << m_nomFichier << " pour consulter la liste" << endl ;
}

void Erreur::operator()(string const& contenu)
{
    if (!m_existence_fichier)
    {
        m_fichier = new ofstream (m_nomFichier.c_str()) ;
        m_fichier->close() ;
        delete m_fichier ;
        m_existence_fichier = true ;
    }
    m_fichier = new ofstream (m_nomFichier.c_str(), ios::app) ;
    *m_fichier << contenu << endl ;
    m_fichier->close() ;
    delete m_fichier ;
    exit( EXIT_FAILURE ) ;
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
    if (m_existence_fichier && DEBUG) //le fichier à été créé donc il y a des warnings, on le signale avant la fermeture du programme
        cout << "Un ou plusieurs Warning(s) lors de l'éxécution du programme, ouvrir le fichier " << m_nomFichier << " pour les consulter " << endl ;
}
void Warning::operator()(string const& contenu, bool arret)
{
    if (!m_existence_fichier)
    {
        m_fichier = new ofstream (m_nomFichier.c_str()) ;
        m_fichier->close() ;
        delete m_fichier ;
        m_existence_fichier = true ;
    }
    m_fichier = new ofstream (m_nomFichier.c_str(), ios::app) ;
    *m_fichier << contenu << endl ;
    m_fichier->close() ;
    delete m_fichier ;
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

}
void Debugage::operator()(string const& contenu)
{
    if (!m_existence_fichier)
    {
        m_fichier = new ofstream (m_nomFichier.c_str()) ;
        m_fichier->close() ;
        delete m_fichier ;
        m_existence_fichier = true ;
    }
    m_fichier = new ofstream (m_nomFichier.c_str(), ios::app) ;
    *m_fichier << contenu << endl ;
    m_fichier->close() ;
    delete m_fichier ;
}
#include "fonctions.h"
using namespace std;

//Générer un message d'erreur
void erreur (string const& message)
{
    string const nomFichier("erreurs.txt") ;
    ofstream fichierErreur(nomFichier.c_str()) ;
    fichierErreur << "\n" << message << endl ;
    fichierErreur.close() ;
    exit( EXIT_FAILURE ) ;
}

//Générer un message de wrning
void warning (string const& message)
{
    string const nomFichier("warning.txt") ;
    ofstream fichierWarning(nomFichier.c_str()) ;
    fichierWarning << "\n" << message << endl ;
    fichierWarning.close() ;
}

//Pour afficher un message utile au débugage
void test_message (string const& message)
{
    string const nomFichier("test.txt") ;
    ofstream fichierTest(nomFichier.c_str()) ;
    fichierTest << "\n" << message << endl ;
    fichierTest.close() ;
}
#ifndef DEF_FONCTIONS
#define DEF_FONCTIONS

#include <string>
#include <iostream>
#include <fstream>

/*
Foncteurs communs à l'esemble du
programme : Gestions des erreurs,
des warnings et des messages utiles 
au débogage du programme
*/

//Une classe foncteur pour chaque type de message car le traitement, d'une erreur, d'un warning et d'un message de débugage peut-être différent

//Gestion des Erreurs
class Erreur{
	
	public:
    	Erreur(std::string nom_fichier) ;
    	~Erreur() ;

    void operator()(std::string const& contenu) ;

	private:
		bool m_existence_fichier ;
		std::ofstream* m_fichier ;
    	std::string m_nomFichier ;
};

//Gestion des Warnings
class Warning{
	
	public:
    	Warning(std::string const& nom_fichier, bool arret = false) ;
    	~Warning() ;

    void operator()(std::string const& contenu, bool arret = false) ;

	private:
		bool m_existence_fichier ;
		std::ofstream* m_fichier ;
    	std::string m_nomFichier ;
    	bool m_arret ;
};

//Gestion des Warnings
class Debugage{
	
	public:
    	Debugage(std::string const& nom_fichier) ;
    	~Debugage() ;

    void operator()(std::string const& contenu) ;

	private:
		bool m_existence_fichier ;
		std::ofstream* m_fichier ;
    	std::string m_nomFichier ;
};


extern Erreur erreur ;
extern Warning warning ;
extern Debugage debugage ;


#endif
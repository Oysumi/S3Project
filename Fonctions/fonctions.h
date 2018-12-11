#ifndef DEF_FONCTIONS
#define DEF_FONCTIONS

#include <iostream>
#include <fstream>
#include <string>

/*
Foncteurs communs à l'esemble du
programme : Gestions des erreur_messages,
des warnings et des messages utiles 
au débogage du programme
*/

//Une classe foncteur pour chaque type de message car le traitement, d'une erreur_message, d'un warning et d'un message de débugage peut-être différent

#define DEBUG true

//Gestion des erreur_messages
class Erreur{
	
	public:
    	Erreur(std::string const& nom_fichier) ;
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

//Gestion des messages de debugages
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


extern Erreur erreur_message ;
extern Warning warning_message ;
extern Debugage debugage_message ;


#endif
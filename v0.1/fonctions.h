#ifndef DEF_FONCTIONS
#define DEF_FONCTIONS

#include <iostream>
#include <fstream>
#include <string>

/*
Foncteurs communs à l'esemble du
programme : Gestions des erreur_messagess,
des warnings et des messages utiles 
au débogage du programme
*/

//Une classe foncteur pour chaque type de message car le traitement, d'une erreur_messages, d'un warning et d'un message de débugage peut-être différent

//Gestion des erreur_messagess
class erreur_messages{
	
	public:
    	erreur_messages(std::string const& nom_fichier) ;
    	~erreur_messages() ;

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


extern erreur_messages erreur_messages_messages ;
extern Warning warning ;
extern Debugage debugage ;


#endif
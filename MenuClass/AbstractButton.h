#ifndef __ABSTRACTBUTTON_H__
#define __ABSTRACTBUTTON_H__

#include <string>
#include <SDL/SDL.h>
#include "../DisplayClass/fenetre.h"
#include "../DisplayClass/Texte.h"
#include <vector>

#define CENTER_TEXT 0
#define LEFT_TEXT 1

class Texte ;

// We put the constructor in protected so that we can't instanciate this class in the main code, making it a sort of abstract class
class AbstractButton
{
	protected:
		unsigned int m_width ;
		unsigned int m_height ;
		int m_id ;
    	int m_sizeText ;  // Taille du texte pour les boutons
		std::string m_text ;
		SDL_Color m_back_color ;
		SDL_Color m_text_color ;
		
	public:

		static std::vector<AbstractButton*>* getAllButton() ;

		//GETTERS
		unsigned int getWidth() const ;
		unsigned int getHeight() const ;
		int getID() const ;
		SDL_Color getBackColor() const ;
		SDL_Color getTextColor() const ;
		const char * getText() const ;
    	int sizeText() const ;

		//SETTERS
		virtual void setText(std::string text, std::string font = "") = 0 ;
		virtual void setColor(SDL_Color* background, SDL_Color* text = NULL) = 0 ;

		//Méthodes virtuelles pures
		virtual SurfaceAffichage const& getSurfaceAffichage() const = 0 ;
		virtual Texte const& getTexte() const = 0 ;
		virtual void addTexture (SurfaceAffichage const& surface, unsigned short x, unsigned short y) = 0 ;

		// destructeur
		virtual ~AbstractButton() ;
};

#define NOTHING 100
#define SUBMENU 200

//Menu principal
#define RETOUR 0
#define MUSIQUE 1
#define QUITTER 2
#define FIN_DU_TOUR 3
#define AFFICHAGE 4
#define CAPTURE 5
#define ENREGISTRER 6

//Construction unitées
#define CATAPULTE 11
#define BALISTE 12
#define BELIER 13
#define TREBUCHET 14
#define TOWERSIEGE 15

//Construction batiments
#define CHATEAU1 22
#define CHATEAU2 23
#define ATELIER1 24
#define ATELIER2 25
#define FERME 26
#define TOWER 27

//Entete menu de tous les batiments
#define ENTETE_BATIMENT 32
#define ENTETE_GOLD 33
#define ENTETE_FOOD 34
#define ENTETE_WOOD 35
#define ENTETE_DEFENSE 36
#define RETOUR2 37

//Entete Construction unités et batiments
#define ENTETE_CONSTRUCTION 47
#define CONSTRUIRE_PETIT_BATIMENT 48
#define CONSTRUIRE_GRAND_BATIMENT 49
#define CONSTRUIRE_PETITE_UNITE 50
#define CONSTRUIRE_GRANDE_UNITE 51

#define AMELIORATION_CHATEAU 60
#define AMELIORATION_FERME 61

#define AMELIORER 66
#define UP_GOLD 67
#define UP_FOOD 68
#define UP_WOOD 69
#define UP_DEFENSE 70

#define RECHERCHE 79
#define UPGRADES_UNIT 80
#define DEPLACEMENTPLUS 81
#define MOREDEGATS 82

#define UPGRADES_CONS 90
#define MOREGOLD 91
#define MOREDEFENSE 92
#endif // __ABSTRACTBUTTON_H__
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

#define RETOUR 0
#define MUSIQUE 1
#define QUITTER 2
#define FIN_DU_TOUR 3
#define AFFICHAGE 4

#define CATAPULTE 11
#define BALISTE 12
#define BELIER 13
#define TREBUCHET 14
#define TOWERSIEGE 15
#define RETOUR2 16

#define CHATEAU1 19
#define CHATEAU2 20
#define ARCHERIE1 21
#define ARCHERIE2 22
#define FERME 23
#define TOWER 24

#define ENTETE_BATIMENT 26
#define ENTETE_CONSTRUCTION 27
#define CONSTRUIRE_UNIT 28
#define CONSTRUIRE_BATIMENT 29
#define AMELIORATION_BATIMENT 30
#define AMELIORATION_CHATEAU 31
#define ENTETE_GOLD 32
#define ENTETE_FOOD 33
#define ENTETE_WOOD 34

#define AMELIORER 37
#define UP_GOLD 38
#define UP_FOOD 39
#define UP_WOOD 40
#define UP_DEFENSE 41

#define UPGRADES 60
#define DEPLACEMENTPLUS 61

#endif // __ABSTRACTBUTTON_H__
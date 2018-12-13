#ifndef __ABSTRACTBUTTON_H__
#define __ABSTRACTBUTTON_H__

#include <string>
#include <SDL/SDL.h>
#include "../DisplayClass/fenetre.h"
#include "../DisplayClass/Texte.h"
#include <vector>

class Texte ;

// We put the constructor in protected so that we can't instanciate this class in the main code, making it a sort of abstract class
class AbstractButton
{
	protected:
		unsigned int m_width ;
		unsigned int m_height ;
		unsigned int m_posx ;
		unsigned int m_posy ;
		int m_id ;
    int m_sizeText ;  // Taille du texte pour les boutons
		std::string m_text ;
		SDL_Color m_back_color ;
		SDL_Color m_text_color ;
		
	public:

		static std::vector<AbstractButton*>* getAllButton() ;

		//GETTERS
		unsigned int getPosX() const ;
		unsigned int getPosY() const ;
		unsigned int getWidth() const ;
		unsigned int getHeight() const ;
		int getID() const ;
		SDL_Color getBackColor() const ;
		SDL_Color getTextColor() const ;
		const char * getText() const ;
    	int sizeText() const ;

		//SETTERS
		void setPosX(unsigned int x) ;
		void setPosY(unsigned int y) ;
		virtual void setText(std::string text) ;

		//Méthodes virtuelles pures
		virtual void displayButton(Fenetre& screen) const = 0 ;
		virtual SurfaceAffichage const& getSurfaceAffichage() const = 0 ;
		virtual Texte const& getTexte() const = 0 ;

		// destructeur
		virtual ~AbstractButton() ;

		// à définir méthode virtuelle qui renvoit la surface d'affichage du bouton
};

#define NOTHING 100
#define SUBMENU 200

#define RETOUR 0
#define MUSIQUE 1
#define QUITTER 2
#define FIN_DU_TOUR 3
#define AFFICHAGE 4

#define ENTETE_CONSTRUCTION_UNITE 10
#define BELIER 11
#define CATAPULTE 12
#define RETOUR2 13

#define ENTETE_CONSTRUCTION_BATIMENT 20
#define CHATEAU 21
#define FERME 22
#define RETOUR3 23

#define ENTETE_CONSTRUCTION 27
#define CONSTRUIRE_UNIT 28
#define CONSTRUIRE_BATIMENT 29

#endif // __ABSTRACTBUTTON_H__
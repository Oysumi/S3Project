#ifndef DEF_CONSTRUCTION
#define DEF_CONSTRUCTION

#include <string>

#include "../Fonctions/fonctions.h"
#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "../CharactersClass/AbstractPlayer.h"
#include "position.h"

class Construction
{
    public :
    	Construction(std::string const& texture_path, MapPos const& pos, AbstractPlayer* proprietaire) ;
        Construction(Construction const& aCopier) ;
		~Construction() ;
		Texture const& getSurface() const ;
		MapPos const& getPos() const ;
		void changePos (MapPos const& new_pos) ;

    private :
    	AbstractPlayer* m_proprietaire ;

        MapPos m_pos ;
        std::string m_texture_path ;
        Texture* m_texture ;
};


#endif
#ifndef DEF_TERRAIN
#define DEF_TERRAIN

#include <string>

#include "../fonctions.h"
#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"

#define MAP_CASE_SIZE 64
#define NB_SPRITE 17


class Terrain
{
    public :
        Terrain(std::string const& fileMap, std::string const& fileSprite) ;
        ~Terrain() ;

        bool saveBMP (std::string const& fileName) const ;
        SurfaceAffichage* const terrainComplet() const ;
        
    private : // Fonctions internes
        unsigned short assocCodeToCaseSprite (char const& c) const ;

    private : //Attributs
        SpriteTexture m_sprite ;
        unsigned short m_nb_width_sprite ;
        unsigned short m_nb_height_sprite ;
        SurfaceAffichage* m_terrainComplet ;
};


#endif
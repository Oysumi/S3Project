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
        Terrain(std::string const& fileMap) ;
        Terrain(unsigned short const& width, unsigned int const& height) ;
        ~Terrain() ;

        bool saveBMP (std::string const& fileName) const ;
        SurfaceAffichage const& terrainComplet() const ;
        
    private : // Fonctions internes
        unsigned short assocCodeToCaseSprite (char const& c) const ;
        void generer_le_terrain (std::string const& terrain_representation) ;

    private : //Attributs
        SpriteTexture m_sprite ;
        unsigned short m_nb_width_sprite ;
        unsigned short m_nb_height_sprite ;
        SurfaceAffichage* m_terrainComplet ;
        char ** m_terrainTab ;
        static std::string nameSpriteTexture ;
};


#endif
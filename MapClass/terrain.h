#ifndef DEF_TERRAIN
#define DEF_TERRAIN

#include <string>
#include <map>
#include <list>

#include "../Fonctions/fonctions.h"
#include "../DisplayClass/texture.h"
#include "../DisplayClass/fenetre.h"
#include "position.h"

#define MAP_CASE_SIZE 64
#define NB_SPRITE 17


class Terrain
{
    public :
        Terrain(std::string const& fileMap, std::list <MapPos>* & free_pos) ;
        Terrain(unsigned short const& width, unsigned int const& height, std::list <MapPos>* & free_pos) ;
        ~Terrain() ;

        unsigned short posxOut() const ;
        unsigned short posyOut() const ;
        unsigned short sprite_size() const ;

        SpriteTexture const& sprite() const ;
        unsigned short sprite_code (MapPos const& pos) ; //const

        bool saveBMP (std::string const& fileName) const ;
        SurfaceAffichage const& terrainComplet() const ;
        static std::string nameSpriteTexture ;
        
    private : // Fonctions internes
        unsigned short assocCodeToCaseSprite (char const& c) const ;
        void generer_le_terrain (std::string const& terrain_representation, std::list <MapPos>* free_pos) ;

    private : //Attributs
        SpriteTexture m_sprite ;
        unsigned short m_nb_width_sprite ;
        unsigned short m_nb_height_sprite ;
        SurfaceAffichage* m_terrainComplet ;
        std::map <MapPos, char> m_sprite_representation ;
};


#endif
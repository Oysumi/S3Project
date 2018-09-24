#include "terrain.h"
#include <iostream>
#include <fstream>
using namespace std ;


Terrain::Terrain(string const& fileMap, string const& fileSprite) : m_sprite(fileSprite, MAP_CASE_SIZE, NB_SPRITE)
{
	

    //ANALYSE DU FICHIER DU TERRAIN
    string texte, ligne ;
    ifstream fichier (fileMap.c_str());
    
    if ( fichier )
    {
        unsigned short longueur_max_ligne = 0 ;
        unsigned short  nb_de_lignes = 0 ;
        while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            texte += ligne + '\n' ;
            nb_de_lignes++ ;
            if (ligne.size() > longueur_max_ligne)
                longueur_max_ligne = ligne.size() ;
        }

        m_nb_width_sprite = longueur_max_ligne ;
        m_nb_height_sprite = nb_de_lignes ;
    }
    else
    {
        erreur_message("Impossible d'ouvrir le fichier de la Map");
        cout << "imossible" << endl ;
    }

    debugage_message("Lecture du fichier de terrain") ;


    //Création d'un tableau réprésentant les textures du terrain
    char ** terrain = 0 ;
    terrain = (char**)malloc(m_nb_height_sprite * sizeof(char*));
    for (unsigned short i = 0 ; i < m_nb_height_sprite ; i++)
    {
        terrain[i] = (char*)malloc(m_nb_width_sprite * sizeof(char));
    }

    //Remplissage par des cases d'herbes (lignes complétées si de tailles différentes)
    for (unsigned short l = 0 ; l < m_nb_height_sprite ; l++)
    {
        for (unsigned short i = 0; i < m_nb_width_sprite ; i++)
        {
            terrain[l][i] = 'G' ;
        }
    }

    //On indique les char du fichier dans le tableau
    unsigned short texte_curseur = 0 ;
    for (unsigned short l = 0 ; l < m_nb_height_sprite ; l++)
    {
        unsigned short i ;
        for (i = 0 ; texte[texte_curseur] != '\n' ; i++)
        {
            terrain[l][i] = texte[texte_curseur] ;
            texte_curseur ++;
        }
        texte_curseur++ ;
    }
    
    texte = "" ;
    for (unsigned short l = 0 ; l < m_nb_height_sprite ; l++)
    {
        for (unsigned short i = 0 ; i < m_nb_width_sprite ; i++)
        {
            texte += terrain[l][i] ;
        }
        texte += "\n" ;
    }
    debugage_message("Vérfication et correction de celui-ci") ;
    debugage_message(texte) ;



    m_terrainComplet = new SurfaceAffichage(m_nb_width_sprite*MAP_CASE_SIZE, m_nb_height_sprite*MAP_CASE_SIZE) ;
    for (unsigned short x = 0 ; x < m_nb_width_sprite ; x++)
    {
        for (unsigned short y = 0 ; y < m_nb_height_sprite ; y++)
        {
            m_terrainComplet->ajouter(m_sprite, x*MAP_CASE_SIZE, y*MAP_CASE_SIZE, assocCodeToCaseSprite(terrain[y][x]) ) ;
        }
    }


}

Terrain::~Terrain()
{
	delete m_terrainComplet ;
}



bool Terrain::saveBMP (std::string const& fileName) const
{
	return m_terrainComplet->saveBMP(fileName) ;
}


SurfaceAffichage const& Terrain::terrainComplet() const
{
	return *m_terrainComplet ;
}


unsigned short Terrain::assocCodeToCaseSprite(char const& c) const
{
    unsigned short n = (unsigned short) c ;
    if (97 <= n && n <= 122)
    {
        return(n-87) ;
    }

    if (65 <= n && n <= 90)
    {
        return(n-55) ;
    }

    if (48 <= n && n <= 57)
    {
        return(n-48) ;
    }
    if (c == ' ')
    {
        return 16;
    }

    Warning("La map contient des caractères ne correspondant à aucun Sprite") ;
    return 16; //Ce sera donc de l'hebre
}
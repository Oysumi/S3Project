#include "terrain.h"
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std ;

string Terrain::nameSpriteTexture = "../ressources/SpriteMap64.bmp" ;

//GENERATION D'UN TEXTE REPRESENTANT LE TERRAIN A PARTIR D'UN FICHIER
Terrain::Terrain(string const& fileMap) : m_sprite(nameSpriteTexture, MAP_CASE_SIZE, NB_SPRITE)
{
    
    debugage_message("Lecture du fichier de terrain") ;

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

    generer_le_terrain(texte) ;
}

//GENERATION ALEATOIRE D'UN TEXTE REPRESENTANT LE TERRAIN
Terrain::Terrain (unsigned short const& width, unsigned int const& height) : m_sprite(nameSpriteTexture, MAP_CASE_SIZE, NB_SPRITE)
{
    //ANALYSE DU FICHIER DU TERRAIN
    string texte = "" ;


    m_nb_width_sprite = width ;
    m_nb_height_sprite = height ;

	debugage_message("Génération aléatoire du terrain") ;
    for (unsigned short x = 0 ; x < width ; x++)
    {
        for (unsigned short y = 0 ; y < height ; y++)
        {
            if (rand()%3==0)
            	texte += 'W' ;
            else
            	texte += 'G' ;
        }
        texte += '\n' ;
    }
    debugage_message("map gènerée : ") ;
    debugage_message(texte) ;

    generer_le_terrain(texte) ;

}

//DESTRUCTEUR
Terrain::~Terrain()
{
    cout << "Destruction terrain" << endl ;
    for (unsigned short i = 0 ; i < m_nb_height_sprite ; i++)
    {
        if(m_terrainTab[i]!=NULL){
            free(m_terrainTab[i]) ;
            m_terrainTab[i] = NULL;
        }
    }

    if(m_terrainTab!=NULL){
        free(m_terrainTab);
        m_terrainTab = NULL;
    }

    if(m_terrainComplet!=NULL){
        delete m_terrainComplet ;
        m_terrainComplet = NULL;
    }
}

//SAUVERGARDER L'IMAGE DU TERRAIN
bool Terrain::saveBMP (std::string const& fileName) const
{
	return m_terrainComplet->saveBMP(fileName) ;
}

//RETOURNE LA SURFACE D'AFFICHAGE DU TERRAIN
SurfaceAffichage const& Terrain::terrainComplet() const
{
	return *m_terrainComplet ;
}



void Terrain::generer_le_terrain (string const& terrain_representation)
{

	//Création d'un tableau réprésentant les textures du terrain
    debugage_message("Vérification du format de la map et correction") ;
    m_terrainTab = 0 ;
    m_terrainTab = (char**)malloc(m_nb_height_sprite * sizeof(char*));
    for (unsigned short i = 0 ; i < m_nb_height_sprite ; i++)
    {
        m_terrainTab[i] = (char*)malloc(m_nb_width_sprite * sizeof(char));
    }

    //Remplissage par des cases d'herbes (lignes complétées si de tailles différentes)
    for (unsigned short l = 0 ; l < m_nb_height_sprite ; l++)
    {
        for (unsigned short i = 0; i < m_nb_width_sprite ; i++)
        {
            m_terrainTab[l][i] = 'G' ;
        }
    }

    //On indique les char du fichier dans le tableau
    unsigned short texte_curseur = 0 ;
    for (unsigned short l = 0 ; l < m_nb_height_sprite ; l++)
    {
        unsigned short i ;
        for (i = 0 ; terrain_representation[texte_curseur] != '\n' ; i++)
        {
        	//Verfication
        	char carac = terrain_representation[texte_curseur] ;
        	if (carac == 'w' || carac == 'W')
        		carac = 'W' ;
        	else
        		carac = 'G' ;

        	//Remplacement dans le tablleau
            m_terrainTab[l][i] = carac ;
            texte_curseur ++;
        }
        texte_curseur++ ;
    }
    
    debugage_message("Choix automatique du bon sprite pour chaque cas") ;
    //On remplace les cases d'eau par les bons sprites
	for (unsigned short x = 0 ; x < m_nb_width_sprite ; x++)
    {
        for (unsigned short y = 0 ; y < m_nb_height_sprite ; y++)
        {
            if(m_terrainTab[y][x] == 'W')
            {
            	short lettre_sprite = 0 ;
            	
            	if (x-1 < 0)
            		lettre_sprite += 8 ;
            	else if (m_terrainTab[y][x-1] == 'G')
            			lettre_sprite += 8 ;

            	if (y-1 < 0)
            		lettre_sprite += 4 ;
            	else if (m_terrainTab[y-1][x] == 'G')
            			lettre_sprite += 4 ;

            	if (x+1 >= m_nb_width_sprite)
            		lettre_sprite += 2 ;
            	else if (m_terrainTab[y][x+1] == 'G')
            			lettre_sprite += 2 ;

            	if (y+1 >= m_nb_height_sprite)
            		lettre_sprite += 1 ;
            	else if (m_terrainTab[y+1][x] == 'G')
            			lettre_sprite += 1 ;
            	
            	if (lettre_sprite >= 10)
            		lettre_sprite += 55 ;
            	else
            		lettre_sprite += 48 ;

            	m_terrainTab[y][x] = (char) lettre_sprite ;
            }
        }
    }

    //Affichage de test
    string texte_representation_terrain_final ;
    for (unsigned short l = 0 ; l < m_nb_height_sprite ; l++)
    {
        for (unsigned short i = 0 ; i < m_nb_width_sprite ; i++)
        {
            texte_representation_terrain_final += m_terrainTab[l][i] ;
        }
        texte_representation_terrain_final += "\n" ;
    }

    debugage_message("Représentation des sprites calculées : ") ;
    debugage_message(texte_representation_terrain_final) ;
    m_terrainComplet = new SurfaceAffichage(m_nb_width_sprite*MAP_CASE_SIZE, m_nb_height_sprite*MAP_CASE_SIZE, true) ;
    for (unsigned short x = 0 ; x < m_nb_width_sprite ; x++)
    {
        for (unsigned short y = 0 ; y < m_nb_height_sprite ; y++)
        {
            m_terrainComplet->ajouter(m_sprite, x*MAP_CASE_SIZE, y*MAP_CASE_SIZE, assocCodeToCaseSprite(m_terrainTab[y][x]) ) ;
        }
    }

}

//ASSOCIER UNE LETTRE DE REPRESENTATION AU NUMERO DU SPRITE
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
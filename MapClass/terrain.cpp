#include "terrain.h"
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std ;

string Terrain::nameSpriteTexture = "../ressources/SpriteMap64.bmp" ;

//GENERATION D'UN TEXTE REPRESENTANT LE TERRAIN A PARTIR D'UN FICHIER
Terrain::Terrain(string const& fileMap, list <MapPos>* & free_pos) : m_sprite(nameSpriteTexture, MAP_CASE_SIZE, MAP_CASE_SIZE, NB_SPRITE)
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
    }
    free_pos = new list <MapPos> ;
    generer_le_terrain(texte, free_pos) ;
}

//GENERATION ALEATOIRE D'UN TEXTE REPRESENTANT LE TERRAIN
Terrain::Terrain (unsigned short const& width, unsigned int const& height, list <MapPos>* & free_pos) : m_sprite(nameSpriteTexture, MAP_CASE_SIZE, MAP_CASE_SIZE, NB_SPRITE)
{

    m_nb_width_sprite = width ;
    m_nb_height_sprite = height ;


    //Création d'un tableau servant à la création aléatoire du terrain
    char ** terrainConstruction ;
    terrainConstruction = 0 ;
    terrainConstruction = (char**)malloc(m_nb_height_sprite * sizeof(char*));
    for (unsigned short i = 0 ; i < m_nb_height_sprite ; i++)
    {
        terrainConstruction[i] = (char*)malloc(m_nb_width_sprite * sizeof(char));
    }


    //L'algorithme augmente la probabilité que ce soit une case d'eau si d'autres sont déjà présente à proximité
    unsigned short pnvl = 5 ; // Probabilité (sur cent) d'obtenir un nouveau lac
    unsigned short patl = 45 ; // Probabilité (sur cent) d'augmenter la taille du lac pour une case minimum présente à côté
    unsigned short chance_eau ;
    unsigned short seuil ;
    for (unsigned short y = 0 ; y < height ; y++)
    {
        for (unsigned short x = 0 ; x < width ; x++)
        {
            chance_eau = rand() % 100 ;
            seuil = 0 ;

            if (x > 0)
            	if (terrainConstruction[y][x-1] == 'W')
                    seuil += patl ;

            if (y > 0)
                if (terrainConstruction[y-1][x] == 'W')
                    {
                        if (seuil == 0)
                            seuil += patl ;
                        else 
                            seuil += 0 ;
                    }

            if (y > 0 && x > 0)
                if (terrainConstruction[y-1][x-1] == 'W')
                    {
                        if (seuil == 0)
                            seuil += patl/4 ; //diagonale à une incidence minime
                        else if (seuil == patl)
                            seuil += 0 ;
                        else
                            seuil += 5 ;
                    }

            if (chance_eau < pnvl || chance_eau < seuil)
                terrainConstruction[y][x] = 'W' ;
            else
                terrainConstruction[y][x] = 'G' ;
        }
    }

    //Transformation du tableau en texte
    string texte = "" ;
    for (unsigned short y = 0 ; y < height ; y++)
    {
        for (unsigned short x = 0 ; x < width ; x++)
        {
            texte += terrainConstruction[y][x] ;
        }
        texte += '\n' ;
    }

    //Destruction du tableau de construction
    for (unsigned short i = 0 ; i < m_nb_height_sprite ; i++)
    {
        free(terrainConstruction[i]) ;
    }
    free(terrainConstruction) ;

    //Affichage et passage à la fonction qui génère l'affichage à partir du texte représentant le terrain
    debugage_message("map gènerée : ") ;
    debugage_message(texte) ;
    free_pos = new list <MapPos> ;
    generer_le_terrain(texte, free_pos) ;
}

//DESTRUCTEUR
Terrain::~Terrain()
{
    if (m_terrainComplet != NULL)
    {
        delete m_terrainComplet ;
        m_terrainComplet = NULL ;
    }
    else 
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_terrainComplet in ~Terrain()") ;

    if (m_sprite_representation != NULL)
    {
        delete(m_sprite_representation) ;
        m_sprite_representation = NULL ;
    }
    else 
        warning_message("Potentielle fuite de mémoire : Impossible de supprimer m_sprite_representation in ~Terrain()") ;

}

unsigned short Terrain::posxOut() const
{
    return m_nb_width_sprite ;
}

unsigned short Terrain::posyOut() const
{
    return m_nb_height_sprite ;
}

SpriteTexture const& Terrain::sprite() const
{
    return m_sprite ;
}

unsigned short Terrain::sprite_code (MapPos const& pos) const
{
    return assocCodeToCaseSprite((*m_sprite_representation)[pos]) ;
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

string Terrain::to_string() const
{
    return m_map_to_string ;
}

void Terrain::generer_le_terrain (string const& terrain_representation, std::list <MapPos>* free_pos)
{

	m_map_to_string = terrain_representation ;

    //Création d'un tableau réprésentant les textures du terrain
    debugage_message("Vérification du format de la map et correction ...") ;
    char ** terrainTab ;
    terrainTab = 0 ;
    terrainTab = (char**)malloc(m_nb_height_sprite * sizeof(char*));
    for (unsigned short i = 0 ; i < m_nb_height_sprite ; i++)
    {
        terrainTab[i] = (char*)malloc(m_nb_width_sprite * sizeof(char));
    }

    //Remplissage par des cases d'herbes (lignes complétées si de tailles différentes)
    for (unsigned short l = 0 ; l < m_nb_height_sprite ; l++)
    {
        for (unsigned short i = 0; i < m_nb_width_sprite ; i++)
        {
            terrainTab[l][i] = 'G' ;
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
            terrainTab[l][i] = carac ;
            texte_curseur ++;
        }
        texte_curseur++ ;
    }
    
    //On remplace les cases d'eau par les bons sprites
	for (unsigned short x = 0 ; x < m_nb_width_sprite ; x++)
    {
        for (unsigned short y = 0 ; y < m_nb_height_sprite ; y++)
        {
            if(terrainTab[y][x] == 'W')
            {
            	short lettre_sprite = 0 ;
            	
            	if (x-1 < 0)
            		lettre_sprite += 8 ;
            	else if (terrainTab[y][x-1] == 'G')
            			lettre_sprite += 8 ;

            	if (y-1 < 0)
            		lettre_sprite += 4 ;
            	else if (terrainTab[y-1][x] == 'G')
            			lettre_sprite += 4 ;

            	if (x+1 >= m_nb_width_sprite)
            		lettre_sprite += 2 ;
            	else if (terrainTab[y][x+1] == 'G')
            			lettre_sprite += 2 ;

            	if (y+1 >= m_nb_height_sprite)
            		lettre_sprite += 1 ;
            	else if (terrainTab[y+1][x] == 'G')
            			lettre_sprite += 1 ;
            	
            	if (lettre_sprite >= 10)
            		lettre_sprite += 55 ;
            	else
            		lettre_sprite += 48 ;

            	terrainTab[y][x] = (char) lettre_sprite ;
            }
        }
    }

    //Affichage de test
    string texte_representation_terrain_final ;
    for (unsigned short l = 0 ; l < m_nb_height_sprite ; l++)
    {
        for (unsigned short i = 0 ; i < m_nb_width_sprite ; i++)
        {
            texte_representation_terrain_final += terrainTab[l][i] ;
        }
        texte_representation_terrain_final += "\n" ;
    }
    debugage_message("Représentation des sprites calculées : ") ;
    debugage_message(texte_representation_terrain_final) ;


    m_terrainComplet = new SurfaceAffichage(m_nb_width_sprite*MAP_CASE_SIZE, m_nb_height_sprite*MAP_CASE_SIZE) ;
    m_sprite_representation = new map <MapPos, char> ;
    for (unsigned short x = 0 ; x < m_nb_width_sprite ; x++)
    {
        for (unsigned short y = 0 ; y < m_nb_height_sprite ; y++)
        {
            m_terrainComplet->ajouter(m_sprite, x*MAP_CASE_SIZE, y*MAP_CASE_SIZE, assocCodeToCaseSprite(terrainTab[y][x]) ) ;
            m_sprite_representation->insert(std::pair<MapPos,char>(MapPos(x,m_nb_height_sprite-1-y),terrainTab[y][x]));
            if(assocCodeToCaseSprite(terrainTab[y][x]) == 16)
            {
                free_pos->insert(free_pos->begin(), MapPos(x,m_nb_height_sprite-1-y)) ;
            }
        }
    }

    //Destruction de la variable locale terrainTab
    for (unsigned short i = 0 ; i < m_nb_height_sprite ; i++)
    {
        free(terrainTab[i]) ;
    }

    free(terrainTab) ;
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

    Warning("La map contient des caractères ne correspondant à aucun Sprite") ;
    return GRASS; //Ce sera donc de l'hebre
}

unsigned short Terrain::sprite_size() const
{
    return MAP_CASE_SIZE ;
}
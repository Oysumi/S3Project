#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include "SDL/SDL.h"

#include "fonctions.h"
#include "DisplayClass/texture.h"
#include "DisplayClass/fenetre.h"

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define MAP_CASE_SIZE 64
#define NB_SPRITE 17



short assocToSprite(char const& c)
{
    short n = (short) c ;
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
    return 16; //Ce sera donc de l'hebre
}




int main ( int args, char * argv[] )
{

    Fenetre fenetre("Title", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_HWSURFACE || SDL_DOUBLEBUF) ;
    SpriteTexture spriteTerrain("ressources/SpriteMap64.bmp", MAP_CASE_SIZE, NB_SPRITE) ;
    debugage_message("Création de la fenêtre et du sprite de Terrain") ;

    

    //ANALYSE DU FICHIER DU TERRAIN
    string texte, ligne ;
    unsigned short longueur_max_ligne = 0 ;
    unsigned short nb_de_lignes = 0 ;
    ifstream fichier ("ressources/map.txt");
    if ( fichier )
    {
        while (getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
        {
            texte += ligne + '\n' ;
            nb_de_lignes++ ;
            if (ligne.size() > longueur_max_ligne)
                longueur_max_ligne = ligne.size() ;
        }
    }
    else
    {
        erreur_message("Impossible d'ouvrir le fichier de la Map");
        cout << "impossible" << endl ;
    }

    debugage_message("Lecture du fichier de terrain") ;


    //Création d'un tableau réprésentant les textures du terrain
    char ** terrain = 0 ;
    terrain = (char**)malloc(nb_de_lignes * sizeof(char*));
    for (unsigned short i = 0 ; i < nb_de_lignes ; i++)
    {
        terrain[i] = (char*)malloc(longueur_max_ligne * sizeof(char));
    }

    //Remplissage par des cases d'herbes (lignes complétées si de tailles différentes)
    for (unsigned short l = 0 ; l < nb_de_lignes ; l++)
    {
        for (unsigned short i = 0; i < longueur_max_ligne ; i++)
        {
            terrain[l][i] = 'G' ;
        }
    }

    //On indique les char du fichier dans le tableau
    unsigned short texte_curseur = 0 ;
    for (unsigned short l = 0 ; l < nb_de_lignes ; l++)
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
    for (unsigned short l = 0 ; l < nb_de_lignes ; l++)
    {
        for (unsigned short i = 0 ; i < longueur_max_ligne ; i++)
        {
            texte += terrain[l][i] ;
        }
        texte += "\n" ;
    }
    debugage_message("Vérfication et correction de celui-ci") ;
    debugage_message(texte) ;
    
    
    //EVENT LOOP
    debugage_message("Début du Jeu") ;
    SDL_Event event ;
    bool end = false ;
    while (!end)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    end = true ;
                    break ;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            end = true ;
                            break ;
                            
                        default:
                            break;
                    }
                    break;
            }
        }
        for (unsigned short x = 0 ; x < longueur_max_ligne ; x++)
        {
            for (unsigned short y = 0 ; y < nb_de_lignes ; y++)
            {
                spriteTerrain.ajouterA( fenetre, x*MAP_CASE_SIZE, y*MAP_CASE_SIZE, assocToSprite(terrain[y][x]) ) ;
            }
        }
        fenetre.actualiser() ;

    }
    debugage_message("Fin du Jeu") ;
    return 0 ;
}
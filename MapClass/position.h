#ifndef DEF_POSITION
#define DEF_POSITION

#include <ostream>

//Classe très classiques permettant de gérer les positions sur la Map plus simplement
class MapPos
{
    public :
        MapPos(unsigned short const& x, unsigned short const& y) ;
        MapPos(MapPos const& aCopier) ;
        unsigned short x () const ;
        unsigned short y () const ;

        //fonctions utilisées pour le déplacement des unités
        unsigned short separation_value(MapPos const& pos) const ;
        bool adjacent(MapPos const& pos, unsigned short nb_cases_de_separation = 1) const ;

        //Opérateur d'égalité, d'affichage et de comparaison pour certains conteneurs de la STL
        friend bool operator==(MapPos const& a, MapPos const& b);
        friend bool operator<(MapPos const& a, MapPos const& b);
        friend std::ostream &operator<<( std::ostream &flux, MapPos const& pos);
    
    private :
        //méthode privées utilisées par les trois opérateurs
    	bool estegala(MapPos const& b) const;
    	bool estpluspetitque(MapPos const& b) const;
    	void afficher(std::ostream &flux) const;
        
    private :
	    unsigned short m_x ;
	    unsigned short m_y ;

};

//Opérateur d'égalité, d'affichage et de comparaison pour certains conteneurs de la STL
bool operator==(MapPos const& a, MapPos const& b);
bool operator!=(MapPos const& a, MapPos const& b);
bool operator<(MapPos const& a, MapPos const& b);
std::ostream &operator<<( std::ostream &flux, MapPos const& pos);

#endif
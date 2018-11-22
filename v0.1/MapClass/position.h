#ifndef DEF_POSITION
#define DEF_POSITION

#include <ostream>

class MapPos
{
    public :
        MapPos(unsigned short const& x, unsigned short const& y) ;
        MapPos(MapPos const& aCopier) ;
        unsigned short x () const ;
        unsigned short y () const ;

        friend bool operator==(MapPos const& a, MapPos const& b);
        friend bool operator<(MapPos const& a, MapPos const& b);
        friend std::ostream &operator<<( std::ostream &flux, MapPos const& pos);
    
    private :
    	bool estegala(MapPos const& b) const;
    	bool estpluspetitque(MapPos const& b) const;
    	void afficher(std::ostream &flux) const;
        
    private :
	    unsigned short m_x ;
	    unsigned short m_y ;

};

bool operator==(MapPos const& a, MapPos const& b);
bool operator<(MapPos const& a, MapPos const& b);
std::ostream &operator<<( std::ostream &flux, MapPos const& pos);

#endif
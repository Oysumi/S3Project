#ifndef DEF_POSITION
#define DEF_POSITION

class MapPos
{
    public :
        MapPos(unsigned short const& x, unsigned short const& y) ;
        unsigned short x () const ;
        unsigned short y () const ;
        
    private :
	    unsigned short m_x ;
	    unsigned short m_y ;

};


#endif
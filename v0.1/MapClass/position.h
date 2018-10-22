#ifndef DEF_POSITION
#define DEF_POSTION

class MapPos
{
    public :
        MapPos(unsigned int const& x, unsigned int const& y) ;
        unsigned short x () const ;
        unsigned short y () const ;
        
    private :
	    unsigned short m_x ;
	    unsigned short m_y ;

};


#endif
#ifndef DEF_CONSTRUCTION
#define DEF_CONSTRUCTION

#include <string>
#include "../MapClass/objetmobile.h"

class Construction : public ObjetMobile
{
    public :
    	Construction(std::string const& texture_path, MapPos const& pos, AbstractPlayer* proprietaire) ;
        Construction(Construction const& aCopier) ;
        ~Construction() ;
};


#endif
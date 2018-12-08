#include "construction.h"
#include "SDL/SDL.h"
using namespace std;

Construction::Construction(std::string const& texture_path, MapPos const& pos, AbstractPlayer* proprietaire) :
	ObjetMobile(texture_path, pos, proprietaire) {}

Construction::Construction(Construction const& aCopier) :
	ObjetMobile(aCopier) {}

Construction::~Construction()
{
	cout << "===========================================" << endl ;
	cout << "Debut destruction construction..." << endl ;
	if (m_texture != NULL)
	{
		delete m_texture ;
		m_texture = NULL ;
	}
	cout << "Fin destruction construction." << endl ;
	cout << "===========================================" << endl ;
}
#include "AbstractUnit.h"

using namespace std ;

AbstractUnit::AbstractUnit() : 
m_name("Cavaliers"), m_health(100), m_strength(0), m_unit_size(0), m_unit_posx(0), m_unit_posy(0)
{ }

AbstractUnit::AbstractUnit(std::string name, short int strength, unsigned short int size, unsigned short int posx, unsigned short int posy) :
m_name(name), m_health(100), m_strength(strength), m_unit_size(size), m_unit_posx(posx), m_unit_posy(posy)
{ }

AbstractUnit::~AbstractUnit()
{ }



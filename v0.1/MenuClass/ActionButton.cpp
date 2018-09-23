#include "ActionButton.h"
#include <string>

using namespace std ;

// We are going to redefine these constructor according to our choice of the representation of the action ID

ActionButton::ActionButton() : m_id_f(0), m_id_s("")
{ }

ActionButton::ActionButton(unsigned short int idToSet) : m_id_f(idToSet), m_id_s("")
{ }

ActionButton::ActionButton(string idToSet) : m_id_f(0), m_id_s(idToSet)
{ }

void ActionButton::setId(unsigned short int idToSet)
{
	m_id_f = idToSet ;
}

void ActionButton::setId(string idToSet)
{
	m_id_s = idToSet ;
}

ActionButton::~ActionButton()
{ }
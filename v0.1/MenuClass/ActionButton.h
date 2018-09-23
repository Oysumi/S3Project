#ifndef __ACTIONBUTTON_H__
#define __ACTIONBUTTON_H__

#include "AbstractButton.h"
#include <string>

class ActionButton : AbstractButton
{
	public:
		ActionButton() ;
		ActionButton(unsigned short int idToSet) ;
		ActionButton(std::string idToSet) ;
		void setId(unsigned short int idToSet) ;
		void setId(std::string idToSet) ;
		~ActionButton() ;
	protected:
		// we're going to choose which one is the better between these two options (int vs string)
		unsigned short int m_id_f ; // 1)
		std::string m_id_s ;
};

#endif // __ACTIONBUTTON_H__
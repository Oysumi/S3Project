#ifndef __RESSOURCES_H__
#define __RESSOURCES_H__

#include <string>


//Classe assez basique permettant de stocker des ressources
class Ressource
{
	public :
		Ressource() ;
		Ressource(int gold, short wood, short food) ;

		int gold () const ;
		short wood () const ;
		short food () const ;

		void set_gold(int gold) ;
		void set_wood(short wood) ;
		void set_food(short food) ;

		void add_gold(int gold) ;
		void add_wood(short wood) ;
		void add_food(short food) ;

		void del_gold(int gold) ;
		void del_wood(short wood) ;
		void del_food(short food) ;

		void operator+=(Ressource const& res);

	private :
		int m_gold ;
		short m_wood ;
		short m_food ;
};

#endif // __RESSOURCES_H__
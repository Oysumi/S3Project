#include "remplissage.h"

using namespace std ;

vector<AbstractButton*> remplissage(){
	vector<AbstractButton*> test ;

	test.push_back(new ActionButton(12, "TEST", 110, 100, 100, 100, {255, 255, 255}, {0, 0, 0})) ;

	return test ;
}

void deleteVect(vector<AbstractButton*> tab){
	for (AbstractButton * abbuton : tab){
		delete abbuton ;
	}
}


#include <iostream>
#include <vector>

#include "Noeud.hpp"
using namespace std;

////////////////////////////////////////////////////////////
Noeud* Noeud::trouveFils(char c){
	for(int i=0;i<vFils.size();i++){
		Noeud* tmp = vFils.at(i);
		if(tmp->getLabel()==c){return tmp;}
	}
	return NULL;
}

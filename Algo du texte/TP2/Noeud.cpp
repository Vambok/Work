#include <iostream>
#include <vector>

#include "Noeud.hpp"
using namespace std;

////////////////////////////////////////////////////////////
Noeud* Noeud::trouveFils(char c){
	Noeud* tmp;
	int taille=vFils.size();

	for(int i=0;i<taille;i++){
		tmp = vFils[i];
		if(tmp->getLabel()==c){return tmp;}
	}

	return NULL;
}

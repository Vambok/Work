#ifndef H_ARBRE
#define H_ARBRE

#include <iostream>
#include "Noeud.cpp"

// Les fonctions ci dessous ne sont pas implantées.

class Arbre{
	Noeud* racine;
	int nextIndice;
public:
	Arbre(){racine = new Noeud;nextIndice = 0;}
	Arbre(std::list<std::string> tabMotifs){
		racine = new Noeud;
		nextIndice = 0;
		std::list<std::string>::iterator it;
		for(it=tabMotifs.begin();it!=tabMotifs.end();it++){ajoutMot(*it);}
	}
	~Arbre(){delete racine;}
	Noeud* getRacine(){return racine;}

//INDEFINIS :
	void ajoutMot(std::string s);
	void ajoutMot(std::string s,int indice);
	bool trouveMot(std::string s);
	void supprMot(std::string s);
//	int trouvePref(std::string s,int deb);

	Noeud* trouveMotAdv(std::string s);
	void calculeErreur();
	std::string recherchePref(std::string s);
	void afficheArbre(Noeud* noeud);
};

#endif

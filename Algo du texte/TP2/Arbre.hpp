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
/*	Arbre(std::string texte){
		racine = new Noeud;
		nextIndice = 0;
		for(int i=0;i<texte.size();i++){ajoutMot(texte.substr(i,texte.size()-i));}
		suffixize(racine);
	}
*/
	Arbre(std::list<std::string> tabMotifs){
		racine = new Noeud;
		nextIndice = 0;
		for(std::list<std::string>::iterator it=tabMotifs.begin();it!=tabMotifs.end();it++){ajoutMot(*it);}
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
	void calculeErreur(bool amelioree);
	std::string recherchePref(std::string s);
	void afficheArbre(Noeud* noeud);
//	void suffixize(Noeud* noeud);
};

#endif

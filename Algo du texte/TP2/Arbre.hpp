#ifndef H_ARBRE
#define H_ARBRE

#include <iostream>
#include "Noeud.cpp"

// Les fonctions ci dessous ne sont pas implantées.

class Arbre{
	Noeud* racine;
	int nextIndice;
	int steptime;
public:
	Arbre(){racine = new Noeud;nextIndice = 0;steptime = 5;}
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
		steptime = 8;
		for(std::list<std::string>::iterator it=tabMotifs.begin();it!=tabMotifs.end();it++){ajoutMot(*it);steptime+=2;}
	}
	~Arbre(){delete racine;}
	Noeud* getRacine(){steptime++;return racine;}
	int getTime(){int buffer=steptime;steptime=0;return buffer;}

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

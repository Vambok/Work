#ifndef H_NOEUD
#define H_NOEUD
#include <iostream>
#include <vector>

const int NON_FIN_MOTIF = -1;

class Noeud{
	char label; // caractere label de l'arc qui mene au noeud
	int finMotif; // int indiquant le mot dont le noeud est la fin
	std::vector<Noeud*> vFils;
//	int lgMot;
	Noeud* echec;
//	Noeud* autre;

public:
	// constructeur
//	Noeud() { label = ' '; finMotif = NON_FIN_MOTIF; lgMot = 0; echec = NULL; autre = NULL; }
	Noeud(char inchar = ' ',int infinMotif = NON_FIN_MOTIF){
		label = inchar;
		finMotif = infinMotif;
		echec = NULL;
	}
	// destructeur
	~Noeud(){
		std::vector<Noeud*>::iterator it;
		for(it=vFils.begin();it!=vFils.end();it++){delete *it;}
	}

	// renvoie label d'un noeud
	char getLabel(){return label;}
	// affecte le label d'un noeud
	void setLabel(char c){label = c;}
	// teste si le noeud represente un motif complet et renvoie un booleen
	bool estFinMotif(){if(finMotif > NON_FIN_MOTIF){return true;}else{return false;}}
//	void setLgMot(int lg){lgMot = lg;}
	void setEchec(Noeud* unNoeud){echec = unNoeud;}
//	void setAutre(Noeud* unNoeud){autre = unNoeud;}
	Noeud* getEchec(){return echec;}
	// renvoie un entier representant le mot dont le noeud est la fin
	int quelMotif(){return finMotif;}
	// affecte l'item finMotif du noeud
	void setFinMotif(int numero = NON_FIN_MOTIF){finMotif = numero;}

	void ajoutFils(Noeud* fils){vFils.push_back(fils);}
	void supprFils(Noeud* fils){vFils.erase(find(vFils.begin(),vFils.end(),fils));}
	std::vector<Noeud*> lesFils(){return vFils;}

//INDEFINIS :
	// renvoie le fils dont le label est c s'il existe et null sinon
	Noeud* trouveFils(char c);
};

#endif

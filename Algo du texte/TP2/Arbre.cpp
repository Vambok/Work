#include <iostream>
#include <vector>
#include <queue>

#include "Arbre.hpp"
using namespace std;

void Arbre::ajoutMot(string s){ajoutMot(s,nextIndice);}
void Arbre::ajoutMot(string s,int indice){
	Noeud* noeudcourant = racine;
	Noeud* noeudsuivant;
	int i = 0;

	if(indice>=nextIndice){nextIndice = indice+1;}

	while(i<s.length()){
		noeudsuivant = (*noeudcourant).trouveFils(s[i]);
		if(!noeudsuivant){
			while(i<s.length()){
				noeudsuivant = new Noeud(s[i]);
				(*noeudcourant).ajoutFils(noeudsuivant);
				noeudcourant = noeudsuivant;
				i++;
			}
		}
		noeudcourant = noeudsuivant;
		i++;
	}
	(*noeudcourant).setFinMotif(indice);
}

Noeud* Arbre::trouveMotAdv(string s){
	Noeud* noeudcourant = racine;
	Noeud* noeudsuivant;

	for(int i=0;i<s.length();i++){
		noeudsuivant = (*noeudcourant).trouveFils(s[i]);
		if(!noeudsuivant){return NULL;}
		noeudcourant = noeudsuivant;
	}
	return noeudcourant;
}

bool Arbre::trouveMot(string s){
	Noeud* noeudtrouve = trouveMotAdv(s);
	if(noeudtrouve){
		if((*noeudtrouve).estFinMotif()){return true;}
	}
	return false;
}

void Arbre::supprMot(string s){
	vector<Noeud*> mot;int j;
	Noeud* noeudcourant = racine;
	Noeud* noeudsuivant;

	for(int i=0;i<s.length();i++){
		mot.push_back(noeudcourant);
		noeudsuivant = (*noeudcourant).trouveFils(s[i]);
		if(!noeudsuivant){return;}
		noeudcourant = noeudsuivant;
	}
	if((*noeudcourant).estFinMotif()){
		(*noeudcourant).setFinMotif();
		j = mot.size()-1;
		while(noeudcourant!=racine){
			if((*noeudcourant).lesFils().empty()){
				noeudsuivant = mot[j];
				(*noeudsuivant).supprFils(noeudcourant);
				delete(noeudcourant);
				noeudcourant = noeudsuivant;
				j++;
			}else{return;}
		}
	}
}

void Arbre::calculeErreur(){
	queue<pair<Noeud*,string> > todo;
	todo.push(pair<Noeud*,string>(racine,""));
	Noeud* noeudcourant;
	Noeud* noeudcible;
	string motcourant;
	string motcible;
	vector<Noeud*> fils;

	while(!todo.empty()){
		noeudcourant = todo.front().first;
		motcourant = todo.front().second;
//		for(it=(*noeudcourant).lesFils().begin();it!=(*noeudcourant).lesFils().end();it++){
		fils = (*noeudcourant).lesFils();
		for(int i=0;i<fils.size();i++){
			motcible = motcourant+(*fils[i]).getLabel();
			todo.push(pair<Noeud*,string>(fils[i],motcible));
			for(int j=1;j<motcible.size();j++){
				noeudcible = trouveMotAdv(motcible.substr(j,motcible.size()-j));
				if(noeudcible){break;}
			}
			if(noeudcible){
				(*fils[i]).setEchec(noeudcible);
				noeudcible = NULL;
			}else{(*fils[i]).setEchec(racine);}
		}
		todo.pop();
	}
	(*racine).setEchec(racine);
}

void Arbre::afficheArbre(Noeud* noeud){
	vector<Noeud*> fils;

	cout<<(*noeud).getLabel();
	if((*noeud).estFinMotif()){cout<<"["<<(*noeud).quelMotif()<<"]";}
	cout<<"{"<<(*((*noeud).getEchec())).getLabel()<<"}(";
	fils = (*noeud).lesFils();
	for(int i=0;i<fils.size();i++){
		afficheArbre(fils[i]);
	}
	cout<<")";
}

string Arbre::recherchePref(string s){
	Noeud* noeudcourant = racine;
	int i;

	for(i=0;i<s.length();i++){
		noeudcourant = (*noeudcourant).trouveFils(s[i]);
		if(!noeudcourant){break;}
	}
	return s.substr(0,i);
}

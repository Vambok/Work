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

void Arbre::calculeErreur(){calculeErreur(false);}
void Arbre::calculeErreur(bool amelioree){
	queue<Noeud*> todo;
	todo.push(racine);
	Noeud* noeudcourant;
	Noeud* noeudcible = NULL;
	vector<Noeud*> fils;

	while(!todo.empty()){
		noeudcourant = todo.front();
		fils = (*noeudcourant).lesFils();
		for(int i=0;i<fils.size();i++){
			todo.push(fils[i]);
			noeudcible = noeudcourant;
			while(noeudcible!=racine){
				noeudcible = (*noeudcible).getEchec();
				if((*noeudcible).trouveFils((*fils[i]).getLabel())){
					noeudcible = (*noeudcible).trouveFils((*fils[i]).getLabel());
					if(amelioree){ //liens d'echec ameliores
						while(noeudcible!=racine){
							int k;for(k=(*noeudcible).lesFils().size()-1;k>-1;k--){
								if((*fils[i]).trouveFils((*((*noeudcible).lesFils())[k]).getLabel())==NULL){
									k = -1; //<=> break 2; si la cible a un fils qu'on n'a pas car le LE est optimal
								}
							}
							if(k<-1){break;
							}else{ //si tout echec sur soi est aussi un echec sur la cible
								if(!(*fils[i]).estFinMotif()&&(*noeudcible).estFinMotif()){
									(*fils[i]).setFinMotif((*noeudcible).quelMotif()); //heritage du motif eventuel
								}
								noeudcible=(*noeudcible).getEchec(); //passage au LE suivant
							}
						}
					}
					break;
				}
			}
			(*fils[i]).setEchec(noeudcible);
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

/*int lafter int minmotif suffixize(Noeud* pere,int lbefore){
	vector<Noeud*> fils = (*pere).lesFils();
	pair<int> interval;

	if(fils.size()<1){
		interval = pair<int>(1,(*pere).quelMotif());
		(*pere).interval = pair<int>(lbefore+interval.second,lbefore+interval.second);
		return interval;
	}else if(fils.size()==1){
		interval = suffixize(fils[0],lbefore+1);
		(*pere).interval = pair<int>(lbefore+interval.second,lbefore+interval.second+interval.first);
		interval.first++;
		return interval;
	}else{
		for(int i=0;i<fils.size();i++){
			suffixize(fils[i]);
		}
	}
	return s.substr(0,i);
}*/

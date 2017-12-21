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

	steptime+=10;
	if(indice>=nextIndice){steptime++;nextIndice = indice+1;}

	while(i<s.length()){
		steptime+=14+5*(*noeudcourant).lesFils().size();
		noeudsuivant = (*noeudcourant).trouveFils(s[i]);
		if(!noeudsuivant){
			steptime+=2;
			while(i<s.length()){
				steptime+=11;
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
	steptime+=8;

	for(int i=0;i<s.length();i++){
		steptime+=11+5*(*noeudcourant).lesFils().size();
		noeudsuivant = (*noeudcourant).trouveFils(s[i]);
		if(!noeudsuivant){return NULL;}
		steptime+=3;
		noeudcourant = noeudsuivant;
	}
	return noeudcourant;
}

bool Arbre::trouveMot(string s){
	Noeud* noeudtrouve = trouveMotAdv(s);
	steptime+=4;
	if(noeudtrouve){
		steptime+=3;
		if((*noeudtrouve).estFinMotif()){return true;}
	}
	return false;
}

void Arbre::supprMot(string s){
	vector<Noeud*> mot;int j;
	Noeud* noeudcourant = racine;
	Noeud* noeudsuivant;
	steptime+=9;

	for(int i=0;i<s.length();i++){
		steptime+=12+5*(*noeudcourant).lesFils().size();
		mot.push_back(noeudcourant);
		noeudsuivant = (*noeudcourant).trouveFils(s[i]);
		if(!noeudsuivant){return;}
		noeudcourant = noeudsuivant;
		steptime+=3;
	}
	steptime+=3;
	if((*noeudcourant).estFinMotif()){
		steptime+=5;
		(*noeudcourant).setFinMotif();
		j = mot.size()-1;
		while(noeudcourant!=racine){
			steptime+=4;
			if((*noeudcourant).lesFils().empty()){
				steptime+=6+3+(*noeudcourant).lesFils().size();
				noeudsuivant = mot[j];
				(*noeudsuivant).supprFils(noeudcourant);
				delete(noeudcourant);
				noeudcourant = noeudsuivant;
				j++;
			}else{return;}
		}
	}
}

void Arbre::calculeErreur(){steptime++;calculeErreur(false);}
void Arbre::calculeErreur(bool amelioree){
	queue<Noeud*> todo;
	todo.push(racine);
	Noeud* noeudcourant;
	Noeud* noeudcible = NULL;
	vector<Noeud*> fils;
	steptime+=9;

	while(!todo.empty()){
		steptime+=11;
		noeudcourant = todo.front();
		fils = (*noeudcourant).lesFils();
		for(int i=0;i<fils.size();i++){
			steptime+=10;
			todo.push(fils[i]);
			noeudcible = noeudcourant;
			while(noeudcible!=racine){
				steptime+=14+5*(*noeudcible).lesFils().size();
				noeudcible = (*noeudcible).getEchec();
				if((*noeudcible).trouveFils((*fils[i]).getLabel())){
					steptime+=12+5*(*noeudcible).lesFils().size();
					noeudcible = (*noeudcible).trouveFils((*fils[i]).getLabel());
					if(amelioree){ //liens d'echec ameliores
						steptime++;
						while(noeudcible!=racine){
							steptime+=8;
							int k;for(k=(*noeudcible).lesFils().size()-1;k>-1;k--){
								steptime+=14+5*(*fils[i]).lesFils().size();
								if((*fils[i]).trouveFils((*((*noeudcible).lesFils())[k]).getLabel())==NULL){
									steptime++;
									k = -1; //<=> break 2; si la cible a un fils qu'on n'a pas car le LE est optimal
								}
							}
							if(k<-1){break;
							}else{ //si tout echec sur soi est aussi un echec sur la cible
								steptime+=10;
								if(!(*fils[i]).estFinMotif()&&(*noeudcible).estFinMotif()){
									steptime+=5;
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

	steptime+=8;
	for(i=0;i<s.length();i++){
		steptime+=11+5*(*noeudcourant).lesFils().size();
		noeudcourant = (*noeudcourant).trouveFils(s[i]);
		if(!noeudcourant){break;}
		steptime+=2;
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

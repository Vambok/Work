/*==========================================================================
Cours d'algorithmique du texte HMSN116M - Universite Montpellier 2 - 2017-18

Cree par Severine Berard, modifie par Peter-Mikhael Richard
==========================================================================*/
#include <iostream>
#include <fstream> //pour lire les fichiers
#include <string>
#include <map> //pour les tableaux associatifs
#include <algorithm> //pour min et fill_n
#include <list>

#include "Arbre.cpp"
using namespace std;

/*
// NAIF
void naif(string P, int m, string T, int n)
{
int j,occurences=0,steps=0;
	for(int i=0;i<n-m+1;i++){
		for(j=0;j<m;j++){
			steps++;
			if(T[i+j+1]!=P[j+1]){
				break;
			}
		}
		if(j==m){
			occurences++;
		}
	}
	cout<<"J'ai trouve "<<occurences<<" occurences de P dans T en "<<steps<<" etapes."<<endl;
}

// MP
int * calcule_MP_next(string P, int m)
{
int* MP_next=new int[m+1];
int j=-1;
	MP_next[0]=-1;
	for(int i=0;i<m;i++){
		while((j>=0)&&(P[i+1]!=P[j+1])){
			j=MP_next[j];
		}
		j++;
		MP_next[i+1]=j;
	}
return MP_next;
}

void MP(string P, int m, string T, int n, int* MP_next)
{
int j=0,steps=0,occurences=0;
	for(int i=0;i<n-m+1;i++){
		while(j>=0){
			steps++;
			if(T[i+1]!=P[j+1]){
				j=MP_next[j];
			}else{
				break;
			}
		}
		j++;
		if(j==m){
			occurences++;
			j=MP_next[j];
		}
	}
	cout<<"J'ai trouve "<<occurences<<" occurences de P dans T en "<<steps<<" etapes."<<endl;
delete [] MP_next;
}

// KMP
int * calcule_KMP_next(string P, int m)
{
int* KMP_next=new int[m+1];
int j=-1;
	KMP_next[0]=-1;
	for(int i=0;i<m;i++){
		while((j>=0)&&(P[i+1]!=P[j+1])){
			j=KMP_next[j];
		}
		j++;
		if(i>m-2){
			KMP_next[i+1]=j;
		}else if(P[i+2]!=P[j+1]){
			KMP_next[i+1]=j;
		}else{
			KMP_next[i+1]=KMP_next[j];
		}
	}
return KMP_next;
}

// Boyer-Moore
int * calcule_suff(string P, int m)
{
int* suff = new int[m];suff[m-1] = m;
int g = m;int f;
	for(int i=m-1;i>0;i--){
		if((i>g)&&(suff[i+m-f-1]!=i-g)){
			suff[i-1]=min(suff[i+m-f-1],i-g);
		}else{
			f=i;g=min(g,i);
			while((g>0)&&(P[g]==P[g+m-f])){g--;}
			suff[i-1]=f-g;
		}
	}
return suff;
}

int * calcule_D(string P, int m)
{
int* suff = calcule_suff(P,m);
int* D = new int[m+1];fill_n(D,m,m);
int j = 1;
	for(int i=m-1;i>=0;i--){
		if((i==0)||(suff[i-1]==i)){
			while(j<=m-i){
				D[j] = m-i;
				j++;
			}
		}
	}
	for(int i=1;i<m;i++){
		D[m-suff[i-1]] = m-i;
	}
delete [] suff;
return D;
}

map<char,list<int> > calcule_R(string P, int m)
{
map<char,list<int> > table;
	for(int i=1;i<=m;i++){
		if(table[P[i]].size()==0){
			table[P[i]] = list<int>(1,i);
		}else{
			table[P[i]].push_front(i);
		}
	}
//for(int i=1;i<m+1;i++){
//	list<int>::iterator it;
//	for(it=table[P[i]].begin();it!=table[P[i]].end();it++){
//		cout<<*it<<endl;
//	}
//}
return table;
}

void BM(string P, int m, string T, int n, bool forte=false)
{
int* D=calcule_D(P,m);
map<char,list<int> > R=calcule_R(P,m);
int i=1, occurences=0, steps=0;
	while(i<n-m+2){
		int j = m;
		while(j>0){
			steps++;
			if(P[j]!=T[i+j-1]){break;}
			j--;
		}
		if(j==0){
			occurences++;cout<<i<<endl;
			i+=D[1];
		}else{
			if(forte){
				list<int> k = R[T[i+j-1]];
				list<int>::iterator it;
				for(it=k.begin();it!=k.end();it++){
					if(*it<j){break;}
				}
				i+=max(D[j],j-*it);
			}else{
				i+=max(D[j],j-R[T[i+j-1]].front());
			}
		}
	}
	cout<<"J'ai trouve "<<occurences<<" occurences de P dans T en "<<steps<<" etapes."<<endl;
delete [] D;
}

// TVSBS
// Decalage :
// m+2-max(R(ab),R(b))
// =
// MVB	 TVSBS=R(ab)
// avec R:
// max:  min:
// m+1	  1		: P[m]='a'
// i+1	m-i+1	: P[i]P[i+1]='ab'
//  1	 m+1	: P[1]='b'
//  0	 m+2
map<unsigned short,int> calcule_biR(string P, int m)
{
map<unsigned short,int> table;
list<unsigned char> pattern_alphabet = list<unsigned char>(1,0);
list<unsigned char>::iterator it;
unsigned char currentchar = P[1];
	pattern_alphabet.push_back(currentchar);
	table[currentchar] = 1;	//P[1]='b'
	for(int i=2;i<=m;i++){
		table[currentchar<<8|(unsigned char)P[i]] = i+1;	//P[i]P[i+1]='ab'
		currentchar = P[i];
		for(it=pattern_alphabet.begin();it!=pattern_alphabet.end();it++){
			if(*it>currentchar){
				pattern_alphabet.insert(it,currentchar);
				break;
			}else if(*it==currentchar){
				break;
			}
		}
	}
	for(it=pattern_alphabet.begin();it!=pattern_alphabet.end();it++){
		table[(currentchar<<8)|*it] = m+1;	//P[m]='a'
	}
return table;
}

void TVSBS(string P, int m, string T, int n)
{
map<unsigned short,int> R=calcule_biR(P,m);
unsigned char currentusc;
int i=1, occurences=0, steps=0,j; //i:premier indice de T dans fen ; j:indice dans fen

while(i<n-m+2){
	//Stage1:
	steps++;
	if(T[i+m-1]==P[m]){
	steps++;
	if(T[i]==P[1]){
	//Stage2:
		for(j=m-1;j>1;j--){
			steps++;
			if(T[i+j-1]!=P[j]){break;}
		}if(j<2){occurences++;cout<<i<<endl;}
	}}
	//Stage3:
	steps++;
	if(i>n-m){i++;}else{if(i==n-m){currentusc=0;}else{currentusc=(unsigned char)T[i+m+1];}//gestion de fin de chaine
	int k = m+2-max(R[(unsigned char)T[i+m]<<8|currentusc],R[currentusc]);cout<<k<<endl;i += k;}
}
cout<<"J'ai trouve "<<occurences<<" occurences de P dans T en "<<steps<<" etapes."<<endl;
}
*/

// multi-motifs
void recherche_multi(list<string> P, string T){
	Arbre* tree = new Arbre(P);
	Noeud* racine = (*tree).getRacine();
	Noeud* noeudcourant = racine;
	Noeud* noeudsuivant;
	int i = 0;
	(*tree).calculeErreur();

	(*tree).afficheArbre(noeudcourant);cout<<endl;
	while(i<T.size()){
		noeudsuivant = (*noeudcourant).trouveFils(T[i]);
		if(!noeudsuivant){
			if(noeudcourant!=racine){
				if((*noeudcourant).estFinMotif()){
					cout<<"Occurence du motif "<<(*noeudcourant).quelMotif()<<" a la position de fin "<<i<<endl;
				}
				i--;
			}
			noeudsuivant = (*noeudcourant).getEchec();
		}
		noeudcourant = noeudsuivant;
		i++;
	}
	delete(tree);
}
void recherche_multi_naif(list<string> P, string T){
	Arbre* tree = new Arbre(P);
	Noeud* noeudcourant;
	Noeud* noeudsuivant = (*tree).getRacine();
	int j,i=0;

	while(i<T.size()){
		j = 0;
		while(noeudsuivant){
			noeudcourant = noeudsuivant;
			if(i+j>=T.size()){break;}
			noeudsuivant = (*noeudcourant).trouveFils(T[i+j]);
			j++;
		}
		if((*noeudcourant).estFinMotif()){
			cout<<"Occurence du motif "<<(*noeudcourant).quelMotif()<<" a la position de fin "<<i+j<<endl;
		}
		noeudsuivant = (*tree).getRacine();
		i++;
	}
	delete(tree);
}

///////////////////////////////////////
int main(int argc, char** argv){
if(argc != 3){
	cout<<"Mauvaise utilisation du programme "<<argv[0]<<", on attend : "<<argv[0]<<" ficMotif ficTexte"<<endl;
}else{
	string line;
	/* Lecture des motifs */
	string nomFicMotif(argv[1]);
	ifstream IfFicMotif(nomFicMotif.c_str(),ios::in);
	if(!IfFicMotif){
		cout<<endl<<"Impossible d'ouvrir le fichier : "<<nomFicMotif<<endl;
		return(0);
	}
	list<string> P;
	list<string>::iterator it;
	while(getline(IfFicMotif,line)){P.push_back(line);}
	IfFicMotif.close();
	int m=P.front().size();

	/* Lecture du texte */
	string nomFicTexte(argv[2]);
	ifstream IfFicTexte (nomFicTexte.c_str(), ios::in);
	if(!IfFicTexte){
		cout<<endl<<"Impossible d'ouvrir le fichier : "<<nomFicTexte<<endl;
		return(0);
	}
	string T;
	while(getline(IfFicTexte,line)){T+=line+'\n';}
	T=T.substr(0,T.size()-1);
	int n=T.size();

	cout<<"********************************************************************"<<endl;
	cout<<"Recherche d"<<((P.size()==1)?"u motif":"es motifs");
	for(it=P.begin();it!=P.end();it++){cout<<" ; "<<*it;}cout<<endl;
	cout<<"Dans un texte de taille "<<n<<endl;
	cout<<"********************************************************************"<<endl<<endl;

/*
	cout<<"************ Recherche naive *************"<<endl;
	naif(P.front(),m,T,n);
	cout<<"##########################################"<<endl<<endl;

	cout<<"*********** Recherche avec MP ************"<<endl;
	MP(P.front(),m,T,n,calcule_MP_next(P,m));
	cout<<"##########################################"<<endl<<endl;

	cout<<"*********** Recherche avec KMP ***********"<<endl;
	MP(P.front(),m,T,n,calcule_KMP_next(P,m));
	cout<<"##########################################"<<endl<<endl;

	cout<<"******* Recherche avec Boyer-Moore *******"<<endl;
	BM(P.front(),m,T,n);
	cout<<"** Recherche avec Boyer-Moore (R forte) **"<<endl;
	BM(P.front(),m,T,n,true);
	cout<<"##########################################"<<endl<<endl;

	cout<<"********** Recherche avec TVSBS **********"<<endl;
	TVSBS(P.front(),m,T,n);
	cout<<"##########################################"<<endl;
*/

//	cout<<"****** Recherche naive multi-motifs ******"<<endl;
//	recherche_multi_naif(P,T);
	cout<<"********* Recherche multi-motifs *********"<<endl;
	recherche_multi(P,T);
	cout<<"##########################################"<<endl;
}}
